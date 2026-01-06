#include "perpus.h"
#include <iomanip>
#include <ctime>
#include <fstream>
/* ======================
   LIST PEMINJAM
   ====================== */

void CreateListPeminjam(ListPeminjam &L) {
    L.first = Nil;
    L.last = Nil;
}

addressPeminjam alokasiPeminjam(infoPeminjam x) {
    addressPeminjam P = new PeminjamElmList;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertLastPeminjam(ListPeminjam &L, addressPeminjam P) {
    if (P == Nil) return;
    if (L.first == Nil) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

int generateIdPeminjam(ListPeminjam LPM) {
    int maxId = 0;
    addressPeminjam p = LPM.first;
    while (p != Nil) {
        if (p->info.idPeminjam > maxId) {
            maxId = p->info.idPeminjam;
        }
        p = p->next;
    }
    return maxId + 1;
}

void printInfoPeminjam(ListPeminjam L) {
    addressPeminjam P = L.first;

    cout << "---------------------------------------------- Daftar Peminjam ------------------------------------------------------\n";
    cout << left
         << setw(3) << "ID"
         << " | " << setw(14) << "Nama Peminjam"
         << " | " << setw(8) << "ID Buku"
         << " | " << setw(35) << "Info Buku"
         << " | " << setw(15) << "Tanggal Pinjam"
         << " | " << setw(19) << "Batas Pengembalian" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    while (P != Nil) {
        cout << left
             << setw(3) << P->info.idPeminjam
             << " | " << setw(14) << P->info.namaPeminjam
             << " | " << setw(8) << P->info.idBuku
             << " | " << setw(35) << P->info.infoBuku
             << " | " << setw(15) << P->info.tanggalPinjam
             << " | " << setw(19) << P->info.tenggatPengembalian << endl;
        P = P->next;
    }

    cout << "---------------------------------------------------------------------------------------------------------------------\n";
}


void setTanggalPeminjam(infoPeminjam &pj) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday
       << "-" 
       << setfill('0') << setw(2) << (ltm->tm_mon + 1)
       << "-"
       << setfill('0') << setw(4) << (ltm->tm_year + 1900);

    pj.tanggalPinjam = ss.str();
}

void setTenggatPengembalian(infoPeminjam &pj) {
    time_t now = time(0);
    time_t tenggat = now + (7 * 24 * 60 * 60);

    tm *ltm = localtime(&tenggat);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday
       << "-"
       << setfill('0') << setw(2) << (ltm->tm_mon + 1)
       << "-"
       << setfill('0') << setw(4) << (ltm->tm_year + 1900);

    pj.tenggatPengembalian = ss.str();
}

addressPeminjam findPeminjamById(ListPeminjam L, int id) {
    addressPeminjam P = L.first;
    while (P != Nil) {
        if (P->info.idPeminjam == id) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

addressPeminjam findPeminjamByNama(ListPeminjam L, string namaPeminjam) {
    addressPeminjam P = L.first;
    while (P != Nil) {
        if (P->info.namaPeminjam == namaPeminjam) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

void hapusPeminjamById(ListPeminjam &L, ListBuku &LB, int idPeminjam) {
    addressPeminjam P = findPeminjamById(L, idPeminjam);
    if (P == Nil) {
        cout << "Peminjam dengan ID " << idPeminjam << " tidak ditemukan!\n";
        return;
    }
    addressBuku bk = findBukuById(LB, P->info.idBuku);
    
    if (bk != Nil) {
        bk->info.tersedia = bk->info.tersedia+1;
    }
    if (P == L.first && P == L.last) {
        L.first = Nil;
        L.last = Nil;
    } else if (P == L.first) {
        L.first = P->next;
        L.first->prev = Nil;
    } else if (P == L.last) {
        L.last = P->prev;
        L.last->next = Nil;
    } else {
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }

    delete P;
    cout << "Peminjam dikembalikan dan stok buku diperbarui.\n";
}

bool prosesPeminjaman(
    ListPeminjam &LPM,
    ListBuku &LB,
    string namaPeminjam,
    int idBuku
) {
    addressBuku bk = findBukuById(LB, idBuku);
    if (bk == Nil || bk->info.tersedia <= 0) {
        cout << "Buku tidak tersedia!\n";
        return false;
    }
    bk->info.tersedia--;

    infoPeminjam pj;
    pj.idPeminjam = generateIdPeminjam(LPM);
    pj.namaPeminjam = namaPeminjam;
    pj.idBuku = bk->info.idBuku;
    pj.infoBuku = bk->info.namaBuku;


    setTanggalPeminjam(pj);
    setTenggatPengembalian(pj);

    insertLastPeminjam(LPM, alokasiPeminjam(pj));
    return true;
}

void accRequest(
    ListRequest &LRQ,
    ListPeminjam &LPM,
    ListBuku &LB,
    int idRequest
) {
    addressRequest rq = findRequestById(LRQ, idRequest);
    if (rq == Nil) {
        cout << "Request tidak ditemukan!\n";
        return;
    }

    bool sukses = prosesPeminjaman(
        LPM,
        LB,
        rq->info.namaRequest,
        rq->info.idBuku
    );

    if (sukses) {
        hapusRequest(LRQ, rq);
        cout << "Request berhasil di-ACC!\n";
    }
}

bool pinjamLangsung(
    ListPeminjam &LPM,
    ListBuku &LB,
    string namaPeminjam,
    int idBuku
) {
    if (prosesPeminjaman(LPM, LB, namaPeminjam, idBuku)) {
        cout << "Peminjaman langsung berhasil!\n";
        return true;
    }
    return false;
}
