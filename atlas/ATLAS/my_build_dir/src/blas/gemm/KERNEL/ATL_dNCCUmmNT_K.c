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

static void ATL_dJIK0x0x40NT1x1x4_aX_bX
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=40, 
 * lda=0, ldb=0, ldc=0, mu=1, nu=1, ku=4, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   #define Mb M
   #define Nb N
   const double *stM = A + (Mb);
   const double *stN = B + (Nb);
   const double *pfA = A + lda*M;
   const double BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 1 - (((lda) << 5)+((lda) << 3)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 5)+((ldb) << 3));
   #define incBn 1
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 1
   const int incCn = (ldc) - (Mb);
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0;
   register double rB0;
   register double m0, m1, m2, m3;
   register double rC0_0;
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
/*
 *       Start pipeline
 */
         rA0 = *pA0;
         rB0 = *pB0;
         m0 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rA0 = *pA0;
         rB0 = *pB0;
         m1 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rA0 = *pA0;
         rB0 = *pB0;
         m2 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rA0 = *pA0;
         rB0 = *pB0;
         m3 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rA0 = *pA0;
         rB0 = *pB0;

         for (k=0; k < 32; k += 4) /* easy loop to unroll */
         {
            rC0_0 += m0;
            m0 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m1;
            m1 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m2;
            m2 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m3;
            m3 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
         } /* end K-loop */
         rC0_0 += m0;
         m0 = rA0 * rB0;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rC0_0 += m1;
         m1 = rA0 * rB0;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
         rC0_0 += m2;
         m2 = rA0 * rB0;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
/*
 *       Drain pipe on last iteration of K-loop
 */
         rC0_0 += m3;
         m3 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rC0_0 += m0;
         rC0_0 += m1;
         rC0_0 += m2;
         rC0_0 += m3;
         rB0 = alpha;
         rC0_0 *= rB0;
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
void ATL_dJIK0x0x40NT0x0x0_aX_bX
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=40, 
 * lda=0, ldb=0, ldc=0, mu=10, nu=1, ku=4, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const int Mb = (M/10)*10;
   #define Nb N
   const double *ca=A, *cb=B;
   double *cc=C;
   const double *stM = A + (Mb);
   const double *stN = B + (Nb);
   const double *pfA = A + lda*M;
   const double BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 10 - (((lda) << 5)+((lda) << 3)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 5)+((ldb) << 3));
   #define incBn 1
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 10
   const int incCn = (ldc) - (Mb);
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
            rC1_0 = pC0[1];
            rC1_0 *= rA0;
            rC2_0 = pC0[2];
            rC2_0 *= rA0;
            rC3_0 = pC0[3];
            rC3_0 *= rA0;
            rC4_0 = pC0[4];
            rC4_0 *= rA0;
            rC5_0 = pC0[5];
            rC5_0 *= rA0;
            rC6_0 = pC0[6];
            rC6_0 *= rA0;
            rC7_0 = pC0[7];
            rC7_0 *= rA0;
            rC8_0 = pC0[8];
            rC8_0 *= rA0;
            rC9_0 = pC0[9];
            rC9_0 *= rA0;
/*
 *          Start pipeline
 */
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rA3 = pA0[3];
            rA4 = pA0[4];
            rA5 = pA0[5];
            m0 = rA0 * rB0;
            rA6 = pA0[6];
            m1 = rA1 * rB0;
            rA7 = pA0[7];
            m2 = rA2 * rB0;
            rA8 = pA0[8];
            m3 = rA3 * rB0;
            rA9 = pA0[9];
            m4 = rA4 * rB0;

            for (k=0; k < 36; k += 4) /* easy loop to unroll */
            {
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rA2 = pA0[2];
               rA3 = pA0[3];
               rA4 = pA0[4];
               rA5 = pA0[5];
               rA6 = pA0[6];
               rC5_0 += m0;
               m0 = rA0 * rB0;
               rA7 = pA0[7];
               rC6_0 += m1;
               m1 = rA1 * rB0;
               rA8 = pA0[8];
               rC7_0 += m2;
               m2 = rA2 * rB0;
               rA9 = pA0[9];
               rC8_0 += m3;
               m3 = rA3 * rB0;
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rA2 = pA0[2];
               rA3 = pA0[3];
               rA4 = pA0[4];
               rA5 = pA0[5];
               rA6 = pA0[6];
               rC5_0 += m0;
               m0 = rA0 * rB0;
               rA7 = pA0[7];
               rC6_0 += m1;
               m1 = rA1 * rB0;
               rA8 = pA0[8];
               rC7_0 += m2;
               m2 = rA2 * rB0;
               rA9 = pA0[9];
               rC8_0 += m3;
               m3 = rA3 * rB0;
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rA2 = pA0[2];
               rA3 = pA0[3];
               rA4 = pA0[4];
               rA5 = pA0[5];
               rA6 = pA0[6];
               rC5_0 += m0;
               m0 = rA0 * rB0;
               rA7 = pA0[7];
               rC6_0 += m1;
               m1 = rA1 * rB0;
               rA8 = pA0[8];
               rC7_0 += m2;
               m2 = rA2 * rB0;
               rA9 = pA0[9];
               rC8_0 += m3;
               m3 = rA3 * rB0;
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rA2 = pA0[2];
               rA3 = pA0[3];
               rA4 = pA0[4];
               rA5 = pA0[5];
               rA6 = pA0[6];
               rC5_0 += m0;
               m0 = rA0 * rB0;
               rA7 = pA0[7];
               rC6_0 += m1;
               m1 = rA1 * rB0;
               rA8 = pA0[8];
               rC7_0 += m2;
               m2 = rA2 * rB0;
               rA9 = pA0[9];
               rC8_0 += m3;
               m3 = rA3 * rB0;
               rC9_0 += m4;
               m4 = rA4 * rB0;
            } /* end K-loop */
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
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rA3 = pA0[3];
            rA4 = pA0[4];
            rA5 = pA0[5];
            rA6 = pA0[6];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA7 = pA0[7];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA8 = pA0[8];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA9 = pA0[9];
            rC8_0 += m3;
            m3 = rA3 * rB0;
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
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rA3 = pA0[3];
            rA4 = pA0[4];
            rA5 = pA0[5];
            rA6 = pA0[6];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA7 = pA0[7];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA8 = pA0[8];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA9 = pA0[9];
            rC8_0 += m3;
            m3 = rA3 * rB0;
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
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rA3 = pA0[3];
            rA4 = pA0[4];
            rA5 = pA0[5];
            rA6 = pA0[6];
            rC5_0 += m0;
            m0 = rA0 * rB0;
            rA7 = pA0[7];
            rC6_0 += m1;
            m1 = rA1 * rB0;
            rA8 = pA0[8];
            rC7_0 += m2;
            m2 = rA2 * rB0;
            rA9 = pA0[9];
            rC8_0 += m3;
            m3 = rA3 * rB0;
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
            pA0 += incAk0;
            pB0 += incBk0;
            rC5_0 += m0;
            rC6_0 += m1;
            rC7_0 += m2;
            rC8_0 += m3;
            rC9_0 += m4;
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
            pC0[1] = rC1_0;
            pC0[2] = rC2_0;
            pC0[3] = rC3_0;
            pC0[4] = rC4_0;
            pC0[5] = rC5_0;
            pC0[6] = rC6_0;
            pC0[7] = rC7_0;
            pC0[8] = rC8_0;
            pC0[9] = rC9_0;
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
      ATL_dJIK0x0x40NT1x1x4_aX_bX(k, N, 40, alpha, ca + (Mb), lda, cb, ldb, beta, cc + (Mb), ldc);
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
