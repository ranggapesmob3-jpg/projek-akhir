#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// menyimpan data pemesanan
struct Data {
    int id;
    string nama;
    string film;
    int jumlah;
    Data* next;
};

Data* head = NULL;
Data* tail = NULL;
int no = 1;

// menambah data
void tambah() {
    Data* baru = new Data;

    baru->id = no++;

    cout << "Nama: ";
    cin.ignore();
    getline(cin, baru->nama);

    cout << "Film: ";
    getline(cin, baru->film);

    cout << "Jumlah tiket: ";
    cin >> baru->jumlah;

    baru->next = NULL;

    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Data ditambahkan\n";
}

// menampilkan data
void tampil() {
    Data* temp = head;

    cout << "\nDATA:\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Nama"
         << setw(20) << "Film"
         << setw(10) << "Tiket" << endl;

    while (temp != NULL) {
        cout << setw(5) << temp->id
             << setw(20) << temp->nama
             << setw(20) << temp->film
             << setw(10) << temp->jumlah << endl;

        temp = temp->next;
    }
}

// mencari data berdasarkan nama
void cari() {
    string nama;
    cout << "Cari nama: ";
    cin.ignore();
    getline(cin, nama);

    Data* temp = head;

    while (temp != NULL) {
        if (temp->nama == nama) {
            cout << "Ditemukan: " << temp->film << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Tidak ditemukan\n";
}

// menghapus data berdasarkan id
void hapus() {
    int id;
    cout << "ID yang dihapus: ";
    cin >> id;

    Data *temp = head, *sebelum = NULL;

    while (temp != NULL) {
        if (temp->id == id) {
            if (temp == head) {
                head = head->next;
            } else {
                sebelum->next = temp->next;
            }

            if (temp == tail) {
                tail = sebelum;
            }

            delete temp;
            cout << "Data dihapus\n";
            return;
        }

        sebelum = temp;
        temp = temp->next;
    }

    cout << "ID tidak ada\n";
}

// mengurutkan data berdasarkan jumlah tiket
void urut() {
    for (Data* i = head; i != NULL; i = i->next) {
        for (Data* j = i->next; j != NULL; j = j->next) {
            if (i->jumlah > j->jumlah) {
                swap(i->nama, j->nama);
                swap(i->film, j->film);
                swap(i->jumlah, j->jumlah);
            }
        }
    }

    cout << "Data diurutkan\n";
}

// menyimpan data ke file
void simpan() {
    ofstream file("data.txt");
    Data* temp = head;

    while (temp != NULL) {
        file << temp->id << " "
             << temp->nama << " "
             << temp->film << " "
             << temp->jumlah << endl;

        temp = temp->next;
    }

    file.close();
    cout << "Data disimpan\n";
}

// menu utama
int main() {
    int pilih;

    do {
        cout << "\n=== BIOSKOP ===\n";
        cout << "1. Tambah\n";
        cout << "2. Tampil\n";
        cout << "3. Cari\n";
        cout << "4. Hapus\n";
        cout << "5. Urut\n";
        cout << "6. Simpan\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambah(); break;
            case 2: tampil(); break;
            case 3: cari(); break;
            case 4: hapus(); break;
            case 5: urut(); break;
            case 6: simpan(); break;
        }

    } while (pilih != 0);

    return 0;
}