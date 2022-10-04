#include <iostream>
#include <chrono>

int main() {
    int a[6][8];
    int min, max;

    srand(time(NULL));
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 8; j++) {
            a[i][j] = rand() / 100;
        }
    }

    #pragma omp parallel num_threads(6)
    {
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 8; j++) {
                #pragma omp critical
                {
                    if(a[i][j] < min) {
                        min = a[i][j];
                    } else if(a[i][j] > max){
                        max = a[i][j];
                    }
                }
            }
        }
    };
    printf("min  - %d, max - %d", min, max);
}