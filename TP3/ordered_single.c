#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int counter = 0;

    #pragma omp parallel
    {
        for(int i = 0; i < omp_get_num_threads(); i++) {
            #pragma omp single
            {
                printf("Thread %d generated value %d\n", omp_get_thread_num(), counter);
                counter++;
            }
        }
    }
}