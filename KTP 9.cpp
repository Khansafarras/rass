#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstring> 

using namespace std;

const int MAX_DATA = 100; 

class KTP {
private:
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

public:
    void inputKTP() {
        cout << "Masukkan NIK: ";
        cin >> nik;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Masukkan Nama: ";
        getline(cin, nama);
        cout << "Masukkan Tempat/Tgl Lahir: ";
        getline(cin, tempat_tgl_lahir);
        cout << "Masukkan Jenis Kelamin: ";
        getline(cin, jenis_kelamin);
        cout << "Masukkan Golongan Darah (A/B/AB/O): ";
        cin >> gol_darah;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Masukkan Alamat: ";
        getline(cin, alamat);
        cout << "Masukkan RT/RW: ";
        getline(cin, rt_rw);
        cout << "Masukkan Kelurahan/Desa: ";
        getline(cin, kel_desa);
        cout << "Masukkan Kecamatan: ";
        getline(cin, kecamatan);
        cout << "Masukkan Agama: ";
        getline(cin, agama);
        cout << "Masukkan Status Perkawinan: ";
        getline(cin, status_perkawinan);
        cout << "Masukkan Pekerjaan: ";
        getline(cin, pekerjaan);
        cout << "Masukkan Kewarganegaraan: ";
        getline(cin, kewarganegaraan);
        cout << "Masukkan Berlaku Hingga: ";
        getline(cin, berlaku_hingga);
    }

    void displayKTP() const {
        cout << "\n--------------------------------------------\n";
        cout << left << setw(20) << "NIK" << ": " << nik << endl;
        cout << left << setw(20) << "Nama" << ": " << nama << endl;
        cout << left << setw(20) << "Tempat/Tgl Lahir" << ": " << tempat_tgl_lahir << endl;
        cout << left << setw(20) << "Jenis Kelamin" << ": " << jenis_kelamin << "    Gol Darah: " << gol_darah << endl;
        cout << left << setw(20) << "Alamat" << ": " << alamat << endl;
        cout << left << setw(20) << "RT/RW" << ": " << rt_rw << endl;
        cout << left << setw(20) << "Kel/Desa" << ": " << kel_desa << endl;
        cout << left << setw(20) << "Kecamatan" << ": " << kecamatan << endl;
        cout << left << setw(20) << "Agama" << ": " << agama << endl;
        cout << left << setw(20) << "Status Perkawinan" << ": " << status_perkawinan << endl;
        cout << left << setw(20) << "Pekerjaan" << ": " << pekerjaan << endl;
        cout << left << setw(20) << "Kewarganegaraan" << ": " << kewarganegaraan << endl;
        cout << left << setw(20) << "Berlaku Hingga" << ": " << berlaku_hingga << endl;
        cout << "--------------------------------------------\n";
    }

    const char* getNIK() const {
        return nik;
    }

    string getNama() const {
        return nama;
    }
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayAllKTP(const KTP ktp[], int jumlah) {
    cout << "\n=================== KTP ===================\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "\nData ke-" << i + 1 << ":";
        ktp[i].displayKTP();
    }
    cout << "============================================\n";
}

void bubbleSortByNama(KTP ktp[], int jumlah, bool ascending = true) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            bool condition = ascending ? (ktp[j].getNama() > ktp[j + 1].getNama()) 
                                       : (ktp[j].getNama() < ktp[j + 1].getNama());
            if (condition) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan Nama " << (ascending ? "Ascending" : "Descending") << ".\n";
}

void bubbleSortByNIK(KTP ktp[], int jumlah, bool ascending = true) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            bool condition = ascending ? (strcmp(ktp[j].getNIK(), ktp[j + 1].getNIK()) > 0) 
                                       : (strcmp(ktp[j].getNIK(), ktp[j + 1].getNIK()) < 0);
            if (condition) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan NIK " << (ascending ? "Ascending" : "Descending") << ".\n";
}


void sortByNama(KTP ktp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (ktp[j].getNama() > ktp[j + 1].getNama()) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan Nama (Ascending).\n";
}


void sortByNIK(KTP ktp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (strcmp(ktp[j].getNIK(), ktp[j + 1].getNIK()) > 0) {
                KTP temp = ktp[j];
                ktp[j] = ktp[j + 1];
                ktp[j + 1] = temp;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan NIK (Ascending).\n";
}

int main() {
    KTP dataKTP[MAX_DATA];
    int jumlah = 0;
    int pilihan;

    do {
        cout << "\n=== MENU PROGRAM KTP ===\n";
        cout << "1. Input Data KTP\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Urutkan Data (Nama Ascending)\n";
        cout << "4. Urutkan Data (Nama Descending)\n";
        cout << "5. Urutkan Data (NIK Ascending)\n";
        cout << "6. Urutkan Data (NIK Descending)\n";
        cout << "7. Urutkan Data (Nama)\n";
        cout << "8. Urutkan Data (NIK)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                if (jumlah < MAX_DATA) {
                    cout << "\nInput Data ke-" << jumlah + 1 << endl;
                    dataKTP[jumlah].inputKTP();
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
                    bubbleSortByNama(dataKTP, jumlah, true);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 4:
                if (jumlah > 0) {
                    bubbleSortByNama(dataKTP, jumlah, false);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 5:
                if (jumlah > 0) {
                    bubbleSortByNIK(dataKTP, jumlah, true);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 6:
                if (jumlah > 0) {
                    bubbleSortByNIK(dataKTP, jumlah, false);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 7:
                if (jumlah > 0) {
                    sortByNama(dataKTP, jumlah);
                    displayAllKTP(dataKTP, jumlah);
                } else {
                    cout << "Belum ada data.\n";
                }
                break;
            case 8:
                if (jumlah > 0) {
                    sortByNIK(dataKTP, jumlah);
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

