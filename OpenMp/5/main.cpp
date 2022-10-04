#include <iostream>
#include <omp.h>

int main() {
    int a[6][8];

    srand(time(NULL));
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 8; j++) {
            a[i][j] = rand() / 100;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int m;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 8; j++) {
                    m += (a[i][j] / 48);
                }
            }

            printf("Thread #%d of %d: average = %d\n", omp_get_thread_num(), omp_get_num_threads(), m);
        }

        #pragma omp section
        {
            int min, max;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 8; j++) {
                    if(a[i][j] < min) min = a[i][j];
                    if(a[i][j] > max) max = a[i][j];
                }
            }

            printf("Thread #%d of %d: min = %d, max = %d\n", omp_get_thread_num(), omp_get_num_threads(), min, max);
        }

        #pragma omp section
        {
            int count = 0;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 8; j++) {
                    if(a[i][j] % 3 == 0) count++;
                }
            }

            printf("Thread #%d of %d: count of (%3==0) = %d\n", omp_get_thread_num(), omp_get_num_threads(), count);
        }
    };

    return EXIT_SUCCESS;
}