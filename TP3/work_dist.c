#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int N = 1000000;
    float A[N];
    float sum, max, sd;

    for(int i=0; i<N; i++) {
        A[i] = (double)rand() / (double)(RAND_MAX - 1);
    }

    double start, end;
    start = omp_get_wtime();

    #pragma omp parallel sections
    {

        #pragma omp section
        {
            sum = 0.0;
            for(int i=0; i<N; i++) {
                sum += A[i];
            }

        }

        #pragma omp section
        {
            max = A[0];
            for(int i=1; i<N; i++) {
                if(A[i] > max) {
                    max = A[i];
                }
            }
        }

        #pragma omp section
        {
            float mean = sum / N;
            sd = 0.0;
            for(int i=0; i<N; i++) {
                sd += (A[i] - mean) * (A[i] - mean);
            }
            sd = sqrt(sd / N);
        }

    }

    end = omp_get_wtime();
    printf("Time = %.6f seconds\n", end - start);

    printf("Sum: %f\n", sum);
    printf("Max: %f\n", max);
    printf("Standard Deviation: %f\n", sd);

    return 0;

}