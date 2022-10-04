#include <iostream>
#include <chrono>

int main() {
    int a[16000];
    double b[16000];
    using namespace std::chrono;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    int chunk = 2000;

    for (int i = 0; i < 16000; i++) {
        a[i] = i;
    }
    steady_clock::time_point t1 = steady_clock::now();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(static, chunk)
        for (int i = 1; i < 15999; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
        }
    }
    steady_clock::time_point t2 = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    printf("(static, %d)  - %f\n", chunk, time_span.count());

    t1 = steady_clock::now();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(dynamic, chunk)
        for (int i = 1; i < 15999; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
        }
    }
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("(dynamic, %d) - %f\n", chunk, time_span.count());

    t1 = steady_clock::now();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(guided, chunk)
        for (int i = 1; i < 15999; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
        }
    }
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("(guided, %d)  - %f\n", chunk, time_span.count());

    t1 = steady_clock::now();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(auto)
        for (int i = 1; i < 15999; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0;
        }
    }
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("(auto)       - %f\n", time_span.count());
}