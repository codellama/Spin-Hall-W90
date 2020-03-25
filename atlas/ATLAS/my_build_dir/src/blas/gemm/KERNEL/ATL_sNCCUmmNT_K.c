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
#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
static void ATL_sJIK0x0x68NT1x1x4_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=1, nu=1, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   #define Mb M
   #define Nb N
   const float *stM = A + (Mb);
   const float *stN = B + (Nb);
   const float BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 1 - (((lda) << 6)+((lda) << 2)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 1
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 1
   const int incCn = (ldc) - (Mb);
   float *pC0=C;
   const float *pA0=A;
   const float *pB0=B;
   register int k;
   register float rA0;
   register float rB0;
   register float m0;
   register float rC0_0;
   do /* N-loop */
   {
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

         for (k=0; k < 64; k += 4) /* easy loop to unroll */
         {
            rC0_0 += m0;
            m0 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m0;
            m0 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m0;
            m0 = rA0 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += m0;
            m0 = rA0 * rB0;
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
         rC0_0 += m0;
         m0 = rA0 * rB0;
         pA0 += incAk;
         pB0 += incBk;
         rA0 = *pA0;
         rB0 = *pB0;
/*
 *       Drain pipe on last iteration of K-loop
 */
         rC0_0 += m0;
         m0 = rA0 * rB0;
         pA0 += incAk0;
         pB0 += incBk0;
         rC0_0 += m0;
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
static void ATL_sJIK0x0x68NT2x1x4_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=2, nu=1, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const int Mb = (M>>1)<<1;
   #define Nb N
   const float *ca=A, *cb=B;
   float *cc=C;
   const float *stM = A + (Mb);
   const float *stN = B + (Nb);
   const float BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 2 - (((lda) << 6)+((lda) << 2)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 1
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 2
   const int incCn = (ldc) - (Mb);
   float *pC0=C;
   const float *pA0=A;
   const float *pB0=B;
   register int k;
   register float rA0, rA1;
   register float rB0;
   register float m0;
   register float rC0_0, rC1_0;
   if (pA0 != stM)
   {
      do /* N-loop */
      {
         do /* M-loop */
         {
            rA0 = BetaAlpha;
            rC0_0 = *pC0;
            rC0_0 *= rA0;
            rC1_0 = pC0[1];
            rC1_0 *= rA0;
/*
 *          Start pipeline
 */
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            m0 = rA0 * rB0;

            for (k=0; k < 64; k += 4) /* easy loop to unroll */
            {
               rC0_0 += m0;
               m0 = rA1 * rB0;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rC1_0 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA1 * rB0;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rC1_0 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA1 * rB0;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rC1_0 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA1 * rB0;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rC1_0 += m0;
               m0 = rA0 * rB0;
            } /* end K-loop */
            rC0_0 += m0;
            m0 = rA1 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rC1_0 += m0;
            m0 = rA0 * rB0;
            rC0_0 += m0;
            m0 = rA1 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rC1_0 += m0;
            m0 = rA0 * rB0;
            rC0_0 += m0;
            m0 = rA1 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[1];
            rC1_0 += m0;
            m0 = rA0 * rB0;
/*
 *          Drain pipe on last iteration of K-loop
 */
            rC0_0 += m0;
            m0 = rA1 * rB0;
            pA0 += incAk0;
            pB0 += incBk0;
            rC1_0 += m0;
            rB0 = alpha;
            rC0_0 *= rB0;
            rC1_0 *= rB0;
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
   if (k=M-Mb)
      ATL_sJIK0x0x68NT1x1x4_aX_bX(k, N, 68, alpha, ca + (Mb), lda, cb, ldb, beta, cc + (Mb), ldc);
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
#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
static void ATL_sJIK0x0x68NT1x5x4_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=1, nu=5, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   #define Mb M
   const int Nb = (N/5)*5;
   const float *ca=A, *cb=B;
   float *cc=C;
   const float *stM = A + (Mb);
   const float *stN = B + (Nb);
   const float BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 1 - (((lda) << 6)+((lda) << 2)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 5
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 1
   const int incCn = (((ldc) << 2)+ldc) - (Mb);
   float *pC0=C, *pC1=pC0+(ldc), *pC2=pC1+(ldc), *pC3=pC2+(ldc), *pC4=pC3+(ldc);
   const float *pA0=A;
   const float *pB0=B;
   register int k;
   register float rA0;
   register float rB0, rB1, rB2, rB3, rB4;
   register float m0;
   register float rC0_0, rC0_1, rC0_2, rC0_3, rC0_4;
   if (pB0 != stN)
   {
      do /* N-loop */
      {
         do /* M-loop */
         {
            rA0 = BetaAlpha;
            rC0_0 = *pC0;
            rC0_0 *= rA0;
            rC0_1 = *pC1;
            rC0_1 *= rA0;
            rC0_2 = *pC2;
            rC0_2 *= rA0;
            rC0_3 = *pC3;
            rC0_3 *= rA0;
            rC0_4 = *pC4;
            rC0_4 *= rA0;
/*
 *          Start pipeline
 */
            rA0 = *pA0;
            rB0 = *pB0;
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            m0 = rA0 * rB0;

            for (k=0; k < 64; k += 4) /* easy loop to unroll */
            {
               rC0_0 += m0;
               m0 = rA0 * rB1;
               rC0_1 += m0;
               m0 = rA0 * rB2;
               rC0_2 += m0;
               m0 = rA0 * rB3;
               rC0_3 += m0;
               m0 = rA0 * rB4;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rB1 = pB0[1];
               rB2 = pB0[2];
               rB3 = pB0[3];
               rB4 = pB0[4];
               rC0_4 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA0 * rB1;
               rC0_1 += m0;
               m0 = rA0 * rB2;
               rC0_2 += m0;
               m0 = rA0 * rB3;
               rC0_3 += m0;
               m0 = rA0 * rB4;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rB1 = pB0[1];
               rB2 = pB0[2];
               rB3 = pB0[3];
               rB4 = pB0[4];
               rC0_4 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA0 * rB1;
               rC0_1 += m0;
               m0 = rA0 * rB2;
               rC0_2 += m0;
               m0 = rA0 * rB3;
               rC0_3 += m0;
               m0 = rA0 * rB4;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rB1 = pB0[1];
               rB2 = pB0[2];
               rB3 = pB0[3];
               rB4 = pB0[4];
               rC0_4 += m0;
               m0 = rA0 * rB0;
               rC0_0 += m0;
               m0 = rA0 * rB1;
               rC0_1 += m0;
               m0 = rA0 * rB2;
               rC0_2 += m0;
               m0 = rA0 * rB3;
               rC0_3 += m0;
               m0 = rA0 * rB4;
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rB1 = pB0[1];
               rB2 = pB0[2];
               rB3 = pB0[3];
               rB4 = pB0[4];
               rC0_4 += m0;
               m0 = rA0 * rB0;
            } /* end K-loop */
            rC0_0 += m0;
            m0 = rA0 * rB1;
            rC0_1 += m0;
            m0 = rA0 * rB2;
            rC0_2 += m0;
            m0 = rA0 * rB3;
            rC0_3 += m0;
            m0 = rA0 * rB4;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC0_4 += m0;
            m0 = rA0 * rB0;
            rC0_0 += m0;
            m0 = rA0 * rB1;
            rC0_1 += m0;
            m0 = rA0 * rB2;
            rC0_2 += m0;
            m0 = rA0 * rB3;
            rC0_3 += m0;
            m0 = rA0 * rB4;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC0_4 += m0;
            m0 = rA0 * rB0;
            rC0_0 += m0;
            m0 = rA0 * rB1;
            rC0_1 += m0;
            m0 = rA0 * rB2;
            rC0_2 += m0;
            m0 = rA0 * rB3;
            rC0_3 += m0;
            m0 = rA0 * rB4;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rB1 = pB0[1];
            rB2 = pB0[2];
            rB3 = pB0[3];
            rB4 = pB0[4];
            rC0_4 += m0;
            m0 = rA0 * rB0;
/*
 *          Drain pipe on last iteration of K-loop
 */
            rC0_0 += m0;
            m0 = rA0 * rB1;
            rC0_1 += m0;
            m0 = rA0 * rB2;
            rC0_2 += m0;
            m0 = rA0 * rB3;
            rC0_3 += m0;
            m0 = rA0 * rB4;
            pA0 += incAk0;
            pB0 += incBk0;
            rC0_4 += m0;
            rB0 = alpha;
            rC0_0 *= rB0;
            rC0_1 *= rB0;
            rC0_2 *= rB0;
            rC0_3 *= rB0;
            rC0_4 *= rB0;
            *pC0 = rC0_0;
            *pC1 = rC0_1;
            *pC2 = rC0_2;
            *pC3 = rC0_3;
            *pC4 = rC0_4;
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
   if (k=N-Nb)
      ATL_sJIK0x0x68NT1x1x4_aX_bX(M, k, 68, alpha, ca, lda, cb + (Nb), ldb, beta, cc + (Nb*ldc), ldc);
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
void ATL_sJIK0x0x68NT0x0x0_aX_bX
   (const int M, const int N, const int K, const float alpha, const float * ATL_RESTRICT A, const int lda, const float * ATL_RESTRICT B, const int ldb, const float beta, float * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=0, NB=0, KB=68, 
 * lda=0, ldb=0, ldc=0, mu=2, nu=5, ku=4, pf=0
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.2)
 */
{
   const int Mb = (M>>1)<<1;
   const int Nb = (N/5)*5;
   const float *ca=A, *cb=B;
   float *cc=C;
   const float *stM = A + (Mb);
   const float *stN = B + (Nb);
   const float BetaAlpha = beta / alpha;
   const int incAk = (lda);
   const int incAm = 2 - (((lda) << 6)+((lda) << 2)), incAn = -(Mb);
   const int incBk = (ldb), incBm = -(((ldb) << 6)+((ldb) << 2));
   #define incBn 5
   #define incAk0 incAk
   #define incBk0 incBk
   #define incCm 2
   const int incCn = (((ldc) << 2)+ldc) - (Mb);
   float *pC0=C, *pC1=pC0+(ldc), *pC2=pC1+(ldc), *pC3=pC2+(ldc), *pC4=pC3+(ldc);
   const float *pA0=A;
   const float *pB0=B;
   register int k;
   register float rA0, rA1;
   register float rB0, rB1, rB2, rB3, rB4;
   register float m0;
   register float rC0_0, rC1_0, rC0_1, rC1_1, rC0_2, rC1_2, rC0_3, rC1_3, rC0_4, rC1_4;
   if (pA0 != stM)
   {
      if (pB0 != stN)
      {
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
 *             Start pipeline
 */
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
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
                  pA0 += incAk;
                  pB0 += incBk;
                  rA0 = *pA0;
                  rB0 = *pB0;
                  rA1 = pA0[1];
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
                  pA0 += incAk;
                  pB0 += incBk;
                  rA0 = *pA0;
                  rB0 = *pB0;
                  rA1 = pA0[1];
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
                  pA0 += incAk;
                  pB0 += incBk;
                  rA0 = *pA0;
                  rB0 = *pB0;
                  rA1 = pA0[1];
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
                  pA0 += incAk;
                  pB0 += incBk;
                  rA0 = *pA0;
                  rB0 = *pB0;
                  rA1 = pA0[1];
                  rB1 = pB0[1];
                  rB2 = pB0[2];
                  rB3 = pB0[3];
                  rB4 = pB0[4];
                  rC1_4 += m0;
                  m0 = rA0 * rB0;
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
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
               pA0 += incAk;
               pB0 += incBk;
               rA0 = *pA0;
               rB0 = *pB0;
               rA1 = pA0[1];
               rB1 = pB0[1];
               rB2 = pB0[2];
               rB3 = pB0[3];
               rB4 = pB0[4];
               rC1_4 += m0;
               m0 = rA0 * rB0;
/*
 *             Drain pipe on last iteration of K-loop
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
               pA0 += incAk0;
               pB0 += incBk0;
               rC1_4 += m0;
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
   }
   if (k=N-Nb)
      ATL_sJIK0x0x68NT2x1x4_aX_bX(M, k, 68, alpha, ca, lda, cb + (Nb), ldb, beta, cc + (Nb*ldc), ldc);
   if (Nb && (k=M-Mb))
      ATL_sJIK0x0x68NT1x5x4_aX_bX(k, Nb, 68, alpha, ca + (Mb), lda, cb, ldb, beta, cc + (Mb), ldc);
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
