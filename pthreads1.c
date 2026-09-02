#include "header.h"

typedef struct ArgsPthreads1 {
    double* vertical_positions;
    double* horizontal_positions;
    double normalize;
    int** matrix;
    int num_interactions;
    int width;
    int height;
    int start;
    int end;
    char* output;
} ArgsPthreads1;

void *pthreads1_calculate_matrix(void* args_void) {
    ArgsPthreads1* args = (ArgsPthreads1*) args_void;

    int rows = args->end - args->start;
    size_t buffer_size = (size_t)rows * (args->width * 4 + 2) + 1;
    args->output = (char*) malloc(buffer_size * sizeof(char));
    if (args->output == NULL) {
        fprintf(stderr, "Failed malloc for thread output buffer\n");
        exit(EXIT_FAILURE);
    }

    int offset = 0;

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

            if (j != args->width - 1) {
                offset += sprintf(args->output + offset, "%d ", normalized_cont);
            } else {
                offset += sprintf(args->output + offset, "%d", normalized_cont);
            }
        }
        if (i != args->height - 1) {
            offset += sprintf(args->output + offset, "\n");
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

    ArgsPthreads1* array_args = (ArgsPthreads1*)malloc(num_threads * sizeof(ArgsPthreads1));
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
        ArgsPthreads1 args;
        args.vertical_positions = vertical_positions;
        args.horizontal_positions = horizontal_positions;
        args.normalize = normalize;
        args.matrix = matrix;
        args.num_interactions = num_interactions;
        args.width = width;
        args.height = height;
        args.start = (int)(i * exec_per_thread);
        
        if (i == num_threads-1 && (int)((i+1) * exec_per_thread) < (i+1) * exec_per_thread) {
            args.end = height;
            
        }else {
            args.end = (int)((i+1) * exec_per_thread);
        }
        array_args[i] = args;

        if (pthread_create(&array_ids[i], NULL, pthreads1_calculate_matrix, (void*)&array_args[i]) != 0) {
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

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(time_file, "Pthreads1: %fs\n", elapsed_time);

    fclose(time_file);

    for (int i = 0; i < num_threads; i++) {
        fprintf(file, "%s", array_args[i].output);
        free(array_args[i].output);
    }

    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);

    free(array_args);
    free(array_ids);
    free(vertical_positions);
    free(horizontal_positions);

    fclose(file);
}