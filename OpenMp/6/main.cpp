#include <iostream>
#include <omp.h>
#include <time.h>

int main() {
    int a[100];
    double for_average = 0, reduction_average = 0;

    srand(time(NULL));
    for(int i = 0; i < 100; i++) {
        a[i] = i + 1;
    }

    #pragma omp parallel for
    for(int i = 0; i < 100; i++)
    {
        for_average += (a[i] / 100.0);
        printf("Thread #%d average= %f\n", omp_get_thread_num(), for_average);
    }

    printf("average = %f\n", for_average);
    printf("---------------------\n");

    #pragma omp parallel for reduction(+ : reduction_average)
    for(int i = 0; i < 100; i++)
    {
        reduction_average += (a[i] / 100.0);
        printf("Thread #%d average= %f\n", omp_get_thread_num(), reduction_average);
    }

    printf("average = %f\n", reduction_average);
    printf("---------------------\n");

    printf("for_average = %f, reduction_average = %f", for_average, reduction_average);

    return EXIT_SUCCESS;
}