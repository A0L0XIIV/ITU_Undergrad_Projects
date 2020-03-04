#include <iostream>
#include <stdlib.h>
#include <iomanip>
//#include <conio.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <cstring>
#include <conio.h>
#include "diziislemleri.h"

using namespace std;

typedef Dizi Veriyapisi;
Veriyapisi defter;

void menu_yazdir();
bool islem_yap(char);
void kayit_ara();
void kayit_ekle();
void kayit_sil();
void kayit_guncelle();
void kayit_listele();

int main(){
	//defter.olustur();
	//defter.dosyaokuma();
	bool bitir = false;
	char secim;
	while (!bitir) {
		menu_yazdir();
		cin >> secim;
		bitir = islem_yap(secim);
	}
	return EXIT_SUCCESS;
}

void menu_yazdir(){
	system("cls||clear"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	cout << endl << endl;
	cout << "Telefon Defteri Uygulamasi" << endl;
	cout << "Bir islem seciniz:" << endl;
	cout << "A: Kayit ara" << endl;
	cout << "E: Kayit ara" << endl;
	cout << "G: Kayit guncelle" << endl;
	cout << "S: Kayit sil" << endl;
	cout << "L: Tum kayitlari listele" << endl;
	cout << "C: Cikis" << endl;
	cout << endl;
	cout << "Enter an option {A, E, G, S, C, L} : ";
}

bool islem_yap(char secim){
	bool sonlandir=false;
	switch (secim) {
		case 'A': case 'a':
		kayit_ara();
		break;
		case 'E': case 'e':
		kayit_ekle();
		break;
		case 'G': case 'g':
		kayit_guncelle();
		break;
		case 'S': case 's':
		kayit_sil();
		break;
		case 'C': case 'c':
		cout << "Programi kapatmak istiyor musunuz? (E/H):";
		cin >> secim;
		if(secim=='E' || secim=='e'){
			//defter.dosyayazma();
			defter.listeyiSil();
			sonlandir=true;
		}
		
		break;
		case 'L': case 'l':
		kayit_listele();
		break;
		default:
		cout << "Hata: Gecersiz islem komutu" << endl;
		cout << "Tekrar deneyin {A, E, G, S, B, C} :" ;
		cin >> secim;
		sonlandir = islem_yap(secim);
		break;
	}
	return sonlandir;
}

void kayit_ara(){
	char ad[AD_UZUNLUK];
	cout << "Lutfen aramak istediginiz kayidin adini girin ('*' karakteri tum kayitlari gosterir):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	if(defter.ara(ad)==0){
		cout << "Kayit bulunamadi" << endl;
	}
	getchar();
};

void kayit_ekle(){
	Tel_Kayit yenikayit;
	cout << "Lutfen eklemek istediginiz kayidin bilgilerini girin" << endl;
	cout << "Ad : " ;
	cin.ignore(1000, '\n');
	cin.getline(yenikayit.ad,AD_UZUNLUK);
	cout << "Telefon numarasi :";
	cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
	defter.ekle(&yenikayit);
	cout << "Kayit baþarili bir sekilde eklendi" << endl;
	getchar();
};

void kayit_sil(){
	char ad[AD_UZUNLUK];
	char *secim = "";
	cout << "Lutfen silmek istediginiz kayidin adini girin ('*' karakteri tum kayitlari gosterir):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	int kisisayisi=defter.ara(ad);
	if(kisisayisi==0){
		cout << "Kayit bulunamadi" << endl;
	}
	else {
		if (kisisayisi==1){
			cout << "Kayit bulundu" << endl;
			cout << "Eger bu kaydi silmek istiyorsaniz Lutfen kaydin adini girin ('cikis' yazarak kayitlari silemeden cikabilirsiniz): " ;
		}
		else
			cout << "Lutfen silmek istediginiz kaydin adini girin ('cikis' yazarak kayitlari silemeden cikabilirsiniz): " ;
		cin.ignore(1000, '\n');
		cin.getline(secim,100);
		if( strcmp( secim, "cikis" ) == 0 ) return;
		defter.sil(secim);
		cout << "Kayit basarili bir sekilde silindi" <<endl;
	}
	getchar();
};

void kayit_guncelle(){
	char ad[AD_UZUNLUK];
	char *secim = "";
	cout << "Lutfen guncellemek istediginiz kayidin adini girin ('*' karakteri tum kayitlari gosterir):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	int kisisayisi=defter.ara(ad);
	if(kisisayisi==0){
		cout << "Kayit bulunamadi" << endl;
	}
	else {
		if (kisisayisi==1){
			cout << "Kayit bulundu" << endl;
			cout << "Eger bu kaydi guncellemek istiyorsaniz Lutfen kaydin adini girin ('cikis' yazarak kayitlari guncellemeden cikabilirsiniz): " ;
		}
		else
			cout << "Lutfen guncellemek istediginiz kaydin adini girin ('cikis' yazarak kayitlari guncellemeden cikabilirsiniz): " ;
		cin.ignore(1000, '\n');
		cin.getline(secim,100);
		if( strcmp( secim, "cikis" ) == 0 ) return;
		Tel_Kayit yenikayit;
		cout << "Lutfen guncellenecek kaydin yeni bilgilerini girin:" << endl;
		cout << "Ad : " ;
		cin.ignore(1000, '\n');
		cin.getline(yenikayit.ad,AD_UZUNLUK);
		cout << "Telefon numarasi :";
		cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
		defter.guncelle(secim,&yenikayit);
		cout << "Kayit basari ile guncellendi" <<endl;
	}
	getchar();
};

void kayit_listele(){
	defter.listele();
	getchar();
}