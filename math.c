#include "header.h"

void define_positions(double *vertical_positions, double *horizontal_positions, int width, int height) {
    if (vertical_positions == NULL) {
        fprintf(stderr, "Vertical positions malloc failed\n");
        exit(EXIT_FAILURE);
    }
    double increment = (TOP_LIMIT-BOTTOM_LIMIT)/(height);
    for (int i = 0; i < height; i++) {
        vertical_positions[i] = TOP_LIMIT - (i * increment);
    }

    if (horizontal_positions == NULL) {
        fprintf(stderr, "Horizontal positions malloc failed\n");
        exit(EXIT_FAILURE);
    }
    increment = (RIGHT_LIMIT-LEFT_LIMIT)/(width);
    for (int i = 0; i < width; i++) {
        horizontal_positions[i] = LEFT_LIMIT + (i * increment);
    }
}

void alocate_matrix(int **matrix, int width, int height) {
    check_matrix_errors(matrix);
    
    for (int i = 0; i < height; i++) {
        matrix[i] = (int*) malloc(width * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Matrix column %d malloc failed\n", i);
            exit(EXIT_FAILURE);
        }
    }
}