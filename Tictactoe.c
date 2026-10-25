#include <stdio.h>
#include <stdlib.h>

// Deklarasi papan permainan 3x3
char board[3][3];

// Fungsi untuk menginisialisasi papan dengan angka 1-9
void initBoard() {
    char count = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = count++;
        }
    }
}

// Fungsi untuk menampilkan tampilan papan di layar
void displayBoard() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Bersihkan layar di Windows
    #else
        system("clear"); // Bersihkan layar di Linux/macOS
    #endif

    printf("\n=============================\n");
    printf("   GAME TIC-TAC-TOE (2 PLAYER) \n");
    printf("=============================\n\n");
    printf(" Player 1 : X\n");
    printf(" Player 2 : O\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n\n");
}

// Fungsi untuk memeriksa apakah ada pemain yang menang
// Mengembalikan 1 jika ada pemenang, 0 jika belum ada
int checkWin() {
    // Cek Baris dan Kolom
    for (int i = 0; i < 3; i++) {
        // Cek Baris
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        // Cek Kolom
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    // Cek Diagonal (Utama dan Samping)
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0; // Belum ada yang menang
}

// Fungsi untuk menandai papan berdasarkan pilihan pemain
int makeMove(int choice, char mark) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    // Cek apakah kotak yang dipilih valid dan belum diisi oleh 'X' atau 'O'
    if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = mark;
        return 1; // Pilihan valid
    } else {
        return 0; // Pilihan tidak valid
    }
}

int main() {
    int player = 1;
    int totalMoves = 0;
    int choice;
    int validMove;
    char mark;

    initBoard();

    do {
        displayBoard();
        player = (player % 2 != 0) ? 1 : 2; // Menentukan giliran (Player 1 / 2)
        mark = (player == 1) ? 'X' : 'O';

        printf(" Player %d (%c), masukkan nomor kotak (1-9): ", player, mark);
        
        // Memastikan input berupa angka
        if (scanf("%d", &choice) != 1) {
            // Clear buffer jika input bukan angka
            while (getchar() != '\n');
            printf("Input tidak valid! Tekan Enter untuk mencoba lagi...");
            getchar();
            continue;
        }

        // Lakukan pengisian kotak
        validMove = makeMove(choice, mark);

        if (!validMove) {
            printf("Langkah tidak valid atau kotak sudah terisi! Tekan Enter untuk mencoba lagi...");
            while (getchar() != '\n'); // Clear buffer
            getchar();
        } else {
            totalMoves++;
            
            // Cek kondisi menang
            if (checkWin()) {
                displayBoard();
                printf("=============================\n");
                printf("  SELAMAT! PLAYER %d (%c) MENANG!\n", player, mark);
                printf("=============================\n");
                return 0;
            }
            
            // Berpindah ke player berikutnya
            player++;
        }

    } while (totalMoves < 9);

    // Jika 9 langkah selesai dan tidak ada yang menang
    displayBoard();
    printf("=============================\n");
    printf("      PERMAINAN SERI (DRAW)! \n");
    printf("=============================\n");

    return 0;
}