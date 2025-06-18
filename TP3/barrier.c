#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    long num_steps;
    double step, x, sum = 0.0;

    double start, end;
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Enter a number of steps for pi calculation: ");
            scanf("%ld", &num_steps);
            step = 1.0 / (double)num_steps;
        }
        
        start = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum)

        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }

        end = omp_get_wtime();
        #pragma omp barrier

        #pragma omp single
        {
            double pi = step * sum;
            printf("pi = %.15f\n", pi);
            printf("Time = %.6f seconds\n", end - start);
        }
    }
}