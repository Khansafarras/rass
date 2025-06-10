#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
};

void inputDataMahasiswa(Mahasiswa data[], int &jumlahData) {
    cout << "--- Input Data Mahasiswa ---" << endl;
    cout << "Masukkan jumlah data mahasiswa (minimal 5): ";
    cin >> jumlahData;

    while (jumlahData < 5) {
        cout << "Jumlah data minimal harus 5. Masukkan lagi: ";
        cin >> jumlahData;
    }

    cin.ignore();

    for (int i = 0; i < jumlahData; ++i) {
        cout << "\nData Mahasiswa ke-" << i + 1 << endl;
        cout << "NIM  : ";
        getline(cin, data[i].nim);
        cout << "Nama : ";
        getline(cin, data[i].nama);
    }
}

void tampilkanDataMahasiswa(const Mahasiswa data[], int jumlahData) {
    cout << "\n--- Data Mahasiswa ---" << endl;
    if (jumlahData == 0) {
        cout << "Belum ada data mahasiswa." << endl;
        return;
    }
    cout << "No.\tNIM\t\tNama" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i < jumlahData; ++i) {
        cout << i + 1 << ".\t" << data[i].nim << "\t\t" << data[i].nama << endl;
    }
    cout << "---------------------------------" << endl;
}

void urutkanNIM(Mahasiswa data[], int jumlahData) {
    for (int i = 0; i < jumlahData - 1; ++i) {
        for (int j = 0; j < jumlahData - i - 1; ++j) {
            if (data[j].nim > data[j + 1].nim) {
                Mahasiswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan NIM secara Ascending." << endl;
}

void cariNIM(const Mahasiswa data[], int jumlahData) {
    string nimCari;
    cout << "\n--- Pencarian Data Mahasiswa Berdasarkan NIM ---" << endl;
    if (jumlahData == 0) {
        cout << "Belum ada data mahasiswa untuk dicari." << endl;
        return;
    }
    cout << "Masukkan NIM yang ingin dicari: ";
    cin.ignore();
    getline(cin, nimCari);

    bool ditemukan = false;
    for (int i = 0; i < jumlahData; ++i) {
        if (data[i].nim == nimCari) {
            cout << "\nData Ditemukan!" << endl;
            cout << "NIM  : " << data[i].nim << endl;
            cout << "Nama : " << data[i].nama << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "NIM '" << nimCari << "' tidak ditemukan." << endl;
    }
}

int main() {
    Mahasiswa daftarMahasiswa[100];
    int jumlahData = 0;
    int pilihan;

    do {
        cout << "\n===== MENU UTAMA =====" << endl;
        cout << "1. Input Data Mahasiswa" << endl;
        cout << "2. Tampilkan Data Mahasiswa" << endl;
        cout << "3. Urutkan Data Mahasiswa (NIM Ascending)" << endl;
        cout << "4. Cari Data Mahasiswa (Berdasarkan NIM)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputDataMahasiswa(daftarMahasiswa, jumlahData);
                break;
            case 2:
                tampilkanDataMahasiswa(daftarMahasiswa, jumlahData);
                break;
            case 3:
                if (jumlahData > 0) {
                    urutkanNIM(daftarMahasiswa, jumlahData);
                    tampilkanDataMahasiswa(daftarMahasiswa, jumlahData);
                } else {
                    cout << "Belum ada data untuk diurutkan." << endl;
                }
                break;
            case 4:
                cariNIM(daftarMahasiswa, jumlahData);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}
