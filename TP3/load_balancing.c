#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int n = 500;
    double a[n][n], b[n][n], c[n][n];
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp task
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    c[i][j] = 0.0; 
                }
                
        }
        

        #pragma omp task
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    a[i][j] = (double)rand(); 
                    b[i][j] = (double)rand();
                }

        }

        #pragma omp taskwait
        {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        c[i][j] += a[i][k] * b[k][j];
                        c[i][j] *= c[i][j]; 
                    }
                }
            }
        }
    }
    end = omp_get_wtime();
    printf("Time %.10f seconds.\n", end - start);
}