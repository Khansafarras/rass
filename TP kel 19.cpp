#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <limits>
#include <cctype>
#include <vector>
#include <map>

using namespace std;
const string CAFE_ADDRESS = "Jl.Ki Hajar Dewantara No.03 kec. Bantul Daerah Istimewa Yogyakarta";
const int POINTS_PER_TRANSACTION = 1;
const int FREE_DRINK_THRESHOLD = 1000;

string loggedInCashierName = "N/A";

class MenuStock
{
private:
    map<int, int> stockMap;

public:
    MenuStock()
    {
        for (int i = 1; i <= 19; i++)
        {
            stockMap[i] = 50;
        }

        for (int i = 20; i <= 35; i++)
        {
            stockMap[i] = 30;
        }
    }

    bool checkStock(int menuChoice, int quantity)
    {
        if (stockMap.find(menuChoice) == stockMap.end())
            return false;
        return stockMap[menuChoice] >= quantity;
    }

    void reduceStock(int menuChoice, int quantity)
    {
        if (stockMap.find(menuChoice) != stockMap.end())
        {
            stockMap[menuChoice] -= quantity;
        }
    }

    void restoreStock(int menuChoice, int quantity)
    {
        if (stockMap.find(menuChoice) != stockMap.end())
        {
            stockMap[menuChoice] += quantity;
        }
    }

    int getStock(int menuChoice)
    {
        if (stockMap.find(menuChoice) != stockMap.end())
        {
            return stockMap[menuChoice];
        }
        return 0;
    }
};

class CustomerPoints
{
private:
    int points;

public:
    CustomerPoints() : points(0) {}

    void addPoints(int amount)
    {
        points += amount;
    }

    int getPoints() const
    {
        return points;
    }

    bool redeemFreeDrink()
    {
        if (points >= FREE_DRINK_THRESHOLD)
        {
            points -= FREE_DRINK_THRESHOLD;
            return true;
        }
        return false;
    }
};

struct OrderItem
{
    int menuChoice;
    int quantity;
    int sugarChoice;
    int iceChoice;
};

void showDrinkMenu();
void showFoodMenu();
void takeOrder(vector<OrderItem> &currentOrder, MenuStock &stock);
void editOrder(vector<OrderItem> &currentOrder, MenuStock &stock);
void showBill(const vector<OrderItem> &currentOrder);
void processPayment(const vector<OrderItem> &currentOrder, const string &cashierName,
                    const string &transactionDay, const string &transactionTime,
                    bool isTakeaway, bool isOnlineOrder, double shippingCost,
                    int additionalFee, CustomerPoints &customerPoints);
int getPrice(int choice);
void adminLogin();
void customerLogin(MenuStock &stock, CustomerPoints &customerPoints);
void searchMenu(const string &category);
bool isAdmin(const string &username, const string &password);
double calculateDiscount(int total);
double calculateShippingCost(double weight, double distance);
void displayQRIS();
void clearInputBuffer();
int getSugarFee(int sugarChoice);
int getIceFee(int iceChoice);
int calculateTotalFromOrder(const vector<OrderItem> &currentOrder);
string getMenuName(int choice);

// Selection sort implementation for currentOrder vector based on menuChoice
void selectionSortOrder(vector<OrderItem> &currentOrder)
{
    int n = currentOrder.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (currentOrder[j].menuChoice < currentOrder[minIndex].menuChoice)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(currentOrder[i], currentOrder[minIndex]);
        }
    }
}

int main()
{
    MenuStock stock;
    CustomerPoints customerPoints;

    cout << "=== Selamat Datang di Rambat Coffee and Space ===" << endl;
    cout << "Silakan masukkan nama kasir untuk memulai: ";
    getline(cin, loggedInCashierName);

    if (loggedInCashierName.empty())
    {
        cout << "Nama kasir tidak boleh kosong. Program akan keluar." << endl;
        return 1;
    }
    cout << "Selamat datang, " << loggedInCashierName << "!" << endl;

    int option;
    do
    {
        cout << "\n=== Menu Utama ===" << endl;
        cout << "1. Login sebagai Admin" << endl;
        cout << "2. Proses Pesanan Pelanggan" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi: ";
        while (!(cin >> option))
        {
            cout << "Input tidak valid. Silakan masukkan angka (0, 1, atau 2): ";
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (option)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            customerLogin(stock, customerPoints);
            break;
        case 0:
            cout << "Terima kasih " << loggedInCashierName << " sudah bekerja hari ini!" << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (true);
}

void showDrinkMenu()
{
    cout << "\n=== Menu Minuman Rambat Coffee and Space ===" << endl;
    cout << "1. Espresso                     - Rp 15.000" << endl;
    cout << "2. Latte                        - Rp 20.000" << endl;
    cout << "3. Cappuccino                   - Rp 22.000" << endl;
    cout << "4. Americano                    - Rp 18.000" << endl;
    cout << "5. Aruna                        - Rp 28.000" << endl;
    cout << "6. Flavour                      - Rp 28.000" << endl;
    cout << "7. Scottchies                   - Rp 27.000" << endl;
    cout << "8. Karibia                      - Rp 25.000" << endl;
    cout << "9. Cinema Pop Corn              - Rp 26.000" << endl;
    cout << "10. Havana                      - Rp 26.000" << endl;
    cout << "11. Chocoreo                    - Rp 25.000" << endl;
    cout << "12. Snow White                  - Rp 28.000" << endl;
    cout << "13. Redvelvet Cheese Cake       - Rp 30.000" << endl;
    cout << "14. Blackforest                 - Rp 28.000" << endl;
    cout << "15. Classic Gold Caramel        - Rp 25.000" << endl;
    cout << "16. White Noise                 - Rp 23.000" << endl;
    cout << "17. Caffe Latte                 - Rp 20.000" << endl;
    cout << "18. Cafe Moca                   - Rp 22.000" << endl;
    cout << "19. Caramel Macchiato           - Rp 25.000" << endl;
    cout << "=============================================" << endl;
}

void showFoodMenu()
{
    cout << "\n=== Menu Makanan Rambat Coffee and Space ===" << endl;
    cout << "20. Chocolate Cake Slice        - Rp 25.000" << endl;
    cout << "21. Cheese Cake Slice           - Rp 30.000" << endl;
    cout << "22. Sandwich                    - Rp 20.000" << endl;
    cout << "23. Spaghetti Carbonara         - Rp 45.000" << endl;
    cout << "24. Spaghetti Aglio Prawn       - Rp 35.000" << endl;
    cout << "25. Spaghetti Bolognese         - Rp 38.000" << endl;
    cout << "26. Ayam Bakar Madu             - Rp 43.000" << endl;
    cout << "27. Mie Goreng Fish Ball        - Rp 45.000" << endl;
    cout << "28. Teri Medan Fried Rice       - Rp 35.000" << endl;
    cout << "29. Mie Goreng Jawa             - Rp 35.000" << endl;
    cout << "30. Nasi Goreng Kampoeng        - Rp 40.000" << endl;
    cout << "31. Nasi Goreng Smoke           - Rp 45.000" << endl;
    cout << "32. Ayam Taliwang               - Rp 48.000" << endl;
    cout << "33. Iga Bakar Balado            - Rp 55.000" << endl;
    cout << "34. Iga Bakar Kecap             - Rp 58.000" << endl;
    cout << "35. Japanese Curry Katsu        - Rp 47.000" << endl;
    cout << "=============================================" << endl;
}

void takeOrder(vector<OrderItem> &currentOrder, MenuStock &stock)
{
    int choice, quantity;
    int sugarChoice, iceChoice;

    do
    {
        cout << "\nPilih kategori menu:" << endl;
        cout << "1. Minuman" << endl;
        cout << "2. Makanan" << endl;
        cout << "0. Kembali ke menu utama" << endl;
        cout << "Pilihan: ";
        while (!(cin >> choice))
        {
            cout << "Input tidak valid. Silakan masukkan angka: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (choice == 0)
            break;

        if (choice == 1)
            showDrinkMenu();
        else if (choice == 2)
            showFoodMenu();
        else
        {
            cout << "Pilihan tidak valid!" << endl;
            continue;
        }

        cout << "Masukkan nomor menu yang ingin dipesan (0 untuk kembali): ";
        while (!(cin >> choice))
        {
            cout << "Input tidak valid. Silakan masukkan angka: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (choice == 0)
        {
            continue;
        }

        if ((choice < 1 || choice > 35) && choice != 0)
        {
            cout << "Pilihan menu tidak tersedia. Silakan coba lagi." << endl;
            continue;
        }

        int price = getPrice(choice);
        if (price == 0)
        {
            cout << "Pilihan menu tidak tersedia. Silakan coba lagi." << endl;
            continue;
        }

        cout << "Stok tersedia: " << stock.getStock(choice) << endl;
        cout << "Masukkan jumlah yang ingin dipesan: ";
        while (!(cin >> quantity) || quantity <= 0)
        {
            cout << "Jumlah tidak valid. Masukkan angka positif: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (!stock.checkStock(choice, quantity))
        {
            cout << "Maaf, stok tidak mencukupi. Stok tersedia: " << stock.getStock(choice) << endl;
            continue;
        }

        sugarChoice = 1;
        iceChoice = 1;

        if (choice >= 1 && choice <= 19)
        {
            cout << "Pilih tingkat gula:" << endl;
            cout << "1. Normal" << endl;
            cout << "2. Rendah Gula" << endl;
            cout << "3. Ekstra Gula (Tambah Rp 3.000)" << endl;
            cout << "Pilih opsi (1/2/3): ";
            while (!(cin >> sugarChoice) || (sugarChoice < 1 || sugarChoice > 3))
            {
                cout << "Pilihan tidak valid. Silakan masukkan 1, 2, atau 3: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            cout << "Pilih tingkat es batu:" << endl;
            cout << "1. Normal" << endl;
            cout << "2. Sedikit Es Batu" << endl;
            cout << "3. Ekstra Es Batu (Tambah Rp 3.000)" << endl;
            cout << "Pilih opsi (1/2/3): ";
            while (!(cin >> iceChoice) || (iceChoice < 1 || iceChoice > 3))
            {
                cout << "Pilihan tidak valid. Silakan masukkan 1, 2, atau 3: ";
                clearInputBuffer();
            }
            clearInputBuffer();
        }

        bool foundExisting = false;
        for (size_t i = 0; i < currentOrder.size(); i++)
        {
            OrderItem &item = currentOrder[i];
            if (item.menuChoice == choice && item.sugarChoice == sugarChoice && item.iceChoice == iceChoice)
            {
                if (stock.checkStock(choice, item.quantity + quantity))
                {
                    item.quantity += quantity;
                    stock.reduceStock(choice, quantity);
                    foundExisting = true;
                    break;
                }
                else
                {
                    cout << "Maaf, stok tidak mencukupi untuk menambah pesanan ini." << endl;
                    foundExisting = true;
                    break;
                }
            }
        }

        if (!foundExisting)
        {
            OrderItem newItem;
            newItem.menuChoice = choice;
            newItem.quantity = quantity;
            newItem.sugarChoice = sugarChoice;
            newItem.iceChoice = iceChoice;
            currentOrder.push_back(newItem);
            stock.reduceStock(choice, quantity);
        }

        cout << "Anda memesan " << quantity << " " << getMenuName(choice) << "." << endl;

    } while (true);
}

void editOrder(vector<OrderItem> &currentOrder, MenuStock &stock)
{
    if (currentOrder.empty())
    {
        cout << "Tidak ada pesanan yang bisa diedit." << endl;
        return;
    }

    int choice;
    do
    {
        cout << "\n=== Daftar Pesanan Saat Ini ===" << endl;
        for (size_t idx = 0; idx < currentOrder.size(); idx++)
        {
            OrderItem &item = currentOrder[idx];
            string menuName = getMenuName(item.menuChoice);
            string sugarText = "";
            if (item.menuChoice >= 1 && item.menuChoice <= 19)
            {
                switch (item.sugarChoice)
                {
                case 1:
                    sugarText = "Normal Gula";
                    break;
                case 2:
                    sugarText = "Rendah Gula";
                    break;
                case 3:
                    sugarText = "Ekstra Gula";
                    break;
                }
            }
            string iceText = "";
            if (item.menuChoice >= 1 && item.menuChoice <= 19)
            {
                switch (item.iceChoice)
                {
                case 1:
                    iceText = "Normal Es";
                    break;
                case 2:
                    iceText = "Sedikit Es";
                    break;
                case 3:
                    iceText = "Ekstra Es";
                    break;
                }
            }
            cout << (idx + 1) << ". " << menuName << " | Jumlah: " << item.quantity;
            if (!sugarText.empty() || !iceText.empty())
            {
                cout << " | " << sugarText << " - " << iceText;
            }
            cout << " | Subtotal: Rp " << fixed << setprecision(0)
                 << (getPrice(item.menuChoice) * item.quantity +
                     getSugarFee(item.sugarChoice) * item.quantity +
                     getIceFee(item.iceChoice) * item.quantity);
            cout << endl;
        }
        cout << (currentOrder.size() + 1) << ". Selesai mengedit pesanan" << endl;
        cout << "Pilih nomor item yang ingin diedit (atau " << (currentOrder.size() + 1) << " untuk selesai): ";
        while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(currentOrder.size() + 1))
        {
            cout << "Pilihan tidak valid. Silakan masukkan nomor yang sesuai: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (choice == static_cast<int>(currentOrder.size() + 1))
        {
            break;
        }

        OrderItem &itemToEdit = currentOrder[choice - 1];
        int newQuantity;

        cout << "Masukkan jumlah baru (0 untuk menghapus item): ";
        while (!(cin >> newQuantity) || newQuantity < 0)
        {
            cout << "Jumlah tidak valid. Masukkan angka >= 0: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        if (newQuantity == 0)
        {
            stock.restoreStock(itemToEdit.menuChoice, itemToEdit.quantity);
            currentOrder.erase(currentOrder.begin() + (choice - 1));
            cout << "Item dihapus dari pesanan." << endl;
        }
        else
        {
            int quantityChange = newQuantity - itemToEdit.quantity;

            if (stock.checkStock(itemToEdit.menuChoice, quantityChange))
            {

                if (quantityChange > 0)
                {
                    stock.reduceStock(itemToEdit.menuChoice, quantityChange);
                }
                else
                {
                    stock.restoreStock(itemToEdit.menuChoice, -quantityChange);
                }

                itemToEdit.quantity = newQuantity;

                if (itemToEdit.menuChoice >= 1 && itemToEdit.menuChoice <= 19)
                {
                    int newSugarChoice, newIceChoice;

                    cout << "Pilih tingkat gula:" << endl;
                    cout << "1. Normal" << endl;
                    cout << "2. Rendah Gula" << endl;
                    cout << "3. Ekstra Gula (Tambah Rp 3.000)" << endl;
                    cout << "Pilih opsi (1/2/3): ";
                    while (!(cin >> newSugarChoice) || (newSugarChoice < 1 || newSugarChoice > 3))
                    {
                        cout << "Pilihan tidak valid. Silakan masukkan 1, 2, atau 3: ";
                        clearInputBuffer();
                    }
                    clearInputBuffer();

                    cout << "Pilih tingkat es batu:" << endl;
                    cout << "1. Normal" << endl;
                    cout << "2. Sedikit Es Batu" << endl;
                    cout << "3. Ekstra Es Batu (Tambah Rp 3.000)" << endl;
                    cout << "Pilih opsi (1/2/3): ";
                    while (!(cin >> newIceChoice) || (newIceChoice < 1 || newIceChoice > 3))
                    {
                        cout << "Pilihan tidak valid. Silakan masukkan 1, 2, atau 3: ";
                        clearInputBuffer();
                    }
                    clearInputBuffer();

                    itemToEdit.sugarChoice = newSugarChoice;
                    itemToEdit.iceChoice = newIceChoice;
                }
                cout << "Item berhasil diperbarui." << endl;
            }
            else
            {
                cout << "Maaf, stok tidak mencukupi untuk perubahan ini." << endl;
            }
        }
    } while (true);
}

string getMenuName(int choice)
{
    switch (choice)
    {
    case 1:
        return "Espresso";
    case 2:
        return "Latte";
    case 3:
        return "Cappuccino";
    case 4:
        return "Americano";
    case 5:
        return "Aruna";
    case 6:
        return "Flavour";
    case 7:
        return "Scottchies";
    case 8:
        return "Karibia";
    case 9:
        return "Cinema Pop Corn";
    case 10:
        return "Havana";
    case 11:
        return "Chocoreo";
    case 12:
        return "Snow White";
    case 13:
        return "Redvelvet Cheese Cake";
    case 14:
        return "Blackforest";
    case 15:
        return "Classic Gold Caramel";
    case 16:
        return "White Noise";
    case 17:
        return "Caffe Latte";
    case 18:
        return "Cafe Moca";
    case 19:
        return "Caramel Macchiato";
    case 20:
        return "Chocolate Cake Slice";
    case 21:
        return "Cheese Cake Slice";
    case 22:
        return "Sandwich";
    case 23:
        return "Spaghetti Carbonara";
    case 24:
        return "Spaghetti Aglio Prawn";
    case 25:
        return "Spaghetti Bolognese";
    case 26:
        return "Ayam Bakar Madu";
    case 27:
        return "Mie Goreng Fish Ball";
    case 28:
        return "Teri Medan Fried Rice";
    case 29:
        return "Mie Goreng Jawa";
    case 30:
        return "Nasi Goreng Kampoeng";
    case 31:
        return "Nasi Goreng Smoke";
    case 32:
        return "Ayam Taliwang";
    case 33:
        return "Iga Bakar Balado";
    case 34:
        return "Iga Bakar Kecap";
    case 35:
        return "Japanese Curry Katsu";
    default:
        return "Unknown";
    }
}

int getPrice(int choice)
{
    switch (choice)
    {
    case 1:
        return 15000;
    case 2:
        return 20000;
    case 3:
        return 22000;
    case 4:
        return 18000;
    case 5:
        return 28000;
    case 6:
        return 28000;
    case 7:
        return 27000;
    case 8:
        return 25000;
    case 9:
        return 26000;
    case 10:
        return 26000;
    case 11:
        return 25000;
    case 12:
        return 28000;
    case 13:
        return 30000;
    case 14:
        return 28000;
    case 15:
        return 25000;
    case 16:
        return 23000;
    case 17:
        return 20000;
    case 18:
        return 22000;
    case 19:
        return 25000;
    case 20:
        return 25000;
    case 21:
        return 30000;
    case 22:
        return 20000;
    case 23:
        return 45000;
    case 24:
        return 35000;
    case 25:
        return 38000;
    case 26:
        return 43000;
    case 27:
        return 45000;
    case 28:
        return 35000;
    case 29:
        return 35000;
    case 30:
        return 40000;
    case 31:
        return 45000;
    case 32:
        return 48000;
    case 33:
        return 55000;
    case 34:
        return 58000;
    case 35:
        return 47000;
    default:
        return 0;
    }
}

int getSugarFee(int sugarChoice)
{
    return (sugarChoice == 3) ? 3000 : 0;
}

int getIceFee(int iceChoice)
{
    return (iceChoice == 3) ? 3000 : 0;
}

double calculateDiscount(int total)
{
    if (total >= 150000)
    {
        cout << "Selamat! Anda mendapatkan diskon 15%!" << endl;
        return total * 0.15;
    }
    return 0.0;
}

double calculateShippingCost(double weight, double distance)
{
    double costPerKg = 5000.0;
    double costPerKm = 2000.0;
    return (weight * costPerKg) + (distance * costPerKm);
}

void showBill(const vector<OrderItem> &currentOrder)
{
    if (currentOrder.empty())
    {
        cout << "Tidak ada pesanan yang dibuat." << endl;
        return;
    }

    cout << "\n===============================" << endl;
    cout << "       DETAIL PESANAN ANDA       " << endl;
    cout << "===============================" << endl;

    int total = 0;
    for (size_t i = 0; i < currentOrder.size(); i++)
    {
        const OrderItem &item = currentOrder[i];
        int price = getPrice(item.menuChoice);
        int sugarFee = getSugarFee(item.sugarChoice);
        int iceFee = getIceFee(item.iceChoice);
        int subtotal = (price * item.quantity) + sugarFee * item.quantity + iceFee * item.quantity;
        total += subtotal;

        string menuName = getMenuName(item.menuChoice);

        cout << left << setw(3) << (i + 1) << ". "
             << left << setw(25) << menuName
             << " x" << setw(3) << item.quantity;

        if (item.menuChoice >= 1 && item.menuChoice <= 19)
        {
            string sugarText = (item.sugarChoice == 1) ? "Normal Gula" : (item.sugarChoice == 2) ? "Rendah Gula"
                                                                                                 : "Ekstra Gula";
            string iceText = (item.iceChoice == 1) ? "Normal Es" : (item.iceChoice == 2) ? "Sedikit Es"
                                                                                         : "Ekstra Es";
            cout << " (" << sugarText << " - " << iceText << ")";
        }

        cout << right << setw(10) << "Rp " << fixed << setprecision(0) << subtotal << endl;
    }

    cout << "-------------------------------" << endl;
    cout << "TOTAL BELANJA: Rp " << fixed << setprecision(0) << total << endl;
    cout << "===============================" << endl;
}

void displayQRIS()
{
    cout << "\n-----------------------------------" << endl;
    cout << "         Scan QRIS untuk Bayar        " << endl;
    cout << "-----------------------------------" << endl;
    cout << "  [QRIS IMAGE PLACEHOLDER]  " << endl;
    cout << "Silakan lakukan pembayaran melalui aplikasi e-wallet Anda." << endl;
    cout << "Tekan ENTER setelah pembayaran berhasil." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << "Pembayaran QRIS diterima. Terima kasih!" << endl;
}

int calculateTotalFromOrder(const vector<OrderItem> &currentOrder)
{
    int total = 0;
    for (size_t i = 0; i < currentOrder.size(); i++)
    {
        const OrderItem &item = currentOrder[i];
        int price = getPrice(item.menuChoice);
        int sugarFee = getSugarFee(item.sugarChoice);
        int iceFee = getIceFee(item.iceChoice);
        total += (price * item.quantity) + sugarFee * item.quantity + iceFee * item.quantity;
    }
    return total;
}

void processPayment(const vector<OrderItem> &currentOrder, const string &cashierName,
                    const string &transactionDay, const string &transactionTime,
                    bool isTakeaway, bool isOnlineOrder, double shippingCost,
                    int additionalFee, CustomerPoints &customerPoints)
{
    if (currentOrder.empty())
    {
        cout << "Tidak ada pesanan untuk diproses." << endl;
        return;
    }

    int paymentMethodChoice;
    string paymentMethod = "Tunai";
    int bayar = 0;

    int total = calculateTotalFromOrder(currentOrder);
    double diskon = calculateDiscount(total);
    double totalSetelahDiskon = total - diskon;
    double totalAkhir = totalSetelahDiskon + shippingCost + additionalFee;


    bool hasFreeDrink = customerPoints.redeemFreeDrink();
    if (hasFreeDrink)
    {
        cout << "\n===================================" << endl;
        cout << "  SELAMAT! Anda mendapatkan 1 Ice Latte" << endl;
        cout << "  gratis karena telah mencapai " << FREE_DRINK_THRESHOLD << " poin!" << endl;
        cout << "===================================" << endl;
    }

    do
    {
        cout << "\nPilih metode pembayaran:" << endl;
        cout << "1. Tunai" << endl;
        cout << "2. Debit (QRIS)" << endl;
        cout << "Pilih opsi (1/2): ";
        while (!(cin >> paymentMethodChoice) || (paymentMethodChoice != 1 && paymentMethodChoice != 2))
        {
            cout << "Pilihan tidak valid. Silakan masukkan 1 atau 2: ";
            clearInputBuffer();
        }
        clearInputBuffer();
    } while (paymentMethodChoice != 1 && paymentMethodChoice != 2);

    if (paymentMethodChoice == 2)
    {
        paymentMethod = "Debit (QRIS)";
        displayQRIS();
        bayar = static_cast<int>(totalAkhir);
    }
    else
    {
        do
        {
            cout << "\nTotal yang harus dibayar: Rp " << fixed << setprecision(0) << totalAkhir << endl;
            cout << "Masukkan jumlah uang yang dibayarkan: Rp ";
            while (!(cin >> bayar))
            {
                cout << "Input tidak valid. Silakan masukkan angka: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            if (bayar < totalAkhir)
            {
                cout << "Uang Anda kurang. Silakan bayar minimal sebesar total tagihan." << endl;
            }
        } while (bayar < totalAkhir);
    }

    int kembalian = bayar - static_cast<int>(totalAkhir);


    int pointsEarned = totalAkhir / 50000 * POINTS_PER_TRANSACTION;
    customerPoints.addPoints(pointsEarned);

    cout << "\n===================================" << endl;
    cout << "        Rambat Coffee and Space      " << endl;
    cout << "   " << CAFE_ADDRESS << endl;
    cout << "===================================" << endl;
    cout << "Kasir            : " << cashierName << endl;
    cout << "Tanggal Transaksi: " << transactionDay << endl;
    cout << "Waktu Transaksi  : " << transactionTime << endl;
    cout << "-----------------------------------" << endl;
    cout << "Jenis Pesanan    : " << (isTakeaway ? "Bawa Pulang" : "Makan di Tempat") << endl;
    cout << "Metode Pesanan   : " << (isOnlineOrder ? "Online" : "Langsung") << endl;
    cout << "Metode Pembayaran: " << paymentMethod << endl;
    cout << "-----------------------------------" << endl;


    cout << "DETAIL PESANAN:" << endl;
    for (size_t i = 0; i < currentOrder.size(); i++)
    {
        const OrderItem &item = currentOrder[i];
        int price = getPrice(item.menuChoice);
        int sugarFee = getSugarFee(item.sugarChoice);
        int iceFee = getIceFee(item.iceChoice);
        int subtotal = (price * item.quantity) + sugarFee * item.quantity + iceFee * item.quantity;

        string menuName = getMenuName(item.menuChoice);
        cout << (i + 1) << ". " << menuName << " x" << item.quantity;

        if (item.menuChoice >= 1 && item.menuChoice <= 19)
        {
            string sugarText = (item.sugarChoice == 1) ? "Normal Gula" : (item.sugarChoice == 2) ? "Rendah Gula": "Ekstra Gula";
            string iceText = (item.iceChoice == 1) ? "Normal Es" : (item.iceChoice == 2) ? "Sedikit Es": "Ekstra Es";
            cout << " (" << sugarText << " - " << iceText << ")";
        }

        cout << " : Rp " << fixed << setprecision(0) << subtotal << endl;
    }

    cout << "-----------------------------------" << endl;
    cout << "Total Belanja Awal: Rp " << fixed << setprecision(0) << total << endl;
    if (diskon > 0)
    {
        cout << "Diskon (15%)    : Rp " << fixed << setprecision(0) << diskon << endl;
    }
    cout << "Total Setelah Diskon: Rp " << fixed << setprecision(0) << totalSetelahDiskon << endl;
    if (shippingCost > 0)
    {
        cout << "Ongkos Kirim     : Rp " << fixed << setprecision(0) << shippingCost << endl;
    }
    if (additionalFee > 0)
    {
        cout << "Biaya Tambahan   : Rp " << fixed << setprecision(0) << additionalFee << endl;
    }
    if (hasFreeDrink)
    {
        cout << "Minuman Gratis   : 1 Ice Latte (Free)" << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << "Total Akhir      : Rp " << fixed << setprecision(0) << totalAkhir << endl;
    cout << "Jumlah Dibayar   : Rp " << fixed << setprecision(0) << bayar << endl;
    if (paymentMethodChoice == 1)
    {
        cout << "Kembalian        : Rp " << fixed << setprecision(0) << kembalian << endl;
    }
    cout << "===================================" << endl;
    cout << "Poin yang didapat: " << pointsEarned << " poin" << endl;
    cout << "Total Poin Anda  : " << customerPoints.getPoints() << " poin" << endl;
    cout << "Pembayaran berhasil! Terima kasih atas pesanan Anda!" << endl;

    char cetakStrukChoice;
    do
    {
        cout << "\nCetak struk pembayaran? (Y/T): ";
        cin >> cetakStrukChoice;
        clearInputBuffer();
        cetakStrukChoice = toupper(cetakStrukChoice);
        if (cetakStrukChoice != 'Y' && cetakStrukChoice != 'T')
        {
            cout << "Pilihan tidak valid. Silakan masukkan Y atau T." << endl;
        }
    } while (cetakStrukChoice != 'Y' && cetakStrukChoice != 'T');

    if (cetakStrukChoice == 'Y')
    {
        cout << "Struk berhasil dicetak." << endl;
    }
    else
    {
        cout << "Struk tidak dicetak." << endl;
    }
}

void adminLogin()
{
    string username, password;
    cout << "\n--- Login Admin ---" << endl;
    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admin: ";
    cin >> password;
    clearInputBuffer();

    if (isAdmin(username, password))
    {
        cout << "Login berhasil sebagai Admin!" << endl;

        
        int choice;
        do
        {
            cout << "\n=== Menu Admin ===" << endl;
            cout << "1. Lihat Laporan Penjualan" << endl;
            cout << "2. Kelola Stok Menu" << endl;
            cout << "0. Kembali ke Menu Utama" << endl;
            cout << "Pilihan: ";
            while (!(cin >> choice))
            {
                cout << "Input tidak valid. Silakan masukkan angka: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            switch (choice)
            {
            case 1:
                cout << "\nFitur laporan penjualan belum diimplementasikan." << endl;
                break;
            case 2:
                cout << "\nFitur kelola stok menu belum diimplementasikan." << endl;
                break;
            case 0:
                cout << "Kembali ke menu utama." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
            }
        } while (choice != 0);
    }
    else
    {
        cout << "Login gagal. Username atau password salah." << endl;
    }
}

void customerLogin(MenuStock &stock, CustomerPoints &customerPoints)
{
    cout << "\n--- Memproses Pesanan Pelanggan ---" << endl;
    vector<OrderItem> currentOrder;
    int categoryChoice;
    int orderTypeChoice;
    int orderMethodChoice;
    bool isTakeaway = false;
    bool isOnlineOrder = false;
    double shippingCost = 0.0;
    int additionalFee = 0;

    do
    {
        cout << "\nPilih metode pemesanan:" << endl;
        cout << "1. Order Langsung" << endl;
        cout << "2. Order Online" << endl;
        cout << "Pilih opsi (1/2): ";
        while (!(cin >> orderMethodChoice) || (orderMethodChoice != 1 && orderMethodChoice != 2))
        {
            cout << "Pilihan tidak valid. Silakan masukkan 1 atau 2: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        isOnlineOrder = (orderMethodChoice == 2);
    } while (orderMethodChoice != 1 && orderMethodChoice != 2);

    do
    {
        cout << "\nPilih jenis pesanan:" << endl;
        cout << "1. Makan di Tempat" << endl;
        cout << "2. Bawa Pulang (Takeaway)" << endl;
        cout << "Pilih opsi (1/2): ";
        while (!(cin >> orderTypeChoice) || (orderTypeChoice != 1 && orderTypeChoice != 2))
        {
            cout << "Pilihan tidak valid. Silakan masukkan 1 atau 2: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        isTakeaway = (orderTypeChoice == 2);
    } while (orderTypeChoice != 1 && orderTypeChoice != 2);

    do
    {
        cout << "\n=== Menu Pelanggan ===" << endl;
        cout << "1. Lihat Menu Minuman" << endl;
        cout << "2. Lihat Menu Makanan" << endl;
        cout << "3. Tambah Pesanan" << endl;
        cout << "4. Edit Pesanan" << endl;
        cout << "5. Lihat Tagihan" << endl;
        cout << "6. Cek Poin Saya" << endl;
        cout << "0. Selesai memesan dan lanjut ke pembayaran" << endl;
        cout << "Pilih opsi: ";
        while (!(cin >> categoryChoice))
        {
            cout << "Input tidak valid. Silakan masukkan angka: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (categoryChoice)
        {
        case 1:
            showDrinkMenu();
            break;
        case 2:
            showFoodMenu();
            break;
        case 3:
            takeOrder(currentOrder, stock);
            break;
        case 4:
            editOrder(currentOrder, stock);
            break;
        case 5:
            showBill(currentOrder);
            break;
        case 6:
            cout << "\nTotal Poin Anda: " << customerPoints.getPoints() << " poin" << endl;
            if (customerPoints.getPoints() >= FREE_DRINK_THRESHOLD)
            {
                cout << "Anda bisa menukarkan " << FREE_DRINK_THRESHOLD
                     << " poin untuk mendapatkan 1 Ice Latte gratis!" << endl;
            }
            else
            {
                cout << "Anda membutuhkan " << (FREE_DRINK_THRESHOLD - customerPoints.getPoints())
                     << " poin lagi untuk mendapatkan minuman gratis." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (categoryChoice != 0);

    if (!currentOrder.empty())
    {
        // Sort the current order by menuChoice ascending using selection sort
        selectionSortOrder(currentOrder);

        if (isOnlineOrder)
        {
            double weight, distance;
            cout << "\n--- Perhitungan Ongkos Kirim ---" << endl;
            cout << "Masukkan berat total barang (kg): ";
            while (!(cin >> weight) || weight <= 0)
            {
                cout << "Berat tidak valid. Masukkan angka positif: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            cout << "Masukkan jarak pengiriman (km): ";
            while (!(cin >> distance) || distance <= 0)
            {
                cout << "Jarak tidak valid. Masukkan angka positif: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            shippingCost = calculateShippingCost(weight, distance);
        }

        if (isTakeaway && isOnlineOrder)
        {
            additionalFee = 5000;
            cout << "Tambahan biaya Rp 5.000 untuk pesanan Bawa Pulang (Online)." << endl;
        }

        time_t now = time(0);
        tm *ltm = localtime(&now);

        char dateBuffer[80];
        strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", ltm);
        string transactionDay = dateBuffer;

        char timeBuffer[80];
        strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", ltm);
        string transactionTime = timeBuffer;

        processPayment(currentOrder, loggedInCashierName, transactionDay, transactionTime,
                       isTakeaway, isOnlineOrder, shippingCost, additionalFee, customerPoints);
    }
    else
    {
        cout << "Tidak ada pesanan yang dibuat." << endl;
    }
}

void searchMenu(const string &category)
{
    if (category == "minuman")
    {
        showDrinkMenu();
    }
    else if (category == "makanan")
    {
        showFoodMenu();
    }
    else
    {
        cout << "Kategori tidak ditemukan." << endl;
    }
}

bool isAdmin(const string &username, const string &password)
{
    return (username == "admin" && password == "admin123");
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


