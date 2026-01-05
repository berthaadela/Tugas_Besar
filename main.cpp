#include "perpus.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ListBuku LB;
    ListPengunjung LP;
    ListPeminjam LPM;
    ListRequest LRQ;
    bool statusPerpustakaan = loadStatusPerpustakaan("status.txt");
    bool passwordAcc = false;
    int pilihan0, pilihan1, pilihan2, pilihan3, pilihan4, idb, idp;
    int pilihanP1, pilihanP2;
    string jud, pen, inputPassword;

    CreateListBuku(LB);
    CreateListPengunjung(LP);
    CreateListPeminjam(LPM);
    CreateListRequest(LRQ);
    loadBukuDariFile(LB, "daftarbuku.txt");
    loadPengunjungDariFile(LP, "daftarpengunjung.txt");
    loadRequestDariFile(LRQ, "daftarrequest.txt");
    loadPeminjamDariFile(LPM, "daftarpeminjam.txt");
    string password = loadPassword("adminpw.txt");

    do {
        cout << "=========== PERPUSTAKAAN SPARKLE ===========" << endl
             << "1. Saya adalah Admin" << endl
             << "2. Saya adalah Pengunjung" << endl
             << "0. Keluar" << endl
             << "Pilihan: ";
        cin >> pilihan0;
        cout << endl;
        switch (pilihan0) {
            case 1: {
                cout << "Ketik 0 untuk kembali" << endl;
                do {
                    cout << "Admin security password: ";
                    cin >> inputPassword;
                    if (inputPassword == password) {
                        passwordAcc = true;
                        do {
                            cout << "=========== PERPUSTAKAAN SPARKLE ===========" << endl;
                            cout << "Selamat datang di Perpustakaan!" << endl;
                            cout << "Status Perpustakaan: " << (statusPerpustakaan ? "BUKA" : "TUTUP") << endl;
                            cout << "Jumlah pengunjung saat ini: " << hitungJumlahPengunjung(LP) << endl;
                            if (!statusPerpustakaan) {
                                cout << "1. Buka Perpustakaan" << endl;
                            } else {
                                cout << "1. Tutup Perpustakaan" << endl;
                            }
                            cout << "2. Kelola Daftar Buku" << endl;
                            cout << "3. Kelola Log Pengunjung" << endl;
                            cout << "4. Kelola Peminjaman" << endl;
                            cout << "0. Keluar" << endl;
                            cout << "Pilihan: ";
                            cin >> pilihan1;
                            cout << endl;

                            switch (pilihan1) {
                                case 1:
                                    statusPerpustakaan = !statusPerpustakaan;
                                    cout << (statusPerpustakaan ? "Perpustakaan dibuka!\n" : "Perpustakaan ditutup!\n");
                                    simpanStatusPerpustakaan(statusPerpustakaan, "status.txt");
                                    break;
                                case 2: {
                                    do {
                                        cout << "=========== DAFTAR BUKU ===========" << endl;
                                        cout << "1. Tampilkan Daftar Buku" << endl;
                                        cout << "2. Cari Buku Berdasarkan Judul" << endl;
                                        cout << "3. Cari Buku Berdasarkan Penulis" << endl;
                                        cout << "4. Tambah Buku" << endl;
                                        cout << "5. Update (Edit) Buku" << endl;
                                        cout << "6. Hapus Buku" << endl;
                                        cout << "7. Hapus List Buku" << endl;
                                        cout << "0. Kembali" << endl;
                                        cout << "Pilihan: ";
                                        cin >> pilihan2;
                                        cout << endl;
                                        switch (pilihan2) {
                                            case 1: {
                                                printInfoBuku(LB);
                                                break;
                                            }
                                            case 2: {
                                                cout << "Masukkan Judul: ";
                                                cin.ignore();
                                                getline(cin, jud);
                                                searchbyTitle(LB, jud);
                                                break;
                                            }
                                            case 3: {
                                                cout << "Masukkan Penulis: ";
                                                cin.ignore();
                                                getline(cin, pen);
                                                searchbyAuthor(LB, pen);
                                                break;
                                            }
                                            case 4: {
                                                tambahBuku(LB);
                                                break;
                                            }
                                            case 5: {
                                                cout << "Masukkan ID Buku yang ingin diupdate: ";
                                                cin >> idb;
                                                updateBook(LB, idb);
                                                break;
                                            }
                                            case 6: {
                                                cout << "Masukkan ID Buku yang ingin dihapus: ";
                                                cin >> idb;
                                                hapusBukuById(LB, idb);
                                                
                                                cout << "Buku berhasil dihapus!" << endl;
                                                break;
                                            }
                                            case 7: {
                                                resetListBuku(LB);
                                                cout << "List telah di reset" << endl;
                                                break;
                                            }
                                        }
                                        cout << endl;
                                    } while (pilihan2 != 0);
                                    break;
                                }
                                case 3: {
                                    do {
                                        cout << "=== Daftar Pengunjung ===" << endl;
                                        cout << "1. Tambahkan Pengunjung" << endl;
                                        cout << "2. Lihat Daftar Pengunjung" << endl;
                                        cout << "3. Hapus Pengunjung Berdasarkan ID" << endl;
                                        cout << "4. Hapus Seluruh Pengunjung" << endl;
                                        cout << "0. Kembali" << endl;
                                        cout << "Pilihan: ";
                                        cin >> pilihan3;
                                        cout << endl;

                                        switch (pilihan3) {
                                            case 1:
                                                tambahPengunjung(LP, statusPerpustakaan);
                                                break;
                                            case 2:
                                                printListPengunjung(LP);
                                                break;
                                            case 3:
                                                cout << "Masukkan ID pengunjung yang akan dihapus: ";
                                                cin >> idp;
                                                hapusPengunjungById(LP, idp);
                                                break;
                                            case 4:
                                                resetListPengunjung(LP);
                                                cout << "List telah di reset" << endl;
                                                break;
                                        }
                                        cout << endl;
                                    } while (pilihan3 != 0);
                                    break;
                                }
                                case 4: {
                                    do {
                                        printInfoRequest(LRQ);
                                        cout << "1. Konfirmasi Permintaan" << endl;
                                        cout << "2. Tolak Permintaan" << endl;
                                        cout << "3. Lihat Daftar Peminjam" << endl;
                                        cout << "4. Tambah Peminjam" << endl;
                                        cout << "5. Hapus Peminjam (Pengembalian Buku)" << endl;
                                        cout << "0. Kembali" << endl;
                                        cout << "Pilihan: ";
                                        cin >> pilihan4;
                                        cout << endl;
                                        switch (pilihan4) {
                                            case 1: {
                                                int idRequest;
                                                cout << "Masukkan ID Pengaju: ";
                                                cin >> idRequest;
                                                accRequest(LRQ, LPM, LB, idRequest);
                                                cout << "Permintaan Dikonfirmasi!";
                                                simpanBukuKeFile(LB, "daftarbuku.txt");
                                                simpanRequestKeFile(LRQ, "daftarrequest.txt");
                                                simpanPeminjamKeFile(LPM, "daftarpeminjam.txt");
                                                break;
                                            }
                                            case 2: {
                                                int idRequest;
                                                cout << "Masukkan ID Pengaju: ";
                                                cin >> idRequest;
                                                hapusRequestById(LRQ, idRequest);
                                                cout << "Permintaan Ditolak!";
                                                simpanRequestKeFile(LRQ, "daftarrequest.txt");
                                                break; 
                                            }
                                            case 3: {
                                                int ketik0;
                                                printInfoPeminjam(LPM);
                                                do {
                                                    cout<< endl << "Ketik 0 untuk kembali."
                                                        << endl << "Ketik: ";
                                                    cin >> ketik0;
                                                } while (ketik0 != 0);
                                                break;
                                            }
                                            case 4: {
                                                string namaPeminjam;
                                                int idBuku;

                                                printInfoPeminjam(LPM);

                                                cin.ignore();
                                                cout << "Masukkan Nama Peminjam: ";
                                                getline(cin, namaPeminjam);

                                                cout << "Masukkan ID Buku: ";
                                                cin >> idBuku;

                                                if (pinjamLangsung(LPM, LB, namaPeminjam, idBuku)) {
                                                    simpanPeminjamKeFile(LPM, "daftarpeminjam.txt");
                                                    simpanBukuKeFile(LB, "daftarbuku.txt");
                                                }

                                                break;
                                            }

                                            case 5: {
                                                printInfoPeminjam(LPM);
                                                int idPeminjam;
                                                cout << "Masukkan ID Peminjam: ";
                                                cin >> idPeminjam;
                                                hapusPeminjamById(LPM, LB, idPeminjam);
                                                simpanPeminjamKeFile(LPM, "daftarpeminjam.txt");
                                                simpanBukuKeFile(LB, "daftarbuku.txt");
                                                break;
                                            }
                                        }
                                        cout << endl;
                                    } while (pilihan4 != 0);
                                    break;
                                }
                            }
                        } while (pilihan1 != 0);
                        cout << "Terimakasih telah menggunakan aplikasi Perpustakaan Sparkle! :)";
                        return 0;
                    } else if (inputPassword == "0") {
                        break;
                    } else {
                        cout << "Password salah!" << endl;
                    }
                } while (!passwordAcc && inputPassword != "0");
                break;
            }
            case 2: {
                do {
                    cout << "=========== PERPUSTAKAAN SPARKLE ===========" << endl;
                    cout << "Selamat datang di Perpustakaan!" << endl;
                    cout << "Status Perpustakaan: " << (statusPerpustakaan ? "BUKA" : "TUTUP") << endl;
                    cout << "Jumlah pengunjung saat ini: " << hitungJumlahPengunjung(LP) << endl;
                    cout << "1. Tampilkan Daftar Buku" << endl;
                    cout << "2. Cari Buku Berdasarkan Judul" << endl;
                    cout << "3. Cari Buku Berdasarkan Penulis" << endl;
                    cout << "4. Ajukan Peminjaman" << endl;
                    cout << "5. Cek Tiket" << endl;
                    cout << "0. Keluar" << endl;
                    cout << "Pilihan: ";
                    cin >> pilihanP1;
                    switch (pilihanP1) {
                        case 1: {
                            printInfoBuku(LB);
                            break;
                        }
                        case 2: {
                            cin.ignore();
                            cout << "Masukkan Judul: ";
                            getline(cin, jud);
                            searchbyTitle(LB, jud);
                            break;
                        }
                        case 3: {
                            cin.ignore();
                            cout << "Masukkan Penulis: ";
                            getline(cin, pen);
                            searchbyAuthor(LB, pen);
                            break;
                        }
                        case 4: {
                            tambahRequest(LRQ, LB);
                            break;
                        }
                        case 5: {
                            int ketikCek;
                            string namaTiket;
                            cout << "Masukkan nama pemilik tiket: ";
                            cin.ignore();
                            getline(cin, namaTiket);
                            cekTiket(LRQ, namaTiket);
                            do {
                                cout<< endl << "Ketik 0 untuk kembali."
                                    << endl << "Ketik: ";
                                cin >> ketikCek;
                            } while (ketikCek != 0);
                            break;
                        }
                    }
                    cout << endl;
                } while (pilihanP1 != 0);
                cout << "Terimakasih telah menggunakan aplikasi Perpustakaan Sparkle! :)";
                return 0;
            }
        }
        cout << endl;
    } while (pilihan0 != 0);
    cout << "Keluar dari aplikasi...";
    return 0;
}
