#include "atlas_asm.h"
/*
 * This file does a 2x2 unrolled mvt_sse with these params:
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
/*
 * SSE register assignment
 */
#define rA0     %xmm0
#define rX0     %xmm1
#define rY0     %xmm2
#define rY1     %xmm3

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
   shr $4, M            /* M = M / MU */
   shl $4, M            /* M = (M/MU)*MU */
   sub M, Mr            /* Mr = M - (M/MU)*MU */
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
   mov $-128, incAXm     /* code comp: use reg rather than constant */
   add lda, incAn               /* incAn = (2*lda-M)*sizeof */
   mov $8*2, incII      /* code comp: use reg rather than constant */
   mov M, II
   ALIGN32
   LOOPN:
      #ifdef BETA0
         xorpd rY0, rY0
         xorpd rY1, rY1
      #else
         movsd 0(pY), rY0
         movsd 8(pY), rY1
      #endif

      LOOPM:
         movapd 0-128(pX), rX0
         MOVA   0-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0
         prefA(PFADIST+0(pA0))

         MOVA   0-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1
         prefA(PFADIST+0(pA0,lda))

         movapd 64-128(pX), rX0
         MOVA   64-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0
         prefA(PFADIST+64(pA0))

         MOVA   64-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1
         prefA(PFADIST+64(pA0,lda))

         movapd 16-128(pX), rX0
         MOVA   16-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   16-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         movapd 32-128(pX), rX0
         MOVA   32-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   32-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         movapd 48-128(pX), rX0
         MOVA   48-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   48-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         movapd 80-128(pX), rX0
         MOVA   80-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   80-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         movapd 96-128(pX), rX0
         MOVA   96-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   96-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         movapd 112-128(pX), rX0
         MOVA   112-128(pA0), rA0
         mulpd rX0, rA0
         addpd rA0, rY0

         MOVA   112-128(pA0,lda), rA0
         mulpd rX0, rA0
         addpd rA0, rY1

         sub incAXm, pX
         sub incAXm, pA0
      sub incII, II
      jnz LOOPM

      #ifdef ATL_OS_OSX     /* workaround retarded OS X assembly */
         cmp $0, Mr
         jz  MCLEANED
      #else
         jecxz MCLEANED        /* skip cleanup loop if Mr == 0 */
      #endif

      mov Mr, II
      LOOPMCU:
         movsd -128(pX), rX0
         movsd -128(pA0), rA0
         mulsd rX0, rA0
         addsd rA0, rY0
         movsd -128(pA0,lda), rA0
         mulsd rX0, rA0
         addsd rA0, rY1
         add $8, pX
         add $8, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
      haddpd rY1, rY0
      movapd rY0, 0(pY)
      prefY(2*8+PFYDIST(pY))
      add $2*8, pY
      add incAn, pA0
      mov pX0, pX
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
