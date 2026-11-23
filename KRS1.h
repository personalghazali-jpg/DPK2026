#ifndef KRS1_H
#define KRS1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT DATABASE
struct Mahasiswa {
    char nama[50];
    char nim[11];
    struct Mahasiswa *next;
};

struct MataKuliah {
    char matkul[50];
    char kode_matkul[11];
    int sks;
    struct MataKuliah *next;
};

struct KRS {
    char kode_matkul[11];
    char nim[11];
    struct KRS *next;
};

typedef struct MataKuliah *node_mk;
typedef struct Mahasiswa *node_mhs;
typedef struct KRS *node_krs;

// HELPER
void clear_buffer();

// 1. CREATE (TAMBAH DATA)
void tambah_mhs(node_mhs *head, char *nama, char *nim);
void tambah_mk(node_mk *head, char *matkul, char *kode_matkul, int sks);
void tambah_krs(node_krs *head, char *kode_matkul, char *nim);

// 2. READ (TAMPILKAN DATA)
void tampilkan_mhs(node_mhs head);
void tampilkan_mk(node_mk head);
void tampilkan_krs(node_krs head);

// 3. UPDATE (UBAH DATA)
void ubah_mhs(node_mhs head, char *nim_cari);
void ubah_mk(node_mk head, char *kode_cari);
void ubah_krs(node_krs head, char *nim_cari, char *kode_lama);

// 4. DELETE (HAPUS DATA)
void hapus_mhs(node_mhs *head, char *nim_hapus);
void hapus_mk(node_mk *head, char *kode_hapus);
void hapus_krs(node_krs *head, char *nim_hapus, char *kode_hapus);

#endif
