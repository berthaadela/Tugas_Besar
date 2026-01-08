#include "perpus.h"
#include <iomanip>
#include <ctime>
/* ======================
   LIST PENGUNJUNG
   ====================== */

void CreateListPengunjung(ListPengunjung &L) {
    L.first = Nil;
    L.last = Nil;
}

addressPengunjung alokasiPengunjung(infoPengunjung x) {
    addressPengunjung P = new PengunjungElmList;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertLastPengunjung(ListPengunjung &L, addressPengunjung P) {
    if (L.first == Nil) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void tambahPengunjung(ListPengunjung &LP, bool statusPerpustakaan) {
    int back;
    infoPengunjung pg;
    if (!statusPerpustakaan) {
        do {
            cout << "Perpustakaan masih tutup"
            << endl << "Ketik 0 untuk kembali"
            << endl << "Ketik: ";
            cin >> back;
        } while (back != 0);
    } else {
        pg.idPengunjung = generateIdPengunjung(LP);
        cout << "Masukkan Nama Pengunjung: ";
        cin.ignore();
        getline(cin, pg.namaPengunjung);
        setWaktuKunjungan(pg);
        insertLastPengunjung(LP, alokasiPengunjung(pg));
        cout << "Pengunjung berhasil ditambahkan!" << endl;
        simpanPengunjungKeFile(LP, "daftarpengunjung.txt");

    }
}

int hitungJumlahPengunjung(ListPengunjung L) {
    addressPengunjung P = L.first;
    int count = 0;

    while (P != Nil) {
        count++;
        P = P->next;
    }
    return count;
}

void printListPengunjung(ListPengunjung L) {
    addressPengunjung P = L.first;
    time_t now = time(0);
    cout << "*------------------------------------------------------------------------*\n";
    cout << "                           DAFTAR PENGUNJUNG                              \n";
    cout << "                        " << ctime(&now) << "                             \n";
    cout << "*------------------------------------------------------------------------*\n";
    cout << left
         << setw(6) << "ID"
         << " | " << setw(45) << "Nama"
         << " | " << setw(20) << "Waktu Datang" << endl;

    cout << "--------------------------------------------------------------------------\n";

    while (P != Nil) {
        cout << left
             << setw(6) << P->info.idPengunjung
             << " | " << setw(45) << P->info.namaPengunjung
             << " | " << setw(20) << P->info.waktuKunjungan << endl;
        P = P->next;
    }

    cout << "--------------------------------------------------------------------------\n";
}


void resetListPengunjung(ListPengunjung &L) {
    addressPengunjung P = L.first;
    addressPengunjung temp;
    while (P != Nil) {
        temp = P->next;
        delete P;
        P = temp;
    }
    L.first = Nil;
    L.last = Nil;

    cout << "List pengunjung telah di-reset." << endl;
    simpanPengunjungKeFile(L, "daftarpengunjung.txt");
}

void hapusPengunjungById(ListPengunjung &L, int idPengunjung) {
    addressPengunjung P = L.first;

    while (P != Nil && P->info.idPengunjung != idPengunjung) {
        P = P->next;
    }

    if (P == Nil) {
        cout << "Pengunjung dengan ID tersebut tidak ditemukan." << endl;
        return;
    }
    addressPengunjung after = P->next;
    if (P == L.first && P == L.last) {
        L.first = Nil;
        L.last = Nil;
    } 
    else if (P == L.first) {
        L.first = P->next;
        L.first->prev = Nil;
    } 
    else if (P == L.last) {
        L.last = P->prev;
        L.last->next = Nil;
    } 
    else {
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }

    delete P;
    P = after;
    while (P != Nil) {
        P->info.idPengunjung -= 1;
        P = P->next;
    }
    cout << "Pengunjung berhasil dihapus." << endl;

    simpanPengunjungKeFile(L, "daftarpengunjung.txt");
}


int generateIdPengunjung(ListPengunjung LPG) {
    int maxId = 0;
    addressPengunjung p = LPG.first;
    while (p != Nil) {
        if (p->info.idPengunjung > maxId) {
            maxId = p->info.idPengunjung;
        }
        p = p->next;
    }
    return maxId + 1;
}
void setWaktuKunjungan(infoPengunjung &pg) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_hour
       << ":" 
       << setfill('0') << setw(2) << ltm->tm_min;

    pg.waktuKunjungan = ss.str();
}