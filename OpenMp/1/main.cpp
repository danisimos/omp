#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello world! from Thread #%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    printf("--------------------------\n");

    #pragma omp parallel num_threads(16)
    {
        printf("Hello world! from Thread #%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return EXIT_SUCCESS;
}