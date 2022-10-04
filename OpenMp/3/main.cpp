#include <iostream>
#include <omp.h>

int main() {
    int a = 5, b = 6;

    printf("a before = %d, b before = %d\n", a, b);
    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        a = 5;
        a+=5;
        b+=6;
        printf("Thread #%d of %d;  a= %d, b= %d\n", omp_get_thread_num(), omp_get_num_threads(), a, b);
    }
    printf("a after = %d, b after = %d\n", a, b);

    printf("--------------------------\n");

    printf("a before = %d, b before = %d\n", a, b);
    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        b = 6;
        a-=5;
        b-=6;
        printf("Thread #%d of %d; a=%d, b=%d\n", omp_get_thread_num(), omp_get_num_threads(), a, b);
    }
    printf("a after = %d, b after = %d\n", a, b);

    return EXIT_SUCCESS;
}