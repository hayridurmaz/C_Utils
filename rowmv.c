#include "utils.h"

#define MATSIZE 2000

static size_t totalMemUsage = 0;

int main(int argc, char *argv[])
{
    // Global declerations
    size_t i, j;
    MPI_Status status;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int taskid;
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if (argc != 2)
    {
        if (taskid == 0)
            printf("Usage: %s <N>\n", argv[0]);
        MPI_Finalize();
        return 0;
    }
    int n = atoi(argv[1]);

    double *a = allocarray1D(n * n);
    double *b = allocarray1D(n);
    double *x = allocarray1D(n);
    double *xseq = allocarray1D(n);

    if (a == NULL || b == NULL || x == NULL || xseq == NULL)
    {
        if (taskid == 0)
            printf("Allocation failed\n");
        MPI_Finalize();
        return 0;
    }

    fullfillArrayWithRandomNumbers(a, n * n);
    fullfillArrayWithRandomNumbers(b, n);
    if (taskid == 0)
    {
        printf("A:\n");
        print_2d_arr(a, n, n);
        printf("b:\n");
        print_1d_arr(b, n);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double time_start = MPI_Wtime();
    // TODO: scatter matrix A
    ParallelRowMatrixVectorMultiply(n, a, b, x, MPI_COMM_WORLD);
    double time_end = MPI_Wtime();
    double time = time_end - time_start;

    SequentialMatrixMultiply(n, a, b, xseq);
    // check difference between x and xseq using OpenMP
    double time_start_openmp = omp_get_wtime();
    //TODO: Use, openmp parallel
    //#pragma omp parallel
    double time_end_openmp = omp_get_wtime();
    double time_openmp = time_end_openmp - time_start_openmp;
    // print matrix size, number of processors, number of threads, time, time_openmp, L2 norm of difference of x and xseq (use %.12e while printing norm)

    MPI_Finalize();
    return 0;
}
