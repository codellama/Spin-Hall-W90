#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

void ATL_cJIK40x40x40NT0x0x0_a1_b1
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=40, NB=40, KB=40, 
 * lda=0, ldb=0, ldc=0, mu=2, nu=5, ku=40, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const float *stM = A + 80;
   const float *stN = B + 80;
   const float *pfA = A + lda*M;
   const int incAk = (((lda) << 1));
   const int incAm = 4 - (((lda) << 6)+((lda) << 4)), incAn = -80;
   const int incBk = (((ldb) << 1)), incBm = -(((ldb) << 6)+((ldb) << 4));
   #define incBn 10
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 4
   const int incCn = (((ldc) << 3)+((ldc) << 1)) - 80;
   float *pC0=C, *pC1=pC0+(((ldc) << 1)), *pC2=pC1+(((ldc) << 1)), *pC3=pC2+(((ldc) << 1)), *pC4=pC3+(((ldc) << 1));
   const float *pA0=A;
   const float *pB0=B;
   register int k;
   register float rA0, rA1;
   register float rB0, rB1, rB2, rB3, rB4;
   register float m0;
   register float rC0_0, rC1_0, rC0_1, rC1_1, rC0_2, rC1_2, rC0_3, rC1_3, rC0_4, rC1_4;
   do /* N-loop */
   {
      ATL_pfl1R(pfA+0);
      ATL_pfl1R(pfA+16);
      pfA += lda;
      do /* M-loop */
      {
         rC0_0 = *pC0;
         rC1_0 = pC0[2];
         rC0_1 = *pC1;
         rC1_1 = pC1[2];
         rC0_2 = *pC2;
         rC1_2 = pC2[2];
         rC0_3 = *pC3;
         rC1_3 = pC3[2];
         rC0_4 = *pC4;
         rC1_4 = pC4[2];
/*
 *       Start pipeline
 */
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         m0 = rA0 * rB0;
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];

/*
 *       Completely unrolled K-loop
 */
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rB4 = pB0[8];
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[2];
         rB1 = pB0[2];
         rB2 = pB0[4];
         rB3 = pB0[6];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         rB4 = pB0[8];
/*
 *       Drain pipe on last iteration of K-loop
 */
         rC0_0 += m0;
         m0 = rA1 * rB0;
         rC1_0 += m0;
         m0 = rA0 * rB1;
         rC0_1 += m0;
         m0 = rA1 * rB1;
         rC1_1 += m0;
         m0 = rA0 * rB2;
         rC0_2 += m0;
         m0 = rA1 * rB2;
         rC1_2 += m0;
         m0 = rA0 * rB3;
         rC0_3 += m0;
         m0 = rA1 * rB3;
         rC1_3 += m0;
         m0 = rA0 * rB4;
         rC0_4 += m0;
         m0 = rA1 * rB4;
         pA0 += incAk;
         pB0 += incBk;
         rC1_4 += m0;
         *pC0 = rC0_0;
         pC0[2] = rC1_0;
         *pC1 = rC0_1;
         pC1[2] = rC1_1;
         *pC2 = rC0_2;
         pC2[2] = rC1_2;
         *pC3 = rC0_3;
         pC3[2] = rC1_3;
         *pC4 = rC0_4;
         pC4[2] = rC1_4;
         pC0 += incCm;
         pC1 += incCm;
         pC2 += incCm;
         pC3 += incCm;
         pC4 += incCm;
         pA0 += incAm;
         pB0 += incBm;
      }
      while(pA0 != stM);
      pC0 += incCn;
      pC1 += incCn;
      pC2 += incCn;
      pC3 += incCn;
      pC4 += incCn;
      pA0 += incAn;
      pB0 += incBn;
   }
   while(pB0 != stN);
}
#ifdef incAm
   #undef incAm
#endif
#ifdef incAn
   #undef incAn
#endif
#ifdef incAk
   #undef incAk
#endif
#ifdef incBm
   #undef incBm
#endif
#ifdef incBn
   #undef incBn
#endif
#ifdef incBk
   #undef incBk
#endif
#ifdef incCm
   #undef incCm
#endif
#ifdef incCn
   #undef incCn
#endif
#ifdef incCk
   #undef incCk
#endif
#ifdef Mb
   #undef Mb
#endif
#ifdef Nb
   #undef Nb
#endif
#ifdef Kb
   #undef Kb
#endif
