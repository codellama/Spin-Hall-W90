#ifndef ATLAS_SMVT_L2_H
#define ATLAS_SMVT_L2_H

#include "atlas_type.h"

#ifndef ATL_MVKERN_DEF
   #define ATL_MVKERN_DEF
   typedef void (*ATL_mvkern_t)
      (ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);

#endif
void ATL_smvtk__900006(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);
void ATL_smvtk__900006_b0(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);
void ATL_smvtk__2(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);
void ATL_smvtk__2_b0(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);
void ATL_smvtk__900005(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);
void ATL_smvtk__900005_b0(ATL_CINT, ATL_CINT, const float*, ATL_CINT, const float*, float*);

static ATL_mvkern_t ATL_GetMVTKern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    ATL_mvkern_t *mvk_b0, 
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 4)
         {
            if (M >= 16)
            {
               *minM = 16;   *minN = 4;
               *mu = 16;     *nu = 4;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 24576;
               *mvk_b0 = ATL_smvtk__900006_b0;
               return(ATL_smvtk__900006);
            } /* end if on minimal N guard */
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
   {
      *minM = 0;   *minN = 0;
      *mu = 8;     *nu = 4;
      *alignX = 4;  *alignY = 16;
      *ALIGNX2A = 1;
      *FNU = 0;
      *CacheElts = 24576;
      *mvk_b0 = ATL_smvtk__2_b0;
      return(ATL_smvtk__2);
   } /* end if on lda multiple restriction */
   *minM = 16;   *minN = 4;
   *mu = 16;     *nu = 4;
   *alignX = 16;  *alignY = 16;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 24576;
   *mvk_b0 = ATL_smvtk__900005_b0;
   return(ATL_smvtk__900005);
}

#define ATL_GetPartMVT(A_, lda_, mb_, nb_) { *(mb_) = 2448; *(nb_) = 4; }

#endif  /* end protection around header file contents */
