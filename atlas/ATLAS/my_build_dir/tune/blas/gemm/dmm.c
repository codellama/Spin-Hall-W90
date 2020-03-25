#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
static void ATL_dJIK52x0x52TN2x1x1_a1_b1
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=N, MB=52, NB=0, KB=52, 
 * lda=52, ldb=52, ldc=0, mu=2, nu=1, ku=1, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   #define Nb N
   const double *stM = A + 2704;
   const double *stN = B + (52*(Nb));
   #define incAk 1
   const int incAm = 52, incAn = -2704;
   #define incBk 1
   const int incBm = -52, incBn = 52;
   #define incCm 2
   const int incCn = (ldc) - 52;
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0, rA1;
   register double rB0;
   register double rC0_0, rC1_0;
   do /* N-loop */
   {
      do /* M-loop */
      {
         rC0_0 = *pC0;
         rC1_0 = pC0[1];
         for (k=0; k < 52; k++) /* easy loop to unroll */
         {
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[52];
            rC0_0 += rA0 * rB0;
            rC1_0 += rA1 * rB0;
            pA0 += incAk;
            pB0 += incBk;
         }
         *pC0 = rC0_0;
         pC0[1] = rC1_0;
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
void ATL_dJIK52x0x52TN52x52x0_a1_b1
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=N, MB=52, NB=0, KB=52, 
 * lda=52, ldb=52, ldc=0, mu=2, nu=6, ku=1, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const int Nb = (N/6)*6;
   const double *ca=A, *cb=B;
   double *cc=C;
   const double *stM = A + 2704;
   const double *stN = B + (52*(Nb));
   #define incAk 1
   const int incAm = 52, incAn = -2704;
   #define incBk 1
   const int incBm = -52, incBn = 312;
   #define incCm 2
   const int incCn = (((ldc) << 2)+((ldc) << 1)) - 52;
   double *pC0=C, *pC1=pC0+(ldc), *pC2=pC1+(ldc), *pC3=pC2+(ldc), *pC4=pC3+(ldc), *pC5=pC4+(ldc);
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0, rA1;
   register double rB0, rB1, rB2, rB3, rB4, rB5;
   register double rC0_0, rC1_0, rC0_1, rC1_1, rC0_2, rC1_2, rC0_3, rC1_3, rC0_4, rC1_4, rC0_5, rC1_5;
   if (pB0 != stN)
   {
      do /* N-loop */
      {
         do /* M-loop */
         {
            rC0_0 = *pC0;
            rC1_0 = pC0[1];
            rC0_1 = *pC1;
            rC1_1 = pC1[1];
            rC0_2 = *pC2;
            rC1_2 = pC2[1];
            rC0_3 = *pC3;
            rC1_3 = pC3[1];
            rC0_4 = *pC4;
            rC1_4 = pC4[1];
            rC0_5 = *pC5;
            rC1_5 = pC5[1];
            for (k=0; k < 52; k++) /* easy loop to unroll */
            {
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[52];
               rB1 = pB0[52];
               rB2 = pB0[104];
               rC0_0 += rA0 * rB0;
               rB3 = pB0[156];
               rC1_0 += rA1 * rB0;
               rB4 = pB0[208];
               rC0_1 += rA0 * rB1;
               rB5 = pB0[260];
               rC1_1 += rA1 * rB1;
               rC0_2 += rA0 * rB2;
               rC1_2 += rA1 * rB2;
               rC0_3 += rA0 * rB3;
               rC1_3 += rA1 * rB3;
               rC0_4 += rA0 * rB4;
               rC1_4 += rA1 * rB4;
               rC0_5 += rA0 * rB5;
               rC1_5 += rA1 * rB5;
               pA0 += incAk;
               pB0 += incBk;
            }
            *pC0 = rC0_0;
            pC0[1] = rC1_0;
            *pC1 = rC0_1;
            pC1[1] = rC1_1;
            *pC2 = rC0_2;
            pC2[1] = rC1_2;
            *pC3 = rC0_3;
            pC3[1] = rC1_3;
            *pC4 = rC0_4;
            pC4[1] = rC1_4;
            *pC5 = rC0_5;
            pC5[1] = rC1_5;
            pC0 += incCm;
            pC1 += incCm;
            pC2 += incCm;
            pC3 += incCm;
            pC4 += incCm;
            pC5 += incCm;
            pA0 += incAm;
            pB0 += incBm;
         }
         while(pA0 != stM);
         pC0 += incCn;
         pC1 += incCn;
         pC2 += incCn;
         pC3 += incCn;
         pC4 += incCn;
         pC5 += incCn;
         pA0 += incAn;
         pB0 += incBn;
      }
      while(pB0 != stN);
   }
   if (k=N-Nb)
      ATL_dJIK52x0x52TN2x1x1_a1_b1(52, k, 52, alpha, ca, lda, cb + (52*(Nb)), ldb, beta, cc + (Nb*ldc), ldc);
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
