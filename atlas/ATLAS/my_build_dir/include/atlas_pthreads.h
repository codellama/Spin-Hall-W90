  /* This file generated by /work/03192/priyaj/wannier90-2.0.0/atlas/ATLAS/my_build_dir/..//tune/threads/probe_nthr.c */
#ifndef ATLAS_NTHREADS_H
   #define ATLAS_NTHREADS_H

#include "pthread.h"
   #define ATL_NTHREADS 16
   #define ATL_NTHRPOW2 4
   #ifdef ATL_LAUNCHORDER
       static int ATL_launchorder[16] = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
   #endif

#endif
