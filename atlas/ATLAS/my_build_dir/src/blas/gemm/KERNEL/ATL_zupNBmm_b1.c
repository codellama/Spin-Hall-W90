#define DCPLX
#include "atlas_misc.h"
void ATL_zupNBmm0_2_0_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpNBmm_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupNBmm0_2_0_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpNBmm_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupNBmm0_2_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpNBmm_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);

#define ATL_ZupNBmm0_2_0_b1(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_zupNBmm0_2_0_bX(M_, N_, K_, al_, A_, lda_, B_, ldb_, ATL_rnone, C_, ldc_); \
   ATL_zupNBmm0_2_0_b1(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_zupNBmm0_2_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_zupNBmm0_2_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}

void ATL_zpNBmm_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc)
{

   if (N == (((((N) >> 1)) << 1)))
   {
      ATL_ZupNBmm0_2_0_b1(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else ATL_zgpNBmm_b1(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
