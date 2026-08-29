#include "header.h"

typedef struct ArgsPthreads {
    double* vertical_positions;
    double* horizontal_positions;
    double normalize;
    int** matrix;
    int num_interactions;
    int width;
    int start;
    int end;
} ArgsPthreads;

void *threads_calculate_matrix(void* args_void) {
    ArgsPthreads* args = (ArgsPthreads*) args_void;
    for (int i = args->start; i < args->end; i++) {
        for (int j = 0; j < args->width; j++) {
            int cont = 0;
            double c_real = args->horizontal_positions[j];
            double c_imag = args->vertical_positions[i];
            double z_real = 0.0;
            double z_imag = 0.0;

            while (cont < args->num_interactions && ((z_real * z_real) + (z_imag * z_imag)) <= 4) {
                double temp_real = ((z_real * z_real) - (z_imag * z_imag)) + c_real;
                z_imag = (2 * z_real * z_imag) + c_imag;
                z_real = temp_real;
                cont++;
            }
            int normalized_cont = (int)(cont * args->normalize + 0.001); // 0.001 para compensar falha de soma
            args->matrix[i][j] = normalized_cont;
        }
    }
    return (void*)args;
}

void mandelbrot_pthreads1(int width, int height, int num_interactions, int num_threads) {
    struct timespec start, end;

    double *vertical_positions = (double*) malloc(height * sizeof(double));
    double *horizontal_positions = (double*) malloc(width * sizeof(double));
    
    define_positions(vertical_positions, horizontal_positions, width, height);
    
    FILE* file = fopen("mandelbrot_vchlm_pthreads1.pgm", "w");
    
    check_file_errors(file);

    FILE* time_file = fopen("times.txt", "a");
    
    check_file_errors(time_file);

    clock_gettime(CLOCK_MONOTONIC, &start);


    int **matrix = (int**) malloc(height * sizeof(int*));
    allocate_matrix(matrix, width, height);

    double normalize = 255.0 / num_interactions;
    double exec_per_thread = (double)height / num_threads;

    for (int i = 0; i < num_threads; i++) {
        ArgsPthreads args;
        args.vertical_positions = vertical_positions;
        args.horizontal_positions = horizontal_positions;
        args.normalize = normalize;
        args.matrix = matrix;
        args.num_interactions = num_interactions;
        args.width = width;
        args.start = (int)(i * exec_per_thread);

        if (i == num_threads-1 && (int)((i+1) * exec_per_thread) < (i+1) * exec_per_thread) {
            args.end = height;

        }else {
            args.end = (int)((i+1) * exec_per_thread);
        }
        threads_calculate_matrix(&args);
    }



    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(time_file, "Phreads1: %fs\n", elapsed_time);

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