#include "header.h"

void check_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads) {
    if (argc != 5) {
        printf("Unexpected amount of arguments: expected 4");
        exit(EXIT_FAILURE);
    }

    char *end;

    errno = 0;
    *width = strtol(argv[1], &end, 10);

    if (errno == ERANGE) {
        printf("Width value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (*end == *argv[1]) {
        printf("Width conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*width < 1) {
        printf("Invalid width: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *height = strtol(argv[2], &end, 10);

    if (errno == ERANGE) {
        printf("Height value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (*end == *argv[2]) {
        printf("Height conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*height < 1) {
        printf("Invalid height: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *num_interactions = strtol(argv[3], &end, 10);

    if (errno == ERANGE) {
        printf("Amount of interactions out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (*end == *argv[3]) {
        printf("Amount of interactions conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*num_interactions < 1) {
        printf("Invalid amount of interactions: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *num_interactions = strtol(argv[4], &end, 10);

    if (errno == ERANGE) {
        printf("Amount of threads out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (*end == *argv[4]) {
        printf("Amount of threads conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*num_threads < 1) {
        printf("Invalid amount of threads: should be higher than 0");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int width, height, num_interactions, num_threads;

    check_errors(argc, argv, &width, &height, &num_interactions, &num_threads);

    mandelbrot_serial(width, height, num_interactions);
    mandelbrot_openmp(width, height, num_interactions, num_threads);
    mandelbrot_pthreads1(width, height, num_interactions, num_threads);
    mandelbrot_pthreads2(width, height, num_interactions, num_threads);
}