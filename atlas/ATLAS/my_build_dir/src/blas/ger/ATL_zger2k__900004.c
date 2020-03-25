#include "atlas_asm.h"
/*
 * This file does a 2x2 unrolled r2_sse with these params:
 *    CL=4, ORDER=clmajor
 */
#ifndef ATL_GAS_x8664
   #error "This kernel requires x86-64 assembly!"
#endif
/*
 * Integer register assignment
 */
#define M       %rdi
#define N       %rsi
#define pA0     %r10
#define lda     %rax
#define pX      %rdx
#define pY      %rbp
#define pW      %r8
#define pZ      %r9
#define II      %rbx
#define M0      %r11
#define Mr      %rcx
#define incM    $-128
#define incII   %r15
#define incAn   %r14
/*
 * SSE register assignment
 */
#define rA0      %xmm0
#define rX0      %xmm1
#define rW0      %xmm2
#define rxt      %xmm3
#define ra0      %xmm4
#define rYr0     %xmm5
#define rYi0     %xmm6
#define rZr0     %xmm7
#define rZi0     %xmm8
#define rYr1     %xmm9
#define rYi1     %xmm10
#define rZr1     %xmm11
#define rZi1     %xmm12
#define rponenone %xmm15
#define PONENONEOFF -72
/*
 * macros
 */
#ifndef MOVA
   #define MOVA movups
#endif
#define movapd movaps
#define movupd movups
#define xorpd xorps
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
   #define PFIY prefetchnta
#endif
#ifndef PFIA
   #ifdef ATL_3DNow
      #define PFIA prefetchw
   #else
      #define PFIA prefetcht0
   #endif
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
 *                       %rdi        %rsi           %rdx          %rcx
 * void ATL_UGER2K(ATL_CINT M, ATL_CINT N, const TYPE *X, const TYPE *Y,
 *                     %r8                  %r9  8(%rsp)       16(%rsp)
 *                 const TYPE *W, const TYPE *Z, TYPE *A, ATL_CINT lda)
 */
.text
.text
.global ATL_asmdecor(ATL_UGER2K)
ALIGN64
ATL_asmdecor(ATL_UGER2K):

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
   movq   8(%rsp), pA0   /* load A ptr */
   movslq 16(%rsp), lda /* move lda to assigned register, rax */
   mov %rcx, pY         /* move pY to assigned register, rbp */
   mov M, M0            /* save full M for W/X restoration */
   shl $4, M0           /* M0 *= sizeof */
   mov  M, Mr           /* Mr = M */
   shr $3, M            /* M = M / MU */
   shl $3, M            /* M = (M/MU)*MU */
   sub M, Mr            /* Mr = M - (M/MU)*MU */
/*
 * Construct ponenone = {-1.0,1.0}
 */
   finit
   fld1                                 /* ST =  1.0 */
   fldz                                 /* ST =  0.0 1.0 */
   fsub %st(1), %st                     /* ST = -1.0 1.0 */
   fstpl PONENONEOFF(%rsp)              /* ST = 1.0, mem=-1.0 */
   fstpl PONENONEOFF+8(%rsp)            /* mem= +1.0, -1.0 */
   movapd PONENONEOFF(%rsp), rponenone
/*
 * Setup constants
 */
   mov lda, incAn       /* incAn = lda */
   sub M, incAn         /* incAn = lda - (M/MU)*MU */
   sub Mr, incAn        /* incAn = lda - M */
   shl $4, incAn        /* incAn = (lda-M)*sizeof */
   shl $4, lda          /* lda *= sizeof */
   sub $-128, pA0       /* code compaction by using signed 1-byte offsets */
   sub $-128, pX        /* code compaction by using signed 1-byte offsets */
   sub $-128, pW
   add lda, incAn               /* incAn = (2*lda-M)*sizeof */
   mov $4*2, incII      /* code comp: use reg rather than constant */
   mov M, II

   ALIGN32
   LOOPN:
      movapd 0*16(pY), rYr0  /* rYr0 = {Yi,  Yr} */
      pshufd $0xEE, rYr0, rYi0  /* rYi0 = {Yi,  Yi} */
      mulpd  rponenone, rYi0    /* rYi0 = {Yi, -Yi} */
      unpcklpd rYr0, rYr0    /* rYr0 = {Yr, Yr} */
      movapd 0*16(pZ), rZr0  /* rZr0 = {Zi,  Zr} */
      pshufd $0xEE, rZr0, rZi0  /* rZi0 = {Zi,  Zi} */
      mulpd  rponenone, rZi0    /* rZi0 = {Zi, -Zi} */
      unpcklpd rZr0, rZr0    /* rZr0 = {Zr, Zr} */
      movapd 1*16(pY), rYr1  /* rYr1 = {Yi,  Yr} */
      pshufd $0xEE, rYr1, rYi1  /* rYi1 = {Yi,  Yi} */
      mulpd  rponenone, rYi1    /* rYi1 = {Yi, -Yi} */
      unpcklpd rYr1, rYr1    /* rYr1 = {Yr, Yr} */
      movapd 1*16(pZ), rZr1  /* rZr1 = {Zi,  Zr} */
      pshufd $0xEE, rZr1, rZi1  /* rZi1 = {Zi,  Zi} */
      mulpd  rponenone, rZi1    /* rZi1 = {Zi, -Zi} */
      unpcklpd rZr1, rZr1    /* rZr1 = {Zr, Zr} */

      LOOPM:
         movapd 0-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    0-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 0-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 0-128(pA0)
         prefA(PFADIST+0(pA0))
         prefA(PFADIST+0(pA0,lda))
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    0-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 0-128(pA0,lda)

         movapd 64-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    64-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 64-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 64-128(pA0)
         prefA(PFADIST+64(pA0))
         prefA(PFADIST+64(pA0,lda))
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    64-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 64-128(pA0,lda)

         movapd 16-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    16-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 16-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 16-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    16-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 16-128(pA0,lda)

         movapd 32-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    32-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 32-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 32-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    32-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 32-128(pA0,lda)

         movapd 48-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    48-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 48-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 48-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    48-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 48-128(pA0,lda)

         movapd 80-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    80-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 80-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 80-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    80-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 80-128(pA0,lda)

         movapd 96-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    96-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 96-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 96-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    96-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 96-128(pA0,lda)

         movapd 112-128(pX), rX0      /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    112-128(pA0), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd 112-128(pW), rW0      /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 112-128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    112-128(pA0,lda), ra0    /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, 112-128(pA0,lda)

         sub incM, pX
         sub incM, pW
         sub incM, pA0
      sub incII, II
      jnz LOOPM

      cmp $0, Mr
      jz  MCLEANED

      mov Mr, II
      LOOPMCU:
         movapd -128(pX), rX0           /* rX0 = {Xi, Xr} */
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr0, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    -128(pA0), ra0         /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi0, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd -128(pW), rW0           /* rW0 = {Wi, Wr} */
         movapd rZr0, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi0, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, -128(pA0)
         pshufd $0x4E, rX0, rxt         /* rxt = {Xr, Xi} */
         movapd rYr1, rA0               /* rA0 = {Yr, Yr} */
         mulpd  rX0, rA0                /* rA0 = {Xi*Yr, Xr*Yr} */
         MOVA    -128(pA0,lda), ra0       /* ra0 = present A */
         addpd   ra0, rA0               /* rA0 += present A */
         mulpd  rYi1, rxt               /* rxt = {Xr*Yi, -xi*Yi} */
         addpd  rxt, rA0                /* rA0 = {Xi*Yr+Xr*Yi, Xr*Yr-Xi*Yi} */
         movapd rZr1, ra0               /* ra0 = {Zr, Zr} */
         mulpd  rW0, ra0                /* ra0 = {Wi*Zr, Wr*Zr} */
         addpd  ra0, rA0
         pshufd $0x4E, rW0, ra0         /* ra0 = {Wr, Wi} */
         mulpd  rZi1, ra0               /* ra0 = {Wr*Zi, -Wi*Zi} */
         addpd  ra0, rA0
         MOVA rA0, -128(pA0,lda)
         add $16, pX
         add $16, pW
         add $16, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
      prefY(2*16+PFYDIST(pY))
      add $2*16, pY
      sub M0, pX
      prefY(2*16+PFYDIST(pZ))
      add $2*16, pZ
      add incAn, pA0
      sub M0, pW
      mov M, II
   sub $2, N
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
