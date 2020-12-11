#ifndef PARALLEL_UTILS_H_INCLUDED
#define PARALLEL_UTILS_H_INCLUDED
#ifndef PERSONAL_UTILS_H_INCLUDED
#define PERSONAL_UTILS_H_INCLUDED
#include "personal_utils.h"
#endif

#include "mpi.h"
#include <omp.h>

int ParallelRowMatrixVectorMultiply(int n, double *a, double *b, double *x, MPI_Comm comm);

#endif