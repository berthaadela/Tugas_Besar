#include "perpus.h"
#include <iomanip>
#include <ctime>
#include <fstream>
/* ======================
   PENYIMPANAN DATA
   ====================== */

void simpanBukuKeFile(ListBuku LB, string namaFile) {
    ofstream file(namaFile);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    addressBuku p = LB.first;
    while (p != NULL) {
        file << p->info.idBuku << endl;
        file << p->info.namaBuku << endl;
        file << p->info.namaPenulis << endl;
        file << p->info.tahunTerbit << endl;
        file << p->info.tersedia << endl;
        p = p->next;
    }
    file.close();
    cout << "Data buku berhasil disimpan ke " << namaFile << endl;
}

void simpanPengunjungKeFile(ListPengunjung LP, string namaFile) {
    ofstream file(namaFile);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    addressPengunjung p = LP.first;
    while (p != NULL) {
        file << p->info.idPengunjung << endl;
        file << p->info.namaPengunjung << endl;
        file << p->info.waktuKunjungan << endl;
        p = p->next;
    }
    file.close();
    cout << "Data pengunjung berhasil disimpan ke " << namaFile << endl;
}

void loadBukuDariFile(ListBuku &LB, string namaFile) {
    ifstream file(namaFile);
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }
    infoBuku bk;
    while (file >> bk.idBuku) {
        file.ignore();
        getline(file, bk.namaBuku);
        getline(file, bk.namaPenulis);
        file >> bk.tahunTerbit;
        file >> bk.tersedia;
        file.ignore();
        insertLastBuku(LB, alokasiBuku(bk));
    }
    file.close();
    cout << "Data buku berhasil dimuat dari " << namaFile << endl;
}

void loadPengunjungDariFile(ListPengunjung &LP, string namaFile) {
    ifstream file(namaFile);
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }
    infoPengunjung pg;
    while (file >> pg.idPengunjung) {
        file.ignore();
        getline(file, pg.namaPengunjung);
        getline(file, pg.waktuKunjungan);
        insertLastPengunjung(LP, alokasiPengunjung(pg));
    }
    file.close();
    cout << "Data pengunjung berhasil dimuat dari " << namaFile << endl;
}

string loadPassword(string namaFile) {
    ifstream file(namaFile);
    string line;
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return "";
    }
    while (getline(file, line)) {
        if (line.find("password = ") == 0) {
            return line.substr(11);
        }
    }
    file.close();
    return "";
}

/* ====================== SIMPAN PEMINJAM ====================== */
void simpanPeminjamKeFile(ListPeminjam LPM, string namaFile) {
    ofstream file(namaFile);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    addressPeminjam p = LPM.first;
    while (p != NULL) {
        file << p->info.idPeminjam << endl;
        file << p->info.namaPeminjam << endl;
        file << p->info.idBuku << endl;
        file << p->info.infoBuku << endl;
        file << p->info.tanggalPinjam << endl;
        file << p->info.tenggatPengembalian << endl;
        p = p->next;
    }
    file.close();
    cout << "Data peminjam berhasil disimpan ke " << namaFile << endl;
}

/* ====================== LOAD PEMINJAM ====================== */
void loadPeminjamDariFile(ListPeminjam &LPM, string namaFile) {
    ifstream file(namaFile);
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    CreateListPeminjam(LPM);
    infoPeminjam pj;
    while (file >> pj.idPeminjam) {
        file.ignore();
        getline(file, pj.namaPeminjam);
        file >> pj.idBuku;
        file.ignore();
        getline(file, pj.infoBuku);
        getline(file, pj.tanggalPinjam);
        getline(file, pj.tenggatPengembalian);
        insertLastPeminjam(LPM, alokasiPeminjam(pj));
    }

    file.close();
    cout << "Data peminjam berhasil dimuat dari " << namaFile << endl;
}

/* ====================== SIMPAN REQUEST ====================== */
void simpanRequestKeFile(ListRequest LRQ, string namaFile) {
    ofstream file(namaFile);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }
    addressRequest p = LRQ.first;
    while (p != NULL) {
        file << p->info.idRequest << endl;
        file << p->info.namaRequest << endl;
        file << p->info.idBuku << endl;
        file << p->info.waktu << endl;
        file << p->info.tanggal << endl;
        p = p->next;
    }
    file.close();
    cout << "Data request berhasil disimpan ke " << namaFile << endl;
}

/* ====================== LOAD REQUEST ====================== */
void loadRequestDariFile(ListRequest &LRQ, string namaFile) {
    ifstream file(namaFile);
    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    CreateListRequest(LRQ);
    infoRequest rq;
    while (file >> rq.idRequest) {
        file.ignore();
        getline(file, rq.namaRequest);
        file >> rq.idBuku;
        file.ignore();
        getline(file, rq.waktu);
        getline(file, rq.tanggal);
        insertLastRequest(LRQ, alokasiRequest(rq));
    }

    file.close();
    cout << "Data request berhasil dimuat dari " << namaFile << endl;
}

void simpanStatusPerpustakaan(bool status, string namaFile) {
    ofstream file(namaFile);
    if (!file) return;
    file << status;
    file.close();
}

bool loadStatusPerpustakaan(string namaFile) {
    ifstream file(namaFile);
    if (!file) return false;
    bool status;
    file >> status;
    file.close();
    return status;
}
