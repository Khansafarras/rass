#include <iostream>
#include <iomanip>

using namespace std;

class Matriks {
    friend ostream& operator<<(ostream&, Matriks&);
    friend istream& operator>>(istream&, Matriks&);

public:
    void baca_matriks();
    void matriks_jumlah(const Matriks&, const Matriks&);
    void perkalian_matriks(const Matriks&, const Matriks&);
    void cetak_matriks();

private:
    int A[10][10];
    int baris, kolom;
};

// Fungsi untuk membaca input matriks
void Matriks::baca_matriks() {
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            cout << "Data [" << i + 1 << "," << j + 1 << "] : ";
            cin >> A[i][j];
        }
    }
}

// Fungsi penjumlahan dua matriks
void Matriks::matriks_jumlah(const Matriks& matriks1, const Matriks& matriks2) {
    baris = matriks1.baris;
    kolom = matriks1.kolom;
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            A[i][j] = matriks1.A[i][j] + matriks2.A[i][j];
        }
    }
}

// Fungsi perkalian dua matriks
void Matriks::perkalian_matriks(const Matriks& matriks1, const Matriks& matriks2) {
    int barkol = matriks1.kolom;
    baris = matriks1.baris;
    kolom = matriks2.kolom;

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
                A[i][j] = matriks1.A[i][j] * matriks2.A[i][j];
            
        }
    }
}

// Fungsi mencetak isi matriksx
void Matriks::cetak_matriks() {
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            cout << setw(5) << A[i][j] << " ";
        }
        cout << endl;
    }
}

// Overload operator >> untuk input
istream& operator>>(istream& in, Matriks& A) {
    cout << "Banyak baris : ";
    in >> A.baris;
    cout << "Banyak kolom : ";
    in >> A.kolom;
    cout << "Masukkan data matriks\n";
    A.baca_matriks();
    cout << "Matriks yang dibuat adalah : \n";
    A.cetak_matriks();
    return in;
}

// Overload operator << untuk output
ostream& operator<<(ostream& out, Matriks& A) {
    for (int i = 0; i < A.baris; i++) {
        for (int j = 0; j < A.kolom; j++) {
            out << setw(5) << A.A[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

// Fungsi utama
int main() {
    Matriks matriks1, matriks2;
    Matriks jumlah;

    cout << "Memasukkan data matriks I\n";
    cin >> matriks1;

    cout << "Memasukkan data matriks II\n";
    cin >> matriks2;

    jumlah.matriks_jumlah(matriks1, matriks2);
    cout << "\nHasil Penjumlahan:\n";
    jumlah.cetak_matriks();

    jumlah.perkalian_matriks(matriks1, matriks2);
    cout << "\nHasil Perkalian:\n";
    jumlah.cetak_matriks();

    return 0;
}
