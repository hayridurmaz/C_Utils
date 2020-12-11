#include "parallel_utils.h"

int ParallelRowMatrixVectorMultiply(int n, double *a, double *b, double *x, MPI_Comm comm)
{
    size_t i, j;
    int nlocal;
    double *fb;
    int npes, myrank;
    MPI_Status status;
    MPI_Comm_size(comm, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    fb = (double *)malloc(n * sizeof(double));
    nlocal = n / npes;
    MPI_Allgather(b, nlocal, MPI_DOUBLE, fb, nlocal, MPI_DOUBLE, comm);
    for (i = 0; i < nlocal; i++)
    {
        x[i] = 0.0;
        for (j = 0; j < n; j++)
        {
            size_t index = i * n + j;
            x[i] += a[index] * fb[j];
        }
    }
    free(fb);
    return 0;