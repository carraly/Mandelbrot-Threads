#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 5) {
        printf("Unexpected amount of arguments: expected 4");
        return EXIT_FAILURE;
    }else if (*argv[1] < 1) {
        printf("Invalid width: should be higher than 0");
        return EXIT_FAILURE;
    }else if (*argv[2] < 1) {
        printf("Invalid height: should be higher than 0");
        return EXIT_FAILURE;
    }else if (*argv[3] < 1) {
        printf("Invalid amount of interactions: should be higher than 0");
        return EXIT_FAILURE;
    }else if (*argv[4] < 1) {
        printf("Invalid amount of threads: should be higher than 0");
        return EXIT_FAILURE;
    }

    
}