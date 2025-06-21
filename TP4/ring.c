#include "stdio.h"
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter data: \n");
        scanf("%d", &data);
        data += rank; 
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process %d sent data: %d to process 1\n", rank, data);
    } else {
        // All other processes wait for rank 0 
        int prev = (rank - 1 + size) % size;
        MPI_Recv(&data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received data: %d from process %d\n", rank, data, prev);
        
        data += rank;
        
        if (rank != size - 1) {
            int next = (rank + 1) % size;
            MPI_Send(&data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            printf("Process %d sent data: %d to process %d\n", rank, data, next);
        } else {
            printf("Process %d has final data: %d\n", rank, data);
        }
    }

    MPI_Finalize();
    return 0;
}