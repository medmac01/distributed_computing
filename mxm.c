#include "stdio.h" 
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

void mxm_unoptimized(int n, double a[n][n], double b[n][n], double c[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n ; j++) 
            for (int k = 0; k < n ; k++)
                c[i][j] += a[i][k]* b[k][j];
}

void mxm_optimized(int n, double a[n][n], double b[n][n], double c[n][n]) {
    // I used the transpose of matrix b to improve cache access
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n ; k++) 
            for (int j = 0; j < n ; j++)
                c[i][j] += a[i][k]* b[k][j];
}

void mxm_blocked(int n, double a[n][n], double b[n][n], double c[n][n], int block_size) {
    
    for (int i = 0; i < n; i += block_size)
        for (int j = 0; j < n; j += block_size)
            for (int k = 0; k < n; k += block_size)
                // Process block
                for (int ii = i; ii < min(i + block_size, n); ii++)
                    for (int jj = j; jj < min(j + block_size, n); jj++) {
                        double sum = c[ii][jj];
                        for (int kk = k; kk < min(k + block_size, n); kk++)
                            sum += a[ii][kk] * b[kk][jj];
                        c[ii][jj] = sum;
                    }
}

int main() {

    int n = 500;
    double a[n][n], b[n][n], c[n][n];
    
    // Initialize matrices a and b
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = 1.0; 
            b[i][j] = 1.0;
            c[i][j] = 0.0; 
        }
        
    double rate, msec, start, end;

    start = (double)clock() / CLOCKS_PER_SEC;
    mxm_unoptimized(n, a, b, c);
    end = (double)clock() / CLOCKS_PER_SEC;

    msec = (end - start) * 1000.0; // Time in milliseconds
    rate = sizeof(double) * n * n * n * (1000.0 / msec) / (1024 * 1024);
    printf("Unoptimized matrix multiplication\n");
    printf("time␣(msec),␣rate␣(MB/s)\n");
    printf("%f,␣%f\n", msec, rate);

    // Print only a subset of the result matrix c
    // printf("Result matrix c (subset):\n");

    // for (int i = 0; i < n && i < 2; i++) {
    //     for (int j = 0; j < n && j < 2; j++) {
    //         printf("%f ", c[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("\n\n");

    // Reset matrix c
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            c[i][j] = 0.0; 
        }


    start = (double)clock() / CLOCKS_PER_SEC;
    mxm_optimized(n, a, b, c);
    end = (double)clock() / CLOCKS_PER_SEC;
    msec = (end - start) * 1000.0; // Time in milliseconds
    rate = sizeof(double) * n * n * n * (1000.0 / msec) / (1024 * 1024);
    printf("Optimized matrix multiplication\n");
    printf("time␣(msec),␣rate␣(MB/s)\n");
    printf("%f,␣%f\n", msec, rate); 
    printf("\n\n");

    // Print only a subset of the result matrix c
    // printf("Result matrix c (subset):\n");
    // for (int i = 0; i < n && i < 2; i++) {
    //     for (int j = 0; j < n && j < 2; j++) {
    //         printf("%f ", c[i][j]);
    //     }
    //     printf("\n");
    // }




    for(int block_size = 16; block_size <= n; block_size *= 2) {
        // Reset matrix c
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                c[i][j] = 0.0; 
        }

        // Blocked matrix multiplication
        start = (double)clock() / CLOCKS_PER_SEC;
        mxm_blocked(n, a, b, c, block_size);
        end = (double)clock() / CLOCKS_PER_SEC;
        msec = (end - start) * 1000.0; // Time in milliseconds
        rate = sizeof(double) * n * n * n * (1000.0 / msec) / (1024 * 1024);
        printf("_____________________________\n");
        printf("Blocked matrix multiplication with block size %d\n", block_size);
        printf("time␣(msec),␣rate␣(MB/s)\n");
        printf("%f,␣%f\n", msec, rate);
        printf("\n\n");
    }

    return 0;
}
