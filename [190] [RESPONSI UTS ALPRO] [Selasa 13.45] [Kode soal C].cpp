#include <iostream>
using namespace std;

int main() {
	string user, alamat;
	int login, password, jalan;
	
	
	cout<<"Silahkan Login" <<endl;
	cout<<"1. Login Aplikasi" <<endl;
	cout<<"2. Login Alamat" <<endl;
	cout<<"Pilih Login: ";
	cin>>login;
	cout<<endl;
	
	if (login==1){
		cout<<"Login aplikasi" <<endl;
		cout<<"username: ";
		cin>>user;
		cout<<"password: ";
		cin>>password;
		cout<<"Login aplikasi berhasil" <<endl <<endl;
		
		int pilihan;
		char pil;
		do {
			
			cout<<"Menu barang: " <<endl;
			cout<<"1. Skincare" <<endl;
			cout<<"2. Alat tulis" <<endl;
			cout<<"3. Pakaian" <<endl;
			cout<<"Masukkan pilihan: ";
			cin>>pilihan;
		
			if (pilihan==1){
				cout<<"Skincare"<<endl;
				cout<<"| Skincare | toner | mois | serum |" <<endl;
				cout<<"------------------------------------------------" <<endl;
				cout<<"| 001 | 30000 | 35000 | 40000| 45000 |" <<endl;
				
			}
	
			else if (pilihan==2){
				cout<<"Alat tulis"<<endl;
				cout<<"|Pensil | Buku | Penghapus |" <<endl;
				cout<<"--------------------------------------" <<endl;
				cout<<"| 5000 | 10000 | 2000 |" <<endl;
				
			}
	
			else if (pilihan==3){
				cout<<"Pakaian" <<endl;
				cout<<"1. Baju" <<endl;
				cout<<"2. Celana" <<endl;
			}
			else{
				cout<<"Pilihan anda tidak tersedia" <<endl;
			}
			
		
		cout<<"Masukkan pilihan yang lain (y/n): ";
		cin>>pil;
		}while (pil=='y' || pil=='Y');
	}
	
	else if (login==2){
		cout<<"Alamat" <<endl;
		cin>>alamat;
		cout<<"Jalan: ";
		cin>>jalan;
		cout<<"Login Alamat berhasil" <<endl <<endl;
		
		int vocher,ekspedisi,struk;
		char gratisongkir;
		do {
			
			cout<<"Pilihan Vocher: " <<endl;
			cout<<"1. Vocher barang" <<endl;
			cout<<"2. Ekspedisi    " <<endl;
			cout<<"3. Struk        " <<endl;
			cout<<"Masukkan pilihan: ";
			cin>>vocher;
		
			if (vocher==1){
				cout<<"vocher"<<endl;
				cout<<"| vocher 50% |" <<endl;
				cout<<"| vocher 15% |" <<endl;
				cout<<"| vocher 45% |" <<endl;
			}
			else if(ekspedisi==2){
				cout<<"Cepat" <<endl;
				cout<<"Standar" <<endl;
			}
			else if(struk==3){
				cout<<"invoice"<<endl;
				cout<<"|Skincare | Alat tulis | Pakaian |" <<endl;
				cout<<"--------------------------------------" <<endl;
				cout<<"| 150000 | 17000 | Baju,celana |" <<endl;
			}
			
		
		cout<<"Mau pilih yang lain (y/n): ";
		cin>>gratisongkir;
		}while (gratisongkir=='y' || gratisongkir=='Y');	
	}
	return 0;
}
