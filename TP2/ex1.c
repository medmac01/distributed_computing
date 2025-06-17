#include "stdio.h"
#ifdef _OPENMP
#include "omp.h"
#endif

int main() {
#ifdef _OPENMP

    static int n_threads;

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("Hello from the thread %d \n", thread_num);
        n_threads = omp_get_num_threads();
    }
    printf("Parallel execution of hello_world with %d threads\n", n_threads);

    #else

    printf("Hello from the main thread\n");
    printf("Parallel execution of hello_world with 1 thread\n");

#endif

    return 0;
}