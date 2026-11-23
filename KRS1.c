#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KRS1.h"

void bersihkan_newline(char *str) {
    if (!str) return;
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void bersihkan_buffer_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* buang sisa karakter di buffer */
    }
}

void init_dashboard(DashboardKRS *db) {
    if (!db) return;
    db->jumlah_mahasiswa = 0;
}

int cari_index_mahasiswa(const DashboardKRS *db, const char *nim) {
    if (!db || !nim) return -1;
    for (int i = 0; i < db->jumlah_mahasiswa; i++) {
        if (strcmp(db->data[i].nim, nim) == 0) {
            return i;
        }
    }
    return -1;
}

int tambah_data_krs(DashboardKRS *db, const char *nama, const char *nim,
                    const char *kode_mk, const char *nama_mk, int sks) {
    if (!db || sks <= 0) return 0;

    int idx = cari_index_mahasiswa(db, nim);

    if (idx == -1) {
        if (db->jumlah_mahasiswa >= MAX_MAHASISWA) {
            printf("[!] Kapasitas maksimum mahasiswa (%d) tercapai.\n", MAX_MAHASISWA);
            return 0;
        }
        idx = db->jumlah_mahasiswa++;
        strncpy(db->data[idx].nama, nama, MAX_LEN_NAMA - 1);
        db->data[idx].nama[MAX_LEN_NAMA - 1] = '\0';

        strncpy(db->data[idx].nim, nim, MAX_LEN_NIM - 1);
        db->data[idx].nim[MAX_LEN_NIM - 1] = '\0';

        db->data[idx].jumlah_krs = 0;
    }

    Mahasiswa *mhs = &db->data[idx];
    if (mhs->jumlah_krs >= MAX_KRS_PER_MHS) {
        printf("[!] KRS mahasiswa %s sudah mencapai batas (%d MK).\n", mhs->nim, MAX_KRS_PER_MHS);
        return 0;
    }

    /* Cegah duplikasi kode mata kuliah pada mahasiswa yang sama */
    for (int j = 0; j < mhs->jumlah_krs; j++) {
        if (strcmp(mhs->krs[j].kode_mk, kode_mk) == 0) {
            printf("[!] Mata kuliah %s sudah ada di KRS %s.\n", kode_mk, mhs->nim);
            return 0;
        }
    }

    MataKuliahKRS *item = &mhs->krs[mhs->jumlah_krs++];
    strncpy(item->kode_mk, kode_mk, MAX_LEN_KODE - 1);
    item->kode_mk[MAX_LEN_KODE - 1] = '\0';

    strncpy(item->nama_mk, nama_mk, MAX_LEN_MK - 1);
    item->nama_mk[MAX_LEN_MK - 1] = '\0';

    item->sks = sks;
    return 1;
}

int hitung_total_sks(const Mahasiswa *mhs) {
    if (!mhs) return 0;
    int total = 0;
    for (int i = 0; i < mhs->jumlah_krs; i++) {
        total += mhs->krs[i].sks;
    }
    return total;
}

void tampilkan_dashboard(const DashboardKRS *db) {
    printf("\n==========================================================================================\n");
    printf("                     DASHBOARD DATA MAHASISWA & KARTU RENCANA STUDI (KRS)\n");
    printf("==========================================================================================\n");

    if (!db || db->jumlah_mahasiswa == 0) {
        printf("Belum ada data tersimpan.\n");
        printf("==========================================================================================\n");
        return;
    }

    int total_entri_krs = 0;
    int total_seluruh_sks = 0;

    printf("%-14s | %-20s | %-10s | %-24s | %-8s\n",
           "NIM", "Nama Mahasiswa", "Kode MK", "Mata Kuliah", "KRS(SKS)");
    printf("---------------+----------------------+------------+--------------------------+---------\n");

    for (int i = 0; i < db->jumlah_mahasiswa; i++) {
        const Mahasiswa *mhs = &db->data[i];
        int sks_mhs = hitung_total_sks(mhs);
        total_seluruh_sks += sks_mhs;

        if (mhs->jumlah_krs == 0) {
            printf("%-14s | %-20s | %-10s | %-24s | %-8s\n",
                   mhs->nim, mhs->nama, "-", "Belum mengambil KRS", "0 SKS");
        } else {
            for (int j = 0; j < mhs->jumlah_krs; j++) {
                total_entri_krs++;
                char sks_label[16];
                snprintf(sks_label, sizeof(sks_label), "%d SKS", mhs->krs[j].sks);

                if (j == 0) {
                    printf("%-14s | %-20s | %-10s | %-24s | %-8s\n",
                           mhs->nim, mhs->nama, mhs->krs[j].kode_mk, mhs->krs[j].nama_mk, sks_label);
                } else {
                    printf("%-14s | %-20s | %-10s | %-24s | %-8s\n",
                           "", "", mhs->krs[j].kode_mk, mhs->krs[j].nama_mk, sks_label);
                }
            }
            printf("  -> Total KRS %s (%s): %d SKS\n", mhs->nim, mhs->nama, sks_mhs);
            printf("---------------+----------------------+------------+--------------------------+---------\n");
        }
    }

    printf("Ringkasan Dashboard: %d Mahasiswa | %d Item KRS | %d Total SKS\n",
           db->jumlah_mahasiswa, total_entri_krs, total_seluruh_sks);
    printf("==========================================================================================\n");
}

void tampilkan_detail_nim(const DashboardKRS *db, const char *nim) {
    int idx = cari_index_mahasiswa(db, nim);
    if (idx == -1) {
        printf("\n[!] Data mahasiswa dengan NIM '%s' tidak ditemukan.\n", nim);
        return;
    }

    const Mahasiswa *mhs = &db->data[idx];
    printf("\n--- DETAIL KRS MAHASISWA ---\n");
    printf("Nama Mahasiswa : %s\n", mhs->nama);
    printf("NIM            : %s\n", mhs->nim);
    printf("Daftar KRS     :\n");

    if (mhs->jumlah_krs == 0) {
        printf("  (Kosong)\n");
    } else {
        for (int i = 0; i < mhs->jumlah_krs; i++) {
            printf("  %d. [%s] %s (%d SKS)\n",
                   i + 1, mhs->krs[i].kode_mk, mhs->krs[i].nama_mk, mhs->krs[i].sks);
        }
    }
    printf("Total KRS      : %d SKS\n", hitung_total_sks(mhs));
    printf("----------------------------\n");
}

int main(void) {
    DashboardKRS db;
    init_dashboard(&db);
    /* Fungsi muat_data_contoh(&db) sudah dihapus agar data dimulai dari kosong */

    int pilihan = 0;
    do {
        printf("\n=== MENU DASHBOARD AKADEMIK ===\n");
        printf("1. Tampilkan Dashboard KRS\n");
        printf("2. Tambah Data Mahasiswa & KRS\n");
        printf("3. Cari Mahasiswa berdasarkan NIM\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("[!] Input harus berupa angka.\n");
            bersihkan_buffer_stdin();
            continue;
        }
        bersihkan_buffer_stdin();

        if (pilihan == 1) {
            tampilkan_dashboard(&db);
        } else if (pilihan == 2) {
            char nama[MAX_LEN_NAMA], nim[MAX_LEN_NIM];
            char kode_mk[MAX_LEN_KODE], nama_mk[MAX_LEN_MK];
            int sks = 0;

            printf("Nama Mahasiswa  : ");
            fgets(nama, sizeof(nama), stdin);
            bersihkan_newline(nama);

            printf("NIM             : ");
            fgets(nim, sizeof(nim), stdin);
            bersihkan_newline(nim);

            printf("Kode Mata Kuliah: ");
            fgets(kode_mk, sizeof(kode_mk), stdin);
            bersihkan_newline(kode_mk);

            printf("Mata Kuliah     : ");
            fgets(nama_mk, sizeof(nama_mk), stdin);
            bersihkan_newline(nama_mk);

            printf("KRS (jumlah SKS): ");
            if (scanf("%d", &sks) != 1) {
                printf("[!] Input SKS tidak valid.\n");
                bersihkan_buffer_stdin();
                continue;
            }
            bersihkan_buffer_stdin();

            if (tambah_data_krs(&db, nama, nim, kode_mk, nama_mk, sks)) {
                printf("[OK] Data KRS berhasil ditambahkan.\n");
            }
        } else if (pilihan == 3) {
            char nim_cari[MAX_LEN_NIM];
            printf("Masukkan NIM yang dicari: ");
            fgets(nim_cari, sizeof(nim_cari), stdin);
            bersihkan_newline(nim_cari);
            tampilkan_detail_nim(&db, nim_cari);
        } else if (pilihan == 0) {
            printf("Keluar dari program. Sampai jumpa!\n");
        } else {
            printf("[!] Pilihan tidak tersedia.\n");
        }
    } while (pilihan != 0);

    return 0;
}