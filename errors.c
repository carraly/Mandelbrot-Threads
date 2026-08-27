#include "header.h"
#include <stdio.h>

void check_start_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads) {
    if (argc != 5) {
        printf(stderr, "Unexpected amount of arguments: expected 4");
        exit(EXIT_FAILURE);
    }

    char *end;

    errno = 0;
    *width = strtol(argv[1], &end, 10);

    if (errno == ERANGE) {
        printf(stderr, "Width value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[1]) {
        printf(stderr, "Width conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*width < 1) {
        printf(stderr, "Invalid width: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *height = strtol(argv[2], &end, 10);

    if (errno == ERANGE) {
        printf(stderr, "Height value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[2]) {
        printf(stderr, "Height conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*height < 1) {
        printf(stderr, "Invalid height: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *num_interactions = strtol(argv[3], &end, 10);

    if (errno == ERANGE) {
        printf(stderr, "Amount of interactions out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[3]) {
        printf(stderr, "Amount of interactions conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*num_interactions < 1) {
        printf(stderr, "Invalid amount of interactions: should be higher than 0");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    *num_threads = strtol(argv[4], &end, 10);

    if (errno == ERANGE) {
        printf(stderr, "Amount of threads out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[4]) {
        printf(stderr, "Amount of threads conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*num_threads < 1) {
        printf(stderr, "Invalid amount of threads: should be higher than 0");
        exit(EXIT_FAILURE);
    }
}