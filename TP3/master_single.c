#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int N = 200;
    double A[N][N];
    double sum = 0.0;

    double start, end;
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp master
        {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    A[i][j] = (double)rand() / (double)(RAND_MAX - 1);
                }
            }
        }

        #pragma omp single
        {
            printf("Matrix A:\n");
            for (int i = 0; i < 10; i++) { // I printed only the first 10x10 elements for visibility
                for (int j = 0; j < 10; j++) {
                    printf("%f ", A[i][j]);
                }
                printf("\n");
            }
        }

        #pragma omp for reduction(+:sum)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sum += A[i][j];
            }
        }
    }

    end = omp_get_wtime();
    printf("Time = %.6f seconds\n", end - start);

    printf("Sum of all elements in matrix A: %f\n", sum);
    return 0;
}