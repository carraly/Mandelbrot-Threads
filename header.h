#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void check_start_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads);
void mandelbrot_serial(int width, int height, int num_interactions);
void mandelbrot_openmp(int width, int height, int num_interactions, int num_threads);
void mandelbrot_pthreads1(int width, int height, int num_interactions, int num_threads);
void mandelbrot_pthreads2(int width, int height, int num_interactions, int num_threads);

#endif