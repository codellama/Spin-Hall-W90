#include "atlas_asm.h"
/*
 * This file does a 4x6 unrolled mvt_sse with these params:
 *    CL=8, ORDER=clmajor
 */
#ifndef ATL_GAS_x8664
   #error "This kernel requires x86-64 assembly!"
#endif
/*
 * Integer register assignment
 */
#define M       %rdi
#define N       %rsi
#define pA0     %rdx
#define lda     %rax
#define pX      %r8
#define pY      %r9
#define II      %rbx
#define pX0     %r11
#define Mr      %rcx
#define incAXm  %r10
#define incII   %r15
#define incAn   %r14
#define lda3    %r12
#define lda5    %r13
/*
 * SSE register assignment
 */
#define rA0     %xmm0
#define rX0     %xmm1
#define rx0     %xmm2
#define rt0     %xmm3
#define rY0r    %xmm4
#define rY0i    %xmm5
#define rY1r    %xmm6
#define rY1i    %xmm7
#define rY2r    %xmm8
#define rY2i    %xmm9
#define rY3r    %xmm10
#define rY3i    %xmm11
#define rY4r    %xmm12
#define rY4i    %xmm13
#define rY5r    %xmm14
#define rY5i    %xmm15
#define NONEPONEOFF -72
#define NONEPONE rt0
/*
 * macros
 */
#ifndef MOVA
   #define MOVA movups
#endif
#define movapd movaps
#define movupd movups
#define xorpd xorps
#define addpd addps
#define mulpd mulps
#define addsd addss
#define mulsd mulss
#define movsd movss
#define haddpd haddps
/*
 * Define macros controlling prefetch
 */
#ifndef PFDIST
   #define PFDIST 256
#endif
#ifndef PFADIST
   #define PFADIST PFDIST
#endif
#ifndef PFYDIST
   #define PFYDIST 64
#endif
#ifndef PFXDIST
   #define PFXDIST 64
#endif
#ifndef PFIY
   #ifdef ATL_3DNow
      #define PFIY prefetchw
   #else
      #define PFIY prefetchnta
   #endif
#endif
#ifndef PFIX
   #define PFIX prefetcht0
#endif
#ifndef PFIA
   #define PFIA prefetchnta
#endif
#if PFADIST == 0                /* flag for no prefetch */
   #define prefA(mem)
#else
   #define prefA(mem) PFIA mem
#endif
#if PFYDIST == 0                /* flag for no prefetch */
   #define prefY(mem)
#else
   #define prefY(mem) PFIY mem
#endif
#if PFXDIST == 0                /* flag for no prefetch */
   #define prefX(mem)
#else
   #define prefX(mem) PFIX mem
#endif
/*
 *                      %rdi        %rsi           %rdx          %rcx
 * void ATL_UGEMV(ATL_CINT M, ATL_CINT N, const TYPE *A, ATL_CINT lda,
 *                          %r8      %r9
 *                const TYPE *X, TYPE *Y)
 */
.text
.text
.global ATL_asmdecor(ATL_UGEMV)
ALIGN64
ATL_asmdecor(ATL_UGEMV):

/*
 * Save callee-saved iregs
 */
   movq %rbp, -8(%rsp)
   movq %rbx, -16(%rsp)
   movq %r12, -24(%rsp)
   movq %r13, -32(%rsp)
   movq %r14, -40(%rsp)
   movq %r15, -48(%rsp)
/*
 * Compute M = (M/MU)*MU, Mr = M - (M/MU)*MU
 * NOTE: Mr is %rcx reg, so we can use jcx to go to cleanup loop
 */
   mov  %rcx, lda       /* move lda to assigned register, rax */
   mov  M, Mr           /* Mr = M */
   shr $5, M            /* M = M / MU */
   shl $5, M            /* M = (M/MU)*MU */
   sub M, Mr            /* Mr = M - (M/MU)*MU */
/*
 * Construct ponenone = {-1.0,1.0,-1.0,1.0}
 */
   finit
   fld1                                 /* ST =  1.0 */
   fldz                                 /* ST =  0.0 1.0 */
   fsub %st(1), %st                     /* ST = -1.0 1.0 */
   fsts NONEPONEOFF+4(%rsp)
   fstps NONEPONEOFF+12(%rsp)           /* ST = 1.0 */
   fsts NONEPONEOFF(%rsp)
   fstps NONEPONEOFF+8(%rsp)            /* ST=NULL, mem=-1,1,-1,1*/
/*
 * Setup constants
 */
   mov lda, incAn       /* incAn = lda */
   sub M, incAn         /* incAn = lda - (M/MU)*MU */
   sub Mr, incAn        /* incAn = lda - M */
   shl $3, incAn        /* incAn = (lda-M)*sizeof */
   shl $3, lda          /* lda *= sizeof */
   sub $-128, pA0       /* code compaction by using signed 1-byte offsets */
   sub $-128, pX        /* code compaction by using signed 1-byte offsets */
   mov pX, pX0          /* save for restore after M loops */
   mov $-256, incAXm     /* code comp: use reg rather than constant */
   lea (lda, lda,2), lda3       /* lda3 = 3*lda */
   lea (lda, lda,4), lda5       /* lda5 = 5*lda */
   add lda5, incAn              /* incAn = (6*lda-M)*sizeof */
   mov $8*4, incII      /* code comp: use reg rather than constant */
   mov M, II
   ALIGN32
   LOOPN:
      xorpd rY0r, rY0r
      xorpd rY0i, rY0i
      xorpd rY1r, rY1r
      xorpd rY1i, rY1i
      xorpd rY2r, rY2r
      xorpd rY2i, rY2i
      xorpd rY3r, rY3r
      xorpd rY3i, rY3i
      xorpd rY4r, rY4r
      xorpd rY4i, rY4i
      xorpd rY5r, rY5r
      xorpd rY5i, rY5i

      LOOPM:
         movapd 0-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   0-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         prefA(PFADIST+0(pA0))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   0-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         prefA(PFADIST+0(pA0,lda))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   0-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         prefA(PFADIST+0(pA0,lda,2))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   0-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         prefA(PFADIST+0(pA0,lda3))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   0-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         prefA(PFADIST+0(pA0,lda,4))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   0-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         prefA(PFADIST+0(pA0,lda5))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 64-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   64-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         prefA(PFADIST+64(pA0))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   64-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         prefA(PFADIST+64(pA0,lda))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   64-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         prefA(PFADIST+64(pA0,lda,2))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   64-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         prefA(PFADIST+64(pA0,lda3))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   64-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         prefA(PFADIST+64(pA0,lda,4))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   64-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         prefA(PFADIST+64(pA0,lda5))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 128-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   128-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         prefA(PFADIST+128(pA0))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   128-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         prefA(PFADIST+128(pA0,lda))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   128-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         prefA(PFADIST+128(pA0,lda,2))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   128-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         prefA(PFADIST+128(pA0,lda3))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   128-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         prefA(PFADIST+128(pA0,lda,4))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   128-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         prefA(PFADIST+128(pA0,lda5))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 192-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   192-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         prefA(PFADIST+192(pA0))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   192-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         prefA(PFADIST+192(pA0,lda))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   192-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         prefA(PFADIST+192(pA0,lda,2))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   192-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         prefA(PFADIST+192(pA0,lda3))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   192-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         prefA(PFADIST+192(pA0,lda,4))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   192-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         prefA(PFADIST+192(pA0,lda5))
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 16-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   16-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   16-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   16-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   16-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   16-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   16-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 32-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   32-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   32-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   32-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   32-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   32-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   32-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 48-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   48-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   48-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   48-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   48-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   48-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   48-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 80-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   80-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   80-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   80-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   80-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   80-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   80-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 96-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   96-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   96-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   96-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   96-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   96-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   96-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 112-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   112-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   112-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   112-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   112-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   112-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   112-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 144-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   144-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   144-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   144-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   144-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   144-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   144-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 160-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   160-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   160-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   160-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   160-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   160-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   160-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 176-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   176-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   176-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   176-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   176-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   176-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   176-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 208-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   208-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   208-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   208-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   208-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   208-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   208-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 224-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   224-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   224-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   224-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   224-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   224-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   224-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         movapd 240-128(pX), rX0              /* rX0 = Xi,    Xr */
         pshufd $0xB1, rX0, rx0                 /* rx0 = Xr,    Xi */
         MOVA   240-128(pA0), rA0             /* rA0 = Ai,    Ar */
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY0i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY0r

         MOVA   240-128(pA0,lda), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY1i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY1r
         MOVA   240-128(pA0,lda,2), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY2i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY2r
         MOVA   240-128(pA0,lda3), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY3i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY3r
         MOVA   240-128(pA0,lda,4), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY4i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY4r
         MOVA   240-128(pA0,lda5), rA0           /* rA0 = Ai,    Ar */ 
         movapd rA0, rt0                        /* rt0 = Ai,    Ar */
         mulpd rx0, rA0                         /* rA0 = Ai*Xr, Ar*Xi */
         addpd rA0, rY5i
         mulpd rX0, rt0                         /* rt0 = Ai*Xi, Ar*Xr */
         addpd rt0, rY5r

         sub incAXm, pX
         sub incAXm, pA0
      sub incII, II
      jnz LOOPM

      cmp $0, Mr
      jz  MCLEANED

      mov Mr, II
      xorps rA0, rA0
      xorps rX0, rX0
      xorps rx0, rx0
      LOOPMCU:
         movlps -128(pX), rX0           /* rX0 = {0, 0, Xi, Xr} */
         pshufd $0xB1, rX0, rx0     /* rx0 = {0, 0, Xr, Xi} */
         movlps -128(pA0), rA0          /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY0i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY0r
         movlps -128(pA0,lda), rA0        /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY1i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY1r
         movlps -128(pA0,lda,2), rA0        /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY2i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY2r
         movlps -128(pA0,lda3), rA0        /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY3i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY3r
         movlps -128(pA0,lda,4), rA0        /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY4i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY4r
         movlps -128(pA0,lda5), rA0        /* rA0 = {0, 0, Ai, Ar} */
         movaps rA0, rt0                /* rt0 = {0, 0, Ai, Ar} */
         mulps rx0, rA0                 /* rA0 = {0, 0, Xr*Ai, Xi*Ar} */
         addps rA0, rY5i
         mulps rX0, rt0                 /* rt0 = {0, 0, Xi*Ai, Xr*Ar} */
         addps rt0, rY5r
         add $8, pX
         add $8, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
                                /* rYr0 = {-rY0d, rY0c, -rY0b, rY0a} */
                                /* rYi0 = { iY0d, iY0c,  iY0b, iY0a} */
      movaps NONEPONEOFF(%rsp), NONEPONE
      mulps NONEPONE, rY0r   /* rYr = {rY0d,  rY0c,    rY0b,   rY0a} */
      mulps NONEPONE, rY1r   /* rYr = {rY1d,  rY1c,    rY1b,   rY1a} */
      haddps rY0i, rY0r   /* rYr = {iY0cd  ,iY0ab,  rY0cd,  rY0ab} */
      haddps rY1i, rY1r   /* rYr = {iY1cd  ,iY1ab,  rY1cd,  rY1ab} */
      haddps rY1r, rY0r   /* rYr = {iY1abcd,rY1abcd,iY0abcd,rY0abcd} */
      #ifndef BETA0
         addpd 0(pY), rY0r
      #endif
      movaps rY0r, 0(pY)
      mulps NONEPONE, rY2r   /* rYr = {rY0d,  rY0c,    rY0b,   rY0a} */
      mulps NONEPONE, rY3r   /* rYr = {rY1d,  rY1c,    rY1b,   rY1a} */
      haddps rY2i, rY2r   /* rYr = {iY0cd  ,iY0ab,  rY0cd,  rY0ab} */
      haddps rY3i, rY3r   /* rYr = {iY1cd  ,iY1ab,  rY1cd,  rY1ab} */
      haddps rY3r, rY2r   /* rYr = {iY1abcd,rY1abcd,iY0abcd,rY0abcd} */
      #ifndef BETA0
         addpd 16(pY), rY2r
      #endif
      movaps rY2r, 16(pY)
      mulps NONEPONE, rY4r   /* rYr = {rY0d,  rY0c,    rY0b,   rY0a} */
      mulps NONEPONE, rY5r   /* rYr = {rY1d,  rY1c,    rY1b,   rY1a} */
      haddps rY4i, rY4r   /* rYr = {iY0cd  ,iY0ab,  rY0cd,  rY0ab} */
      haddps rY5i, rY5r   /* rYr = {iY1cd  ,iY1ab,  rY1cd,  rY1ab} */
      haddps rY5r, rY4r   /* rYr = {iY1abcd,rY1abcd,iY0abcd,rY0abcd} */
      #ifndef BETA0
         addpd 32(pY), rY4r
      #endif
      movaps rY4r, 32(pY)
      prefY(6*8+PFYDIST(pY))
      add $6*8, pY
      add incAn, pA0
      mov pX0, pX
      mov M, II
   sub $6, N
   jnz LOOPN
/*
 * EPILOGUE: restore registers and return
 */
   movq -8(%rsp), %rbp
   movq -16(%rsp), %rbx
   movq -24(%rsp), %r12
   movq -32(%rsp), %r13
   movq -40(%rsp), %r14
   movq -48(%rsp), %r15
   ret
