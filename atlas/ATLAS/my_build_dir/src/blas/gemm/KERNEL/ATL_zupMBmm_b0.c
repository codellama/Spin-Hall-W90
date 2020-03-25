#define DCPLX
#include "atlas_misc.h"
void ATL_zupMBmm0_2_0_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_4_0_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_6_0_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpMBmm_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_2_0_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_4_0_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_6_0_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpMBmm_b1
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_2_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_4_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zupMBmm0_6_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_zgpMBmm_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);

#define ATL_ZupMBmm0_2_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_zupMBmm0_2_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, ATL_rzero, C_, ldc_); \
   ATL_zupMBmm0_2_0_b0(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_zupMBmm0_2_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_zupMBmm0_2_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}
#define ATL_ZupMBmm0_4_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_zupMBmm0_4_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, ATL_rzero, C_, ldc_); \
   ATL_zupMBmm0_4_0_b0(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_zupMBmm0_4_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_zupMBmm0_4_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}
#define ATL_ZupMBmm0_6_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_zupMBmm0_6_0_b0(M_, N_, K_, al_, A_, lda_, B_, ldb_, ATL_rzero, C_, ldc_); \
   ATL_zupMBmm0_6_0_b0(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_zupMBmm0_6_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_zupMBmm0_6_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}

void ATL_zpMBmm_b0
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc)
{

   if (M == (((((M) / 6)) << 2)+((((M) / 6)) << 1)))
   {
      ATL_ZupMBmm0_6_0_b0(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else if (M == (((((M) >> 2)) << 2)))
   {
      ATL_ZupMBmm0_4_0_b0(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else if (M == (((((M) >> 1)) << 1)))
   {
      ATL_ZupMBmm0_2_0_b0(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else ATL_zgpMBmm_b0(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
