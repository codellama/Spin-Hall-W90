#define SREAL
#include "atlas_misc.h"
void ATL_supKBmm8_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm16_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm24_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm32_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm40_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm48_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm56_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm64_8_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm4_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm12_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm20_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm28_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm36_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm44_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm52_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm60_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_supKBmm68_4_1_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_spKBmm_bX
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);
void ATL_sgpKBmm
   (const int M, const int N, const int K, const float alpha,
    const float *A, const int lda, const float *B, const int ldb,
    const float beta, float *C, const int ldc);

typedef void (*MMfunc)(const int, const int, const int, const TYPE,
                       const TYPE *, const int, const TYPE *, const int,
                       const TYPE, TYPE *, const int);

void ATL_spKBmm_bX
   (const int M, const int N, const int K, const TYPE alpha,
    const TYPE *A, const int lda, const TYPE *B, const int ldb,
    const TYPE beta, TYPE *C, const int ldc)
{

   static MMfunc mmfunc[72] = 
   {
      NULL,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm4_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm8_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm12_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm16_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm20_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm24_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm28_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm32_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm36_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm40_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm44_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm48_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm52_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm56_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm60_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm64_8_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_supKBmm68_4_1_bX,
      ATL_sgpKBmm,
      ATL_sgpKBmm,
      ATL_sgpKBmm
   };

   mmfunc[K](M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
