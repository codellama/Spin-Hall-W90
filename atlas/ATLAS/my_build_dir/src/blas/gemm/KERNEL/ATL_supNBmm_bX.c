#define SREAL
#include "atlas_misc.h"
void ATL_supNBmm0_1_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supNBmm0_2_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_sgpNBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);

void ATL_spNBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc)
{

   if (N == (((((N) >> 1)) << 1)))
   {
      ATL_supNBmm0_2_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else
   {
      ATL_supNBmm0_1_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
}
