#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int m, n;
    m = n = 1000; // Matrix dimensions

    // Allocate memory dynamically
    double *a = (double *)malloc(m * n * sizeof(double));
    double *b = (double *)malloc(n * m * sizeof(double)); double *c = (double *)malloc(m * m * sizeof(double));
    
    double start, end;
    start = omp_get_wtime();

    # pragma omp parallel for
    // Initialize matrices
    for (int i = 0; i < m; i++) { for (int j = 0; j < n; j++) {
        a[i * n + j] = (i + 1) + (j + 1);
        }
    }

    # pragma omp parallel for
    for (int i = 0; i < n; i++) { for (int j = 0; j < m; j++) {
        b[i * m + j] = (i + 1) - (j + 1);
        }
    }

    # pragma omp parallel for
    for (int i = 0; i < m; i++) { for (int j = 0; j < m; j++) {
        c[i * m + j] = 0;
        }
    }
    
    # pragma omp parallel for
    // Matrix multiplication
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) { for (int k = 0; k < n; k++) {
        c[i * m + j] += a[i * n + k] * b[k * m + j];
        }
        }      
    }

    end = omp_get_wtime();
    printf("Matrix multiplication (%d x %d) time = %.3f seconds\n", m, m, end - start);

    // Free allocated memory
    free(a);
    free(b);
    free(c);

    return 0;
}