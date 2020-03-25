#ifndef ATLAS_SR1_L1_H
#define ATLAS_SR1_L1_H

#include "atlas_type.h"

typedef void (*ATL_r1kern_t)
   (ATL_CINT, ATL_CINT, const float*, const float*, float*, ATL_CINT);
void ATL_sgerk__6
   (ATL_CINT, ATL_CINT, const float*, const float*, float*, ATL_CINT);
void ATL_sgerk__900005
   (ATL_CINT, ATL_CINT, const float*, const float*, float*, ATL_CINT);

static ATL_r1kern_t ATL_GetR1Kern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
   {
      *minM = 0;   *minN = 0;
      *mu = 8;     *nu = 4;
      *alignX = 4;  *alignY = 4;
      *ALIGNX2A = 1;
      *FNU = 0;
      *CacheElts = 6881;
      return(ATL_sgerk__6);
   } /* end if on lda multiple restriction */
   *minM = 16;   *minN = 4;
   *mu = 16;     *nu = 4;
   *alignX = 16;  *alignY = 16;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 6881;
   return(ATL_sgerk__900005);
}

#define ATL_GetPartR1(A_, lda_, mb_, nb_) { (mb_) = 672; (nb_) = 4; }

#endif  /* end protection around header file contents */
