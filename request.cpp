#include "perpus.h"
#include <iomanip>
#include <ctime>
#include <fstream>


/* ======================
   LIST REQUEST
   ====================== */

void CreateListRequest(ListRequest &L) {
    L.first = Nil;
    L.last = Nil;
}

addressRequest alokasiRequest(infoRequest x) {
    addressRequest P = new RequestElmList;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertLastRequest(ListRequest &L, addressRequest P) {
    if (L.first == Nil) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void tambahRequest(ListRequest &LRQ, ListBuku &L) {
    infoRequest rq;
    int ketik;
    string x;
    rq.idRequest = generateIdRequest(LRQ);
    cout << "Masukkan Nama Pengaju: ";
    cin.ignore();
    getline(cin, rq.namaRequest);
    cout << "Masukkan Judul Buku: ";
    getline(cin, x);
    addressBuku p = findBukuByNama(L, x);
    rq.idBuku = p->info.idBuku;
    setWaktuRequest(rq);
    setTanggalRequest(rq);
    addressRequest baru = alokasiRequest(rq);
    insertLastRequest(LRQ, baru);
    cout << "Pengajuan Peminjaman Berhasil!" << endl << endl;
    simpanRequestKeFile(LRQ, "daftarrequest.txt");
    printSatuTiket(baru);
    cout    << "Tunjukkan Tiket Kepada Petugas Pada Saat Melakukan Peminjaman.";
    do {
        cout<< endl << "Ketik 0 untuk kembali."
            << endl << "Ketik: ";
        cin >> ketik;
    } while (ketik != 0);
}

int generateIdRequest(ListRequest LRQ) {
    if (LRQ.first == NULL) {
        return 1;
    } else {
        addressRequest p = LRQ.first;
        while (p->next != NULL) {
            p = p->next;
        }
        return p->info.idRequest+1;
    }
}

addressRequest findRequestById(ListRequest L, int id) {
    addressRequest P = L.first;
    while (P != Nil) {
        if (P->info.idRequest == id) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

addressRequest findRequestByNama(ListRequest L, string nama) {
    addressRequest P = L.first;
    while (P != Nil) {
        if (P->info.namaRequest == nama) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}
void hapusRequestById(ListRequest &L, int idRequest) {
    addressRequest P = L.first;
    while (P != Nil && P->info.idRequest != idRequest) {
        P = P->next;
    }
    if (P == Nil) return;
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
}

void hapusRequest(ListRequest &L, addressRequest P) {
    if (P == Nil) return;

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
}

void printSatuTiket(addressRequest P) {
    const int WIDTH = 24;

    cout << "========================================" << endl;
    cout << "|        TIKET PENGAJUAN PINJAMAN       |" << endl;
    cout << "========================================" << endl;

    cout << "| ID Request: " << setw(WIDTH) << left << P->info.idRequest << "|" << endl;
    cout << "| Nama      : " << setw(WIDTH) << left << P->info.namaRequest << "|" << endl;
    cout << "| ID Buku   : " << setw(WIDTH) << left << P->info.idBuku << "|" << endl;
    cout << "| Waktu     : " << setw(WIDTH) << left << P->info.waktu << "|" << endl;
    cout << "| Tanggal   : " << setw(WIDTH) << left << P->info.tanggal << "|" << endl;

    cout << "========================================" << endl;
}


void cekTiket(ListRequest &LRQ, string nama) {
    addressRequest rq = findRequestByNama(LRQ, nama);
    if (rq == Nil) {
        cout << "Tiket tidak ditemukan!\n";
        return;
    }
    printSatuTiket(rq);
}

void printInfoRequest(ListRequest L) {
    addressRequest P = L.first;

    cout << "---------------------------------------------- Daftar Request ------------------------------------------------------\n";
    cout << left
         << setw(3) << "ID"
         << " | " << setw(35) << "Nama Pengaju"
         << " | " << setw(3) << "ID Buku"
         << " | " << setw(5) << "Waktu"
         << " | " << setw(10) << "Tanggal" << endl;

    cout << "--------------------------------------------------------------------------------------------------------------------\n";

    while (P != Nil) {
        cout << left
             << setw(3) << P->info.idRequest
             << " | " << setw(35) << P->info.namaRequest
             << " | " << setw(3) << P->info.idBuku
             << " | " << setw(5) << P->info.waktu
             << " | " << setw(10) << P->info.tanggal << endl;
        P = P->next;
    }

    cout << "--------------------------------------------------------------------------------------------------------------------\n";
}


void setWaktuRequest(infoRequest &rq) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_hour
       << ":" 
       << setfill('0') << setw(2) << ltm->tm_min;

    rq.waktu = ss.str();
}

void setTanggalRequest(infoRequest &rq) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday
       << "-" 
       << setfill('0') << setw(2) << (ltm->tm_mon + 1)
       << "-"
       << setfill('0') << setw(4) << (ltm->tm_year + 1900);

    rq.tanggal = ss.str();
}