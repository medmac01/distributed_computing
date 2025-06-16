#include "stdio.h" 
#include "stdlib.h"
#include "time.h"

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
                c[i][j] += a[i][k]* b[j][k];
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

    // Transpose matrix b
    double bT[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            bT[j][i] = b[i][j];

    start = (double)clock() / CLOCKS_PER_SEC;
    mxm_optimized(n, a, bT, c);
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


    return 0;
}
