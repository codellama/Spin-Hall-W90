#include "atlas_asm.h"
/*
 * This file does a 1x2 unrolled r2_sse with these params:
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
#define pA0     %r10
#define lda     %rax
#define pX      %rdx
#define pY      %rbp
#define pW      %r8
#define pZ      %r9
#define II      %rbx
#define M0      %r11
#define Mr      %rcx
#define incM    $-64
#define incII   %r15
#define incAn   %r14
/*
 * SSE register assignment
 */
#define rA0     %xmm0
#define ra0     %xmm1
#define rXr     %xmm2
#define rXi     %xmm3
#define rWr     %xmm4
#define rWi     %xmm5
#define rY0     %xmm6
#define rYh0    %xmm7
#define rZ0     %xmm8
#define rZh0    %xmm9
#define rY1     %xmm10
#define rYh1    %xmm11
#define rZ1     %xmm12
#define rZh1    %xmm13
#define rneg    %xmm15
#define NONEPONEOFF -72
/*
 * macros
 */
#ifndef MOVA
   #define MOVA movaps
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
   shl $3, M0           /* M0 *= sizeof */
   mov  M, Mr           /* Mr = M */
   shr $3, M            /* M = M / MU */
   shl $3, M            /* M = (M/MU)*MU */
   sub M, Mr            /* Mr = M - (M/MU)*MU */
/*
 * Construct nonepone = {1.0,-1.0,1.0,-1.0}
 */
   finit
   fld1                                 /* ST =  1.0 */
   fldz                                 /* ST =  0.0 1.0 */
   fsub %st(1), %st                     /* ST = -1.0 1.0 */
   fsts NONEPONEOFF(%rsp)               /* ST= -1.0 1.0 */
   fstps NONEPONEOFF+8(%rsp)            /* ST=1.0 */
   fsts NONEPONEOFF+4(%rsp)             /* ST=1.0 */
   fstps NONEPONEOFF+12(%rsp)          /* ST=NULL, mem={1.0, -1.0, 1.0, -1.0}*/
   movaps NONEPONEOFF(%rsp), rneg
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
   sub $-128, pW
   add lda, incAn               /* incAn = (2*lda-M)*sizeof */
   mov $8*1, incII      /* code comp: use reg rather than constant */
   mov M, II

   ALIGN32
   LOOPN:
      movlps 0*8(pY), rY0   /* rY0 = {xx,xx, Y0i, Y0r} */
      movlhps rY0, rY0      /* rY0 = {Y0i, Y0r, Y0i, Y0r} */
      pshufd $0x11, rY0, rYh0 /* rYh0 = {Y0r, Y0i, Y0r, Y0i} */
      mulps rneg, rYh0  /* rYh0 = {Y0r,-Y0i, Y0r,-Y0i} */
      movlps 0*8(pZ), rZ0   /* rZ0 = {xx,xx, Z0i, Z0r} */
      movlhps rZ0, rZ0      /* rZ0 = {Z0i, Z0r, Z0i, Z0r} */
      pshufd $0x11, rZ0, rZh0 /* rZh0 = {Z0r, Z0i, Z0r, Z0i} */
      mulps rneg, rZh0  /* rZh0 = {Z0r,-Z0i, Z0r,-Z0i} */
      movlps 1*8(pY), rY1   /* rY1 = {xx,xx, Y1i, Y1r} */
      movlhps rY1, rY1      /* rY1 = {Y1i, Y1r, Y1i, Y1r} */
      pshufd $0x11, rY1, rYh1 /* rYh1 = {Y1r, Y1i, Y1r, Y1i} */
      mulps rneg, rYh1  /* rYh1 = {Y1r,-Y1i, Y1r,-Y1i} */
      movlps 1*8(pZ), rZ1   /* rZ1 = {xx,xx, Z1i, Z1r} */
      movlhps rZ1, rZ1      /* rZ1 = {Z1i, Z1r, Z1i, Z1r} */
      pshufd $0x11, rZ1, rZh1 /* rZh1 = {Z1r, Z1i, Z1r, Z1i} */
      mulps rneg, rZh1  /* rZh1 = {Z1r,-Z1i, Z1r,-Z1i} */

      LOOPM:
         movsldup 0-128(pX), rXr /* rXr = { X1r, X1r, X0r, X0r} */
         movaps rY0, rA0   /* rA0 = {Y0i, Y0r,Y0i, Y0r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y0i,X1r*Y0r,X0r*Y0i,X0r*Y0r} */
         addps  0-128(pA0), rA0
         movshdup 0-128(pX), rXi /* rXi = {X1i, X1i, X0i, X0i} */
         movaps rYh0, ra0  /* ra0 = {Y0r,-Y0i,Y0r,-Y0i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movsldup 0-128(pW), rWr /* rWr = { W1r, W1r, W0r, W0r} */
         movaps rZ0, ra0   /* ra0 = {Z0i, Z0r,Z0i, Z0r} */
         mulps  rWr, ra0   /* ra0 = {W1r*Z0i,W1r*Z0r,W0r*Z0i,W0r*Z0r} */
         addps  ra0, rA0
         movshdup 0-128(pW), rWi /* rWi = {W1i, W1i, W0i, W0i} */
         movaps rZh0, ra0  /* ra0 = {Z0r,-Z0i,Z0r,-Z0i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 0-128(pA0)
         movaps rY1, rA0   /* rA0 = {Y1i, Y1r,Y1i, Y1r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y1i,X1r*Y1r,X0r*Y1i,X0r*Y1r} */
         addps  0-128(pA0,lda), rA0
         movaps rYh1, ra0  /* ra0 = {Y1r,-Y1i,Y1r,-Y1i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movaps rZ1, ra0   /* ra0 = {Z1i, Z1r,Z1i, Z1r} */
         mulps  rWr, ra0   /* rA0 = {W1r*Z1i,W1r*Z1r,W0r*Z1i,W0r*Y1r} */
         addps ra0, rA0
         movaps rZh1, ra0  /* ra0 = {Z1r,-Z1i,Z1r,-Z1i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 0-128(pA0,lda)

         movsldup 16-128(pX), rXr /* rXr = { X1r, X1r, X0r, X0r} */
         movaps rY0, rA0   /* rA0 = {Y0i, Y0r,Y0i, Y0r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y0i,X1r*Y0r,X0r*Y0i,X0r*Y0r} */
         addps  16-128(pA0), rA0
         movshdup 16-128(pX), rXi /* rXi = {X1i, X1i, X0i, X0i} */
         movaps rYh0, ra0  /* ra0 = {Y0r,-Y0i,Y0r,-Y0i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movsldup 16-128(pW), rWr /* rWr = { W1r, W1r, W0r, W0r} */
         movaps rZ0, ra0   /* ra0 = {Z0i, Z0r,Z0i, Z0r} */
         mulps  rWr, ra0   /* ra0 = {W1r*Z0i,W1r*Z0r,W0r*Z0i,W0r*Z0r} */
         addps  ra0, rA0
         movshdup 16-128(pW), rWi /* rWi = {W1i, W1i, W0i, W0i} */
         movaps rZh0, ra0  /* ra0 = {Z0r,-Z0i,Z0r,-Z0i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 16-128(pA0)
         movaps rY1, rA0   /* rA0 = {Y1i, Y1r,Y1i, Y1r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y1i,X1r*Y1r,X0r*Y1i,X0r*Y1r} */
         addps  16-128(pA0,lda), rA0
         movaps rYh1, ra0  /* ra0 = {Y1r,-Y1i,Y1r,-Y1i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movaps rZ1, ra0   /* ra0 = {Z1i, Z1r,Z1i, Z1r} */
         mulps  rWr, ra0   /* rA0 = {W1r*Z1i,W1r*Z1r,W0r*Z1i,W0r*Y1r} */
         addps ra0, rA0
         movaps rZh1, ra0  /* ra0 = {Z1r,-Z1i,Z1r,-Z1i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 16-128(pA0,lda)

         movsldup 32-128(pX), rXr /* rXr = { X1r, X1r, X0r, X0r} */
         movaps rY0, rA0   /* rA0 = {Y0i, Y0r,Y0i, Y0r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y0i,X1r*Y0r,X0r*Y0i,X0r*Y0r} */
         addps  32-128(pA0), rA0
         movshdup 32-128(pX), rXi /* rXi = {X1i, X1i, X0i, X0i} */
         movaps rYh0, ra0  /* ra0 = {Y0r,-Y0i,Y0r,-Y0i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movsldup 32-128(pW), rWr /* rWr = { W1r, W1r, W0r, W0r} */
         movaps rZ0, ra0   /* ra0 = {Z0i, Z0r,Z0i, Z0r} */
         mulps  rWr, ra0   /* ra0 = {W1r*Z0i,W1r*Z0r,W0r*Z0i,W0r*Z0r} */
         addps  ra0, rA0
         movshdup 32-128(pW), rWi /* rWi = {W1i, W1i, W0i, W0i} */
         movaps rZh0, ra0  /* ra0 = {Z0r,-Z0i,Z0r,-Z0i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 32-128(pA0)
         movaps rY1, rA0   /* rA0 = {Y1i, Y1r,Y1i, Y1r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y1i,X1r*Y1r,X0r*Y1i,X0r*Y1r} */
         addps  32-128(pA0,lda), rA0
         movaps rYh1, ra0  /* ra0 = {Y1r,-Y1i,Y1r,-Y1i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movaps rZ1, ra0   /* ra0 = {Z1i, Z1r,Z1i, Z1r} */
         mulps  rWr, ra0   /* rA0 = {W1r*Z1i,W1r*Z1r,W0r*Z1i,W0r*Y1r} */
         addps ra0, rA0
         movaps rZh1, ra0  /* ra0 = {Z1r,-Z1i,Z1r,-Z1i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 32-128(pA0,lda)

         movsldup 48-128(pX), rXr /* rXr = { X1r, X1r, X0r, X0r} */
         movaps rY0, rA0   /* rA0 = {Y0i, Y0r,Y0i, Y0r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y0i,X1r*Y0r,X0r*Y0i,X0r*Y0r} */
         addps  48-128(pA0), rA0
         movshdup 48-128(pX), rXi /* rXi = {X1i, X1i, X0i, X0i} */
         movaps rYh0, ra0  /* ra0 = {Y0r,-Y0i,Y0r,-Y0i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movsldup 48-128(pW), rWr /* rWr = { W1r, W1r, W0r, W0r} */
         movaps rZ0, ra0   /* ra0 = {Z0i, Z0r,Z0i, Z0r} */
         mulps  rWr, ra0   /* ra0 = {W1r*Z0i,W1r*Z0r,W0r*Z0i,W0r*Z0r} */
         addps  ra0, rA0
         movshdup 48-128(pW), rWi /* rWi = {W1i, W1i, W0i, W0i} */
         movaps rZh0, ra0  /* ra0 = {Z0r,-Z0i,Z0r,-Z0i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 48-128(pA0)
         movaps rY1, rA0   /* rA0 = {Y1i, Y1r,Y1i, Y1r} */
         mulps  rXr, rA0   /* rA0 = {X1r*Y1i,X1r*Y1r,X0r*Y1i,X0r*Y1r} */
         addps  48-128(pA0,lda), rA0
         movaps rYh1, ra0  /* ra0 = {Y1r,-Y1i,Y1r,-Y1i} */
         mulps  rXi, ra0   /* ra0 = {X1i*Y0r,-X1i*Y0i,X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movaps rZ1, ra0   /* ra0 = {Z1i, Z1r,Z1i, Z1r} */
         mulps  rWr, ra0   /* rA0 = {W1r*Z1i,W1r*Z1r,W0r*Z1i,W0r*Y1r} */
         addps ra0, rA0
         movaps rZh1, ra0  /* ra0 = {Z1r,-Z1i,Z1r,-Z1i} */
         mulps  rWi, ra0   /* ra0 = {W1i*Z0r,-W1i*Z0i,W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         MOVA   rA0, 48-128(pA0,lda)

         prefA(PFADIST+0(pA0))
         sub incM, pX
         prefA(PFADIST+0(pA0,lda))
         sub incM, pW
         sub incM, pA0
      sub incII, II
      jnz LOOPM

      cmp $0, Mr
      jz  MCLEANED

      mov Mr, II
      xorps rXr, rXr
      movaps rXr, rXi
      xorps ra0, ra0
      LOOPMCU:
         movlps -128(pX), rXi           /* rXr = {0, 0, X0i, X0r} */
         pshufd $0xE0, rXi, rXr         /* rXr = {0, 0, X0r, X0r} */
         movaps rY0, rA0                /* rA0 = {Y0i, Y0r, Y0i, Y0r} */
         mulps  rXr, rA0                /* rA0 = {0, 0, X0r*Y0i, X0r*Y0r} */
         movlps -128(pA0), ra0
         addps ra0, rA0
         shufps $0xE5, rXi, rXi         /* rXi = {0, 0, X0i, X0i} */
         movaps rYh0, ra0               /* ra0 = {Y0r, -Y0i, Y0r,-Y0i} */
         mulps  rXi, ra0                /* ra0 = {0, 0, X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0

         movlps -128(pW), rWi           /* rWr = {0, 0, W0i, W0r} */
         pshufd $0xE0, rWi, rWr         /* rWr = {0, 0, W0r, W0r} */
         movaps rZ0, ra0                /* ra0 = {Z0i, Z0r, Z0i, Z0r} */
         mulps  rWr, ra0                /* ra0 = {0, 0, W0r*Z0i, W0r*Z0r} */
         addps  ra0, rA0
         shufps $0xE5, rWi, rWi         /* rWi = {0, 0, W0i, W0i} */
         movaps rZh0, ra0               /* ra0 = {Z0r, -Z0i, Z0r,-Z0i} */
         mulps  rWi, ra0                /* ra0 = {0, 0, W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         movlps rA0, -128(pA0)
         movaps rY1, rA0                /* rA0 = {Y1i, Y1r, Y1i, Y1r} */
         mulps  rXr, rA0                /* rA0 = {0, 0, X0r*Y1i, X0r*Y1r} */
         movlps -128(pA0,lda), ra0
         addps ra0, rA0
         movaps rYh1, ra0               /* ra0 = {Y1r, -Y1i, Y1r,-Y1i} */
         mulps  rXi, ra0                /* ra0 = {0, 0, X0i*Y0r,-X0i*Y0i} */
         addps  ra0, rA0
         movaps rZ1, ra0                /* ra0 = {Z1i, Z1r, Z1i, Z1r} */
         mulps  rWr, ra0                /* ra0 = {0, 0, W0r*Z1i, W0r*Z1r} */
         addps  ra0, rA0
         movaps rZh1, ra0               /* ra0 = {Z1r, -Z1i, Z1r,-Z1i} */
         mulps  rWi, ra0                /* ra0 = {0, 0, W0i*Z0r,-W0i*Z0i} */
         addps  ra0, rA0
         movlps rA0, -128(pA0,lda)
         add $8, pX
         add $8, pW
         add $8, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
      prefY(2*8+PFYDIST(pY))
      add $2*8, pY
      sub M0, pX
      prefY(2*8+PFYDIST(pZ))
      add $2*8, pZ
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
