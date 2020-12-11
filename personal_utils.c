#include "personal_utils.h"

double get_random()
{

    double range = 1000;
    double div = RAND_MAX / range;
    double randomNumber = (rand() / div);
    // printf("%d\n", randomNumber);
    return randomNumber;
}

void print_2d_arr(double *arr, int row, int col)
{
    size_t i, j, index;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            index = i * col + j;
            printf("%3f ", arr[index]);
        }
        printf("\n");
    }
}
void print_1d_arr(double *arr, int row)
{
    size_t i, j;
    for (i = 0; i < row; i++)
    {
        printf("%f, ", arr[i]);
    }
    printf("\n");
}

int **fullfillArrayWithRandomNumbers(double *arr, int n)
{
    /*
    * Fulfilling the array with random numbers 
    * */
    size_t i;
    for (i = 0; i < n; i++)
    {
        arr[i] = get_random();
    }
    return 0;
}

double *allocarray1D(int size)
{
    double *array = (double *)calloc(size, sizeof(double));
    // totalMemUsage += size * sizeof(int);
    return array;
}

int vectors_dot_prod(double *x, double *y, int n)
{
    double res = 0.0;
    size_t i;
    for (i = 0; i < n; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

int vectors_dot_prod2(double *x, double *y, int n)
{
    size_t res = 0.0;
    size_t i = 0;
    for (; i <= n - 4; i += 4)
    {
        res += (x[i] * y[i] +
                x[i + 1] * y[i + 1] +
                x[i + 2] * y[i + 2] +
                x[i + 3] * y[i + 3]);
    }
    for (; i < n; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

void matrix_vector_mult(double **mat, double *vec, double *result, int rows, int cols)
{ // in matrix form: result = mat * vec;
    size_t i;
    for (i = 0; i < rows; i++)
    {
        result[i] = vectors_dot_prod2(mat[i], vec, cols);
    }
}

int SequentialMatrixMultiply(int n, double *a, double *b, double *x)
{
    size_t i, j;
    for (i = 0; i < n; i++)
    {
        x[i] = 0.0;
        for (j = 0; j < n; j++)
        {
            size_t index = i * n + j;
            x[i] += a[index] * b[j];
        }
    }
    return 0;
}

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
}