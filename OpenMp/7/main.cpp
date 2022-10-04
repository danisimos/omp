#include <iostream>
#include <omp.h>
#include <time.h>

int main() {
    int a[12], b[12], c[12];

    srand(time(NULL));

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for schedule(static, 4)
        for (int i = 0; i < 12; i++) {
            a[i] = i * 100;
            b[i] = i * 100;
            printf("Thread #%d a[%d] = %d, b[%d] = %d\n", omp_get_thread_num(), i, a[i], i, b[i]);
        }
    }

    printf("\n----------------\n");

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for schedule(dynamic, 2)
        for (int i = 0; i < 12; i++) {
            c[i] = a[i] + b[i];
            printf("Thread #%d c[%d] = %d\n", omp_get_thread_num(), i, c[i]);
        }
    }

    bool isCorrect = true;
    for(int i = 0; i < 12; i++) {
        isCorrect &= c[i] == a[i] + b[i];
    }

    printf("%d", isCorrect);
}