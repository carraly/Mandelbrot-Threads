#include "header.h"

void check_start_errors(int argc, char *argv[], int *width, int *height, int *num_interactions, int *num_threads) {
    if (argc != 5) {
        fprintf(stderr, "Unexpected amount of arguments: expected 4");
        exit(EXIT_FAILURE);
    }

    char *end;

    errno = 0;
    long temp_width = strtol(argv[1], &end, 10);

    if (errno == ERANGE || temp_width > INT_MAX || temp_width < INT_MIN) {
        fprintf(stderr, "Width value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[1]) {
        fprintf(stderr, "Width conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*end != '\0') {
        fprintf(stderr, "Width conversion to integer failed partially");
        exit(EXIT_FAILURE);

    }else if (*width < 1) {
        fprintf(stderr, "Invalid width: should be higher than 0");
        exit(EXIT_FAILURE);
    }
    *width = (int)temp_width;

    errno = 0;
    long temp_height = strtol(argv[2], &end, 10);

    if (errno == ERANGE || temp_height > INT_MAX || temp_height < INT_MIN) {
        fprintf(stderr, "Height value out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[2]) {
        fprintf(stderr, "Height conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*end != '\0') {
        fprintf(stderr, "Width conversion to integer failed partially");
        exit(EXIT_FAILURE);

    }else if (*height < 1) {
        fprintf(stderr, "Invalid height: should be higher than 0");
        exit(EXIT_FAILURE);
    }
    *height = temp_height;

    errno = 0;
    long temp_num_interactions = strtol(argv[3], &end, 10);

    if (errno == ERANGE || temp_num_interactions > INT_MAX || temp_num_interactions < INT_MIN) {
        fprintf(stderr, "Amount of interactions out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[3]) {
        fprintf(stderr, "Amount of interactions conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*end != '\0') {
        fprintf(stderr, "Width conversion to integer failed partially");
        exit(EXIT_FAILURE);

    }else if (*num_interactions < 1) {
        fprintf(stderr, "Invalid amount of interactions: should be higher than 0");
        exit(EXIT_FAILURE);
    }
    *num_interactions = temp_num_interactions;

    errno = 0;
    long temp_num_threads = strtol(argv[4], &end, 10);

    if (errno == ERANGE || temp_num_interactions > INT_MAX || temp_num_interactions < INT_MIN) {
        fprintf(stderr, "Amount of threads out of range for integer type");
        exit(EXIT_FAILURE);

    }else if (end == argv[4]) {
        fprintf(stderr, "Amount of threads conversion to integer failed");
        exit(EXIT_FAILURE);

    }else if (*end != '\0') {
        fprintf(stderr, "Width conversion to integer failed partially");
        exit(EXIT_FAILURE);

    }else if (*num_threads < 1) {
        fprintf(stderr, "Invalid amount of threads: should be higher than 0");
        exit(EXIT_FAILURE);
    }
    *num_threads = temp_num_threads;
}