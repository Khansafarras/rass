#include <iostream>
using namespace std;

void jumlah(int *a, int *b, int *result);
void kurang(int *a, int *b, int *result);
void kali(int *a, int *b, int *result);
void bagi(int *a, int *b, float *result);
void cekGenapGanjil(int *num);
void hitungFaktorial(int *num, int *result);
bool cekPrima(int *num);

int main() {
    int angka1, angka2;
    int hasil;
    float hasilBagi;
    
    cout << "Masukkan angka pertama: ";
    cin >> angka1;
    
    cout << "Masukkan angka kedua: ";
    cin >> angka2;
    
    cout << endl << "Hasil operasi:" << endl;
    
    jumlah(&angka1, &angka2, &hasil);
    cout << angka1 << " + " << angka2 << " = " << hasil << endl;
    
    
    kurang(&angka1, &angka2, &hasil);
    cout << angka1 << " - " << angka2 << " = " << hasil << endl;
    
    
    kali(&angka1, &angka2, &hasil);
    cout << angka1 << " * " << angka2 << " = " << hasil << endl;
    
    
    if (angka2 != 0) {
        bagi(&angka1, &angka2, &hasilBagi);
        cout << angka1 << " / " << angka2 << " = " << hasilBagi << endl;
    } else {
        cout << "Tidak bisa melakukan pembagian dengan 0" << endl;
    }
    
    
    cout << endl << "Cek genap/ganjil:" << endl;
    cout << angka1 << " adalah ";
    cekGenapGanjil(&angka1);
    cout << angka2 << " adalah ";
    cekGenapGanjil(&angka2);
    
    
    cout << endl << "Faktorial:" << endl;
    hitungFaktorial(&angka1, &hasil);
    cout << "Faktorial dari " << angka1 << " = " << hasil << endl;
    hitungFaktorial(&angka2, &hasil);
    cout << "Faktorial dari " << angka2 << " = " << hasil << endl;
    
    
    cout << endl << "Cek bilangan prima:" << endl;
    cout << angka1 << (cekPrima(&angka1) ? " adalah bilangan prima" : " bukan bilangan prima") << endl;
    cout << angka2 << (cekPrima(&angka2) ? " adalah bilangan prima" : " bukan bilangan prima") << endl;
    
    return 0;
}


void jumlah(int *a, int *b, int *result) {
    *result = *a + *b;
}

void kurang(int *a, int *b, int *result) {
    *result = *a - *b;
}

void kali(int *a, int *b, int *result) {
    *result = *a * *b;
}

void bagi(int *a, int *b, float *result) {
    *result = (float)*a / *b;
}

void cekGenapGanjil(int *num) {
    if (*num % 2 == 0) {
        cout << "genap" << endl;
    } else {
        cout << "ganjil" << endl;
    }
}

void hitungFaktorial(int *num, int *result) {
    *result = 1;
    for (int i = 1; i <= *num; ++i) {
        *result *= i;
    }
}

bool cekPrima(int *num) {
    if (*num <= 1) return false;
    if (*num == 2) return true;
    if (*num % 2 == 0) return false;
    
    for (int i = 3; i * i <= *num; i += 2) {
        if (*num % i == 0) return false;
    }
    return true;
}

