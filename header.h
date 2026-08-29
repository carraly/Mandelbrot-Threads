#ifndef HEADER_H
#define HEADER_H
#define LEFT_LIMIT -2.0
#define RIGHT_LIMIT 1.0
#define TOP_LIMIT 1.5
#define BOTTOM_LIMIT -1.5

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <omp.h>
#include <pthread.h>

// errors.c
void check_start_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads);
void check_file_errors(FILE *file);
void check_matrix_errors(int **matrix);

// math.c
void define_positions(double *vertical_positions, double *horizontal_positions, int width, int height);
void allocate_matrix(int **matrix, int width, int height);

// serial.c
void mandelbrot_serial(int width, int height, int num_interactions);
// openmp.c
void mandelbrot_openmp(int width, int height, int num_interactions, int num_threads);
// pthreads1.c
void mandelbrot_pthreads1(int width, int height, int num_interactions, int num_threads);
// pthreads2.c
void mandelbrot_pthreads2(int width, int height, int num_interactions, int num_threads);

#endif