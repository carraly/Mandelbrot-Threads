#include "header.h"

void mandelbrot_serial(int width, int height, int num_interactions) {
    struct timespec start, end;

    double *vertical_positions = (double*) malloc(height * sizeof(double));

    if (vertical_positions == NULL) {
        fprintf(stderr, "Vertical positions malloc failed\n");
        exit(EXIT_FAILURE);
    }
    double increment = (TOP_LIMIT-BOTTOM_LIMIT)/(height);
    for (int i = 0; i < height; i++) {
        vertical_positions[i] = TOP_LIMIT - (i * increment);
    }
    
    double *horizontal_positions = (double*) malloc(width * sizeof(double));

    if (horizontal_positions == NULL) {
        fprintf(stderr, "Horizontal positions malloc failed\n");
        exit(EXIT_FAILURE);
    }
    increment = (RIGHT_LIMIT-LEFT_LIMIT)/(width);
    for (int i = 0; i < width; i++) {
        horizontal_positions[i] = LEFT_LIMIT + (i * increment);
    }
    
    FILE* file = fopen("mandelbrot_vchlm_serial.pgm", "w");
    
    if (file == NULL) {
        fprintf(stderr, "Fail opening file\n");
        exit(EXIT_FAILURE);
    }

    FILE* time_file = fopen("times.txt", "a");
    
    if (time_file == NULL) {
        fprintf(stderr, "Fail opening file\n");
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);


    int **matrix = (int**) malloc(height * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Matrix rows malloc failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < height; i++) {
        matrix[i] = (int*) malloc(width * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Matrix column %d malloc failed\n", i);
            exit(EXIT_FAILURE);
        }
    }

    double normalize = 255.0 / num_interactions;
    
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
    fprintf(time_file, "Serial: %fs\n", elapsed_time);

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