#include <iostream>
#include <chrono>

int main() {
    int a[30];
    int count;

    srand(time(NULL));
    for(int i = 0; i < 30; i++) {
        a[i] = rand() / 100;
    }

#pragma omp parallel for num_threads(6)

        for(int i = 0; i < 30; i++) {
            if (a[i] % 9 == 0) {
                #pragma omp atomic
                count = count + 1;

            }
        }

    printf("count  - %d", count);
}
