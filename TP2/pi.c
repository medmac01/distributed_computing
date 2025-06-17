#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

static long num_steps = 2000000000; double step;

int main () {
    int i; double x, pi, sum = 0.0;
    step = 1.0 / (double) num_steps;
    
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel private(i, x) shared(num_steps, step)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        double local_sum = 0.0;

        for (i = thread_id; i < num_steps; i += num_threads) {
            x = (i + 0.5) * step;
            local_sum = local_sum + 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    pi = step * sum;
    end = omp_get_wtime();
    printf("pi = %.15f, time = %.3f seconds\n", pi, end - start);

}