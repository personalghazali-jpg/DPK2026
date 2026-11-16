#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Validasi jumlah argumen command line (argv[0] adalah nama program)
    if (argc < 2 || argc > 3) {
        printf("Penggunaan:\n");
        printf("  Array 1D : %s <size>\n", argv[0]);
        printf("  Array 2D : %s <baris> <kolom>\n", argv[0]);
        return 1;
    }

    // KASUS 1: Array Dinamis 1 Dimensi (contoh: array_dyn.exe 5)
    if (argc == 2) {
        int size = atoi(argv[1]);
        if (size <= 0) {
            printf("Error: Ukuran array harus lebih dari 0.\n");
            return 1;
        }

        // Alokasi memori dinamis 1D
        int *array = (int *)malloc(size * sizeof(int));
        if (array == NULL) {
            printf("Gagal mengalokasikan memori!\n");
            return 1;
        }

        // Mengisi nilai contoh ke dalam array
        for (int i = 0; i < size; i++) {
            array[i] = (i + 1) * 10;
        }

        // Menampilkan output sesuai ilustrasi papan tulis
        printf("=== ARRAY DINAMIS 1D (size = %d) ===\n", size);
        printf("array -> ");
        for (int i = 0; i < size; i++) {
            printf("[%d]", array[i]);
        }
        printf("\n");

        // Membebaskan memori
        free(array);
    }
    // KASUS 2: Array Dinamis 2 Dimensi (contoh: array_dyn.exe 5 5)
    else if (argc == 3) {
        int rows = atoi(argv[1]);
        int cols = atoi(argv[2]);
        if (rows <= 0 || cols <= 0) {
            printf("Error: Ukuran baris dan kolom harus lebih dari 0.\n");
            return 1;
        }

        // Alokasi memori untuk array pointer baris (**array)
        int **array = (int **)malloc(rows * sizeof(int *));
        if (array == NULL) {
            printf("Gagal mengalokasikan memori baris!\n");
            return 1;
        }

        // Alokasi memori kolom untuk setiap baris (*array[i])
        for (int i = 0; i < rows; i++) {
            array[i] = (int *)malloc(cols * sizeof(int));
            if (array[i] == NULL) {
                printf("Gagal mengalokasikan memori kolom pada baris %d!\n", i);
                return 1;
            }
        }

        // Mengisi nilai contoh ke dalam array 2D
        int nilai = 1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                array[i][j] = nilai++;
            }
        }

        // Menampilkan output sesuai skema pointer di papan tulis
        printf("=== ARRAY DINAMIS 2D (%d x %d) ===\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            printf("*array[%d] -> ", i);
            for (int j = 0; j < cols; j++) {
                printf("[%2d]", array[i][j]);
            }
            printf("\n");
        }

        // Membebaskan memori tiap baris terlebih dahulu, lalu pointer utama
        for (int i = 0; i < rows; i++) {
            free(array[i]);
        }
        free(array);
    }

    return 0;
}
