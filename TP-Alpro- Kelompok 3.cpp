#include <iostream>
#include <iomanip>

using namespace std;

void showMenu();
void takeOrder();
void showBill(int total);
int getPrice(int choice);

int main() {
    char repeat;
    do {
        showMenu();
        takeOrder();
        cout << "Apakah Anda ingin memesan lagi? (y/n): ";
        cin >> repeat;
        cout << endl;
    } while (repeat == 'y' || repeat == 'Y');

    cout << "Terima kasih sudah memesan di Rambat Coffee and Space!" << endl;
    return 0;
}

void showMenu() {
    cout << "=== Menu Rambat Coffee and Space ===" << endl;
    cout << "1. Espresso             - Rp 15.000" << endl;
    cout << "2. Latte                - Rp 20.000" << endl;
    cout << "3. Cappuccino           - Rp 22.000" << endl;
    cout << "4. Americano            - Rp 18.000" << endl;
    cout << "5. Chocolate Cake Slice - Rp 25.000" << endl;
    cout << "6. Cheese Cake Slice    - Rp 30.000" << endl;
    cout << "7. Sandwich             - Rp 20.000" << endl;
    cout << "0. Keluar" << endl;
    cout << "===================================" << endl;
}

void takeOrder() {
    int choice, quantity;
    int total = 0;

    do {
        cout << "Masukkan nomor menu yang ingin dipesan (0 untuk keluar): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 0 || choice > 7) {
            cout << "Pilihan tidak tersedia. Silakan coba lagi." << endl;
            continue;
        }

        cout << "Masukkan jumlah yang ingin dipesan: ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "Jumlah harus lebih dari 0. Silakan coba lagi." << endl;
            continue;
        }

        int price = getPrice(choice);
        total += price * quantity;

        cout << "Anda memesan " << quantity << " item." << endl;

    } while (true);

    if (total > 0) {
        showBill(total);
    } else {
        cout << "Anda tidak memesan apa-apa." << endl;
    }
}

int getPrice(int choice) {
    switch (choice) {
        case 1: return 15000;
        case 2: return 20000;
        case 3: return 22000;
        case 4: return 18000;
        case 5: return 25000;
        case 6: return 30000;
        case 7: return 20000;
        default: return 0;
    }
}

void showBill(int total) {
    cout << "===============================" << endl;
    cout << "Total tagihan Anda: Rp " << fixed << setprecision(0) << total << endl;
    cout << "===============================" << endl;
}


