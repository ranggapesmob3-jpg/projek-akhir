#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

struct Tiket {
    int idTiket;
    char namaPembeli[50];
    char judulFilm[50];
    int indexFilm;
    char baris;
    int kolom;
    int totalHarga;
    Tiket* next;
    Tiket* prev;
};

Tiket* headTiket = NULL;
Tiket* tailTiket = NULL;

int nomorPesanan = 1;
int hargaTiket = 50000; 

const char daftarFilm[5][50] = {
    "Manchester by the sea",
    "Prisoners",
    "Brother",
    "Dune: Part Two", 
    "The Batman"
};

char kursiBioskop[5][5][5]; 

void bersihLayar() {
    system("cls"); 
}

void jedaLayar() {
    cout << endl << "Tekan Enter buat lanjut...";
    cin.get();
}

void tampilHeader(const char* judulMenu) {
    bersihLayar();
    cout << "========================================================" << endl;
    cout << "           SISTEM TIKET BIOSKOP (SISFO UPNYK)           " << endl;
    cout << "========================================================" << endl;
    cout << " > " << judulMenu << endl;
    cout << "--------------------------------------------------------" << endl;
}

int inputAngka() {
    int angka;
    while (true) {
        cin >> angka;
        if (cin.fail()) {
            cout << "Input salah, masukin angka: ";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return angka;
}

void inisialisasiKursi() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                kursiBioskop[i][j][k] = 'O';
            }
        }
    }
}

void tampilFilm() {
    cout << endl << "--- JADWAL FILM ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << daftarFilm[i] << endl;
    }
    cout << "-------------------" << endl;
}

void tampilKursi(int index) {
    cout << endl << "LAYAR BIOSKOP (" << daftarFilm[index] << ")" << endl;
    cout << "=========================" << endl;
    cout << "   1   2   3   4   5" << endl;
    char labelBaris = 'A';
    for (int b = 0; b < 5; b++) {
        cout << labelBaris << "  ";
        for (int k = 0; k < 5; k++) {
            cout << kursiBioskop[index][b][k] << "   ";
        }
        cout << endl;
        labelBaris++;
    }
    cout << endl << "[O] = Kosong, [X] = Terisi" << endl;
}

int konversiBaris(char huruf) {
    if (huruf == 'A' || huruf == 'a') return 0;
    if (huruf == 'B' || huruf == 'b') return 1;
    if (huruf == 'C' || huruf == 'c') return 2;
    if (huruf == 'D' || huruf == 'd') return 3;
    if (huruf == 'E' || huruf == 'e') return 4;
    return -1;
}

bool cekKursiKosong(int indexFilm, char baris, int kolom) {
    int idxBaris = konversiBaris(baris);
    int idxKolom = kolom - 1;
    if (idxBaris == -1 || idxKolom < 0 || idxKolom > 4) return false;
    return (kursiBioskop[indexFilm][idxBaris][idxKolom] == 'O');
}

void pesanKursi(int indexFilm, char baris, int kolom) {
    int idxBaris = konversiBaris(baris);
    kursiBioskop[indexFilm][idxBaris][kolom - 1] = 'X';
}

void kosongkanKursi(int indexFilm, char baris, int kolom) {
    int idxBaris = konversiBaris(baris);
    kursiBioskop[indexFilm][idxBaris][kolom - 1] = 'O';
}

void cetakStruk(Tiket* dataTkt) {
    cout << endl << "========================================" << endl;
    cout << "             STRUK TIKET                " << endl;
    cout << "========================================" << endl;
    cout << "ID       : " << dataTkt->idTiket << endl;
    cout << "Nama     : " << dataTkt->namaPembeli << endl;
    cout << "Film     : " << dataTkt->judulFilm << endl;
    cout << "Studio   : " << dataTkt->indexFilm + 1 << endl;
    cout << "Kursi    : " << dataTkt->baris << dataTkt->kolom << endl;
    cout << "Total    : Rp " << dataTkt->totalHarga << endl;
    cout << "========================================" << endl;
}

void simpanDataTiket(int idBaru, const char* nama, int idFilm, char brs, int klm, int totalHrg) {
    Tiket* tiketBaru = new Tiket;
    tiketBaru->idTiket = idBaru;
    strcpy(tiketBaru->namaPembeli, nama);
    strcpy(tiketBaru->judulFilm, daftarFilm[idFilm]);
    tiketBaru->indexFilm = idFilm;
    
    tiketBaru->baris = brs;
    if (tiketBaru->baris >= 'a' && tiketBaru->baris <= 'e') {
        tiketBaru->baris -= 32;
    }
    
    tiketBaru->kolom = klm;
    tiketBaru->totalHarga = totalHrg;
    
    tiketBaru->next = NULL;
    tiketBaru->prev = NULL;

    if (headTiket == NULL) {
        headTiket = tailTiket = tiketBaru;
    } else { 
        tailTiket->next = tiketBaru; 
        tiketBaru->prev = tailTiket; 
        tailTiket = tiketBaru; 
    }
    pesanKursi(idFilm, brs, klm);
}

void beliTiketLangsung() {
    tampilHeader("BELI TIKET");
    char namaPem[50];
    
    cout << "Nama Pembeli: ";
    cin.getline(namaPem, 50);

    tampilFilm();
    cout << "Pilih Film (1-5): ";
    int pilihan = inputAngka();

    if (pilihan < 1 || pilihan > 5) {
        cout << "Film ga ada!" << endl;
        return;
    }

    int idxFilm = pilihan - 1;
    tampilKursi(idxFilm);
    
    char brs;
    int klm;
    cout << endl << "Baris (A-E): ";
    cin >> brs;
    
    cout << "Kolom (1-5): ";
    klm = inputAngka();

    if (cekKursiKosong(idxFilm, brs, klm) == false) {
        cout << endl << "Bangku udah diisi orang atau salah input!" << endl;
        return;
    }

    simpanDataTiket(nomorPesanan++, namaPem, idxFilm, brs, klm, hargaTiket);
    
    cout << endl << "Sukses beli tiket!" << endl;
    cetakStruk(tailTiket);
}

void tampilSemuaPesanan() {
    tampilHeader("SEMUA DATA PESANAN");
    if (headTiket == NULL) { 
        cout << "Kosong." << endl; 
        return; 
    }
    
    Tiket* penunjuk = headTiket;
    cout << left << setw(5) << "ID" << setw(20) << "Nama" << setw(25) << "Film" << setw(10) << "Kursi" << "Total" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    while (penunjuk != NULL) {
        cout << left << setw(5) << penunjuk->idTiket << setw(20) << penunjuk->namaPembeli << setw(25) << penunjuk->judulFilm 
             << penunjuk->baris << setw(9) << penunjuk->kolom << penunjuk->totalHarga << endl;
        penunjuk = penunjuk->next;
    }
}

void cariDataPembeli() {
    tampilHeader("CARI NAMA PEMBELI");
    if (headTiket == NULL) { 
        cout << "Belum ada yg beli." << endl; 
        return; 
    }
    
    char keywordNama[50];
    cout << "Masukin nama pembeli: ";
    cin.getline(keywordNama, 50);

    Tiket* penunjuk = headTiket;
    bool ketemuData = false;

    while (penunjuk != NULL) {
        if (strcmp(penunjuk->namaPembeli, keywordNama) == 0) {
            cout << endl << "Nemu datanya!" << endl;
            cetakStruk(penunjuk);
            ketemuData = true;
        }
        penunjuk = penunjuk->next;
    }
    
    if (!ketemuData) cout << endl << "Ga ada nama '" << keywordNama << "' di sistem." << endl;
}

void urutkanSesuaiNama() {
    tampilHeader("SORTING NAMA (A-Z)");

    if (headTiket == NULL || headTiket->next == NULL) {
        cout << "Datanya belum cukup buat diurutin." << endl;
        return;
    }

    for (Tiket* i = headTiket; i != NULL; i = i->next) {

        for (Tiket* j = i->next; j != NULL; j = j->next) {

            if (strcmp(i->namaPembeli, j->namaPembeli) > 0) {

                // temporary buat swap char array
                char tempNama[50];
                char tempFilm[50];

                // swap nama pembeli
                strcpy(tempNama, i->namaPembeli);
                strcpy(i->namaPembeli, j->namaPembeli);
                strcpy(j->namaPembeli, tempNama);

                // swap judul film
                strcpy(tempFilm, i->judulFilm);
                strcpy(i->judulFilm, j->judulFilm);
                strcpy(j->judulFilm, tempFilm);

                // swap data lainnya
                swap(i->idTiket, j->idTiket);
                swap(i->indexFilm, j->indexFilm);
                swap(i->baris, j->baris);
                swap(i->kolom, j->kolom);
                swap(i->totalHarga, j->totalHarga);
            }
        }
    }

    cout << "Berhasil diurutkan secara Ascending (Bubble Sort)!" << endl;
}

void batalkanTiket() {
    tampilHeader("HAPUS TIKET");
    if (headTiket == NULL) { 
        cout << "Ga ada data pesanan." << endl; 
        return; 
    }
    
    int targetId;
    cout << "ID Pesanan yg dibatalin: ";
    targetId = inputAngka();

    Tiket* penunjuk = headTiket;
    while (penunjuk != NULL) {
        if (penunjuk->idTiket == targetId) {
            kosongkanKursi(penunjuk->indexFilm, penunjuk->baris, penunjuk->kolom);

            if (penunjuk == headTiket) { 
                headTiket = headTiket->next; 
                if (headTiket != NULL) headTiket->prev = NULL; 
                else tailTiket = NULL;
            } else if (penunjuk == tailTiket) { 
                tailTiket = tailTiket->prev; 
                if (tailTiket != NULL) tailTiket->next = NULL; 
                else headTiket = NULL;
            } else { 
                penunjuk->prev->next = penunjuk->next; 
                penunjuk->next->prev = penunjuk->prev; 
            }

            delete penunjuk; 
            cout << "Udah dihapus ya datanya." << endl;
            return;
        }
        penunjuk = penunjuk->next;
    }
    cout << "ID salah." << endl;
}

struct RecordFile {
    int idTiket;
    char namaPembeli[50];
    int indexFilm;
    char baris;
    int kolom;
    int totalHarga;
};

void simpanDatabase() {
    FILE *file = fopen("db_bioskop.dat", "wb");
    if (!file) {
        cout << "Gagal membuat/membuka file database!" << endl;
        return;
    }

    Tiket* penunjuk = headTiket;
    while (penunjuk != NULL) {
        RecordFile rekaman;
        rekaman.idTiket = penunjuk->idTiket;
        strcpy(rekaman.namaPembeli, penunjuk->namaPembeli);
        rekaman.indexFilm = penunjuk->indexFilm;
        rekaman.baris = penunjuk->baris;
        rekaman.kolom = penunjuk->kolom;
        rekaman.totalHarga = penunjuk->totalHarga;

        fwrite(&rekaman, sizeof(RecordFile), 1, file);
        penunjuk = penunjuk->next;
    }
    fclose(file);
}

void bacaDatabase() {
    FILE *file = fopen("db_bioskop.dat", "rb");
    if (!file) return; 

    RecordFile rekaman;
    while (fread(&rekaman, sizeof(RecordFile), 1, file)) {
        if (rekaman.idTiket >= nomorPesanan) {
            nomorPesanan = rekaman.idTiket + 1; 
        }
        simpanDataTiket(rekaman.idTiket, rekaman.namaPembeli, rekaman.indexFilm, rekaman.baris, rekaman.kolom, rekaman.totalHarga);
    }
    fclose(file);
}

int main() {
    inisialisasiKursi();
    bacaDatabase(); 

    int menuPilihan = -1;
    int inputFilm = 0; 
    
    while (menuPilihan != 0) {
        tampilHeader("MENU BIOSKOP");
        cout << "1. Jadwal & Kursi" << endl;
        cout << "2. Beli Tiket" << endl;
        cout << "3. Liat Semua Pesanan" << endl;
        cout << "4. Cari Data" << endl;
        cout << "5. Urutin Nama" << endl;
        cout << "6. Hapus Tiket" << endl;
        cout << "7. Save Data (.dat File)" << endl;
        cout << "0. Exit" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Pilih (0-7): ";
        menuPilihan = inputAngka();

        switch (menuPilihan) {
            case 1:
                tampilFilm(); 
                cout << "Pilih film (1-5) buat liat denah: "; 
                inputFilm = inputAngka();
                if (inputFilm >= 1 && inputFilm <= 5) {
                    tampilKursi(inputFilm - 1); 
                }
                jedaLayar(); 
                break;
            case 2: 
                beliTiketLangsung(); 
                jedaLayar(); 
                break;
            case 3: 
                tampilSemuaPesanan(); 
                jedaLayar(); 
                break;
            case 4: 
                cariDataPembeli(); 
                jedaLayar(); 
                break;
            case 5: 
                urutkanSesuaiNama(); 
                jedaLayar(); 
                break;
            case 6: 
                batalkanTiket(); 
                jedaLayar(); 
                break;
            case 7: 
                simpanDatabase(); 
                cout << "Data berhasil di-save ke dalam file biner db_bioskop.dat!" << endl; 
                jedaLayar(); 
                break;
            case 0: 
                simpanDatabase();
                cout << endl << "Keluar... Terima Kasih" << endl; 
                break;
            default:
                cout << "Pilihan ga ada di menu bro." << endl;
                jedaLayar();
                break;
        }
    }

    return 0;
}
