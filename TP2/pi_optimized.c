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
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    end = omp_get_wtime();
    printf("pi = %.15f, time = %.3f seconds\n", pi, end - start);

}