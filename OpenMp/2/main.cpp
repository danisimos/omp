#include <iostream>
#include <omp.h>

int main() {
    int k;

    printf("Enter threads num in 1 section\n");
    std::cin >> k;

    #pragma omp parallel if(k > 3) num_threads(k)
    if(omp_in_parallel())
    {
        printf("Thread #%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    else
    {
        printf("single");
    }

    printf("Enter threads num in 2 section\n");
    std::cin >> k;

    #pragma omp parallel if(k > 2) num_threads(k)
    if(omp_in_parallel())
    {
        printf("Thread #%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    else
    {
        printf("single");
    }

    return EXIT_SUCCESS;
}
