#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000000; // 백만 번
    int thread_count = 4;
    double total_sum = 0; 
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for schedule(runtime) num_threads(thread_count) reduction(+:total_sum)
    for (int i = 0; i < n; i++) {
        double val = 0;
        for (int j = 0; j < (i / 10000); j++) {
            val += i * 0.0001;
        }
        total_sum += val;
    }

    end_time = omp_get_wtime();

    printf("Scheduling: %s\n", getenv("OMP_SCHEDULE") ? getenv("OMP_SCHEDULE") : "default");
    printf("Result: %f\n", total_sum); // 계산 결과를 사용함으로써 최적화 삭제 방지
    printf("Total Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}