#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstring> 

using namespace std;

const int MAX_DATA = 100; 

struct KTP {
    char nik[20];
    string nama;
    string tempat_tgl_lahir;
    string jenis_kelamin;
    char gol_darah;
    string alamat;
    string rt_rw;
    string kel_desa;
    string kecamatan;
    string agama;
    string status_perkawinan;
    string pekerjaan;
    string kewarganegaraan;
    string berlaku_hingga;
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void inputKTP(KTP &ktp) {
    cout << "Masukkan NIK: ";
    cin >> ktp.nik;
    clearInputBuffer();

    cout << "Masukkan Nama: ";
    getline(cin, ktp.nama);
    cout << "Masukkan Tempat/Tgl Lahir: ";
    getline(cin, ktp.tempat_tgl_lahir);
    cout << "Masukkan Jenis Kelamin: ";
    getline(cin, ktp.jenis_kelamin);
    cout << "Masukkan Golongan Darah (A/B/AB/O): ";
    cin >> ktp.gol_darah;
    clearInputBuffer();

    cout << "Masukkan Alamat: ";
    getline(cin, ktp.alamat);
    cout << "Masukkan RT/RW: ";
    getline(cin, ktp.rt_rw);
    cout << "Masukkan Kelurahan/Desa: ";
    getline(cin, ktp.kel_desa);
    cout << "Masukkan Kecamatan: ";
    getline(cin, ktp.kecamatan);
    cout << "Masukkan Agama: ";
    getline(cin, ktp.agama);
    cout << "Masukkan Status Perkawinan: ";
    getline(cin, ktp.status_perkawinan);
    cout << "Masukkan Pekerjaan: ";
    getline(cin, ktp.pekerjaan);
    cout << "Masukkan Kewarganegaraan: ";
    getline(cin, ktp.kewarganegaraan);
    cout << "Masukkan Berlaku Hingga: ";
    getline(cin, ktp.berlaku_hingga);
}

void displayKTP(const KTP &ktp) {
    cout << "\n================ KTP SIMULASI ================\n";
    cout << left << setw(20) << "NIK" << ": " << ktp.nik << endl;
    cout << left << setw(20) << "Nama" << ": " << ktp.nama << endl;
    cout << left << setw(20) << "Tempat/Tgl Lahir" << ": " << ktp.tempat_tgl_lahir << endl;
    cout << left << setw(20) << "Jenis Kelamin" << ": " << ktp.jenis_kelamin << "    Gol Darah: " << ktp.gol_darah << endl;
    cout << left << setw(20) << "Alamat" << ": " << ktp.alamat << endl;
    cout << left << setw(20) << "RT/RW" << ": " << ktp.rt_rw << endl;
    cout << left << setw(20) << "Kel/Desa" << ": " << ktp.kel_desa << endl;
    cout << left << setw(20) << "Kecamatan" << ": " << ktp.kecamatan << endl;
    cout << left << setw(20) << "Agama" << ": " << ktp.agama << endl;
    cout << left << setw(20) << "Status Perkawinan" << ": " << ktp.status_perkawinan << endl;
    cout << left << setw(20) << "Pekerjaan" << ": " << ktp.pekerjaan << endl;
    cout << left << setw(20) << "Kewarganegaraan" << ": " << ktp.kewarganegaraan << endl;
    cout << left << setw(20) << "Berlaku Hingga" << ": " << ktp.berlaku_hingga << endl;
    cout << "============================================\n";
}

void displayAllKTP(KTP ktp[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "\nData ke-" << i+1 << ":";
        displayKTP(ktp[i]);
    }
}

void bubbleSortByNama(KTP ktp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (ktp[j].nama > ktp[j + 1].nama) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan Nama.\n";
}

void bubbleSortByNIK(KTP ktp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (strcmp(ktp[j].nik, ktp[j + 1].nik) > 0) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan NIK.\n";
}

int main() {
    KTP dataKTP[MAX_DATA];
    int jumlah = 0;
    int pilihan;

    do {
        cout << "\n=== MENU PROGRAM KTP ===\n";
        cout << "1. Input Data KTP\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Urutkan Data (Bubble Sort by Nama)\n";
        cout << "4. Urutkan Data (Bubble Sort by NIK)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                if (jumlah < MAX_DATA) {
                    cout << "\nInput Data ke-" << jumlah+1 << endl;
                    inputKTP(dataKTP[jumlah]);
                    jumlah++;
                } else {
                    cout << "Data penuh!\n";
                }
                break;
            case 2:
                if (jumlah > 0)
                    displayAllKTP(dataKTP, jumlah);
                else
                    cout << "Belum ada data.\n";
                break;
            case 3:
                if (jumlah > 0) {
                    bubbleSortByNama(dataKTP, jumlah);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 4:
                if (jumlah > 0) {
                    bubbleSortByNIK(dataKTP, jumlah);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 0:
                cout << "Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}

