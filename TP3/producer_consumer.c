#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000


void fill_rand(int n, double *A) { for (int i = 0; i < n; i++)
    A[i] = rand() % 100;
}


double Sum_array(int n, double *A) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    return sum;
}


int main() {
    double *A, sum, runtime;
    int flag = 0; // Synchronization flag


    A = (double *)malloc(N * sizeof(double));
    runtime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp sections
        {
            // Producer fills the array
            #pragma omp section
            {
                fill_rand(N, A);
                flag = 1; 
            }
    
            // Consumer computes the sum
            #pragma omp section
            {
                while (flag == 0) {
                    }
                sum = Sum_array(N, A);
                flag = 0; 
            }
        }
        
    }
    runtime = omp_get_wtime() - runtime;
    printf("In %lf seconds, the sum is %lf\n", runtime, sum);
    free(A);
    return 0;
}