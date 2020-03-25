#ifdef BETA0
#define ATL_INT int
#include <stdio.h>
#include <stdint.h>
#include <pmmintrin.h>

#define I_UNROLL 4
#define J_UNROLL 2
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (a)
#define MMCASTStore( a ) (a)
#define MMCASTStoreintrin( a ) (a)
#define TYPE float
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128 c0_0, c0_1, c0_2, c0_3;
   __m128 c1_0, c1_1, c1_2, c1_3;
   /* Temporary vector registers for use in inner loop */
   __m128 temp; 
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 72*KB); 
   register void const *prefetchB =  (void*)(B + 72*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128 A0, a0, A1, a1, A2, a2, A3, a3;
   /* Unroll B */
   __m128 B0, B1;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (4 * 2 * KB * 4) / 72;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-72; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      

      for( i=-72+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = _mm_load_ps( MMCAST(A0_off) );
         A1 = _mm_load_ps( MMCAST(A0_off + 72) );
         A2 = _mm_load_ps( MMCAST(A0_off + 144) );
         A3 = _mm_load_ps( MMCAST(A0_off + 216) );
         B0 = _mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_ps( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_ps( A1, c0_1 );
         c0_2 = B0;
         c0_2 = _mm_mul_ps( A2, c0_2 );
         c0_3 = B0;
         c0_3 = _mm_mul_ps( A3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 72) );
         c1_0 = B1;
         c1_0 = _mm_mul_ps( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_ps( A1, c1_1 );
         c1_2 = B1;
         c1_2 = _mm_mul_ps( A2, c1_2 );
         c1_3 = B1;
         c1_3 = _mm_mul_ps( A3, c1_3 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 4 */
         A0 = _mm_load_ps( MMCAST(A0_off + 4) );
         A1 = _mm_load_ps( MMCAST(A0_off + 76) );
         A2 = _mm_load_ps( MMCAST(A0_off + 148) );
         A3 = _mm_load_ps( MMCAST(A0_off + 220) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 76) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 8 */
         A0 = _mm_load_ps( MMCAST(A0_off + 8) );
         A1 = _mm_load_ps( MMCAST(A0_off + 80) );
         A2 = _mm_load_ps( MMCAST(A0_off + 152) );
         A3 = _mm_load_ps( MMCAST(A0_off + 224) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 80) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 12 */
         A0 = _mm_load_ps( MMCAST(A0_off + 12) );
         A1 = _mm_load_ps( MMCAST(A0_off + 84) );
         A2 = _mm_load_ps( MMCAST(A0_off + 156) );
         A3 = _mm_load_ps( MMCAST(A0_off + 228) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 84) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 16 */
         A0 = _mm_load_ps( MMCAST(A0_off + 16) );
         A1 = _mm_load_ps( MMCAST(A0_off + 88) );
         A2 = _mm_load_ps( MMCAST(A0_off + 160) );
         A3 = _mm_load_ps( MMCAST(A0_off + 232) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 88) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 20 */
         A0 = _mm_load_ps( MMCAST(A0_off + 20) );
         A1 = _mm_load_ps( MMCAST(A0_off + 92) );
         A2 = _mm_load_ps( MMCAST(A0_off + 164) );
         A3 = _mm_load_ps( MMCAST(A0_off + 236) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 92) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 24 */
         A0 = _mm_load_ps( MMCAST(A0_off + 24) );
         A1 = _mm_load_ps( MMCAST(A0_off + 96) );
         A2 = _mm_load_ps( MMCAST(A0_off + 168) );
         A3 = _mm_load_ps( MMCAST(A0_off + 240) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 96) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 28 */
         A0 = _mm_load_ps( MMCAST(A0_off + 28) );
         A1 = _mm_load_ps( MMCAST(A0_off + 100) );
         A2 = _mm_load_ps( MMCAST(A0_off + 172) );
         A3 = _mm_load_ps( MMCAST(A0_off + 244) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 100) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 32 */
         A0 = _mm_load_ps( MMCAST(A0_off + 32) );
         A1 = _mm_load_ps( MMCAST(A0_off + 104) );
         A2 = _mm_load_ps( MMCAST(A0_off + 176) );
         A3 = _mm_load_ps( MMCAST(A0_off + 248) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 104) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 36 */
         A0 = _mm_load_ps( MMCAST(A0_off + 36) );
         A1 = _mm_load_ps( MMCAST(A0_off + 108) );
         A2 = _mm_load_ps( MMCAST(A0_off + 180) );
         A3 = _mm_load_ps( MMCAST(A0_off + 252) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 108) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 40 */
         A0 = _mm_load_ps( MMCAST(A0_off + 40) );
         A1 = _mm_load_ps( MMCAST(A0_off + 112) );
         A2 = _mm_load_ps( MMCAST(A0_off + 184) );
         A3 = _mm_load_ps( MMCAST(A0_off + 256) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 44 */
         A0 = _mm_load_ps( MMCAST(A0_off + 44) );
         A1 = _mm_load_ps( MMCAST(A0_off + 116) );
         A2 = _mm_load_ps( MMCAST(A0_off + 188) );
         A3 = _mm_load_ps( MMCAST(A0_off + 260) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 48 */
         A0 = _mm_load_ps( MMCAST(A0_off + 48) );
         A1 = _mm_load_ps( MMCAST(A0_off + 120) );
         A2 = _mm_load_ps( MMCAST(A0_off + 192) );
         A3 = _mm_load_ps( MMCAST(A0_off + 264) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 52 */
         A0 = _mm_load_ps( MMCAST(A0_off + 52) );
         A1 = _mm_load_ps( MMCAST(A0_off + 124) );
         A2 = _mm_load_ps( MMCAST(A0_off + 196) );
         A3 = _mm_load_ps( MMCAST(A0_off + 268) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 56 */
         A0 = _mm_load_ps( MMCAST(A0_off + 56) );
         A1 = _mm_load_ps( MMCAST(A0_off + 128) );
         A2 = _mm_load_ps( MMCAST(A0_off + 200) );
         A3 = _mm_load_ps( MMCAST(A0_off + 272) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 60 */
         A0 = _mm_load_ps( MMCAST(A0_off + 60) );
         A1 = _mm_load_ps( MMCAST(A0_off + 132) );
         A2 = _mm_load_ps( MMCAST(A0_off + 204) );
         A3 = _mm_load_ps( MMCAST(A0_off + 276) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 64 */
         A0 = _mm_load_ps( MMCAST(A0_off + 64) );
         A1 = _mm_load_ps( MMCAST(A0_off + 136) );
         A2 = _mm_load_ps( MMCAST(A0_off + 208) );
         A3 = _mm_load_ps( MMCAST(A0_off + 280) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 68 */
         A0 = _mm_load_ps( MMCAST(A0_off + 68) );
         A1 = _mm_load_ps( MMCAST(A0_off + 140) );
         A2 = _mm_load_ps( MMCAST(A0_off + 212) );
         A3 = _mm_load_ps( MMCAST(A0_off + 284) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         prefetchABlock += 1*pfBlockDistance;
         /* Single Scalar Compression */
         c0_0 = _mm_hadd_ps( c0_0, c0_1 );
         c0_2 = _mm_hadd_ps( c0_2, c0_3 );
         c0_0 = _mm_hadd_ps( c0_0, c0_2 );
         
         c1_0 = _mm_hadd_ps( c1_0, c1_1 );
         c1_2 = _mm_hadd_ps( c1_2, c1_3 );
         c1_0 = _mm_hadd_ps( c1_0, c1_2 );
         
         /* Applying Beta */
         /* No beta will be appied */
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
         _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
         cPtrI0 += I_UNROLL;
         cPtrI1 += I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = _mm_load_ps( MMCAST(A0_off) );
      A1 = _mm_load_ps( MMCAST(A0_off + 72) );
      A2 = _mm_load_ps( MMCAST(A0_off + 144) );
      A3 = _mm_load_ps( MMCAST(A0_off + 216) );
      B0 = _mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_ps( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_ps( A1, c0_1 );
      c0_2 = B0;
      c0_2 = _mm_mul_ps( A2, c0_2 );
      c0_3 = B0;
      c0_3 = _mm_mul_ps( A3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 72) );
      c1_0 = B1;
      c1_0 = _mm_mul_ps( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_ps( A1, c1_1 );
      c1_2 = B1;
      c1_2 = _mm_mul_ps( A2, c1_2 );
      c1_3 = B1;
      c1_3 = _mm_mul_ps( A3, c1_3 );
      
      /* K_Unrolling: 4 */
      A0 = _mm_load_ps( MMCAST(A0_off + 4) );
      A1 = _mm_load_ps( MMCAST(A0_off + 76) );
      A2 = _mm_load_ps( MMCAST(A0_off + 148) );
      A3 = _mm_load_ps( MMCAST(A0_off + 220) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 76) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = _mm_load_ps( MMCAST(A0_off + 8) );
      A1 = _mm_load_ps( MMCAST(A0_off + 80) );
      A2 = _mm_load_ps( MMCAST(A0_off + 152) );
      A3 = _mm_load_ps( MMCAST(A0_off + 224) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 80) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = _mm_load_ps( MMCAST(A0_off + 12) );
      A1 = _mm_load_ps( MMCAST(A0_off + 84) );
      A2 = _mm_load_ps( MMCAST(A0_off + 156) );
      A3 = _mm_load_ps( MMCAST(A0_off + 228) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 84) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = _mm_load_ps( MMCAST(A0_off + 16) );
      A1 = _mm_load_ps( MMCAST(A0_off + 88) );
      A2 = _mm_load_ps( MMCAST(A0_off + 160) );
      A3 = _mm_load_ps( MMCAST(A0_off + 232) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 88) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = _mm_load_ps( MMCAST(A0_off + 20) );
      A1 = _mm_load_ps( MMCAST(A0_off + 92) );
      A2 = _mm_load_ps( MMCAST(A0_off + 164) );
      A3 = _mm_load_ps( MMCAST(A0_off + 236) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 92) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = _mm_load_ps( MMCAST(A0_off + 24) );
      A1 = _mm_load_ps( MMCAST(A0_off + 96) );
      A2 = _mm_load_ps( MMCAST(A0_off + 168) );
      A3 = _mm_load_ps( MMCAST(A0_off + 240) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 96) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = _mm_load_ps( MMCAST(A0_off + 28) );
      A1 = _mm_load_ps( MMCAST(A0_off + 100) );
      A2 = _mm_load_ps( MMCAST(A0_off + 172) );
      A3 = _mm_load_ps( MMCAST(A0_off + 244) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 100) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = _mm_load_ps( MMCAST(A0_off + 32) );
      A1 = _mm_load_ps( MMCAST(A0_off + 104) );
      A2 = _mm_load_ps( MMCAST(A0_off + 176) );
      A3 = _mm_load_ps( MMCAST(A0_off + 248) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 104) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = _mm_load_ps( MMCAST(A0_off + 36) );
      A1 = _mm_load_ps( MMCAST(A0_off + 108) );
      A2 = _mm_load_ps( MMCAST(A0_off + 180) );
      A3 = _mm_load_ps( MMCAST(A0_off + 252) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 108) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = _mm_load_ps( MMCAST(A0_off + 40) );
      A1 = _mm_load_ps( MMCAST(A0_off + 112) );
      A2 = _mm_load_ps( MMCAST(A0_off + 184) );
      A3 = _mm_load_ps( MMCAST(A0_off + 256) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = _mm_load_ps( MMCAST(A0_off + 44) );
      A1 = _mm_load_ps( MMCAST(A0_off + 116) );
      A2 = _mm_load_ps( MMCAST(A0_off + 188) );
      A3 = _mm_load_ps( MMCAST(A0_off + 260) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 48 */
      A0 = _mm_load_ps( MMCAST(A0_off + 48) );
      A1 = _mm_load_ps( MMCAST(A0_off + 120) );
      A2 = _mm_load_ps( MMCAST(A0_off + 192) );
      A3 = _mm_load_ps( MMCAST(A0_off + 264) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 52 */
      A0 = _mm_load_ps( MMCAST(A0_off + 52) );
      A1 = _mm_load_ps( MMCAST(A0_off + 124) );
      A2 = _mm_load_ps( MMCAST(A0_off + 196) );
      A3 = _mm_load_ps( MMCAST(A0_off + 268) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 56 */
      A0 = _mm_load_ps( MMCAST(A0_off + 56) );
      A1 = _mm_load_ps( MMCAST(A0_off + 128) );
      A2 = _mm_load_ps( MMCAST(A0_off + 200) );
      A3 = _mm_load_ps( MMCAST(A0_off + 272) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 60 */
      A0 = _mm_load_ps( MMCAST(A0_off + 60) );
      A1 = _mm_load_ps( MMCAST(A0_off + 132) );
      A2 = _mm_load_ps( MMCAST(A0_off + 204) );
      A3 = _mm_load_ps( MMCAST(A0_off + 276) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 64 */
      A0 = _mm_load_ps( MMCAST(A0_off + 64) );
      A1 = _mm_load_ps( MMCAST(A0_off + 136) );
      A2 = _mm_load_ps( MMCAST(A0_off + 208) );
      A3 = _mm_load_ps( MMCAST(A0_off + 280) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 68 */
      A0 = _mm_load_ps( MMCAST(A0_off + 68) );
      A1 = _mm_load_ps( MMCAST(A0_off + 140) );
      A2 = _mm_load_ps( MMCAST(A0_off + 212) );
      A3 = _mm_load_ps( MMCAST(A0_off + 284) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      prefetchB += J_UNROLL*KB*4;
      /* Single Scalar Compression */
      c0_0 = _mm_hadd_ps( c0_0, c0_1 );
      c0_2 = _mm_hadd_ps( c0_2, c0_3 );
      c0_0 = _mm_hadd_ps( c0_0, c0_2 );
      
      c1_0 = _mm_hadd_ps( c1_0, c1_1 );
      c1_2 = _mm_hadd_ps( c1_2, c1_3 );
      c1_0 = _mm_hadd_ps( c1_0, c1_2 );
      
      /* Applying Beta */
      /* No beta will be appied */
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
      _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
      cPtrI0 += I_UNROLL;
      cPtrI1 += I_UNROLL;
      

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

#define I_UNROLL 4
#define J_UNROLL 2
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (a)
#define MMCASTStore( a ) (a)
#define MMCASTStoreintrin( a ) (a)
#define TYPE float
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128 c0_0, c0_1, c0_2, c0_3;
   __m128 c1_0, c1_1, c1_2, c1_3;
   /* Vector register to hold C*beta */
   __m128 bc0_0, bc0_1, bc0_2, bc0_3;
   __m128 bc1_0, bc1_1, bc1_2, bc1_3;
   /* Temporary vector registers for use in inner loop */
   __m128 temp; 
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   const __m128 betaV = _mm_set1_ps( beta ); 
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 72*KB); 
   register void const *prefetchB =  (void*)(B + 72*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128 A0, a0, A1, a1, A2, a2, A3, a3;
   /* Unroll B */
   __m128 B0, B1;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (4 * 2 * KB * 4) / 72;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-72; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      

      for( i=-72+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = _mm_load_ps( MMCAST(A0_off) );
         A1 = _mm_load_ps( MMCAST(A0_off + 72) );
         A2 = _mm_load_ps( MMCAST(A0_off + 144) );
         A3 = _mm_load_ps( MMCAST(A0_off + 216) );
         B0 = _mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_ps( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_ps( A1, c0_1 );
         c0_2 = B0;
         c0_2 = _mm_mul_ps( A2, c0_2 );
         c0_3 = B0;
         c0_3 = _mm_mul_ps( A3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 72) );
         c1_0 = B1;
         c1_0 = _mm_mul_ps( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_ps( A1, c1_1 );
         c1_2 = B1;
         c1_2 = _mm_mul_ps( A2, c1_2 );
         c1_3 = B1;
         c1_3 = _mm_mul_ps( A3, c1_3 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 4 */
         A0 = _mm_load_ps( MMCAST(A0_off + 4) );
         A1 = _mm_load_ps( MMCAST(A0_off + 76) );
         A2 = _mm_load_ps( MMCAST(A0_off + 148) );
         A3 = _mm_load_ps( MMCAST(A0_off + 220) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 76) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 8 */
         A0 = _mm_load_ps( MMCAST(A0_off + 8) );
         A1 = _mm_load_ps( MMCAST(A0_off + 80) );
         A2 = _mm_load_ps( MMCAST(A0_off + 152) );
         A3 = _mm_load_ps( MMCAST(A0_off + 224) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 80) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 12 */
         A0 = _mm_load_ps( MMCAST(A0_off + 12) );
         A1 = _mm_load_ps( MMCAST(A0_off + 84) );
         A2 = _mm_load_ps( MMCAST(A0_off + 156) );
         A3 = _mm_load_ps( MMCAST(A0_off + 228) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 84) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 16 */
         A0 = _mm_load_ps( MMCAST(A0_off + 16) );
         A1 = _mm_load_ps( MMCAST(A0_off + 88) );
         A2 = _mm_load_ps( MMCAST(A0_off + 160) );
         A3 = _mm_load_ps( MMCAST(A0_off + 232) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 88) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 20 */
         A0 = _mm_load_ps( MMCAST(A0_off + 20) );
         A1 = _mm_load_ps( MMCAST(A0_off + 92) );
         A2 = _mm_load_ps( MMCAST(A0_off + 164) );
         A3 = _mm_load_ps( MMCAST(A0_off + 236) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 92) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 24 */
         A0 = _mm_load_ps( MMCAST(A0_off + 24) );
         A1 = _mm_load_ps( MMCAST(A0_off + 96) );
         A2 = _mm_load_ps( MMCAST(A0_off + 168) );
         A3 = _mm_load_ps( MMCAST(A0_off + 240) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 96) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 28 */
         A0 = _mm_load_ps( MMCAST(A0_off + 28) );
         A1 = _mm_load_ps( MMCAST(A0_off + 100) );
         A2 = _mm_load_ps( MMCAST(A0_off + 172) );
         A3 = _mm_load_ps( MMCAST(A0_off + 244) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 100) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 32 */
         A0 = _mm_load_ps( MMCAST(A0_off + 32) );
         A1 = _mm_load_ps( MMCAST(A0_off + 104) );
         A2 = _mm_load_ps( MMCAST(A0_off + 176) );
         A3 = _mm_load_ps( MMCAST(A0_off + 248) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 104) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 36 */
         A0 = _mm_load_ps( MMCAST(A0_off + 36) );
         A1 = _mm_load_ps( MMCAST(A0_off + 108) );
         A2 = _mm_load_ps( MMCAST(A0_off + 180) );
         A3 = _mm_load_ps( MMCAST(A0_off + 252) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 108) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 40 */
         A0 = _mm_load_ps( MMCAST(A0_off + 40) );
         A1 = _mm_load_ps( MMCAST(A0_off + 112) );
         A2 = _mm_load_ps( MMCAST(A0_off + 184) );
         A3 = _mm_load_ps( MMCAST(A0_off + 256) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 44 */
         A0 = _mm_load_ps( MMCAST(A0_off + 44) );
         A1 = _mm_load_ps( MMCAST(A0_off + 116) );
         A2 = _mm_load_ps( MMCAST(A0_off + 188) );
         A3 = _mm_load_ps( MMCAST(A0_off + 260) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 48 */
         A0 = _mm_load_ps( MMCAST(A0_off + 48) );
         A1 = _mm_load_ps( MMCAST(A0_off + 120) );
         A2 = _mm_load_ps( MMCAST(A0_off + 192) );
         A3 = _mm_load_ps( MMCAST(A0_off + 264) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 52 */
         A0 = _mm_load_ps( MMCAST(A0_off + 52) );
         A1 = _mm_load_ps( MMCAST(A0_off + 124) );
         A2 = _mm_load_ps( MMCAST(A0_off + 196) );
         A3 = _mm_load_ps( MMCAST(A0_off + 268) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 56 */
         A0 = _mm_load_ps( MMCAST(A0_off + 56) );
         A1 = _mm_load_ps( MMCAST(A0_off + 128) );
         A2 = _mm_load_ps( MMCAST(A0_off + 200) );
         A3 = _mm_load_ps( MMCAST(A0_off + 272) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 60 */
         A0 = _mm_load_ps( MMCAST(A0_off + 60) );
         A1 = _mm_load_ps( MMCAST(A0_off + 132) );
         A2 = _mm_load_ps( MMCAST(A0_off + 204) );
         A3 = _mm_load_ps( MMCAST(A0_off + 276) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 64 */
         A0 = _mm_load_ps( MMCAST(A0_off + 64) );
         A1 = _mm_load_ps( MMCAST(A0_off + 136) );
         A2 = _mm_load_ps( MMCAST(A0_off + 208) );
         A3 = _mm_load_ps( MMCAST(A0_off + 280) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 68 */
         A0 = _mm_load_ps( MMCAST(A0_off + 68) );
         A1 = _mm_load_ps( MMCAST(A0_off + 140) );
         A2 = _mm_load_ps( MMCAST(A0_off + 212) );
         A3 = _mm_load_ps( MMCAST(A0_off + 284) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         prefetchABlock += 1*pfBlockDistance;
         /* Single Scalar Compression */
         c0_0 = _mm_hadd_ps( c0_0, c0_1 );
         c0_2 = _mm_hadd_ps( c0_2, c0_3 );
         c0_0 = _mm_hadd_ps( c0_0, c0_2 );
         
         c1_0 = _mm_hadd_ps( c1_0, c1_1 );
         c1_2 = _mm_hadd_ps( c1_2, c1_3 );
         c1_0 = _mm_hadd_ps( c1_0, c1_2 );
         
         /* Applying Beta */
            /* Apply Beta Factor */
            /* Load C from memory */
            bc0_0 = _mm_loadu_ps( cPtrI0+0 );
            bc0_0 = _mm_mul_ps( betaV, bc0_0 );
            /* Load C from memory */
            bc1_0 = _mm_loadu_ps( cPtrI1+0 );
            bc1_0 = _mm_mul_ps( betaV, bc1_0 );
            /* C = (beta*C) + (matrix multiply) */
            c0_0 = _mm_add_ps( bc0_0, c0_0 );
            c1_0 = _mm_add_ps( bc1_0, c1_0 );
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
         _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
         cPtrI0 += I_UNROLL;
         cPtrI1 += I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = _mm_load_ps( MMCAST(A0_off) );
      A1 = _mm_load_ps( MMCAST(A0_off + 72) );
      A2 = _mm_load_ps( MMCAST(A0_off + 144) );
      A3 = _mm_load_ps( MMCAST(A0_off + 216) );
      B0 = _mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_ps( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_ps( A1, c0_1 );
      c0_2 = B0;
      c0_2 = _mm_mul_ps( A2, c0_2 );
      c0_3 = B0;
      c0_3 = _mm_mul_ps( A3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 72) );
      c1_0 = B1;
      c1_0 = _mm_mul_ps( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_ps( A1, c1_1 );
      c1_2 = B1;
      c1_2 = _mm_mul_ps( A2, c1_2 );
      c1_3 = B1;
      c1_3 = _mm_mul_ps( A3, c1_3 );
      
      /* K_Unrolling: 4 */
      A0 = _mm_load_ps( MMCAST(A0_off + 4) );
      A1 = _mm_load_ps( MMCAST(A0_off + 76) );
      A2 = _mm_load_ps( MMCAST(A0_off + 148) );
      A3 = _mm_load_ps( MMCAST(A0_off + 220) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 76) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = _mm_load_ps( MMCAST(A0_off + 8) );
      A1 = _mm_load_ps( MMCAST(A0_off + 80) );
      A2 = _mm_load_ps( MMCAST(A0_off + 152) );
      A3 = _mm_load_ps( MMCAST(A0_off + 224) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 80) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = _mm_load_ps( MMCAST(A0_off + 12) );
      A1 = _mm_load_ps( MMCAST(A0_off + 84) );
      A2 = _mm_load_ps( MMCAST(A0_off + 156) );
      A3 = _mm_load_ps( MMCAST(A0_off + 228) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 84) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = _mm_load_ps( MMCAST(A0_off + 16) );
      A1 = _mm_load_ps( MMCAST(A0_off + 88) );
      A2 = _mm_load_ps( MMCAST(A0_off + 160) );
      A3 = _mm_load_ps( MMCAST(A0_off + 232) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 88) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = _mm_load_ps( MMCAST(A0_off + 20) );
      A1 = _mm_load_ps( MMCAST(A0_off + 92) );
      A2 = _mm_load_ps( MMCAST(A0_off + 164) );
      A3 = _mm_load_ps( MMCAST(A0_off + 236) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 92) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = _mm_load_ps( MMCAST(A0_off + 24) );
      A1 = _mm_load_ps( MMCAST(A0_off + 96) );
      A2 = _mm_load_ps( MMCAST(A0_off + 168) );
      A3 = _mm_load_ps( MMCAST(A0_off + 240) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 96) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = _mm_load_ps( MMCAST(A0_off + 28) );
      A1 = _mm_load_ps( MMCAST(A0_off + 100) );
      A2 = _mm_load_ps( MMCAST(A0_off + 172) );
      A3 = _mm_load_ps( MMCAST(A0_off + 244) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 100) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = _mm_load_ps( MMCAST(A0_off + 32) );
      A1 = _mm_load_ps( MMCAST(A0_off + 104) );
      A2 = _mm_load_ps( MMCAST(A0_off + 176) );
      A3 = _mm_load_ps( MMCAST(A0_off + 248) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 104) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = _mm_load_ps( MMCAST(A0_off + 36) );
      A1 = _mm_load_ps( MMCAST(A0_off + 108) );
      A2 = _mm_load_ps( MMCAST(A0_off + 180) );
      A3 = _mm_load_ps( MMCAST(A0_off + 252) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 108) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = _mm_load_ps( MMCAST(A0_off + 40) );
      A1 = _mm_load_ps( MMCAST(A0_off + 112) );
      A2 = _mm_load_ps( MMCAST(A0_off + 184) );
      A3 = _mm_load_ps( MMCAST(A0_off + 256) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = _mm_load_ps( MMCAST(A0_off + 44) );
      A1 = _mm_load_ps( MMCAST(A0_off + 116) );
      A2 = _mm_load_ps( MMCAST(A0_off + 188) );
      A3 = _mm_load_ps( MMCAST(A0_off + 260) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 48 */
      A0 = _mm_load_ps( MMCAST(A0_off + 48) );
      A1 = _mm_load_ps( MMCAST(A0_off + 120) );
      A2 = _mm_load_ps( MMCAST(A0_off + 192) );
      A3 = _mm_load_ps( MMCAST(A0_off + 264) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 52 */
      A0 = _mm_load_ps( MMCAST(A0_off + 52) );
      A1 = _mm_load_ps( MMCAST(A0_off + 124) );
      A2 = _mm_load_ps( MMCAST(A0_off + 196) );
      A3 = _mm_load_ps( MMCAST(A0_off + 268) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 56 */
      A0 = _mm_load_ps( MMCAST(A0_off + 56) );
      A1 = _mm_load_ps( MMCAST(A0_off + 128) );
      A2 = _mm_load_ps( MMCAST(A0_off + 200) );
      A3 = _mm_load_ps( MMCAST(A0_off + 272) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 60 */
      A0 = _mm_load_ps( MMCAST(A0_off + 60) );
      A1 = _mm_load_ps( MMCAST(A0_off + 132) );
      A2 = _mm_load_ps( MMCAST(A0_off + 204) );
      A3 = _mm_load_ps( MMCAST(A0_off + 276) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 64 */
      A0 = _mm_load_ps( MMCAST(A0_off + 64) );
      A1 = _mm_load_ps( MMCAST(A0_off + 136) );
      A2 = _mm_load_ps( MMCAST(A0_off + 208) );
      A3 = _mm_load_ps( MMCAST(A0_off + 280) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 68 */
      A0 = _mm_load_ps( MMCAST(A0_off + 68) );
      A1 = _mm_load_ps( MMCAST(A0_off + 140) );
      A2 = _mm_load_ps( MMCAST(A0_off + 212) );
      A3 = _mm_load_ps( MMCAST(A0_off + 284) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      prefetchB += J_UNROLL*KB*4;
      /* Single Scalar Compression */
      c0_0 = _mm_hadd_ps( c0_0, c0_1 );
      c0_2 = _mm_hadd_ps( c0_2, c0_3 );
      c0_0 = _mm_hadd_ps( c0_0, c0_2 );
      
      c1_0 = _mm_hadd_ps( c1_0, c1_1 );
      c1_2 = _mm_hadd_ps( c1_2, c1_3 );
      c1_0 = _mm_hadd_ps( c1_0, c1_2 );
      
      /* Applying Beta */
         /* Apply Beta Factor */
         /* Load C from memory */
         bc0_0 = _mm_loadu_ps( cPtrI0+0 );
         bc0_0 = _mm_mul_ps( betaV, bc0_0 );
         /* Load C from memory */
         bc1_0 = _mm_loadu_ps( cPtrI1+0 );
         bc1_0 = _mm_mul_ps( betaV, bc1_0 );
         /* C = (beta*C) + (matrix multiply) */
         c0_0 = _mm_add_ps( bc0_0, c0_0 );
         c1_0 = _mm_add_ps( bc1_0, c1_0 );
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
      _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
      cPtrI0 += I_UNROLL;
      cPtrI1 += I_UNROLL;
      

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

#define I_UNROLL 4
#define J_UNROLL 2
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (a)
#define MMCASTStore( a ) (a)
#define MMCASTStoreintrin( a ) (a)
#define TYPE float
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128 c0_0, c0_1, c0_2, c0_3;
   __m128 c1_0, c1_1, c1_2, c1_3;
   /* Vector register to hold C*beta */
   __m128 bc0_0, bc0_1, bc0_2, bc0_3;
   __m128 bc1_0, bc1_1, bc1_2, bc1_3;
   /* Temporary vector registers for use in inner loop */
   __m128 temp; 
   __builtin_prefetch( B, PF_READONLY, PF_DEF );
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 72*KB); 
   register void const *prefetchB =  (void*)(B + 72*ldb);
   __builtin_prefetch( prefetchB, PF_READONLY, PF_DEF );
   
   /* Unroll A */
   __m128 A0, a0, A1, a1, A2, a2, A3, a3;
   /* Unroll B */
   __m128 B0, B1;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (4 * 2 * KB * 4) / 72;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-72; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      register TYPE *cPtrI1 = cPtrI0 + ldc_bytes;
      

      for( i=-72+I_UNROLL; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = _mm_load_ps( MMCAST(A0_off) );
         A1 = _mm_load_ps( MMCAST(A0_off + 72) );
         A2 = _mm_load_ps( MMCAST(A0_off + 144) );
         A3 = _mm_load_ps( MMCAST(A0_off + 216) );
         B0 = _mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_ps( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_ps( A1, c0_1 );
         c0_2 = B0;
         c0_2 = _mm_mul_ps( A2, c0_2 );
         c0_3 = B0;
         c0_3 = _mm_mul_ps( A3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 72) );
         c1_0 = B1;
         c1_0 = _mm_mul_ps( A0, c1_0 );
         c1_1 = B1;
         c1_1 = _mm_mul_ps( A1, c1_1 );
         c1_2 = B1;
         c1_2 = _mm_mul_ps( A2, c1_2 );
         c1_3 = B1;
         c1_3 = _mm_mul_ps( A3, c1_3 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 4 */
         A0 = _mm_load_ps( MMCAST(A0_off + 4) );
         A1 = _mm_load_ps( MMCAST(A0_off + 76) );
         A2 = _mm_load_ps( MMCAST(A0_off + 148) );
         A3 = _mm_load_ps( MMCAST(A0_off + 220) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 4) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 76) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 8 */
         A0 = _mm_load_ps( MMCAST(A0_off + 8) );
         A1 = _mm_load_ps( MMCAST(A0_off + 80) );
         A2 = _mm_load_ps( MMCAST(A0_off + 152) );
         A3 = _mm_load_ps( MMCAST(A0_off + 224) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 8) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 80) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 12 */
         A0 = _mm_load_ps( MMCAST(A0_off + 12) );
         A1 = _mm_load_ps( MMCAST(A0_off + 84) );
         A2 = _mm_load_ps( MMCAST(A0_off + 156) );
         A3 = _mm_load_ps( MMCAST(A0_off + 228) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 12) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 84) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 16 */
         A0 = _mm_load_ps( MMCAST(A0_off + 16) );
         A1 = _mm_load_ps( MMCAST(A0_off + 88) );
         A2 = _mm_load_ps( MMCAST(A0_off + 160) );
         A3 = _mm_load_ps( MMCAST(A0_off + 232) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 16) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 88) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 20 */
         A0 = _mm_load_ps( MMCAST(A0_off + 20) );
         A1 = _mm_load_ps( MMCAST(A0_off + 92) );
         A2 = _mm_load_ps( MMCAST(A0_off + 164) );
         A3 = _mm_load_ps( MMCAST(A0_off + 236) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 20) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 92) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 24 */
         A0 = _mm_load_ps( MMCAST(A0_off + 24) );
         A1 = _mm_load_ps( MMCAST(A0_off + 96) );
         A2 = _mm_load_ps( MMCAST(A0_off + 168) );
         A3 = _mm_load_ps( MMCAST(A0_off + 240) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 24) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 96) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 28 */
         A0 = _mm_load_ps( MMCAST(A0_off + 28) );
         A1 = _mm_load_ps( MMCAST(A0_off + 100) );
         A2 = _mm_load_ps( MMCAST(A0_off + 172) );
         A3 = _mm_load_ps( MMCAST(A0_off + 244) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 28) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 100) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 32 */
         A0 = _mm_load_ps( MMCAST(A0_off + 32) );
         A1 = _mm_load_ps( MMCAST(A0_off + 104) );
         A2 = _mm_load_ps( MMCAST(A0_off + 176) );
         A3 = _mm_load_ps( MMCAST(A0_off + 248) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 32) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 104) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 36 */
         A0 = _mm_load_ps( MMCAST(A0_off + 36) );
         A1 = _mm_load_ps( MMCAST(A0_off + 108) );
         A2 = _mm_load_ps( MMCAST(A0_off + 180) );
         A3 = _mm_load_ps( MMCAST(A0_off + 252) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 36) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 108) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 40 */
         A0 = _mm_load_ps( MMCAST(A0_off + 40) );
         A1 = _mm_load_ps( MMCAST(A0_off + 112) );
         A2 = _mm_load_ps( MMCAST(A0_off + 184) );
         A3 = _mm_load_ps( MMCAST(A0_off + 256) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 40) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 112) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 44 */
         A0 = _mm_load_ps( MMCAST(A0_off + 44) );
         A1 = _mm_load_ps( MMCAST(A0_off + 116) );
         A2 = _mm_load_ps( MMCAST(A0_off + 188) );
         A3 = _mm_load_ps( MMCAST(A0_off + 260) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 44) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 116) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 48 */
         A0 = _mm_load_ps( MMCAST(A0_off + 48) );
         A1 = _mm_load_ps( MMCAST(A0_off + 120) );
         A2 = _mm_load_ps( MMCAST(A0_off + 192) );
         A3 = _mm_load_ps( MMCAST(A0_off + 264) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 48) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 120) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 52 */
         A0 = _mm_load_ps( MMCAST(A0_off + 52) );
         A1 = _mm_load_ps( MMCAST(A0_off + 124) );
         A2 = _mm_load_ps( MMCAST(A0_off + 196) );
         A3 = _mm_load_ps( MMCAST(A0_off + 268) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 52) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 124) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 56 */
         A0 = _mm_load_ps( MMCAST(A0_off + 56) );
         A1 = _mm_load_ps( MMCAST(A0_off + 128) );
         A2 = _mm_load_ps( MMCAST(A0_off + 200) );
         A3 = _mm_load_ps( MMCAST(A0_off + 272) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 56) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 128) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 60 */
         A0 = _mm_load_ps( MMCAST(A0_off + 60) );
         A1 = _mm_load_ps( MMCAST(A0_off + 132) );
         A2 = _mm_load_ps( MMCAST(A0_off + 204) );
         A3 = _mm_load_ps( MMCAST(A0_off + 276) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 60) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 132) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 64 */
         A0 = _mm_load_ps( MMCAST(A0_off + 64) );
         A1 = _mm_load_ps( MMCAST(A0_off + 136) );
         A2 = _mm_load_ps( MMCAST(A0_off + 208) );
         A3 = _mm_load_ps( MMCAST(A0_off + 280) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 64) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 136) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         /* K_Unrolling: 68 */
         A0 = _mm_load_ps( MMCAST(A0_off + 68) );
         A1 = _mm_load_ps( MMCAST(A0_off + 140) );
         A2 = _mm_load_ps( MMCAST(A0_off + 212) );
         A3 = _mm_load_ps( MMCAST(A0_off + 284) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 68) );
         a0 = A0;
         a0 = _mm_mul_ps( B0, a0 );
         c0_0 = _mm_add_ps( a0, c0_0 );
         a1 = A1;
         a1 = _mm_mul_ps( B0, a1 );
         c0_1 = _mm_add_ps( a1, c0_1 );
         a2 = A2;
         a2 = _mm_mul_ps( B0, a2 );
         c0_2 = _mm_add_ps( a2, c0_2 );
         a3 = A3;
         a3 = _mm_mul_ps( B0, a3 );
         c0_3 = _mm_add_ps( a3, c0_3 );
         
         B1 = _mm_load_ps( MMCAST(B0_off + 140) );
         A0 = _mm_mul_ps( B1, A0 );
         c1_0 = _mm_add_ps( A0, c1_0 );
         A1 = _mm_mul_ps( B1, A1 );
         c1_1 = _mm_add_ps( A1, c1_1 );
         A2 = _mm_mul_ps( B1, A2 );
         c1_2 = _mm_add_ps( A2, c1_2 );
         A3 = _mm_mul_ps( B1, A3 );
         c1_3 = _mm_add_ps( A3, c1_3 );
         prefetchABlock += 1*pfBlockDistance;
         /* Single Scalar Compression */
         c0_0 = _mm_hadd_ps( c0_0, c0_1 );
         c0_2 = _mm_hadd_ps( c0_2, c0_3 );
         c0_0 = _mm_hadd_ps( c0_0, c0_2 );
         
         c1_0 = _mm_hadd_ps( c1_0, c1_1 );
         c1_2 = _mm_hadd_ps( c1_2, c1_3 );
         c1_0 = _mm_hadd_ps( c1_0, c1_2 );
         
         /* Applying Beta */
            /* Apply Beta Factor */
            /* Load C from memory */
            bc0_0 = _mm_loadu_ps( cPtrI0+0 );
            /* Load C from memory */
            bc1_0 = _mm_loadu_ps( cPtrI1+0 );
            /* C = (beta*C) + (matrix multiply) */
            c0_0 = _mm_add_ps( bc0_0, c0_0 );
            c1_0 = _mm_add_ps( bc1_0, c1_0 );
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
         _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
         cPtrI0 += I_UNROLL;
         cPtrI1 += I_UNROLL;
         

      } /* End i/MB loop */

      /* K_Unrolling0 */
      A0 = _mm_load_ps( MMCAST(A0_off) );
      A1 = _mm_load_ps( MMCAST(A0_off + 72) );
      A2 = _mm_load_ps( MMCAST(A0_off + 144) );
      A3 = _mm_load_ps( MMCAST(A0_off + 216) );
      B0 = _mm_load_ps( MMCAST(B0_off) );
      c0_0 = B0;
      c0_0 = _mm_mul_ps( A0, c0_0 );
      c0_1 = B0;
      c0_1 = _mm_mul_ps( A1, c0_1 );
      c0_2 = B0;
      c0_2 = _mm_mul_ps( A2, c0_2 );
      c0_3 = B0;
      c0_3 = _mm_mul_ps( A3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 72) );
      c1_0 = B1;
      c1_0 = _mm_mul_ps( A0, c1_0 );
      c1_1 = B1;
      c1_1 = _mm_mul_ps( A1, c1_1 );
      c1_2 = B1;
      c1_2 = _mm_mul_ps( A2, c1_2 );
      c1_3 = B1;
      c1_3 = _mm_mul_ps( A3, c1_3 );
      
      /* K_Unrolling: 4 */
      A0 = _mm_load_ps( MMCAST(A0_off + 4) );
      A1 = _mm_load_ps( MMCAST(A0_off + 76) );
      A2 = _mm_load_ps( MMCAST(A0_off + 148) );
      A3 = _mm_load_ps( MMCAST(A0_off + 220) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 4) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 76) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 8 */
      A0 = _mm_load_ps( MMCAST(A0_off + 8) );
      A1 = _mm_load_ps( MMCAST(A0_off + 80) );
      A2 = _mm_load_ps( MMCAST(A0_off + 152) );
      A3 = _mm_load_ps( MMCAST(A0_off + 224) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 8) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 80) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 0,PF_READONLY, PF_DEF);
      /* K_Unrolling: 12 */
      A0 = _mm_load_ps( MMCAST(A0_off + 12) );
      A1 = _mm_load_ps( MMCAST(A0_off + 84) );
      A2 = _mm_load_ps( MMCAST(A0_off + 156) );
      A3 = _mm_load_ps( MMCAST(A0_off + 228) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 12) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 84) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 16 */
      A0 = _mm_load_ps( MMCAST(A0_off + 16) );
      A1 = _mm_load_ps( MMCAST(A0_off + 88) );
      A2 = _mm_load_ps( MMCAST(A0_off + 160) );
      A3 = _mm_load_ps( MMCAST(A0_off + 232) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 16) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 88) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 28,PF_READONLY, PF_DEF);
      /* K_Unrolling: 20 */
      A0 = _mm_load_ps( MMCAST(A0_off + 20) );
      A1 = _mm_load_ps( MMCAST(A0_off + 92) );
      A2 = _mm_load_ps( MMCAST(A0_off + 164) );
      A3 = _mm_load_ps( MMCAST(A0_off + 236) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 20) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 92) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 24 */
      A0 = _mm_load_ps( MMCAST(A0_off + 24) );
      A1 = _mm_load_ps( MMCAST(A0_off + 96) );
      A2 = _mm_load_ps( MMCAST(A0_off + 168) );
      A3 = _mm_load_ps( MMCAST(A0_off + 240) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 24) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 96) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 56,PF_READONLY, PF_DEF);
      /* K_Unrolling: 28 */
      A0 = _mm_load_ps( MMCAST(A0_off + 28) );
      A1 = _mm_load_ps( MMCAST(A0_off + 100) );
      A2 = _mm_load_ps( MMCAST(A0_off + 172) );
      A3 = _mm_load_ps( MMCAST(A0_off + 244) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 28) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 100) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 32 */
      A0 = _mm_load_ps( MMCAST(A0_off + 32) );
      A1 = _mm_load_ps( MMCAST(A0_off + 104) );
      A2 = _mm_load_ps( MMCAST(A0_off + 176) );
      A3 = _mm_load_ps( MMCAST(A0_off + 248) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 32) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 104) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 84,PF_READONLY, PF_DEF);
      /* K_Unrolling: 36 */
      A0 = _mm_load_ps( MMCAST(A0_off + 36) );
      A1 = _mm_load_ps( MMCAST(A0_off + 108) );
      A2 = _mm_load_ps( MMCAST(A0_off + 180) );
      A3 = _mm_load_ps( MMCAST(A0_off + 252) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 36) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 108) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + 0 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 40 */
      A0 = _mm_load_ps( MMCAST(A0_off + 40) );
      A1 = _mm_load_ps( MMCAST(A0_off + 112) );
      A2 = _mm_load_ps( MMCAST(A0_off + 184) );
      A3 = _mm_load_ps( MMCAST(A0_off + 256) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 40) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 112) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      __builtin_prefetch( prefetchB + -4 + 112,PF_READONLY, PF_DEF);
      /* K_Unrolling: 44 */
      A0 = _mm_load_ps( MMCAST(A0_off + 44) );
      A1 = _mm_load_ps( MMCAST(A0_off + 116) );
      A2 = _mm_load_ps( MMCAST(A0_off + 188) );
      A3 = _mm_load_ps( MMCAST(A0_off + 260) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 44) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 116) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 48 */
      A0 = _mm_load_ps( MMCAST(A0_off + 48) );
      A1 = _mm_load_ps( MMCAST(A0_off + 120) );
      A2 = _mm_load_ps( MMCAST(A0_off + 192) );
      A3 = _mm_load_ps( MMCAST(A0_off + 264) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 48) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 120) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 52 */
      A0 = _mm_load_ps( MMCAST(A0_off + 52) );
      A1 = _mm_load_ps( MMCAST(A0_off + 124) );
      A2 = _mm_load_ps( MMCAST(A0_off + 196) );
      A3 = _mm_load_ps( MMCAST(A0_off + 268) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 52) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 124) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 56 */
      A0 = _mm_load_ps( MMCAST(A0_off + 56) );
      A1 = _mm_load_ps( MMCAST(A0_off + 128) );
      A2 = _mm_load_ps( MMCAST(A0_off + 200) );
      A3 = _mm_load_ps( MMCAST(A0_off + 272) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 56) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 128) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 60 */
      A0 = _mm_load_ps( MMCAST(A0_off + 60) );
      A1 = _mm_load_ps( MMCAST(A0_off + 132) );
      A2 = _mm_load_ps( MMCAST(A0_off + 204) );
      A3 = _mm_load_ps( MMCAST(A0_off + 276) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 60) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 132) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 64 */
      A0 = _mm_load_ps( MMCAST(A0_off + 64) );
      A1 = _mm_load_ps( MMCAST(A0_off + 136) );
      A2 = _mm_load_ps( MMCAST(A0_off + 208) );
      A3 = _mm_load_ps( MMCAST(A0_off + 280) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 64) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 136) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      /* K_Unrolling: 68 */
      A0 = _mm_load_ps( MMCAST(A0_off + 68) );
      A1 = _mm_load_ps( MMCAST(A0_off + 140) );
      A2 = _mm_load_ps( MMCAST(A0_off + 212) );
      A3 = _mm_load_ps( MMCAST(A0_off + 284) );
      
      B0 = _mm_load_ps( MMCAST(B0_off + 68) );
      a0 = A0;
      a0 = _mm_mul_ps( B0, a0 );
      c0_0 = _mm_add_ps( a0, c0_0 );
      a1 = A1;
      a1 = _mm_mul_ps( B0, a1 );
      c0_1 = _mm_add_ps( a1, c0_1 );
      a2 = A2;
      a2 = _mm_mul_ps( B0, a2 );
      c0_2 = _mm_add_ps( a2, c0_2 );
      a3 = A3;
      a3 = _mm_mul_ps( B0, a3 );
      c0_3 = _mm_add_ps( a3, c0_3 );
      
      B1 = _mm_load_ps( MMCAST(B0_off + 140) );
      A0 = _mm_mul_ps( B1, A0 );
      c1_0 = _mm_add_ps( A0, c1_0 );
      A1 = _mm_mul_ps( B1, A1 );
      c1_1 = _mm_add_ps( A1, c1_1 );
      A2 = _mm_mul_ps( B1, A2 );
      c1_2 = _mm_add_ps( A2, c1_2 );
      A3 = _mm_mul_ps( B1, A3 );
      c1_3 = _mm_add_ps( A3, c1_3 );
      prefetchB += J_UNROLL*KB*4;
      /* Single Scalar Compression */
      c0_0 = _mm_hadd_ps( c0_0, c0_1 );
      c0_2 = _mm_hadd_ps( c0_2, c0_3 );
      c0_0 = _mm_hadd_ps( c0_0, c0_2 );
      
      c1_0 = _mm_hadd_ps( c1_0, c1_1 );
      c1_2 = _mm_hadd_ps( c1_2, c1_3 );
      c1_0 = _mm_hadd_ps( c1_0, c1_2 );
      
      /* Applying Beta */
         /* Apply Beta Factor */
         /* Load C from memory */
         bc0_0 = _mm_loadu_ps( cPtrI0+0 );
         /* Load C from memory */
         bc1_0 = _mm_loadu_ps( cPtrI1+0 );
         /* C = (beta*C) + (matrix multiply) */
         c0_0 = _mm_add_ps( bc0_0, c0_0 );
         c1_0 = _mm_add_ps( bc1_0, c1_0 );
      /* Move pointers to next iteration */  
      A0_off += unroll_a;
      
      /* Store results back to memory  */
      _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
      _mm_storeu_ps( MMCAST( cPtrI1 ),  MMCASTStoreintrin( c1_0 ) );
      cPtrI0 += I_UNROLL;
      cPtrI1 += I_UNROLL;
      

      B0_off += J_UNROLL*KB;
      cPtr += J_UNROLL*ldc_bytes;
   } /* End j/NB loop */
   /* End of generated inner loops */
}
#endif
