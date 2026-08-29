#include "header.h"

void mandelbrot_serial(int width, int height, int num_interactions) {
    struct timespec start, end;

    // Trocar por lista dinâmica dps
    double vertical_positions[height];
    double increment = (TOP_LIMIT-BOTTOM_LIMIT)/(height);
    for (int i = 0; i < height; i++) {
        vertical_positions[i] = TOP_LIMIT - (i * increment);
    }
    
    double horizontal_positions[width];
    increment = (RIGHT_LIMIT-LEFT_LIMIT)/(width);
    for (int i = 0; i < width; i++) {
        horizontal_positions[i] = LEFT_LIMIT + (i * increment);
    }
    
    FILE* file = fopen("mandelbrot_login_serial.pgm", "w");
    
    if (file == NULL) {
        fprintf(stderr, "Fail opening file");
        exit(EXIT_FAILURE);
    }

    FILE* time_file = fopen("times.txt", "w");
    
    if (time_file == NULL) {
        fprintf(stderr, "Fail opening file");
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

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
            int normalized_cont = (int)(cont * normalize + 0.4); // 0.4 para arredondar para cima
            fprintf(file, "%d ", normalized_cont);
        }
    fprintf(file, "\n");
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(time_file, "Serial: %fs\n", elapsed_time);

    fclose(file);
    fclose(time_file);
}