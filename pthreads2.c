#include "header.h"

typedef struct ArgsPthreads2 {
    double* vertical_positions;
    double* horizontal_positions;
    double normalize;
    int** matrix;
    int num_interactions;
    int width;
    int* indexes;
    int amount_indexes;
} ArgsPthreads2;

void *pthreads2_calculate_matrix(void* args_void) {
    ArgsPthreads2* args = (ArgsPthreads2*) args_void;
    for (int i = 0; i < args->amount_indexes; i ++) {
        for (int j = 0; j < args->width; j++) {
            int cont = 0;
            double c_real = args->horizontal_positions[j];
            double c_imag = args->vertical_positions[args->indexes[i]];
            double z_real = 0.0;
            double z_imag = 0.0;

            while (cont < args->num_interactions && ((z_real * z_real) + (z_imag * z_imag)) <= 4) {
                double temp_real = ((z_real * z_real) - (z_imag * z_imag)) + c_real;
                z_imag = (2 * z_real * z_imag) + c_imag;
                z_real = temp_real;
                cont++;
            }
            int normalized_cont = (int)(cont * args->normalize + 0.001); // 0.001 para compensar falha de soma
            args->matrix[args->indexes[i]][j] = normalized_cont;
        }
    }
    free(args->indexes);
    return (void*)args;
}

void mandelbrot_pthreads2(int width, int height, int num_interactions, int num_threads) {
    struct timespec start, end;

    double *vertical_positions = (double*) malloc(height * sizeof(double));
    double *horizontal_positions = (double*) malloc(width * sizeof(double));
    
    define_positions(vertical_positions, horizontal_positions, width, height);
    
    FILE* file = fopen("mandelbrot_vchlm_pthreads2.pgm", "w");
    
    check_file_errors(file);

    FILE* time_file = fopen("times.txt", "a");
    
    check_file_errors(time_file);

    clock_gettime(CLOCK_MONOTONIC, &start);


    int **matrix = (int**) malloc(height * sizeof(int*));
    allocate_matrix(matrix, width, height);

    double normalize = 255.0 / num_interactions;
    int exec_per_thread = height / num_threads;
    int partial = height % num_threads;

    ArgsPthreads2* array_args = (ArgsPthreads2*)malloc(num_threads * sizeof(ArgsPthreads2));
    if (array_args == NULL) {
        fprintf(stderr, "Failed malloc\n");
        exit(EXIT_FAILURE);
    }

    pthread_t* array_ids = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    if (array_ids == NULL) {
        fprintf(stderr, "Failed malloc\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_threads; i++) {
        ArgsPthreads2 args;
        args.vertical_positions = vertical_positions;
        args.horizontal_positions = horizontal_positions;
        args.normalize = normalize;
        args.matrix = matrix;
        args.num_interactions = num_interactions;
        args.width = width;
        if (i < partial) {
            args.amount_indexes = exec_per_thread + 1;
        }else {
            args.amount_indexes = exec_per_thread;
        }
        
        if (args.amount_indexes != 0) {
            args.indexes = (int*) malloc(args.amount_indexes * sizeof(int));
            if (args.indexes == NULL) {
                fprintf(stderr, "Failed malloc\n");
                exit(EXIT_FAILURE);
            }
        }else {
            args.indexes = NULL;
        }

        for (int j = 0; j < args.amount_indexes; j++) {
            if (j == 0) {
                args.indexes[j] = i;
            }else {
                args.indexes[j] = args.indexes[j-1] + num_threads;
            }
        }
        array_args[i] = args;

        if (pthread_create(&array_ids[i], NULL, pthreads2_calculate_matrix, (void*)&array_args[i]) != 0) {
            fprintf(stderr, "Failed creating threads\n");
            exit(EXIT_FAILURE); 
        }
    }

    for (int i = 0; i < num_threads; i++) {
        int ret_value = pthread_join(array_ids[i], NULL);
        if (ret_value != 0) {
            fprintf(stderr, "Failed returning threads\n");
            exit(EXIT_FAILURE); 
        }
    }

    free(array_args);
    free(array_ids);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(time_file, "Pthreads2: %fs\n", elapsed_time);

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