#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <ctype.h>
#include "record.h"

using namespace std;

//typedef Dosya Veriyapisi;
//Veriyapisi defter;
typedef Tel_Kayit Fonk;
Fonk bonk;

int *defter;
defter = new int [100];
Tel_Kayit *defter;

void menu_yazdir();
bool islem_yap(char);
void kayit_ara();
void kayit_ekle();
void kayit_sil();
void kayit_guncelle();
void kayit_onar();

int main()
{
	bool bitir = false;
	char secim;
	while (!bitir) {
		menu_yazdir();
		cin >> secim;
		bitir = islem_yap(secim);
	}
	return EXIT_SUCCESS;
}

void menu_yazdir()
{
	system("clear || cls");
	cout << endl << endl;
	cout << "Phone Book Application" << endl;
	cout << "Choose an option" << endl;
	cout << "S: Search Record" << endl;
	cout << "A: Add Record" << endl;
	cout << "U: Update Record" << endl;
	cout << "D: Delete Record" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter your option {S, A, U, D, E} : ";
}

bool islem_yap(char secim)
{
	bool sonlandir = false;

	switch (secim) {
	case 'S': case 's':
		kayit_ara();
		break;
	case 'A': case 'a':
		kayit_ekle();
		break;
	case 'U': case 'u':
		kayit_guncelle();
		break;
	case 'D': case 'd':
		kayit_sil();
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (E/H):";
		cin >> secim;
		if (secim == 'E' || secim == 'e')
			sonlandir = true;
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {A, E, G, S, C} :";
		cin >> secim;
		sonlandir = islem_yap(secim);
		break;
	}
	return sonlandir;
}

void Fonk::kayit_ara(char aranacak[])
{
	char ad[AD_UZUNLUK];
	cout << "Please enter the name of the person you want to search (press '*' for listing all):" << endl;
		cin.ignore(1000, '\n');
	cin.getline(ad, AD_UZUNLUK);
	int sayac = 0;
	while(1){
		if(strcmp(defter[i].ad, aranacak) == 0) break;
		sayac++;
	}
	return sayac;
	//cout << "Record can not be found" << endl;
	
	getchar();
};

void Fonk::kayit_ekle()
{
	Tel_Kayit yenikayit;
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin.getline(yenikayit.ad, AD_UZUNLUK);
	cout << "Phone number :";
	cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
	int enson = kayit_ara("");//Boþ olan en sondaki array elemanýný bumak için
	defter[enson] = yenikayit;
	//alfabetik çaðýr

	cout << "Record has been added" << endl;
	getchar();
};

void Fonk::kayit_sil(int kayitno)
{
	Tel_Kayit boskayit;
	char ad[AD_UZUNLUK];
	int secim;
	cout << "Please enter the name of the person you want to delete (press '*' for listing all):" << endl;
		cin.ignore(1000, '\n');
	cin.getline(ad, AD_UZUNLUK);
	int kisisayisi = defter.ara(ad);
	if (kisisayisi == 0){
		cout << "Record can not be found" << endl;
	}
	else {
		if (kisisayisi == 1){
			cout << "Record has been found." << endl;
			cout << "Please enter the index of the record if you want to delete this contact(Press - 1 to exit without deletion) : " ;
		}
		else
			cout << "Please enter the index of the record that you want to delete (Press - 1 to exit without deletion) : " ;
			cin >> secim;
		if (secim == -1) return;
		//defter.sil(secim);
		defter[kayitno] = boskayit;
		cout << "Record has been deleted" << endl;
	}
	getchar();
};

void Fonk::kayit_guncelle()
{
	char ad[AD_UZUNLUK];
	int secim;
	cout << "Please enter the name of the person you want to update (press '*' for listing all):" << endl;
		cin.ignore(1000, '\n');
	cin.getline(ad, AD_UZUNLUK);
	int kisisayisi = defter.ara(ad);
	if (kisisayisi == 0){
		cout << "Record can not be found" << endl;
	}
	else {
		if (kisisayisi == 1){
			cout << "Record has been found." << endl;
			cout << "Please enter the index of the record if you want to update this contact(Press - 1 to exit without updating) " ;
		}
		else
			cout << "Please enter the index of the record that you want to update (Press - 1 to exit without updating) : " ;
			cin >> secim;
		if (secim == -1) return;
		Tel_Kayit yenikayit;
		cout << "Please enter the up-to-date information" << endl;
		cout << "Name : ";
		cin.ignore(1000, '\n');
		cin.getline(yenikayit.ad, AD_UZUNLUK);
		cout << "Phone number :";
		cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
		defter.guncelle(secim, &yenikayit);
		cout << "Record has been updated successfully" << endl;
	}
	getchar();
};