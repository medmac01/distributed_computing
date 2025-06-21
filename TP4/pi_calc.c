#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long num_steps = 5000000000;
    double step, x, sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    step = 1.0 / (double)num_steps;

    MPI_Bcast(&step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("Process %d started with step size: %.15f\n", rank, step);

    double start = MPI_Wtime();

    for (int i = rank; i < num_steps; i += size) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    printf("Process %d finished its part with local sum: %.15f\n", rank, sum);

    double local_sum = sum;
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("Process %d reduced its sum to: %.15f\n", rank, local_sum);
    

    if (rank == 0) {
        double pi = step * sum;
        double end = MPI_Wtime();
        printf("pi = %.15f\n", pi);
        printf("Time = %.6f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}