#define DREAL
#include "atlas_misc.h"
void ATL_dupNBmm0_1_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_dupNBmm0_2_0_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);
void ATL_dgpNBmm_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc);

void ATL_dpNBmm_bX
   (const int M, const int N, const int K, const double alpha,
    const double *A, const int lda, const double *B, const int ldb,
    const double beta, double *C, const int ldc)
{

   if (N == (((((N) >> 1)) << 1)))
   {
      ATL_dupNBmm0_2_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
   else
   {
      ATL_dupNBmm0_1_0_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   }
}
