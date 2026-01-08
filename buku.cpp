#include "perpus.h"
#include <iomanip>
/* ======================
   LIST BUKU
   ====================== */

void CreateListBuku(ListBuku &L) {
    L.first = Nil;
    L.last = Nil;
}

addressBuku alokasiBuku(infoBuku x) {
    addressBuku P = new BukuElmList;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void insertLastBuku(ListBuku &L, addressBuku P) {
    if (L.first == Nil) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void tambahBuku(ListBuku &LB) {
    infoBuku bk;
    int jumlahBuku;

    bk.idBuku = generateIdBuku(LB);

    cin.ignore();
    cout << "Masukkan Judul Buku: ";
    getline(cin, bk.namaBuku);

    cout << "Masukkan Nama Penulis: ";
    getline(cin, bk.namaPenulis);

    cout << "Masukkan Tahun Terbit: ";
    getline(cin, bk.tahunTerbit);

    cout << "Berapa Buku: ";
    cin >> jumlahBuku;

    bk.tersedia = jumlahBuku;

    insertLastBuku(LB, alokasiBuku(bk));
    simpanBukuKeFile(LB, "daftarbuku.txt");

    cout << "Buku berhasil ditambahkan!\n";
}


void printInfoBuku(ListBuku L) {
    addressBuku P = L.first;

    cout << "--------------------------------------------------- Daftar Buku -----------------------------------------------------\n";
    cout << left
         << setw(3) << "ID"
         << " | " << setw(50) << "Judul Buku"
         << " | " << setw(35) << "Penulis"
         << " | " << setw(4) << "Tahun"
         << " | " << setw(3) << "Tersedia" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    while (P != Nil) {
        cout << left
             << setw(3) << P->info.idBuku
             << " | " << setw(50) << P->info.namaBuku
             << " | " << setw(35) << P->info.namaPenulis
             << " | " << setw(4) << P->info.tahunTerbit
             << " | " << setw(3) << P->info.tersedia << endl;
        P = P->next;
    }

    cout << "---------------------------------------------------------------------------------------------------------------------\n";
}


void hapusBukuById(ListBuku &L, int idBuku) {
    addressBuku P = L.first;

    while (P != Nil && P->info.idBuku != idBuku) {
        P = P->next;
    }
    if (P == Nil) {
        cout << "Buku dengan id " << idBuku << " tidak tersedia..." << endl;
        return;
    }

    addressBuku after = P->next;

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
    P = after;
    while (P != Nil) {
        P->info.idBuku -= 1;
        P = P->next;
    }
    cout << "Buku berhasil dihapus!" << endl;
    simpanBukuKeFile(L, "daftarbuku.txt");
}

void searchbyTitle(ListBuku L, string title) {
    addressBuku P = L.first;
    cout << endl << "Menampilkan pencarian..." << endl << endl;

    cout << "--------------------------------------------------- Daftar Buku -----------------------------------------------------\n";
    cout << left
         << setw(3) << "ID"
         << " | " << setw(50) << "Judul Buku"
         << " | " << setw(35) << "Penulis"
         << " | " << setw(4) << "Tahun"
         << " | " << setw(3) << "Tersedia" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    while (P != Nil) {
        if (P->info.namaBuku == title) {
            cout << left
             << setw(3) << P->info.idBuku
             << " | " << setw(50) << P->info.namaBuku
             << " | " << setw(35) << P->info.namaPenulis
             << " | " << setw(4) << P->info.tahunTerbit
             << " | " << setw(3) << P->info.tersedia << endl;
        }
        P = P->next;
        if (P == L.last->next) {
            cout << "---------------------------------------------------------------------------------------------------------------------\n";
            return;
        } 
    }
    cout << "Buku tidak ditemukan." << endl;
}

void searchbyAuthor(ListBuku L, string author) {
    addressBuku P = L.first;
    cout << "--------------------------------------------------- Daftar Buku -----------------------------------------------------\n";
    cout << left
         << setw(3) << "ID"
         << " | " << setw(50) << "Judul Buku"
         << " | " << setw(35) << "Penulis"
         << " | " << setw(4) << "Tahun"
         << " | " << setw(3) << "Tersedia" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    while (P != Nil) {
        if (P->info.namaPenulis == author) {
            cout << left
             << setw(3) << P->info.idBuku
             << " | " << setw(50) << P->info.namaBuku
             << " | " << setw(35) << P->info.namaPenulis
             << " | " << setw(4) << P->info.tahunTerbit
             << " | " << setw(3) << P->info.tersedia << endl;
        }
        P = P->next;
        if (P == L.last->next) {
            cout << "---------------------------------------------------------------------------------------------------------------------\n";
            return;
        }
    }
}

void updateBook(ListBuku &L, int idBuku) {
    addressBuku P = L.first;
    int input;

    while (P != Nil) {
        if (P->info.idBuku == idBuku) {
            do {
                cout << "1. Edit Judul"
                << endl << "2. Edit Penulis"
                << endl << "3. Edit Tahun Terbit"
                << endl << "4. Edit Ketersediaan"
                << endl << "0. Kembali"
                << endl << "Pilihan: ";
                cin >> input;
                cout << endl;
                switch (input) {
                    case 1: {
                        cout << "Masukkan judul baru: ";
                        getline(cin >> ws, P->info.namaBuku);
                        simpanBukuKeFile(L, "daftarbuku.txt");
                        break;
                    }
                    case 2: {
                        cout << "Masukkan penulis baru: ";
                        getline(cin >> ws, P->info.namaPenulis);
                        simpanBukuKeFile(L, "daftarbuku.txt");
                        break;
                    }
                    case 3: {
                        cout << "Masukkan tahun terbit baru: ";
                        getline(cin >> ws, P->info.tahunTerbit);
                        simpanBukuKeFile(L, "daftarbuku.txt");
                        break;
                    }
                    case 4: {
                        cout << "Tersedia: ";
                        cin >> P->info.tersedia;
                        simpanBukuKeFile(L, "daftarbuku.txt");
                        break;
                    }
                }
                cout << endl;
            } while (input != 0);
        }
        P = P->next;
    }
    cout << "Buku tidak ditemukan." << endl;
    
}

int generateIdBuku(ListBuku LB) {
    int maxId = 0;
    addressBuku p = LB.first;
    while (p != Nil) {
        if (p->info.idBuku > maxId) {
            maxId = p->info.idBuku;
        }
        p = p->next;
    }
    return maxId + 1;
}


void resetListBuku(ListBuku &L) {
    addressBuku P = L.first;
    addressBuku temp;
    while (P != Nil) {
        temp = P->next;
        delete P;
        P = temp;
    }
    L.first = Nil;
    L.last = Nil;
    cout << "List buku telah di-reset." << endl;
}

addressBuku findBukuById(ListBuku L, int idBuku) {
    addressBuku P = L.first;
    while (P != Nil) {
        if (P->info.idBuku == idBuku) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

addressBuku findBukuByNama(ListBuku L, string judulBuku) {
    addressBuku P = L.first;
    while (P != Nil) {
        if (P->info.namaBuku == judulBuku) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}