#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Harga per item
    const double HARGA_AYAM_GORENG = 17000.0;
    const double HARGA_AYAM_BAKAR = 21000.0;
    const double BATAS_DISKON = 45000.0;
    const double PERSEN_DISKON = 0.10; // 10%

    // Variabel untuk menyimpan jumlah pesanan
    int jumlah_goreng;
    int jumlah_bakar;

    // Meminta input jumlah pesanan
    cout << "=====================================" << endl;
    cout << "         KEDAI AYAM MAREM" << endl;
    cout << "=====================================" << endl;
    cout << "Menu:" << endl;
    cout << "1. Ayam Goreng (Rp" << fixed << setprecision(0) << HARGA_AYAM_GORENG << ")" << endl;
    cout << "2. Ayam Bakar  (Rp" << fixed << setprecision(0) << HARGA_AYAM_BAKAR << ")" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Masukkan jumlah Ayam Goreng: ";
    cin >> jumlah_goreng;
    cout << "Masukkan jumlah Ayam Bakar: ";
    cin >> jumlah_bakar;
    cout << "-------------------------------------" << endl;

    // Menghitung total harga sebelum diskon
    double total_harga = (jumlah_goreng * HARGA_AYAM_GORENG) + (jumlah_bakar * HARGA_AYAM_BAKAR);

    // Menghitung diskon jika total pembelian melebihi batas
    double diskon = 0.0;
    if (total_harga > BATAS_DISKON) {
        diskon = total_harga * PERSEN_DISKON;
    }

    // Menghitung total harga setelah diskon
    double total_bayar = total_harga - diskon;

    // Menampilkan struk pembayaran
    cout << "\n========= STRUK PEMBAYARAN =========" << endl;
    cout << fixed << setprecision(0); // Set presisi untuk bilangan bulat

    if (jumlah_goreng > 0) {
        cout << left << setw(15) << "Ayam Goreng" << " x " << right << setw(2) << jumlah_goreng << " @ Rp" << right << setw(8) << HARGA_AYAM_GORENG << " = Rp" << right << setw(9) << (jumlah_goreng * HARGA_AYAM_GORENG) << endl;
    }
    if (jumlah_bakar > 0) {
        cout << left << setw(15) << "Ayam Bakar" << " x " << right << setw(2) << jumlah_bakar << " @ Rp" << right << setw(8) << HARGA_AYAM_BAKAR << " = Rp" << right << setw(9) << (jumlah_bakar * HARGA_AYAM_BAKAR) << endl;
    }
    cout << "-------------------------------------" << endl;
    cout << left << setw(26) << "Subtotal" << " = Rp" << right << setw(9) << total_harga << endl;

    if (diskon > 0) {
        cout << left << setw(26) << "Diskon (10%)" << " = -Rp" << right << setw(9) << diskon << endl;
        cout << "-------------------------------------" << endl;
    }

    cout << left << setw(26) << "Total Bayar" << " = Rp" << right << setw(9) << total_bayar << endl;
    cout << "=====================================" << endl;
    cout << "        TERIMA KASIH ATAS" << endl;
    cout << "           KUNJUNGAN ANDA!" << endl;
    cout << "=====================================" << endl;

    return 0;
}
