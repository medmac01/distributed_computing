#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>


void matrixVectorMult(double* A, double* b, double* x, int size) {
    for (int i = 0; i < size; ++i) {
        x[i] = 0.0;
        for (int j = 0; j < size; ++j) {
            x[i] += A[i * size + j] * b[j];
        }
    }
}

int main(int argc, char* argv[]) {

    
    if (argc != 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("Matrix size must be positive.\n");
        return 1;
    }

    double* A = malloc(size * size * sizeof(double));
    double* b = malloc(size * sizeof(double));
    double* x_serial = malloc(size * sizeof(double));

    int rank, size;
    int data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {

        if (!A || !b || !x_serial) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        srand48(42);

        // Fill A[0][:100] with random values
        int limit = (size < 100) ? size : 100;
        for (int j = 0; j < limit; ++j) {
            A[0 * size + j] = drand48();
        }

        // Copy A[0][:100] into A[1][100:200] if possible
        if (size > 1 && size > 100) {
            int copy_len = (size - 100 < 100) ? (size - 100) : 100;
            for (int j = 0; j < copy_len; ++j) {
                A[1 * size + (100 + j)] = A[0 * size + j];
            }
        }

        // Set diagonal
        for (int i = 0; i < size; ++i) {
            A[i * size + i] = drand48();
        }

        // Fill vector b
        for (int i = 0; i < size; ++i) {
            b[i] = drand48();
        }

        MPI_Send()

    }

    if (rank == 1) {
        
    }

    // Compute x_serial = A * b manually
    matrixVectorMult(A, b, x_serial, size);

    /*
    // Compare both results
    double max_error = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = fabs(x_parallel[i] - x_serial[i]);
        if (diff > max_error) {
            max_error = diff;
        }
    }
    printf("Maximum difference between Parallel and serial result: %e\n", max_error);
    */

    free(A);
    free(b);
    free(x_serial);
    return 0;
}