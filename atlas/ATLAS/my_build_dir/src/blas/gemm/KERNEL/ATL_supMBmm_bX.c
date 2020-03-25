#define SREAL
#include "atlas_misc.h"
void ATL_supMBmm0_14_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supMBmm0_10_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supMBmm0_6_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supMBmm0_4_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supMBmm0_2_0_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_sgpMBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);

typedef void (*MMfunc)(const int, const int, const int, const TYPE,
                       const TYPE *, const int, const TYPE *, const int,
                       const TYPE, TYPE *, const int);

void ATL_spMBmm_bX
   (const int M, const int N, const int K, const TYPE alpha,
    const TYPE *A, const int lda, const TYPE *B, const int ldb,
    const TYPE beta, TYPE *C, const int ldc)
{

   static MMfunc mmfunc[72] = 
   {
      NULL,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_14_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_14_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_14_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_14_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_10_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_2_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_6_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_4_0_bX,
      ATL_sgpMBmm_bX,
      ATL_supMBmm0_14_0_bX,
      ATL_sgpMBmm_bX
   };

   mmfunc[M](M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
