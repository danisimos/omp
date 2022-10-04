#include <iostream>
#include <omp.h>
#include <time.h>

int main() {
    int a[10], b[10];

    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        a[i] = rand();
        b[i] = rand();
        printf("a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
    }

    int mina = a[0], maxb = b[0];

    #pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num() == 0) {
            for(int i = 0; i < 10; i++) {
                if(a[i] < mina) mina = a[i];
            }

            printf("Thread #%d of %d: min of a[] = %d\n", omp_get_thread_num(), omp_get_num_threads(), mina);
        }

        if(omp_get_thread_num() == 1)
        {
            for(int i = 0; i < 10; i++) {
                if(b[i] > maxb) maxb = b[i];
            }
            printf("Thread #%d of %d: max of b[] = %d\n", omp_get_thread_num(), omp_get_num_threads(), maxb);
        }
    }

    return EXIT_SUCCESS;
}