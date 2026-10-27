#include <stdio.h>

#define N 4

int main() {
    // Matriks A ukuran 4x4
    double A[N][N] = {
        {1.0, 2.0, 3.0, 4.0},  // a00, a01, a02, a03
        {5.0, 6.0, 7.0, 8.0},  // a10, a11, a12, a13
        {9.0, 1.0, 2.0, 3.0},  // a20, a21, a22, a23
        {4.0, 5.0, 6.0, 7.0}   // a30, a31, a32, a33
    };

    // Vektor x ukuran 4x1
    double x[N] = {1.0, 2.0, 3.0, 4.0}; // x0, x1, x2, x3

    // Vektor y untuk menampung hasil perkalian C = A * x
    double y[N] = {0.0};

    // Proses perkalian matriks A dengan vektor x
    for (int i = 0; i < N; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    // Menampilkan hasil
    printf("Hasil perkalian matriks A * x:\n");
    for (int i = 0; i < N; i++) {
        printf("y[%d] = %.2f\n", i, y[i]);
    }

    return 0;
}