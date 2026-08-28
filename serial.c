#include "header.h"

void mandelbrot_serial(int width, int height, int num_interactions) {
    // Trocar por lista dinâmica dps
    double vertical_positions[height];
    double increment = (TOP_LIMIT-BOTTOM_LIMIT)/(height-1);
    for (int i = 0; i < height; i++) {
        if (i == (height-1)) {
            vertical_positions[height-1] = BOTTOM_LIMIT;
        }else {
            vertical_positions[i] = TOP_LIMIT - (i * increment);
        }
    }
    
    double horizontal_positions[width];
    increment = (RIGHT_LIMIT-LEFT_LIMIT)/(width-1);
    for (int i = 0; i < width; i++) {
        if (i == (width-1)) {
            horizontal_positions[width-1] = RIGHT_LIMIT;
        }else {
            horizontal_positions[i] = LEFT_LIMIT + (i * increment);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cont = 0;
            double c = vertical_positions[i] + horizontal_positions[j];
            double z = 0.0;
            while (cont < num_interactions || z > 2) {
                z = (z * z) + c;
                cont++;
            }
        }
    }
}