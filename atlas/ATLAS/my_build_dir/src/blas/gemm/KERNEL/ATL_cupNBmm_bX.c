#define SCPLX
#include "atlas_misc.h"
void ATL_cupNBmm0_1_0_b0
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cupNBmm0_2_0_b0
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cgpNBmm_b0
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cupNBmm0_1_0_b1
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cupNBmm0_2_0_b1
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cgpNBmm_b1
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cupNBmm0_1_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cupNBmm0_2_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_cgpNBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);

#define ATL_CupNBmm0_1_0_bX(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_cupNBmm0_1_0_bX(M_, N_, K_, al_, A_, lda_, B_, ldb_, -(be_), C_, ldc_); \
   ATL_cupNBmm0_1_0_bX(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_cupNBmm0_1_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_cupNBmm0_1_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}
#define ATL_CupNBmm0_2_0_bX(M_, N_, K_, al_, A_, lda_, B_, ldb_, be_, C_, ldc_) \
{ \
   ATL_cupNBmm0_2_0_bX(M_, N_, K_, al_, A_, lda_, B_, ldb_, -(be_), C_, ldc_); \
   ATL_cupNBmm0_2_0_bX(M_, N_, K_, al_, A_, lda_, (B_)+(ldb_)*(N_), ldb_, be_, (C_)+1, ldc_); \
   ATL_cupNBmm0_2_0_bX(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, (B_)+(ldb_)*(N_), ldb_, ATL_rnone, C_, ldc); \
   ATL_cupNBmm0_2_0_b1(M_, N_, K_, al_, (A_)+(lda_)*(M_), lda_, B_, ldb_, ATL_rone, (C_)+1, ldc_); \
}

void ATL_cpNBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc)
{

   if (N == (((((N) >> 1)) << 1)))
   {
      ATL_CupNBmm0_2_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else
   {
      ATL_CupNBmm0_1_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
}
