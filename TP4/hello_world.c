#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello World from process %d of %d\n", rank, size);

    if(rank == 0) 
        printf("Total number of processes: %d\n", size);

    MPI_Finalize();
    return 0;
}