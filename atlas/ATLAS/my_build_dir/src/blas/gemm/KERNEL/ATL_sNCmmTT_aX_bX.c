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
static void ATL_sJIK68x3x68TT2x3x4_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=T, MB=68, NB=3, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=2, nu=3, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const float *stM = A + (((lda) << 6)+((lda) << 2));
   const float *stN = B + 3;
   const float BetaAlpha = beta / alpha;
   #define incAk 4
   const int incAm = ((((lda) << 1)) - 68), incAn = -(((lda) << 6)+((lda) << 2));
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 3
   const int incAk0 = ((incAk) >> 2);
   #define incBk0 incBk
   #define incCm 2
   const int incCn = (((ldc) << 1)+ldc) - 68;
   float *pC0=C, *pC1=pC0+(ldc), *pC2=pC1+(ldc);
   const float *pA0=A, *pA1=pA0+(lda);
   const float *pB0=B;
   register int k;
   register float rA0, rA1;
   register float rB0, rB1, rB2;
   register float m0;
   register float rC0_0, rC1_0, rC0_1, rC1_1, rC0_2, rC1_2;
   do /* M-loop */
   {
      rA0 = BetaAlpha;
      rC0_0 = *pC0;
      rC0_0 *= rA0;
      rC1_0 = pC0[1];
      rC1_0 *= rA0;
      rC0_1 = *pC1;
      rC0_1 *= rA0;
      rC1_1 = pC1[1];
      rC1_1 *= rA0;
      rC0_2 = *pC2;
      rC0_2 *= rA0;
      rC1_2 = pC2[1];
      rC1_2 *= rA0;
/*
 *    Start pipeline
 */
      rA0 = *pA0;
      rB0 = *pB0;
      rA1 = *pA1;
      rB1 = pB0[1];
      rB2 = pB0[2];
      m0 = rA0 * rB0;

      for (k=0; k < 64; k += 4) /* easy loop to unroll */
      {
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
         pB0 += incBk;
         rA0 = pA0[1];
         rB0 = *pB0;
         rA1 = pA1[1];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rC1_2 += m0;
         m0 = rA0 * rB0;
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
         pB0 += incBk;
         rA0 = pA0[2];
         rB0 = *pB0;
         rA1 = pA1[2];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rC1_2 += m0;
         m0 = rA0 * rB0;
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
         pB0 += incBk;
         rA0 = pA0[3];
         rB0 = *pB0;
         rA1 = pA1[3];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rC1_2 += m0;
         m0 = rA0 * rB0;
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
         pB0 += incBk;
         rA0 = pA0[4];
         rB0 = *pB0;
         rA1 = pA1[4];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rC1_2 += m0;
         m0 = rA0 * rB0;
         pA0 += incAk;
         pA1 += incAk;
      } /* end K-loop */
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
      pB0 += incBk;
      rA0 = pA0[1];
      rB0 = *pB0;
      rA1 = pA1[1];
      rB1 = pB0[1];
      rB2 = pB0[2];
      rC1_2 += m0;
      m0 = rA0 * rB0;
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
      pB0 += incBk;
      rA0 = pA0[2];
      rB0 = *pB0;
      rA1 = pA1[2];
      rB1 = pB0[1];
      rB2 = pB0[2];
      rC1_2 += m0;
      m0 = rA0 * rB0;
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
      pB0 += incBk;
      rA0 = pA0[3];
      rB0 = *pB0;
      rA1 = pA1[3];
      rB1 = pB0[1];
      rB2 = pB0[2];
      rC1_2 += m0;
      m0 = rA0 * rB0;
      pA0 += (((incAk0) << 1)+incAk0);
      pA1 += (((incAk0) << 1)+incAk0);
/*
 *    Drain pipe on last iteration of K-loop
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
      pB0 += incBk0;
      rC1_2 += m0;
      pA0 += incAk0;
      pA1 += incAk0;
      rB0 = alpha;
      rC0_0 *= rB0;
      rC0_1 *= rB0;
      rC0_2 *= rB0;
      rC1_0 *= rB0;
      rC1_1 *= rB0;
      rC1_2 *= rB0;
      *pC0 = rC0_0;
      pC0[1] = rC1_0;
      *pC1 = rC0_1;
      pC1[1] = rC1_1;
      *pC2 = rC0_2;
      pC2[1] = rC1_2;
      pC0 += incCm;
      pC1 += incCm;
      pC2 += incCm;
      pA0 += incAm;
      pA1 += incAm;
      pB0 += incBm;
   }
   while(pA0 != stM);
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
void ATL_sJIK68x68x68TT0x0x0_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=T, MB=68, NB=68, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=2, nu=5, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const float *ca=A, *cb=B;
   float *cc=C;
   const float *stM = A + (((lda) << 6)+((lda) << 2));
   const float *stN = B + 65;
   const float BetaAlpha = beta / alpha;
   #define incAk 4
   const int incAm = ((((lda) << 1)) - 68), incAn = -(((lda) << 6)+((lda) << 2));
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 5
   const int incAk0 = ((incAk) >> 2);
   #define incBk0 incBk
   #define incCm 2
   const int incCn = (((ldc) << 2)+ldc) - 68;
   float *pC0=C, *pC1=pC0+(ldc), *pC2=pC1+(ldc), *pC3=pC2+(ldc), *pC4=pC3+(ldc);
   const float *pA0=A, *pA1=pA0+(lda);
   const float *pB0=B;
   register int k;
   register float rA0, rA1;
   register float rB0, rB1, rB2, rB3, rB4;
   register float m0;
   register float rC0_0, rC1_0, rC0_1, rC1_1, rC0_2, rC1_2, rC0_3, rC1_3, rC0_4, rC1_4;
   do /* N-loop */
   {
      do /* M-loop */
      {
         rA0 = BetaAlpha;
         rC0_0 = *pC0;
         rC0_0 *= rA0;
         rC1_0 = pC0[1];
         rC1_0 *= rA0;
         rC0_1 = *pC1;
         rC0_1 *= rA0;
         rC1_1 = pC1[1];
         rC1_1 *= rA0;
         rC0_2 = *pC2;
         rC0_2 *= rA0;
         rC1_2 = pC2[1];
         rC1_2 *= rA0;
         rC0_3 = *pC3;
         rC0_3 *= rA0;
         rC1_3 = pC3[1];
         rC1_3 *= rA0;
         rC0_4 = *pC4;
         rC0_4 *= rA0;
         rC1_4 = pC4[1];
         rC1_4 *= rA0;
/*
 *       Start pipeline
 */
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = *pA1;
         rB1 = pB0[1];
         rB2 = pB0[2];
         rB3 = pB0[3];
         m0 = rA0 * rB0;
         rB4 = pB0[4];

         for (k=0; k < 64; k += 4) /* easy loop to unroll */
         {
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
            pB0 += incBk;
            rA0 = pA0[1];
            rB0 = *pB0;
            rA1 = pA1[1];
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC1_4 += m0;
            m0 = rA0 * rB0;
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
            pB0 += incBk;
            rA0 = pA0[2];
            rB0 = *pB0;
            rA1 = pA1[2];
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC1_4 += m0;
            m0 = rA0 * rB0;
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
            pB0 += incBk;
            rA0 = pA0[3];
            rB0 = *pB0;
            rA1 = pA1[3];
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC1_4 += m0;
            m0 = rA0 * rB0;
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
            pB0 += incBk;
            rA0 = pA0[4];
            rB0 = *pB0;
            rA1 = pA1[4];
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC1_4 += m0;
            m0 = rA0 * rB0;
            pA0 += incAk;
            pA1 += incAk;
         } /* end K-loop */
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
         pB0 += incBk;
         rA0 = pA0[1];
         rB0 = *pB0;
         rA1 = pA1[1];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rB3 = pB0[3];
         rB4 = pB0[4];
         rC1_4 += m0;
         m0 = rA0 * rB0;
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
         pB0 += incBk;
         rA0 = pA0[2];
         rB0 = *pB0;
         rA1 = pA1[2];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rB3 = pB0[3];
         rB4 = pB0[4];
         rC1_4 += m0;
         m0 = rA0 * rB0;
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
         pB0 += incBk;
         rA0 = pA0[3];
         rB0 = *pB0;
         rA1 = pA1[3];
         rB1 = pB0[1];
         rB2 = pB0[2];
         rB3 = pB0[3];
         rB4 = pB0[4];
         rC1_4 += m0;
         m0 = rA0 * rB0;
         pA0 += (((incAk0) << 1)+incAk0);
         pA1 += (((incAk0) << 1)+incAk0);
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
         pB0 += incBk0;
         rC1_4 += m0;
         pA0 += incAk0;
         pA1 += incAk0;
         rB0 = alpha;
         rC0_0 *= rB0;
         rC0_1 *= rB0;
         rC0_2 *= rB0;
         rC0_3 *= rB0;
         rC0_4 *= rB0;
         rC1_0 *= rB0;
         rC1_1 *= rB0;
         rC1_2 *= rB0;
         rC1_3 *= rB0;
         rC1_4 *= rB0;
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
         pC0 += incCm;
         pC1 += incCm;
         pC2 += incCm;
         pC3 += incCm;
         pC4 += incCm;
         pA0 += incAm;
         pA1 += incAm;
         pB0 += incBm;
      }
      while(pA0 != stM);
      pC0 += incCn;
      pC1 += incCn;
      pC2 += incCn;
      pC3 += incCn;
      pC4 += incCn;
      pA0 += incAn;
      pA1 += incAn;
      pB0 += incBn;
   }
   while(pB0 != stN);
   ATL_sJIK68x3x68TT2x3x4_aX_bX(68, 3, 68, alpha, ca, lda, cb + 65, ldb, beta, cc + (((ldc) << 6)+ldc), ldc);
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
