#include "header.h"

void mandelbrot_openmp(int width, int height, int num_interactions, int num_threads) {
    struct timespec start, end;

    double *vertical_positions = (double*) malloc(height * sizeof(double));
    double *horizontal_positions = (double*) malloc(width * sizeof(double));
    
    define_positions(vertical_positions, horizontal_positions, width, height);
    
    FILE* file = fopen("mandelbrot_vchlm_openmp.pgm", "w");
    
    check_file_errors(file);

    FILE* time_file = fopen("times.txt", "a");
    
    check_file_errors(time_file);

    clock_gettime(CLOCK_MONOTONIC, &start);


    int **matrix = (int**) malloc(height * sizeof(int*));
    allocate_matrix(matrix, width, height);

    double normalize = 255.0 / num_interactions;
    
    omp_set_num_threads(num_threads);
    #pragma omp parallel for shared(matrix) schedule(dynamic)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cont = 0;
            double c_real = horizontal_positions[j];
            double c_imag = vertical_positions[i];
            double z_real = 0.0;
            double z_imag = 0.0;

            while (cont < num_interactions && ((z_real * z_real) + (z_imag * z_imag)) <= 4) {
                double temp_real = ((z_real * z_real) - (z_imag * z_imag)) + c_real;
                z_imag = (2 * z_real * z_imag) + c_imag;
                z_real = temp_real;
                cont++;
            }
            int normalized_cont = (int)(cont * normalize + 0.001); // 0.001 para compensar falha de soma
            matrix[i][j] = normalized_cont;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(time_file, "OpenMP: %fs\n", elapsed_time);

    fclose(time_file);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j != width-1) {
                fprintf(file, "%d ", matrix[i][j]);
            }else {
                fprintf(file, "%d", matrix[i][j]);
            }
        }
        free(matrix[i]);
        if (i != height-1) {
            fprintf(file, "\n");
        }
    }
    free(matrix);
    free(vertical_positions);
    free(horizontal_positions);

    fclose(file);
}