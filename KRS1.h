#ifndef KRS1_H
#define KRS1_H

#define MAX_MAHASISWA 100
#define MAX_KRS_PER_MHS 15
#define MAX_LEN_NAMA 100
#define MAX_LEN_NIM 25
#define MAX_LEN_MK 100
#define MAX_LEN_KODE 20

typedef struct {
    char kode_mk[MAX_LEN_KODE];
    char nama_mk[MAX_LEN_MK];
    int sks; /* Bobot SKS pada KRS */
} MataKuliahKRS;

typedef struct {
    char nama[MAX_LEN_NAMA];
    char nim[MAX_LEN_NIM];
    MataKuliahKRS krs[MAX_KRS_PER_MHS];
    int jumlah_krs;
} Mahasiswa;

typedef struct {
    Mahasiswa data[MAX_MAHASISWA];
    int jumlah_mahasiswa;
} DashboardKRS;

/* Inisialisasi & data awal contoh */
void init_dashboard(DashboardKRS *db);
void muat_data_contoh(DashboardKRS *db);

/* Operasi utama dashboard */
int cari_index_mahasiswa(const DashboardKRS *db, const char *nim);
int tambah_data_krs(DashboardKRS *db, const char *nama, const char *nim,
                    const char *kode_mk, const char *nama_mk, int sks);
int hitung_total_sks(const Mahasiswa *mhs);
void tampilkan_dashboard(const DashboardKRS *db);
void tampilkan_detail_nim(const DashboardKRS *db, const char *nim);

/* Utilitas input */
void bersihkan_newline(char *str);
void bersihkan_buffer_stdin(void);

#endif /* DASHBOARD_H */