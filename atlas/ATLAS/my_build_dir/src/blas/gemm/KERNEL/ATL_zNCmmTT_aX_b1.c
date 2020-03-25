#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

void ATL_zJIK40x40x40TT0x0x0_aX_b1
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=T, MB=40, NB=40, KB=40, 
 * lda=0, ldb=0, ldc=0, mu=10, nu=1, ku=40, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const double *stM = A + (((lda) << 6)+((lda) << 4));
   const double *stN = B + 80;
   const double *pfA = A + M;
   const double BetaAlpha = beta / alpha;
   #define incAk 80
   const int incAm = ((((((lda) << 3)+((lda) << 1)) - 40) << 1)), incAn = -(((lda) << 6)+((lda) << 4));
   const int incBk = (((ldb) << 1)), incBm = -(((ldb) << 6)+((ldb) << 4));
   #define incBn 2
   #define incCm 20
   const int incCn = (((ldc) << 1)) - 80;
   double *pC0=C;
   const double *pA0=A, *pA1=pA0+(((lda) << 1)), *pA2=pA1+(((lda) << 1)), *pA3=pA2+(((lda) << 1)), *pA4=pA3+(((lda) << 1)), *pA5=pA4+(((lda) << 1)), *pA6=pA5+(((lda) << 1)), *pA7=pA6+(((lda) << 1)), *pA8=pA7+(((lda) << 1)), *pA9=pA8+(((lda) << 1));
   const double *pB0=B;
   register int k;
   register double rA0, rA1, rA2, rA3, rA4, rA5, rA6, rA7, rA8, rA9;
   register double rB0;
   register double rC0_0, rC1_0, rC2_0, rC3_0, rC4_0, rC5_0, rC6_0, rC7_0, rC8_0, rC9_0;
   do /* N-loop */
   {
      ATL_pfl1R(pfA+0);
      ATL_pfl1R(pfA+8);
      ATL_pfl1R(pfA+16);
      ATL_pfl1R(pfA+24);
      ATL_pfl1R(pfA+32);
      pfA += lda;
      do /* M-loop */
      {
         rA0 = BetaAlpha;
         rC0_0 = *pC0;
         rC0_0 *= rA0;
         rC1_0 = pC0[2];
         rC1_0 *= rA0;
         rC2_0 = pC0[4];
         rC2_0 *= rA0;
         rC3_0 = pC0[6];
         rC3_0 *= rA0;
         rC4_0 = pC0[8];
         rC4_0 *= rA0;
         rC5_0 = pC0[10];
         rC5_0 *= rA0;
         rC6_0 = pC0[12];
         rC6_0 *= rA0;
         rC7_0 = pC0[14];
         rC7_0 *= rA0;
         rC8_0 = pC0[16];
         rC8_0 *= rA0;
         rC9_0 = pC0[18];
         rC9_0 *= rA0;
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = *pA1;
         rA2 = *pA2;
         rA3 = *pA3;
         rC0_0 += rA0 * rB0;
         rA4 = *pA4;
         rA5 = *pA5;
         rC1_0 += rA1 * rB0;
         rA6 = *pA6;
         rA7 = *pA7;
         rC2_0 += rA2 * rB0;
         rA8 = *pA8;
         rA9 = *pA9;
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[2];
         rB0 = *pB0;
         rA1 = pA1[2];
         rA2 = pA2[2];
         rA3 = pA3[2];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[2];
         rA5 = pA5[2];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[2];
         rA7 = pA7[2];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[2];
         rA9 = pA9[2];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[4];
         rB0 = *pB0;
         rA1 = pA1[4];
         rA2 = pA2[4];
         rA3 = pA3[4];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[4];
         rA5 = pA5[4];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[4];
         rA7 = pA7[4];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[4];
         rA9 = pA9[4];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[6];
         rB0 = *pB0;
         rA1 = pA1[6];
         rA2 = pA2[6];
         rA3 = pA3[6];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[6];
         rA5 = pA5[6];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[6];
         rA7 = pA7[6];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[6];
         rA9 = pA9[6];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[8];
         rB0 = *pB0;
         rA1 = pA1[8];
         rA2 = pA2[8];
         rA3 = pA3[8];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[8];
         rA5 = pA5[8];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[8];
         rA7 = pA7[8];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[8];
         rA9 = pA9[8];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[10];
         rB0 = *pB0;
         rA1 = pA1[10];
         rA2 = pA2[10];
         rA3 = pA3[10];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[10];
         rA5 = pA5[10];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[10];
         rA7 = pA7[10];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[10];
         rA9 = pA9[10];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[12];
         rB0 = *pB0;
         rA1 = pA1[12];
         rA2 = pA2[12];
         rA3 = pA3[12];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[12];
         rA5 = pA5[12];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[12];
         rA7 = pA7[12];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[12];
         rA9 = pA9[12];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[14];
         rB0 = *pB0;
         rA1 = pA1[14];
         rA2 = pA2[14];
         rA3 = pA3[14];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[14];
         rA5 = pA5[14];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[14];
         rA7 = pA7[14];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[14];
         rA9 = pA9[14];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[16];
         rB0 = *pB0;
         rA1 = pA1[16];
         rA2 = pA2[16];
         rA3 = pA3[16];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[16];
         rA5 = pA5[16];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[16];
         rA7 = pA7[16];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[16];
         rA9 = pA9[16];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[18];
         rB0 = *pB0;
         rA1 = pA1[18];
         rA2 = pA2[18];
         rA3 = pA3[18];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[18];
         rA5 = pA5[18];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[18];
         rA7 = pA7[18];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[18];
         rA9 = pA9[18];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[20];
         rB0 = *pB0;
         rA1 = pA1[20];
         rA2 = pA2[20];
         rA3 = pA3[20];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[20];
         rA5 = pA5[20];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[20];
         rA7 = pA7[20];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[20];
         rA9 = pA9[20];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[22];
         rB0 = *pB0;
         rA1 = pA1[22];
         rA2 = pA2[22];
         rA3 = pA3[22];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[22];
         rA5 = pA5[22];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[22];
         rA7 = pA7[22];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[22];
         rA9 = pA9[22];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[24];
         rB0 = *pB0;
         rA1 = pA1[24];
         rA2 = pA2[24];
         rA3 = pA3[24];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[24];
         rA5 = pA5[24];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[24];
         rA7 = pA7[24];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[24];
         rA9 = pA9[24];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[26];
         rB0 = *pB0;
         rA1 = pA1[26];
         rA2 = pA2[26];
         rA3 = pA3[26];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[26];
         rA5 = pA5[26];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[26];
         rA7 = pA7[26];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[26];
         rA9 = pA9[26];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[28];
         rB0 = *pB0;
         rA1 = pA1[28];
         rA2 = pA2[28];
         rA3 = pA3[28];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[28];
         rA5 = pA5[28];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[28];
         rA7 = pA7[28];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[28];
         rA9 = pA9[28];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[30];
         rB0 = *pB0;
         rA1 = pA1[30];
         rA2 = pA2[30];
         rA3 = pA3[30];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[30];
         rA5 = pA5[30];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[30];
         rA7 = pA7[30];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[30];
         rA9 = pA9[30];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[32];
         rB0 = *pB0;
         rA1 = pA1[32];
         rA2 = pA2[32];
         rA3 = pA3[32];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[32];
         rA5 = pA5[32];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[32];
         rA7 = pA7[32];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[32];
         rA9 = pA9[32];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[34];
         rB0 = *pB0;
         rA1 = pA1[34];
         rA2 = pA2[34];
         rA3 = pA3[34];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[34];
         rA5 = pA5[34];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[34];
         rA7 = pA7[34];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[34];
         rA9 = pA9[34];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[36];
         rB0 = *pB0;
         rA1 = pA1[36];
         rA2 = pA2[36];
         rA3 = pA3[36];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[36];
         rA5 = pA5[36];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[36];
         rA7 = pA7[36];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[36];
         rA9 = pA9[36];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[38];
         rB0 = *pB0;
         rA1 = pA1[38];
         rA2 = pA2[38];
         rA3 = pA3[38];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[38];
         rA5 = pA5[38];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[38];
         rA7 = pA7[38];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[38];
         rA9 = pA9[38];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[40];
         rB0 = *pB0;
         rA1 = pA1[40];
         rA2 = pA2[40];
         rA3 = pA3[40];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[40];
         rA5 = pA5[40];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[40];
         rA7 = pA7[40];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[40];
         rA9 = pA9[40];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[42];
         rB0 = *pB0;
         rA1 = pA1[42];
         rA2 = pA2[42];
         rA3 = pA3[42];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[42];
         rA5 = pA5[42];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[42];
         rA7 = pA7[42];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[42];
         rA9 = pA9[42];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[44];
         rB0 = *pB0;
         rA1 = pA1[44];
         rA2 = pA2[44];
         rA3 = pA3[44];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[44];
         rA5 = pA5[44];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[44];
         rA7 = pA7[44];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[44];
         rA9 = pA9[44];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[46];
         rB0 = *pB0;
         rA1 = pA1[46];
         rA2 = pA2[46];
         rA3 = pA3[46];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[46];
         rA5 = pA5[46];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[46];
         rA7 = pA7[46];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[46];
         rA9 = pA9[46];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[48];
         rB0 = *pB0;
         rA1 = pA1[48];
         rA2 = pA2[48];
         rA3 = pA3[48];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[48];
         rA5 = pA5[48];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[48];
         rA7 = pA7[48];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[48];
         rA9 = pA9[48];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[50];
         rB0 = *pB0;
         rA1 = pA1[50];
         rA2 = pA2[50];
         rA3 = pA3[50];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[50];
         rA5 = pA5[50];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[50];
         rA7 = pA7[50];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[50];
         rA9 = pA9[50];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[52];
         rB0 = *pB0;
         rA1 = pA1[52];
         rA2 = pA2[52];
         rA3 = pA3[52];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[52];
         rA5 = pA5[52];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[52];
         rA7 = pA7[52];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[52];
         rA9 = pA9[52];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[54];
         rB0 = *pB0;
         rA1 = pA1[54];
         rA2 = pA2[54];
         rA3 = pA3[54];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[54];
         rA5 = pA5[54];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[54];
         rA7 = pA7[54];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[54];
         rA9 = pA9[54];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[56];
         rB0 = *pB0;
         rA1 = pA1[56];
         rA2 = pA2[56];
         rA3 = pA3[56];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[56];
         rA5 = pA5[56];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[56];
         rA7 = pA7[56];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[56];
         rA9 = pA9[56];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[58];
         rB0 = *pB0;
         rA1 = pA1[58];
         rA2 = pA2[58];
         rA3 = pA3[58];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[58];
         rA5 = pA5[58];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[58];
         rA7 = pA7[58];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[58];
         rA9 = pA9[58];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[60];
         rB0 = *pB0;
         rA1 = pA1[60];
         rA2 = pA2[60];
         rA3 = pA3[60];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[60];
         rA5 = pA5[60];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[60];
         rA7 = pA7[60];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[60];
         rA9 = pA9[60];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[62];
         rB0 = *pB0;
         rA1 = pA1[62];
         rA2 = pA2[62];
         rA3 = pA3[62];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[62];
         rA5 = pA5[62];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[62];
         rA7 = pA7[62];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[62];
         rA9 = pA9[62];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[64];
         rB0 = *pB0;
         rA1 = pA1[64];
         rA2 = pA2[64];
         rA3 = pA3[64];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[64];
         rA5 = pA5[64];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[64];
         rA7 = pA7[64];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[64];
         rA9 = pA9[64];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[66];
         rB0 = *pB0;
         rA1 = pA1[66];
         rA2 = pA2[66];
         rA3 = pA3[66];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[66];
         rA5 = pA5[66];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[66];
         rA7 = pA7[66];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[66];
         rA9 = pA9[66];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[68];
         rB0 = *pB0;
         rA1 = pA1[68];
         rA2 = pA2[68];
         rA3 = pA3[68];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[68];
         rA5 = pA5[68];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[68];
         rA7 = pA7[68];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[68];
         rA9 = pA9[68];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[70];
         rB0 = *pB0;
         rA1 = pA1[70];
         rA2 = pA2[70];
         rA3 = pA3[70];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[70];
         rA5 = pA5[70];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[70];
         rA7 = pA7[70];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[70];
         rA9 = pA9[70];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[72];
         rB0 = *pB0;
         rA1 = pA1[72];
         rA2 = pA2[72];
         rA3 = pA3[72];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[72];
         rA5 = pA5[72];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[72];
         rA7 = pA7[72];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[72];
         rA9 = pA9[72];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[74];
         rB0 = *pB0;
         rA1 = pA1[74];
         rA2 = pA2[74];
         rA3 = pA3[74];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[74];
         rA5 = pA5[74];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[74];
         rA7 = pA7[74];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[74];
         rA9 = pA9[74];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[76];
         rB0 = *pB0;
         rA1 = pA1[76];
         rA2 = pA2[76];
         rA3 = pA3[76];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[76];
         rA5 = pA5[76];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[76];
         rA7 = pA7[76];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[76];
         rA9 = pA9[76];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         rA0 = pA0[78];
         rB0 = *pB0;
         rA1 = pA1[78];
         rA2 = pA2[78];
         rA3 = pA3[78];
         rC0_0 += rA0 * rB0;
         rA4 = pA4[78];
         rA5 = pA5[78];
         rC1_0 += rA1 * rB0;
         rA6 = pA6[78];
         rA7 = pA7[78];
         rC2_0 += rA2 * rB0;
         rA8 = pA8[78];
         rA9 = pA9[78];
         rC3_0 += rA3 * rB0;
         rC4_0 += rA4 * rB0;
         rC5_0 += rA5 * rB0;
         rC6_0 += rA6 * rB0;
         rC7_0 += rA7 * rB0;
         rC8_0 += rA8 * rB0;
         rC9_0 += rA9 * rB0;
         pB0 += incBk;
         pA0 += incAk;
         pA1 += incAk;
         pA2 += incAk;
         pA3 += incAk;
         pA4 += incAk;
         pA5 += incAk;
         pA6 += incAk;
         pA7 += incAk;
         pA8 += incAk;
         pA9 += incAk;
         rB0 = alpha;
         rC0_0 *= rB0;
         rC1_0 *= rB0;
         rC2_0 *= rB0;
         rC3_0 *= rB0;
         rC4_0 *= rB0;
         rC5_0 *= rB0;
         rC6_0 *= rB0;
         rC7_0 *= rB0;
         rC8_0 *= rB0;
         rC9_0 *= rB0;
         *pC0 = rC0_0;
         pC0[2] = rC1_0;
         pC0[4] = rC2_0;
         pC0[6] = rC3_0;
         pC0[8] = rC4_0;
         pC0[10] = rC5_0;
         pC0[12] = rC6_0;
         pC0[14] = rC7_0;
         pC0[16] = rC8_0;
         pC0[18] = rC9_0;
         pC0 += incCm;
         pA0 += incAm;
         pA1 += incAm;
         pA2 += incAm;
         pA3 += incAm;
         pA4 += incAm;
         pA5 += incAm;
         pA6 += incAm;
         pA7 += incAm;
         pA8 += incAm;
         pA9 += incAm;
         pB0 += incBm;
      }
      while(pA0 != stM);
      pC0 += incCn;
      pA0 += incAn;
      pA1 += incAn;
      pA2 += incAn;
      pA3 += incAn;
      pA4 += incAn;
      pA5 += incAn;
      pA6 += incAn;
      pA7 += incAn;
      pA8 += incAn;
      pA9 += incAn;
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
