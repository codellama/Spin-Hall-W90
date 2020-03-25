#ifndef ATL_UCLEANK
   #define ATL_dgpKBmm ATL_dpKBmm
#endif

void ATL_dJIK0x0x0TN0x0x0_a1_bX(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc);
typedef void (*MMfunc)(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc);

void ATL_dgpKBmm(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc)
{
   ATL_dJIK0x0x0TN0x0x0_a1_bX(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
#ifndef ATL_UCLEANK
void ATL_dpKBmm_b0(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc)
{
   ATL_dgpKBmm(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
void ATL_dpKBmm_b1(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc)
{
   ATL_dgpKBmm(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
void ATL_dpKBmm_bX(const int M, const int N, const int K, const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C, const int ldc)
{
   ATL_dgpKBmm(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
#endif
