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

void check_start_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads);
void mandelbrot_serial(int width, int height, int num_interactions);
void mandelbrot_openmp(int width, int height, int num_interactions, int num_threads);
void mandelbrot_pthreads1(int width, int height, int num_interactions, int num_threads);
void mandelbrot_pthreads2(int width, int height, int num_interactions, int num_threads);

#endif