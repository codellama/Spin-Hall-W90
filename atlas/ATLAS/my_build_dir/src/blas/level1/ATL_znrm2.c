#include "atlas_misc.h"

TYPE ATL_znrm2_xp0yp0aXbX(const int, const TYPE*, const int);
TYPE Mjoin(PATLU,nrm2)(const int, const TYPE*, const int);

TYPE ATL_dznrm2(const int N, const TYPE *X, const int incX)
{
   int incx;

   if (N > 0)
   {
      if (incX > 0) incx = incX;
      else if (incX < 0)
      {
         X += ((N-1)SHIFT) * incX;
         incx = -incX;
      }
      else return(ATL_rzero);
      if (incx==1) return(Mjoin(PATLU,nrm2)(N<<1, X, 1));
      return(ATL_znrm2_xp0yp0aXbX(N, X, incx));
   }
   return(ATL_rzero);
}
