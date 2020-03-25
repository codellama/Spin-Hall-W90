#ifndef ATLAS_DR2_L2_H
#define ATLAS_DR2_L2_H

#include "atlas_type.h"

typedef void (*ATL_r2kern_t)
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);
void ATL_dger2k__900007
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);

static ATL_r2kern_t ATL_GetR2Kern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   *minM = 8;   *minN = 3;
   *mu = 8;     *nu = 3;
   *alignX = 16;  *alignY = 16;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 30720;
   return(ATL_dger2k__900007);
}

#define ATL_GetPartR2(A_, lda_, mb_, nb_) { (mb_) = 3832; (nb_) = 3; }

#endif  /* end protection around header file contents */
