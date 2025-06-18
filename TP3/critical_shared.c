#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int counter = 0;

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        // #pragma omp atomic
        //     counter++;

        #pragma omp critical
        {
            counter++;
        }

        printf("Thread %d incremented counter to %d\n", omp_get_thread_num(), counter);
        
    }
    end = omp_get_wtime();

    printf("Final counter value: %d\n", counter);
    printf("Time taken: %.10f seconds\n", end - start);
    return 0;
}