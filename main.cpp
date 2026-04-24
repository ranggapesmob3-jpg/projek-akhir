#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// ================= DATA =================
struct Data {
    int id;
    string nama;
    string film;
    int jumlah;
    int total;
    Data* next;
};

// Linked List
Data* head = NULL;
Data* tail = NULL;

// Stack (undo)
struct Stack {
    Data data;
    Stack* next;
};
Stack* top = NULL;

// Queue (antrian)
struct Queue {
    string nama;
    string film;
    int jumlah;
    Queue* next;
};
Queue* depan = NULL;
Queue* belakang = NULL;

// ================= GLOBAL =================
int no = 1;
int harga = 50000;

string daftarFilm[5] = {
    "Manchester by the sea",
    "Prisonners",
    "Brother",
    "",
    "Batman"
};

// ================= UTIL =================
void tampilFilm() {
    cout << "\n=== DAFTAR FILM ===\n";
    for (int i = 0; i < 5; i++) {
        cout << i+1 << ". " << daftarFilm[i] << endl;
    }
}

int inputJumlah() {
    int j;
    do {
        cout << "Jumlah tiket (>0): ";
        cin >> j;
        if (j <= 0) cout << "Tidak valid!\n";
    } while (j <= 0);
    return j;
}

// ================= LINKED LIST =================
void tambahData(string nama, string film, int jumlah) {
    Data* baru = new Data;
    baru->id = no++;
    baru->nama = nama;
    baru->film = film;
    baru->jumlah = jumlah;
    baru->total = jumlah * harga;
    baru->next = NULL;

    if (!head) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }
}

// ================= QUEUE =================
void enqueue() {
    Queue* baru = new Queue;
    cin.ignore();

    cout << "Nama: ";
    getline(cin, baru->nama);

    tampilFilm();
    int pilih;
    cout << "Pilih film: ";
    cin >> pilih;

    if (pilih < 1 || pilih > 5) {
        cout << "Film tidak valid!\n";
        return;
    }

    baru->film = daftarFilm[pilih-1];
    baru->jumlah = inputJumlah();
    baru->next = NULL;

    if (!belakang) depan = belakang = baru;
    else {
        belakang->next = baru;
        belakang = baru;
    }

    cout << "Masuk antrian!\n";
}

void dequeue() {
    if (!depan) {
        cout << "Antrian kosong\n";
        return;
    }

    Queue* ambil = depan;
    depan = depan->next;
    if (!depan) belakang = NULL;

    tambahData(ambil->nama, ambil->film, ambil->jumlah);
    delete ambil;

    cout << "Antrian diproses\n";
}

// ================= STACK =================
void pushStack(Data data) {
    Stack* baru = new Stack;
    baru->data = data;
    baru->next = top;
    top = baru;
}

void popStack() {
    if (!top) {
        cout << "Tidak ada undo\n";
        return;
    }

    Stack* ambil = top;
    top = top->next;

    tambahData(ambil->data.nama, ambil->data.film, ambil->data.jumlah);
    delete ambil;

    cout << "Undo berhasil\n";
}

// ================= FITUR =================
void tampil() {
    Data* temp = head;

    cout << "\n=== DATA PEMESANAN ===\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Nama"
         << setw(15) << "Film"
         << setw(10) << "Tiket"
         << setw(10) << "Total" << endl;

    while (temp) {
        cout << setw(5) << temp->id
             << setw(15) << temp->nama
             << setw(15) << temp->film
             << setw(10) << temp->jumlah
             << setw(10) << temp->total << endl;
        temp = temp->next;
    }
}

void cari() {
    string nama;
    cin.ignore();
    cout << "Cari nama: ";
    getline(cin, nama);

    Data* temp = head;
    bool ketemu = false;

    while (temp) {
        if (temp->nama == nama) {
            cout << "Ditemukan: " << temp->film << " (" << temp->jumlah << " tiket)\n";
            ketemu = true;
        }
        temp = temp->next;
    }

    if (!ketemu) cout << "Tidak ditemukan\n";
}

void hapus() {
    int id;
    cout << "ID hapus: ";
    cin >> id;

    Data *temp = head, *prev = NULL;

    while (temp) {
        if (temp->id == id) {
            pushStack(*temp);

            if (temp == head) head = head->next;
            else prev->next = temp->next;

            if (temp == tail) tail = prev;

            delete temp;
            cout << "Data dihapus\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Tidak ditemukan\n";
}

void urut() {
    for (Data* i = head; i; i = i->next) {
        for (Data* j = i->next; j; j = j->next) {
            if (i->jumlah > j->jumlah) {
                swap(i->id, j->id);
                swap(i->nama, j->nama);
                swap(i->film, j->film);
                swap(i->jumlah, j->jumlah);
                swap(i->total, j->total);
            }
        }
    }
    cout << "Data diurutkan\n";
}

// ================= FILE =================
void simpan() {
    ofstream file("data.txt");
    Data* temp = head;

    while (temp) {
        file << temp->id << "|"
             << temp->nama << "|"
             << temp->film << "|"
             << temp->jumlah << endl;
        temp = temp->next;
    }
    file.close();
}

void load() {
    ifstream file("data.txt");
    if (!file) return;

    string nama, film;
    int id, jumlah;
    char delim;

    while (file >> id >> delim) {
        getline(file, nama, '|');
        getline(file, film, '|');
        file >> jumlah;

        tambahData(nama, film, jumlah);
    }
}

// ================= MAIN =================
int main() {
    int pilih;
    load();

    do {
        cout << "\n=== BIOSKOP PRO+ ===\n";
        cout << "1. Masuk Antrian\n";
        cout << "2. Proses Antrian\n";
        cout << "3. Tampil Data\n";
        cout << "4. Cari\n";
        cout << "5. Hapus\n";
        cout << "6. Undo\n";
        cout << "7. Urut\n";
        cout << "8. Simpan\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: tampil(); break;
            case 4: cari(); break;
            case 5: hapus(); break;
            case 6: popStack(); break;
            case 7: urut(); break;
            case 8: simpan(); break;
        }

    } while (pilih != 0);

    simpan();
    return 0;
}