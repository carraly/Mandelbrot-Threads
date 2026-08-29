#include "header.h"

int main(int argc, char *argv[]) {
    int width, height, num_interactions, num_threads;

    check_start_errors(argc, argv, &width, &height, &num_interactions, &num_threads);

    mandelbrot_serial(width, height, num_interactions);
    mandelbrot_openmp(width, height, num_interactions, num_threads);
    mandelbrot_pthreads1(width, height, num_interactions, num_threads);
    //mandelbrot_pthreads2(width, height, num_interactions, num_threads);
}