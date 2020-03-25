#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

static void ATL_zJIK0x0x15TN1x1x15_a1_bX
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=N, MB=0, NB=0, KB=15, 
 * lda=15, ldb=15, ldc=0, mu=1, nu=1, ku=15, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   #define Mb M
   #define Nb N
   const double *stM = A + (15*(Mb));
   const double *stN = B + (15*(Nb));
   const double *pfA = stM;
   const int incPFA0 = (((int)(stM - A))*1*1)/(M*N*sizeof(double));
   const int incPFA = (1 > incPFA0) ? 1 : incPFA0;
   #define incAk 15
   const int incAm = 0, incAn = -(15*(Mb));
   #define incBk 15
   const int incBm = -15, incBn = 15;
   const int incAk0 = ((incAk) / 15), incBk0 = ((incBk) / 15);
   #define incCm 2
   const int incCn = (((ldc) << 1)) - (((Mb) << 1));
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0;
   register double rB0;
   register double m0, m1, m2, m3, m4;
   register double rC0_0;
   do /* N-loop */
   {
      do /* M-loop */
      {
         ATL_pfl1R(pfA);
         pfA += incPFA;
         rA0 = beta;
         rC0_0 = *pC0;
         rC0_0 *= rA0;
/*
 *       Start pipeline
 */
         rA0 = *pA0;
         rB0 = *pB0;
         m0 = rA0 * rB0;
         rA0 = pA0[1];
         rB0 = pB0[1];
         m1 = rA0 * rB0;
         rA0 = pA0[2];
         rB0 = pB0[2];
         m2 = rA0 * rB0;
         rA0 = pA0[3];
         rB0 = pB0[3];
         m3 = rA0 * rB0;
         rA0 = pA0[4];
         rB0 = pB0[4];
         m4 = rA0 * rB0;
         rA0 = pA0[5];
         rB0 = pB0[5];

/*
 *       Completely unrolled K-loop
 */
         rC0_0 += m0;
         m0 = rA0 * rB0;
         rA0 = pA0[6];
         rB0 = pB0[6];
         rC0_0 += m1;
         m1 = rA0 * rB0;
         rA0 = pA0[7];
         rB0 = pB0[7];
         rC0_0 += m2;
         m2 = rA0 * rB0;
         rA0 = pA0[8];
         rB0 = pB0[8];
         rC0_0 += m3;
         m3 = rA0 * rB0;
         rA0 = pA0[9];
         rB0 = pB0[9];
         rC0_0 += m4;
         m4 = rA0 * rB0;
         rA0 = pA0[10];
         rB0 = pB0[10];
         rC0_0 += m0;
         m0 = rA0 * rB0;
         rA0 = pA0[11];
         rB0 = pB0[11];
         rC0_0 += m1;
         m1 = rA0 * rB0;
         rA0 = pA0[12];
         rB0 = pB0[12];
         rC0_0 += m2;
         m2 = rA0 * rB0;
         rA0 = pA0[13];
         rB0 = pB0[13];
         rC0_0 += m3;
         m3 = rA0 * rB0;
         rA0 = pA0[14];
         rB0 = pB0[14];
/*
 *       Drain pipe on last iteration of K-loop
 */
         rC0_0 += m4;
         m4 = rA0 * rB0;
         rC0_0 += m0;
         rC0_0 += m1;
         rC0_0 += m2;
         rC0_0 += m3;
         rC0_0 += m4;
         pA0 += incAk;
         pB0 += incBk;
         *pC0 = rC0_0;
         pC0 += incCm;
         pA0 += incAm;
         pB0 += incBm;
      }
      while(pA0 != stM);
      pC0 += incCn;
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
void ATL_zJIK0x0x15TN15x15x0_a1_bX
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=N, MB=0, NB=0, KB=15, 
 * lda=15, ldb=15, ldc=0, mu=10, nu=1, ku=15, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const int Mb = (M/10)*10;
   #define Nb N
   const double *ca=A, *cb=B;
   double *cc=C;
   const double *stM = A + (15*(Mb));
   const double *stN = B + (15*(Nb));
   const double *pfA = stM;
   const int incPFA0 = (((int)(stM - A))*10*1)/(M*N*sizeof(double));
   const int incPFA = (1 > incPFA0) ? 1 : incPFA0;
   #define incAk 15
   const int incAm = 135, incAn = -(15*(Mb));
   #define incBk 15
   const int incBm = -15, incBn = 15;
   const int incAk0 = ((incAk) / 15), incBk0 = ((incBk) / 15);
   #define incCm 20
   const int incCn = (((ldc) << 1)) - (((Mb) << 1));
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0, rA1, rA2, rA3, rA4, rA5, rA6, rA7, rA8, rA9;
   register double rB0;
   register double m0, m1, m2, m3, m4;
   register double rC0_0, rC1_0, rC2_0, rC3_0, rC4_0, rC5_0, rC6_0, rC7_0, rC8_0, rC9_0;
   if (pA0 != stM)
   {
      do /* N-loop */
      {
         do /* M-loop */
         {
            ATL_pfl1R(pfA);
            pfA += incPFA;
            rA0 = beta;
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
/*
 *          Start pipeline
 */
            rA0 = *pA0;
            rB0 = *pB0;
            m0 = rA0 * rB0;
            rA1 = pA0[15];
            rA2 = pA0[30];
            m1 = rA1 * rB0;
            rA3 = pA0[45];
            rA4 = pA0[60];
            m2 = rA2 * rB0;
            rA5 = pA0[75];
            rA6 = pA0[90];
            m3 = rA3 * rB0;
            rA7 = pA0[105];
            rA8 = pA0[120];
            m4 = rA4 * rB0;
            rA9 = pA0[135];

/*
 *          Completely unrolled K-loop
 */
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[1];
            rB0 = pB0[1];
            rA1 = pA0[16];
            rA2 = pA0[31];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[46];
            rA4 = pA0[61];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[76];
            rA6 = pA0[91];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[106];
            rA8 = pA0[121];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[136];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[2];
            rB0 = pB0[2];
            rA1 = pA0[17];
            rA2 = pA0[32];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[47];
            rA4 = pA0[62];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[77];
            rA6 = pA0[92];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[107];
            rA8 = pA0[122];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[137];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[3];
            rB0 = pB0[3];
            rA1 = pA0[18];
            rA2 = pA0[33];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[48];
            rA4 = pA0[63];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[78];
            rA6 = pA0[93];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[108];
            rA8 = pA0[123];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[138];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[4];
            rB0 = pB0[4];
            rA1 = pA0[19];
            rA2 = pA0[34];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[49];
            rA4 = pA0[64];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[79];
            rA6 = pA0[94];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[109];
            rA8 = pA0[124];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[139];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[5];
            rB0 = pB0[5];
            rA1 = pA0[20];
            rA2 = pA0[35];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[50];
            rA4 = pA0[65];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[80];
            rA6 = pA0[95];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[110];
            rA8 = pA0[125];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[140];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[6];
            rB0 = pB0[6];
            rA1 = pA0[21];
            rA2 = pA0[36];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[51];
            rA4 = pA0[66];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[81];
            rA6 = pA0[96];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[111];
            rA8 = pA0[126];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[141];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[7];
            rB0 = pB0[7];
            rA1 = pA0[22];
            rA2 = pA0[37];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[52];
            rA4 = pA0[67];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[82];
            rA6 = pA0[97];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[112];
            rA8 = pA0[127];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[142];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[8];
            rB0 = pB0[8];
            rA1 = pA0[23];
            rA2 = pA0[38];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[53];
            rA4 = pA0[68];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[83];
            rA6 = pA0[98];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[113];
            rA8 = pA0[128];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[143];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[9];
            rB0 = pB0[9];
            rA1 = pA0[24];
            rA2 = pA0[39];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[54];
            rA4 = pA0[69];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[84];
            rA6 = pA0[99];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[114];
            rA8 = pA0[129];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[144];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[10];
            rB0 = pB0[10];
            rA1 = pA0[25];
            rA2 = pA0[40];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[55];
            rA4 = pA0[70];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[85];
            rA6 = pA0[100];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[115];
            rA8 = pA0[130];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[145];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[11];
            rB0 = pB0[11];
            rA1 = pA0[26];
            rA2 = pA0[41];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[56];
            rA4 = pA0[71];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[86];
            rA6 = pA0[101];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[116];
            rA8 = pA0[131];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[146];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[12];
            rB0 = pB0[12];
            rA1 = pA0[27];
            rA2 = pA0[42];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[57];
            rA4 = pA0[72];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[87];
            rA6 = pA0[102];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[117];
            rA8 = pA0[132];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[147];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[13];
            rB0 = pB0[13];
            rA1 = pA0[28];
            rA2 = pA0[43];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[58];
            rA4 = pA0[73];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[88];
            rA6 = pA0[103];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[118];
            rA8 = pA0[133];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[148];
            rC9_0 += m4;
            m4 = rA4 * rB0;
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rA0 = pA0[14];
            rB0 = pB0[14];
            rA1 = pA0[29];
            rA2 = pA0[44];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA3 = pA0[59];
            rA4 = pA0[74];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA5 = pA0[89];
            rA6 = pA0[104];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA7 = pA0[119];
            rA8 = pA0[134];
            rC8_0 += m3;
            m3 = rA3 * rB0;
            rA9 = pA0[149];
            rC9_0 += m4;
            m4 = rA4 * rB0;
/*
 *          Drain pipe on last iteration of K-loop
 */
            rC0_0 += m0;
            m0 = rA5 * rB0;
            rC1_0 += m1;
            m1 = rA6 * rB0;
            rC2_0 += m2;
            m2 = rA7 * rB0;
            rC3_0 += m3;
            m3 = rA8 * rB0;
            rC4_0 += m4;
            m4 = rA9 * rB0;
            rC5_0 += m0;
            rC6_0 += m1;
            rC7_0 += m2;
            rC8_0 += m3;
            rC9_0 += m4;
            pA0 += incAk;
            pB0 += incBk;
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
            pB0 += incBm;
         }
         while(pA0 != stM);
         pC0 += incCn;
         pA0 += incAn;
         pB0 += incBn;
      }
      while(pB0 != stN);
   }
   if (k=M-Mb)
      ATL_zJIK0x0x15TN1x1x15_a1_bX(k, N, 15, alpha, ca + (15*(Mb)), lda, cb, ldb, beta, cc + (((Mb) << 1)), ldc);
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
