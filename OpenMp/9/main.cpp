#include <iostream>
#include <chrono>

int main() {
    int N = 480;
    int a[N][N];
    int b[N];

    using namespace std::chrono;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    int chunk = 60;

    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = (j+1) * (i+1);

        }
        b[i] = i + 1;
    }

    steady_clock::time_point t1 = steady_clock::now();
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = a[i][j] * b[j];
        }
    }
    steady_clock::time_point t2 = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    printf("single  - %f\n", time_span.count());

    t1 = steady_clock::now();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(dynamic, chunk)
        for (int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                a[i][j] = a[i][j] * b[j];
            }
        }
    }
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);

    printf("(static, %d)  - %f\n", chunk, time_span.count());
}