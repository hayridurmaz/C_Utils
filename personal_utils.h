#ifndef PERSONAL_UTILS_H_INCLUDED
#define PERSONAL_UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <omp.h>

double get_random();

void print_2d_arr(double *arr, int row, int col);

void print_1d_arr(double *arr, int row);

int **fullfillArrayWithRandomNumbers(double *arr, int n);

double *allocarray1D(int size);

int vectors_dot_prod(double *x, double *y, int n);

int vectors_dot_prod2(double *x, double *y, int n);

void matrix_vector_mult(double **mat, double *vec, double *result, int rows, int cols);

int SequentialMatrixMultiply(int n, double *a, double *b, double *x);

#endif