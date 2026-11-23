#include "KRS1.h"

// Helper untuk membersihkan buffer input terminal
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==========================================
// 1. CREATE (TAMBAH DATA)
// ==========================================
void tambah_mhs(node_mhs *head, char *nama, char *nim) {
    node_mhs new_node = (node_mhs)malloc(sizeof(struct Mahasiswa));
    strcpy(new_node->nama, nama);
    strcpy(new_node->nim, nim);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_mhs temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    printf(">> Data mahasiswa berhasil ditambahkan!\n");
}

void tambah_mk(node_mk *head, char *matkul, char *kode_matkul, int sks) {
    node_mk new_node = (node_mk)malloc(sizeof(struct MataKuliah));
    strcpy(new_node->matkul, matkul);
    strcpy(new_node->kode_matkul, kode_matkul);
    new_node->sks = sks;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_mk temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    printf(">> Data mata kuliah berhasil ditambahkan!\n");
}

void tambah_krs(node_krs *head, char *kode_matkul, char *nim) {
    node_krs new_node = (node_krs)malloc(sizeof(struct KRS));
    strcpy(new_node->kode_matkul, kode_matkul);
    strcpy(new_node->nim, nim);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_krs temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    printf(">> Data KRS berhasil ditambahkan!\n");
}

// ==========================================
// 2. READ (TAMPILKAN DATA)
// ==========================================
void tampilkan_mhs(node_mhs head) {
    if (head == NULL) {
        printf(">> Data mahasiswa kosong.\n");
        return;
    }
    printf("\n=== DAFTAR MAHASISWA ===\n");
    while (head != NULL) {
        printf("NIM  : %s | Nama : %s\n", head->nim, head->nama);
        head = head->next;
    }
}

void tampilkan_mk(node_mk head) {
    if (head == NULL) {
        printf(">> Data mata kuliah kosong.\n");
        return;
    }
    printf("\n=== DAFTAR MATA KULIAH ===\n");
    while (head != NULL) {
        printf("Kode : %s | Matkul : %s (%d SKS)\n", head->kode_matkul, head->matkul, head->sks);
        head = head->next;
    }
}

void tampilkan_krs(node_krs head) {
    if (head == NULL) {
        printf(">> Data KRS kosong.\n");
        return;
    }
    printf("\n=== DAFTAR KRS ===\n");
    while (head != NULL) {
        printf("NIM : %s | Kode Matkul : %s\n", head->nim, head->kode_matkul);
        head = head->next;
    }
}

// ==========================================
// 3. UPDATE (UBAH DATA)
// ==========================================
void ubah_mhs(node_mhs head, char *nim_cari) {
    while (head != NULL) {
        if (strcmp(head->nim, nim_cari) == 0) {
            printf("Masukkan Nama Baru: ");
            fgets(head->nama, sizeof(head->nama), stdin);
            head->nama[strcspn(head->nama, "\n")] = 0;
            printf(">> Data mahasiswa berhasil diperbarui!\n");
            return;
        }
        head = head->next;
    }
    printf(">> NIM %s tidak ditemukan.\n", nim_cari);
}

void ubah_mk(node_mk head, char *kode_cari) {
    while (head != NULL) {
        if (strcmp(head->kode_matkul, kode_cari) == 0) {
            printf("Masukkan Nama Mata Kuliah Baru: ");
            fgets(head->matkul, sizeof(head->matkul), stdin);
            head->matkul[strcspn(head->matkul, "\n")] = 0;
            printf("Masukkan Jumlah SKS Baru      : ");
            scanf("%d", &head->sks);
            clear_buffer();
            printf(">> Data mata kuliah berhasil diperbarui!\n");
            return;
        }
        head = head->next;
    }
    printf(">> Kode Matkul %s tidak ditemukan.\n", kode_cari);
}

void ubah_krs(node_krs head, char *nim_cari, char *kode_lama) {
    while (head != NULL) {
        if (strcmp(head->nim, nim_cari) == 0 && strcmp(head->kode_matkul, kode_lama) == 0) {
            printf("Masukkan Kode Mata Kuliah Baru: ");
            fgets(head->kode_matkul, sizeof(head->kode_matkul), stdin);
            head->kode_matkul[strcspn(head->kode_matkul, "\n")] = 0;
            printf(">> Data KRS berhasil diperbarui!\n");
            return;
        }
        head = head->next;
    }
    printf(">> Data KRS tidak ditemukan.\n");
}

// ==========================================
// 4. DELETE (HAPUS DATA)
// ==========================================
void hapus_mhs(node_mhs *head, char *nim_hapus) {
    node_mhs temp = *head, prev = NULL;
    if (temp != NULL && strcmp(temp->nim, nim_hapus) == 0) {
        *head = temp->next;
        free(temp);
        printf(">> Data mahasiswa berhasil dihapus!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->nim, nim_hapus) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(">> NIM %s tidak ditemukan.\n", nim_hapus);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf(">> Data mahasiswa berhasil dihapus!\n");
}

void hapus_mk(node_mk *head, char *kode_hapus) {
    node_mk temp = *head, prev = NULL;
    if (temp != NULL && strcmp(temp->kode_matkul, kode_hapus) == 0) {
        *head = temp->next;
        free(temp);
        printf(">> Data mata kuliah berhasil dihapus!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->kode_matkul, kode_hapus) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(">> Kode Matkul %s tidak ditemukan.\n", kode_hapus);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf(">> Data mata kuliah berhasil dihapus!\n");
}

void hapus_krs(node_krs *head, char *nim_hapus, char *kode_hapus) {
    node_krs temp = *head, prev = NULL;
    if (temp != NULL && strcmp(temp->nim, nim_hapus) == 0 && strcmp(temp->kode_matkul, kode_hapus) == 0) {
        *head = temp->next;
        free(temp);
        printf(">> Data KRS berhasil dihapus!\n");
        return;
    }
    while (temp != NULL && !(strcmp(temp->nim, nim_hapus) == 0 && strcmp(temp->kode_matkul, kode_hapus) == 0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(">> Data KRS tidak ditemukan.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf(">> Data KRS berhasil dihapus!\n");
}

// ==========================================
// MAIN MENU INTERAKTIF TERMINAL
// ==========================================
int main() {
    node_mhs daftar_mhs = NULL;
    node_mk daftar_mk = NULL;
    node_krs daftar_krs = NULL;

    int menu_utama, pilihan_crud, sks;
    char nama[50], nim[10], matkul[50], kode[10], kode_lama[10];

    do {
        printf("\n==============================\n");
        printf("   SISTEM DATABASE AKADEMIK   \n");
        printf("==============================\n");
        printf("1. Kelola Data Mahasiswa\n");
        printf("2. Kelola Data Mata Kuliah\n");
        printf("3. Kelola Data KRS\n");
        printf("0. Keluar\n");
        printf("Pilih tabel (0-3): ");
        scanf("%d", &menu_utama);
        clear_buffer();

        if (menu_utama == 0) break;
        if (menu_utama < 1 || menu_utama > 3) {
            printf(">> Pilihan tidak valid!\n");
            continue;
        }

        printf("\n--- OPERASI CRUD ---\n");
        printf("1. Tambah Data (Create)\n");
        printf("2. Tampilkan Data (Read)\n");
        printf("3. Ubah Data (Update)\n");
        printf("4. Hapus Data (Delete)\n");
        printf("Pilih aksi (1-4): ");
        scanf("%d", &pilihan_crud);
        clear_buffer();

        // KELOLA MAHASISWA
        if (menu_utama == 1) {
            if (pilihan_crud == 1) {
                printf("Masukkan Nama Mahasiswa : ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;
                printf("Masukkan NIM            : ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                tambah_mhs(&daftar_mhs, nama, nim);
            } else if (pilihan_crud == 2) {
                tampilkan_mhs(daftar_mhs);
            } else if (pilihan_crud == 3) {
                printf("Masukkan NIM yang ingin diubah: ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                ubah_mhs(daftar_mhs, nim);
            } else if (pilihan_crud == 4) {
                printf("Masukkan NIM yang ingin dihapus: ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                hapus_mhs(&daftar_mhs, nim);
            }
        }
        // KELOLA MATA KULIAH
        else if (menu_utama == 2) {
            if (pilihan_crud == 1) {
                printf("Masukkan Nama Mata Kuliah : ");
                fgets(matkul, sizeof(matkul), stdin);
                matkul[strcspn(matkul, "\n")] = 0;
                printf("Masukkan Kode Matkul      : ");
                fgets(kode, sizeof(kode), stdin);
                kode[strcspn(kode, "\n")] = 0;
                printf("Masukkan Jumlah SKS       : ");
                scanf("%d", &sks);
                clear_buffer();
                tambah_mk(&daftar_mk, matkul, kode, sks);
            } else if (pilihan_crud == 2) {
                tampilkan_mk(daftar_mk);
            } else if (pilihan_crud == 3) {
                printf("Masukkan Kode Matkul yang ingin diubah: ");
                fgets(kode, sizeof(kode), stdin);
                kode[strcspn(kode, "\n")] = 0;
                ubah_mk(daftar_mk, kode);
            } else if (pilihan_crud == 4) {
                printf("Masukkan Kode Matkul yang ingin dihapus: ");
                fgets(kode, sizeof(kode), stdin);
                kode[strcspn(kode, "\n")] = 0;
                hapus_mk(&daftar_mk, kode);
            }
        }
        // KELOLA KRS
        else if (menu_utama == 3) {
            if (pilihan_crud == 1) {
                printf("Masukkan NIM Mahasiswa : ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                printf("Masukkan Kode Matkul   : ");
                fgets(kode, sizeof(kode), stdin);
                kode[strcspn(kode, "\n")] = 0;
                tambah_krs(&daftar_krs, kode, nim);
            } else if (pilihan_crud == 2) {
                tampilkan_krs(daftar_krs);
            } else if (pilihan_crud == 3) {
                printf("Masukkan NIM pada KRS         : ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                printf("Masukkan Kode Matkul Lama   : ");
                fgets(kode_lama, sizeof(kode_lama), stdin);
                kode_lama[strcspn(kode_lama, "\n")] = 0;
                ubah_krs(daftar_krs, nim, kode_lama);
            } else if (pilihan_crud == 4) {
                printf("Masukkan NIM yang ingin dihapus         : ");
                fgets(nim, sizeof(nim), stdin);
                nim[strcspn(nim, "\n")] = 0;
                printf("Masukkan Kode Matkul yang ingin dihapus : ");
                fgets(kode, sizeof(kode), stdin);
                kode[strcspn(kode, "\n")] = 0;
                hapus_krs(&daftar_krs, nim, kode);
            }
        }
    } while (menu_utama != 0);

    printf("Program selesai.\n");
    return 0;
}