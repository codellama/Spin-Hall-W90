#ifdef BETA0
#define ATL_INT int
#include <stdio.h>
#include <stdint.h>
#include <pmmintrin.h>

#define I_UNROLL 2
#define J_UNROLL 3
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (float*)(a)
#define MMCASTStore( a ) (float*)(a)
#define MMCASTStoreintrin( a ) (__m128)(a)
#define TYPE double
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128d c0_0, c0_1;
   __m128d c1_0, c1_1;
   __m128d c2_0, c2_1;
   /* Temporary vector registers for use in inner loop */
   __m128d temp; 
   __m128d temp0;  
   __m128d temp1;  
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = 2*ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 54*KB); 
   register void const *prefetchB =  (void*)(B + 54*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128d A0, a0, A1, a1;
   /* Unroll B */
   __m128d B0, B1, B2;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (2 * 3 * KB * 8) / 54;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-54; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      register TYPE *cPtrI2 = cPtrI1 + ldc_bytes;
      

      for( i=-54+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_pd( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_pd( A1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
         c1_0 = B1;
         c1_0 = _mm_mul_pd( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_pd( A1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
         c2_0 = B2;
         c2_0 = _mm_mul_pd( A0, c2_0 );
         c2_1 = B2;
         c2_1 = _mm_mul_pd( A1, c2_1 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 2 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 4 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 6 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 8 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 10 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 12 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 14 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 16 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 18 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 20 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 22 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 24 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 26 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 28 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 30 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 32 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 34 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 36 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 38 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 40 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 42 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 44 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 46 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 48 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 50 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 52 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         prefetchABlock += 1*pfBlockDistance;
         /* Combine scalar expansion back to scalar */
         c0_0 = _mm_hadd_pd( c0_0, c0_1 );
         c1_0 = _mm_hadd_pd( c1_0, c1_1 );
         c2_0 = _mm_hadd_pd( c2_0, c2_1 );
         /* Applying Beta */
         /* No beta will be appied */
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_store_sd( cPtrI0+0, c0_0 );
         temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI0+2, temp );

         _mm_store_sd( cPtrI1+0, c1_0 );
         temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI1+2, temp );

         _mm_store_sd( cPtrI2+0, c2_0 );
         temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI2+2, temp );

         cPtrI0 += 2*I_UNROLL;
         cPtrI1 += 2*I_UNROLL;
         cPtrI2 += 2*I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_pd( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_pd( A1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
      c1_0 = B1;
      c1_0 = _mm_mul_pd( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_pd( A1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
      c2_0 = B2;
      c2_0 = _mm_mul_pd( A0, c2_0 );
      c2_1 = B2;
      c2_1 = _mm_mul_pd( A1, c2_1 );
      
      /* K_Unrolling: 2 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 4 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 6 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 10 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 14 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 18 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 22 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 26 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 30 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 34 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 38 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 42 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 46 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 48 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 50 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 52 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      prefetchB += J_UNROLL*KB*8;
      /* Combine scalar expansion back to scalar */
      c0_0 = _mm_hadd_pd( c0_0, c0_1 );
      c1_0 = _mm_hadd_pd( c1_0, c1_1 );
      c2_0 = _mm_hadd_pd( c2_0, c2_1 );
      /* Applying Beta */
      /* No beta will be appied */
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_store_sd( cPtrI0+0, c0_0 );
      temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI0+2, temp );

      _mm_store_sd( cPtrI1+0, c1_0 );
      temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI1+2, temp );

      _mm_store_sd( cPtrI2+0, c2_0 );
      temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI2+2, temp );

      cPtrI0 += 2*I_UNROLL;
      cPtrI1 += 2*I_UNROLL;
      cPtrI2 += 2*I_UNROLL;
      

      B0_off += J_UNROLL*KB;
      cPtr += J_UNROLL*ldc_bytes;
   } /* End j/NB loop */
   /* End of generated inner loops */
}
#elif defined(BETAX)
#define ATL_INT int
#include <stdio.h>
#include <stdint.h>
#include <pmmintrin.h>

#define I_UNROLL 2
#define J_UNROLL 3
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (float*)(a)
#define MMCASTStore( a ) (float*)(a)
#define MMCASTStoreintrin( a ) (__m128)(a)
#define TYPE double
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128d c0_0, c0_1;
   __m128d c1_0, c1_1;
   __m128d c2_0, c2_1;
   /* Vector register to hold C*beta */
   __m128d bc0_0, bc0_1;
   __m128d bc1_0, bc1_1;
   __m128d bc2_0, bc2_1;
   /* Temporary vector registers for use in inner loop */
   __m128d temp; 
   __m128d temp0;  
   __m128d temp1;  
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   const __m128d betaV = _mm_set1_pd( beta ); 
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = 2*ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 54*KB); 
   register void const *prefetchB =  (void*)(B + 54*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128d A0, a0, A1, a1;
   /* Unroll B */
   __m128d B0, B1, B2;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (2 * 3 * KB * 8) / 54;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-54; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      register TYPE *cPtrI2 = cPtrI1 + ldc_bytes;
      

      for( i=-54+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_pd( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_pd( A1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
         c1_0 = B1;
         c1_0 = _mm_mul_pd( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_pd( A1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
         c2_0 = B2;
         c2_0 = _mm_mul_pd( A0, c2_0 );
         c2_1 = B2;
         c2_1 = _mm_mul_pd( A1, c2_1 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 2 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 4 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 6 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 8 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 10 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 12 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 14 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 16 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 18 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 20 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 22 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 24 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 26 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 28 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 30 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 32 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 34 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 36 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 38 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 40 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 42 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 44 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 46 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 48 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 50 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 52 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         prefetchABlock += 1*pfBlockDistance;
         /* Combine scalar expansion back to scalar */
         c0_0 = _mm_hadd_pd( c0_0, c0_1 );
         c1_0 = _mm_hadd_pd( c1_0, c1_1 );
         c2_0 = _mm_hadd_pd( c2_0, c2_1 );
         /* Applying Beta */
            /* Apply Beta Factor */
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI0 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI0 + 2 );
            bc0_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            bc0_0 = _mm_mul_pd( betaV, bc0_0 );
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI1 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI1 + 2 );
            bc1_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            bc1_0 = _mm_mul_pd( betaV, bc1_0 );
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI2 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI2 + 2 );
            bc2_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            bc2_0 = _mm_mul_pd( betaV, bc2_0 );
            /* C = (beta*C) + (matrix multiply) */
            c0_0 = _mm_add_pd( bc0_0, c0_0 );
            c1_0 = _mm_add_pd( bc1_0, c1_0 );
            c2_0 = _mm_add_pd( bc2_0, c2_0 );
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_store_sd( cPtrI0+0, c0_0 );
         temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI0+2, temp );

         _mm_store_sd( cPtrI1+0, c1_0 );
         temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI1+2, temp );

         _mm_store_sd( cPtrI2+0, c2_0 );
         temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI2+2, temp );

         cPtrI0 += 2*I_UNROLL;
         cPtrI1 += 2*I_UNROLL;
         cPtrI2 += 2*I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_pd( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_pd( A1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
      c1_0 = B1;
      c1_0 = _mm_mul_pd( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_pd( A1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
      c2_0 = B2;
      c2_0 = _mm_mul_pd( A0, c2_0 );
      c2_1 = B2;
      c2_1 = _mm_mul_pd( A1, c2_1 );
      
      /* K_Unrolling: 2 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 4 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 6 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 10 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 14 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 18 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 22 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 26 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 30 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 34 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 38 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 42 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 46 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 48 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 50 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 52 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      prefetchB += J_UNROLL*KB*8;
      /* Combine scalar expansion back to scalar */
      c0_0 = _mm_hadd_pd( c0_0, c0_1 );
      c1_0 = _mm_hadd_pd( c1_0, c1_1 );
      c2_0 = _mm_hadd_pd( c2_0, c2_1 );
      /* Applying Beta */
         /* Apply Beta Factor */
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI0 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI0 + 2 );
         bc0_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         bc0_0 = _mm_mul_pd( betaV, bc0_0 );
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI1 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI1 + 2 );
         bc1_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         bc1_0 = _mm_mul_pd( betaV, bc1_0 );
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI2 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI2 + 2 );
         bc2_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         bc2_0 = _mm_mul_pd( betaV, bc2_0 );
         /* C = (beta*C) + (matrix multiply) */
         c0_0 = _mm_add_pd( bc0_0, c0_0 );
         c1_0 = _mm_add_pd( bc1_0, c1_0 );
         c2_0 = _mm_add_pd( bc2_0, c2_0 );
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_store_sd( cPtrI0+0, c0_0 );
      temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI0+2, temp );

      _mm_store_sd( cPtrI1+0, c1_0 );
      temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI1+2, temp );

      _mm_store_sd( cPtrI2+0, c2_0 );
      temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI2+2, temp );

      cPtrI0 += 2*I_UNROLL;
      cPtrI1 += 2*I_UNROLL;
      cPtrI2 += 2*I_UNROLL;
      

      B0_off += J_UNROLL*KB;
      cPtr += J_UNROLL*ldc_bytes;
   } /* End j/NB loop */
   /* End of generated inner loops */
}
#else
#define ATL_INT int
#include <stdio.h>
#include <stdint.h>
#include <pmmintrin.h>

#define I_UNROLL 2
#define J_UNROLL 3
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (float*)(a)
#define MMCASTStore( a ) (float*)(a)
#define MMCASTStoreintrin( a ) (__m128)(a)
#define TYPE double
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128d c0_0, c0_1;
   __m128d c1_0, c1_1;
   __m128d c2_0, c2_1;
   /* Vector register to hold C*beta */
   __m128d bc0_0, bc0_1;
   __m128d bc1_0, bc1_1;
   __m128d bc2_0, bc2_1;
   /* Temporary vector registers for use in inner loop */
   __m128d temp; 
   __m128d temp0;  
   __m128d temp1;  
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = 2*ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 54*KB); 
   register void const *prefetchB =  (void*)(B + 54*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128d A0, a0, A1, a1;
   /* Unroll B */
   __m128d B0, B1, B2;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (2 * 3 * KB * 8) / 54;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-54; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      register TYPE *cPtrI2 = cPtrI1 + ldc_bytes;
      

      for( i=-54+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_pd( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_pd( A1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
         c1_0 = B1;
         c1_0 = _mm_mul_pd( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_pd( A1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
         c2_0 = B2;
         c2_0 = _mm_mul_pd( A0, c2_0 );
         c2_1 = B2;
         c2_1 = _mm_mul_pd( A1, c2_1 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 2 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 4 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 6 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 8 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 10 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 12 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 14 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 16 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 18 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 20 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 22 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 24 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 26 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 28 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 30 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 32 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 34 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 36 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 38 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 40 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 42 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 44 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 46 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 48 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 50 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         /* K_Unrolling: 52 */
         A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
         A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
         
         B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_pd( B0, a0 );
         c0_0 = _mm_add_pd( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B0, a1 );
         c0_1 = _mm_add_pd( a1, c0_1 );
         
         B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
         a0 = A0;
         a0 = _mm_mul_pd( B1, a0 );
         c1_0 = _mm_add_pd( a0, c1_0 );
         a1 = A1;
         a1 = _mm_mul_pd( B1, a1 );
         c1_1 = _mm_add_pd( a1, c1_1 );
         
         B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
         A0 = _mm_mul_pd( B2, A0 );
         c2_0 = _mm_add_pd( A0, c2_0 );
         A1 = _mm_mul_pd( B2, A1 );
         c2_1 = _mm_add_pd( A1, c2_1 );
         prefetchABlock += 1*pfBlockDistance;
         /* Combine scalar expansion back to scalar */
         c0_0 = _mm_hadd_pd( c0_0, c0_1 );
         c1_0 = _mm_hadd_pd( c1_0, c1_1 );
         c2_0 = _mm_hadd_pd( c2_0, c2_1 );
         /* Applying Beta */
            /* Apply Beta Factor */
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI0 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI0 + 2 );
            bc0_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI1 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI1 + 2 );
            bc1_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            /* Load C from memory */
            temp0 = (__m128d)_mm_load_ss( cPtrI2 + 0 );
            temp1 = (__m128d)_mm_load_ss( cPtrI2 + 2 );
            bc2_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
            /* C = (beta*C) + (matrix multiply) */
            c0_0 = _mm_add_pd( bc0_0, c0_0 );
            c1_0 = _mm_add_pd( bc1_0, c1_0 );
            c2_0 = _mm_add_pd( bc2_0, c2_0 );
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_store_sd( cPtrI0+0, c0_0 );
         temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI0+2, temp );

         _mm_store_sd( cPtrI1+0, c1_0 );
         temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI1+2, temp );

         _mm_store_sd( cPtrI2+0, c2_0 );
         temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
         _mm_store_sd( cPtrI2+2, temp );

         cPtrI0 += 2*I_UNROLL;
         cPtrI1 += 2*I_UNROLL;
         cPtrI2 += 2*I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 54) );
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_pd( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_pd( A1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 54) );
      c1_0 = B1;
      c1_0 = _mm_mul_pd( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_pd( A1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 108) );
      c2_0 = B2;
      c2_0 = _mm_mul_pd( A0, c2_0 );
      c2_1 = B2;
      c2_1 = _mm_mul_pd( A1, c2_1 );
      
      /* K_Unrolling: 2 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 2) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 56) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 2) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 110) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 4 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 4) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 58) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 58) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 6 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 6) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 60) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 6) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 114) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 8) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 62) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 62) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 10 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 10) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 64) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 10) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 118) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 12) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 66) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 66) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 20,PF_READONLY, PF_DEF);
      /* K_Unrolling: 14 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 14) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 68) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 14) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 122) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 16) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 70) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 70) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 18 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 18) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 72) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 18) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 72) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 126) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 40,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 20) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 74) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 74) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 22 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 22) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 76) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 22) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 76) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 130) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 24) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 78) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 78) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 60,PF_READONLY, PF_DEF);
      /* K_Unrolling: 26 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 26) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 80) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 26) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 80) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 134) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 28) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 82) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 82) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 30 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 30) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 84) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 30) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 84) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 138) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 80,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 32) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 86) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 86) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 34 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 34) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 88) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 34) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 88) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 142) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 36) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 90) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 90) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 144) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 100,PF_READONLY, PF_DEF);
      /* K_Unrolling: 38 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 38) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 92) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 38) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 92) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 146) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + 0 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 40) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 94) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 94) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 148) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -8 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 42 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 42) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 96) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 42) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 96) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 150) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      __builtin_prefetch( prefetchB + -16 + 120,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 44) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 98) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 98) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 152) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 46 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 46) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 100) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 46) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 100) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 154) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 48 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 48) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 102) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 102) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 156) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 50 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 50) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 104) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 50) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 104) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 158) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      /* K_Unrolling: 52 */
      A0 = (__m128d)_mm_load_ps( MMCAST(A0_off + 52) );
      A1 = (__m128d)_mm_load_ps( MMCAST(A0_off + 106) );
      
      B0 = (__m128d)_mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_pd( B0, a0 );
      c0_0 = _mm_add_pd( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B0, a1 );
      c0_1 = _mm_add_pd( a1, c0_1 );
      
      B1 = (__m128d)_mm_load_ps( MMCAST(B0_off + 106) );
      a0 = A0;
      a0 = _mm_mul_pd( B1, a0 );
      c1_0 = _mm_add_pd( a0, c1_0 );
      a1 = A1;
      a1 = _mm_mul_pd( B1, a1 );
      c1_1 = _mm_add_pd( a1, c1_1 );
      
      B2 = (__m128d)_mm_load_ps( MMCAST(B0_off + 160) );
      A0 = _mm_mul_pd( B2, A0 );
      c2_0 = _mm_add_pd( A0, c2_0 );
      A1 = _mm_mul_pd( B2, A1 );
      c2_1 = _mm_add_pd( A1, c2_1 );
      prefetchB += J_UNROLL*KB*8;
      /* Combine scalar expansion back to scalar */
      c0_0 = _mm_hadd_pd( c0_0, c0_1 );
      c1_0 = _mm_hadd_pd( c1_0, c1_1 );
      c2_0 = _mm_hadd_pd( c2_0, c2_1 );
      /* Applying Beta */
         /* Apply Beta Factor */
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI0 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI0 + 2 );
         bc0_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI1 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI1 + 2 );
         bc1_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         /* Load C from memory */
         temp0 = (__m128d)_mm_load_ss( cPtrI2 + 0 );
         temp1 = (__m128d)_mm_load_ss( cPtrI2 + 2 );
         bc2_0 = _mm_shuffle_pd( temp0, temp1,_MM_SHUFFLE2(0, 0 )  );
         /* C = (beta*C) + (matrix multiply) */
         c0_0 = _mm_add_pd( bc0_0, c0_0 );
         c1_0 = _mm_add_pd( bc1_0, c1_0 );
         c2_0 = _mm_add_pd( bc2_0, c2_0 );
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_store_sd( cPtrI0+0, c0_0 );
      temp = _mm_shuffle_pd( c0_0, c0_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI0+2, temp );

      _mm_store_sd( cPtrI1+0, c1_0 );
      temp = _mm_shuffle_pd( c1_0, c1_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI1+2, temp );

      _mm_store_sd( cPtrI2+0, c2_0 );
      temp = _mm_shuffle_pd( c2_0, c2_0,_MM_SHUFFLE2(1,1));
      _mm_store_sd( cPtrI2+2, temp );

      cPtrI0 += 2*I_UNROLL;
      cPtrI1 += 2*I_UNROLL;
      cPtrI2 += 2*I_UNROLL;
      

      B0_off += J_UNROLL*KB;
      cPtr += J_UNROLL*ldc_bytes;
   } /* End j/NB loop */
   /* End of generated inner loops */
}
#endif
