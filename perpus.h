#ifndef PERPUS_H
#define PERPUS_H

#include <iostream>
#include <string>
using namespace std;

#define Nil NULL

/* ================= FORWARD DECLARATION ================= */
struct ListPengunjung;
struct ListBuku;
struct ListPeminjam;
struct ListRequest;

/* ================= PENGUNJUNG ================= */
struct daftarPengunjung {
    int idPengunjung;
    string namaPengunjung;
    string waktuKunjungan;
};
typedef daftarPengunjung infoPengunjung;

typedef struct PengunjungElmList *addressPengunjung;
struct PengunjungElmList {
    infoPengunjung info;
    addressPengunjung next;
    addressPengunjung prev;
};

struct ListPengunjung {
    addressPengunjung first;
    addressPengunjung last;
};

// Fungsi Pengunjung
void CreateListPengunjung(ListPengunjung &L);
addressPengunjung alokasiPengunjung(infoPengunjung x);
void insertLastPengunjung(ListPengunjung &L, addressPengunjung P);
void tambahPengunjung(ListPengunjung &LP, bool statusPerpustakaan);
int hitungJumlahPengunjung(ListPengunjung L);
void printListPengunjung(ListPengunjung L);
void resetListPengunjung(ListPengunjung &L);
void hapusPengunjungById(ListPengunjung &L, int idPengunjung);
void setWaktuKunjungan(infoPengunjung &pg);
int generateIdPengunjung(ListPengunjung LP);


/* ================= BUKU ================= */
struct daftarbuku {
    int idBuku;
    string namaBuku;
    string namaPenulis;
    string tahunTerbit;
    int tersedia;
};
typedef daftarbuku infoBuku;

typedef struct BukuElmList *addressBuku;
struct BukuElmList {
    infoBuku info;
    addressBuku next;
    addressBuku prev;
};

struct ListBuku {
    addressBuku first;
    addressBuku last;
};

// Fungsi Buku
void CreateListBuku(ListBuku &L);
addressBuku alokasiBuku(infoBuku x);
void insertLastBuku(ListBuku &L, addressBuku P);
void tambahBuku(ListBuku &LB);
void printInfoBuku(ListBuku L);
void hapusBukuById(ListBuku &L, int idBuku);
void resetListBuku(ListBuku &L);
void searchbyTitle(ListBuku L, string title);
void searchbyAuthor(ListBuku L, string author);
void updateBook(ListBuku &L, int idBuku);
int generateIdBuku(ListBuku LB);
addressBuku findBukuById(ListBuku L, int idBuku);
addressBuku findBukuByNama(ListBuku L, string judulBuku);


/* ================= DAFTAR PEMINJAM ================= */
struct daftarPeminjam {
    int idPeminjam;
    string namaPeminjam;
    int idBuku;
    string infoBuku;
    string tanggalPinjam;
    string tenggatPengembalian;
};

typedef daftarPeminjam infoPeminjam;

typedef struct PeminjamElmList *addressPeminjam;
struct PeminjamElmList {
    infoPeminjam info;
    addressPeminjam next;
    addressPeminjam prev;
};

struct ListPeminjam {
    addressPeminjam first;
    addressPeminjam last;
};

// Fungsi Peminjam
void CreateListPeminjam(ListPeminjam &L);
addressPeminjam alokasiPeminjam(infoPeminjam x);
int generateIdPeminjam(ListPeminjam LPM);
void printInfoPeminjam(ListPeminjam L);
void insertLastPeminjam(ListPeminjam &L, addressPeminjam P);
bool prosesPeminjaman(
    ListPeminjam &LPM,
    ListBuku &LB,
    string namaPeminjam,
    int idBuku
);
bool pinjamLangsung(
    ListPeminjam &LPM,
    ListBuku &LB,
    string namaPeminjam,
    int idBuku
);
addressPeminjam findPeminjamById(ListPeminjam L, int id);
addressPeminjam findPeminjamByNama(ListPeminjam L, string namaPeminjam);
/* ================= DAFTAR REQUEST ================= */
struct daftarRequest {
    int idRequest;
    string namaRequest;
    int idBuku;
    string waktu;
    string tanggal;
};
typedef daftarRequest infoRequest;

typedef struct RequestElmList *addressRequest;
struct RequestElmList {
    infoRequest info;
    addressRequest next;
    addressRequest prev;
};

struct ListRequest {
    addressRequest first;
    addressRequest last;
};

// Fungsi Request
void CreateListRequest(ListRequest &L);
addressRequest alokasiRequest(infoRequest x);
void insertLastRequest(ListRequest &L, addressRequest P);
void tambahRequest(ListRequest &LRQ, ListBuku &L);
int generateIdRequest(ListRequest LRQ);
void printInfoRequest(ListRequest L);
addressRequest findRequestById(ListRequest L, int id);
addressRequest findRequestByNama(ListRequest L, string nama);
void hapusRequestById(ListRequest &L, int idRequest);
void hapusRequestByAdr(ListRequest &L, addressRequest P);
void printSatuTiket(addressRequest P);
void cekTiket(ListRequest &L, string nama);

/* ================= PEMINJAMAN (INSERT) ================= */
void insertLastPeminjam(ListPeminjam &L, addressPeminjam P);
/* ================= PEMINJAMAN (DELETE) ================= */
void hapusPeminjamById(ListPeminjam &L, ListBuku &LB, int idPeminjam);
/* ================= PEMINJAMAN (ACC REQUEST) ================= */
void accRequest(
    ListRequest &LRQ,
    ListPeminjam &LPM,
    ListBuku &LB,
    int idRequest
);


/* ================= PENYIMPANAN DATA ================= */
void simpanBukuKeFile(ListBuku LB, string namaFile);
void loadBukuDariFile(ListBuku &LB, string namaFile);

void simpanPengunjungKeFile(ListPengunjung LP, string namaFile);
void loadPengunjungDariFile(ListPengunjung &LP, string namaFile);

void simpanPeminjamKeFile(ListPeminjam LPM, string namaFile);
void loadPeminjamDariFile(ListPeminjam &LPM, string namaFile);

void simpanRequestKeFile(ListRequest LRQ, string namaFile);
void loadRequestDariFile(ListRequest &LRQ, string namaFile);

void simpanStatusPerpustakaan(bool status, string namaFile);
bool loadStatusPerpustakaan(string namaFile);
string loadPassword(string namaFile);
void setWaktuRequest(infoRequest &rq);
void setTanggalRequest(infoRequest &rq);
void setTenggatPengembalian(infoPeminjam &pj);
void setTanggalPeminjam(infoPeminjam &pj);

#endif