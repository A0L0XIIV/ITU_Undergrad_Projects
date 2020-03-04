#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctype.h>
#include "kayit.h"

using namespace std;

typedef Fonksiyon Fonk;//typedef Tel_Kayit Fonk;
Fonk fonks;



/*int *defter = new int[100];
int *defter;
defter = new int[100];*/
Tel_Kayit defter[100];

//defter = new int[100];
//Tel_Kayit defter[100] = new Tel_Kayit[100];

void menu_yazdir();
bool islem_yap(char);


int main()
{
	fonks.kayitsayisi=0;
	fonks.toplamkayit=3; //100 olacak!!!
	fonks.def = new Tel_Kayit[fonks.toplamkayit];
	fonks.def2 = new Tel_Kayit[fonks.toplamkayit];

	bool bitir = false;
	char secim;
	while (!bitir) {
		menu_yazdir();
		cin >> secim;
		bitir = islem_yap(secim);
	}
	delete[] fonks.def;
	delete[] fonks.def2;
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
	cout << "L: Listing all records" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter your option {S, A, U, D, L, E} : ";
}


bool islem_yap(char secim)
{
	bool sonlandir = false;

	switch (secim) {
	case 'S': case 's':
		char bul[30];
		cout << "Please enter the name of the person you want to search (press '*' for listing all):" << endl;
		cin.ignore(1000, '\n');
		cin.getline(bul, 30);
		fonks.kayit_ara(bul);
		break;
	case 'A': case 'a':
		fonks.kayit_ekle();
		break;
	case 'D': case 'd':
		fonks.kayit_sil();
		break;
	case 'L': case 'l':
		fonks.listele();
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (Y/N):";
		cin >> secim;
		if (secim == 'Y' || secim == 'y')
			sonlandir = true;
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {S, A, U, D, L, E} :";
		cin >> secim;
		sonlandir = islem_yap(secim);
		break;
	}
	return sonlandir;
}


int Fonk::kayit_ara(char aranacak[])
{
	string addyn;
	cin >> addyn;
	ad = new char [addyn.length() + 1];
	for(int i=0; i<addyn.length(); i++){
		*(yenikayit.ad + i) = addyn[i];
	}


	if( strcmp(aranacak, "*") == 0 )
		fonks.listele();
	int sayac = 0;

	while(strcmp(defter[sayac].ad, "") != 0){//Boþ kayýt deðilse buradan geçer
		
		if( strncmp(defter[sayac].ad, aranacak, sizeof(aranacak) ) == 0) 
			break;
		sayac++;
	}

	cout << sayac << "." << defter[sayac].ad << " " << defter[sayac].telno << endl;
	if(strcmp(defter[sayac].ad, aranacak) != 0) cout << "Record can not be found" << endl;
	
	getchar();
	return sayac;
	getchar();
};


void Fonk::kayit_ekle()
{
	Tel_Kayit yenikayit;
	string addyn, teldyn;
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	//cin.getline(yenikayit.ad, AD_UZUNLUK);
	cin >> addyn;
	yenikayit.ad = new char addyn[addyn.length()+1];
	for(int i=0; i<addyn.length(); i++){
		*(yenikayit.ad + i) = addyn[i];
	}


	cout << "Phone number :";
	//cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
	cin >> teldyn;
	yenikayit.telno = new char teldyn[teldyn.length()+1];
	for(int i=0; i<teldyn.length(); i++){
		*(yenikayit.telno + i) = teldyn[i];
	}


	//defter[kayitsayisi] = yenikayit;
	(def+kayitsayisi)->ad = yenikayit.ad;
	(def+kayitsayisi)->telno = yenikayit.telno;
	
	//alfabetik sýralama
	/*Tel_Kayit temp[1];
	for(int i=0; i<kayitsayisi; i++){
		if( strcmp((defter+i)->ad, (defter+kayitsayisi)->ad) > 0 && strcmp((defter+i)->ad, "") != 0 ){ //EN soana eklenen kayýt i'nci kayýttan küçükse ve boþ deðilse
			temp[0] = *(defter+i);
			*(defter+i) = *(defter+kayitsayisi);
			*(defter+kayitsayisi) = temp[0];
		}
	}*/
	//fonks.onar();
	kayitsayisi++;
	if(kayitsayisi == toplamkayit){
		def2 = new Tel_Kayit[toplamkayit*2];
		for(int i=0; i<toplamkayit; i++){
			*(def2+i) = *(def+i);
		}
		delete[] def;
		toplamkayit *= 2;
		def = new Tel_Kayit[toplamkayit];
		for(int i=0; i<toplamkayit; i++){
			*(def+i) = *(def2+i);
		}
		delete[] def2;

	}


	cout << "Record has been added" << endl;
	getchar();
};


void Fonk::kayit_sil()
{
	Tel_Kayit boskayit = { 0,"","" };
	string addyn, teldyn;


	defter.telno = new char teldyn[teldyn.length()+1];
	for(int i=0; i<teldyn.length(); i++){
		*(yenikayit.telno + i) = teldyn[i];
	}


	char bul[AD_UZUNLUK];
	char secim;

	cout << "Please enter the name of the person you want to delete (press '*' for listing all):" << endl;
	cin.ignore(1000, '\n');
	//cin.getline(bul, AD_UZUNLUK);
	cin >> addyn;
	defter.ad = new char addyn[addyn.length()+1];
	for(int i=0; i<addyn.length(); i++){
		*(defter.ad + i) = addyn[i];


	int kisisayisi = fonks.kayit_ara(bul);
	if(strcmp(bul, defter[kisisayisi].ad) == 0){ //Bulunan kiþinin sayýsý doðru ise
		cout << "Record has been found." << endl;
		cout << kisisayisi << "." << defter[kisisayisi].ad << " " << defter[kisisayisi].telno << "Do you realy want to delete this? (Y/N)" <<endl;
		cin >>  secim;
		if(secim == 'Y' || secim == 'y'){
			strcpy(defter[kisisayisi].ad, boskayit.ad);
			strcpy(defter[kisisayisi].telno, boskayit.telno);
		}
		cout << "Record has been deleted" << endl;
	}else{
		cout << "Record can not be found" << endl;
	}

	fonks.onar();//Onarmak için fonk. çaðýr
	return;
	
	getchar();
};

/*
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
};*/

void Fonk::listele(){
	if(kayitsayisi == 0)
		cout << "Empty" << endl;
	else{
		for(int i=0;i<kayitsayisi;i++)
			cout<<i+1<<". "<<defter[i].ad<<" \t"<<defter[i].telno<<endl;
	}
	getchar();
	getchar();
}

void Fonk::onar(){
	Tel_Kayit boskayit = { 0,"","" };

	for(int i=0; i < kayitsayisi; i++){
		if( strcmp( (defter+i)->ad, boskayit.ad ) == 0 && strcmp( (defter+i)->telno, boskayit.telno) == 0 ){ //Boþ kayýtlarý en alt kýsma yollama
			*(defter+i) = *(defter+i+1);
			*(defter+i+1) = boskayit;
		}
	}
	if( strcmp(defter[kayitsayisi-1].ad, boskayit.ad) == 0 && strcmp(defter[kayitsayisi-1].telno, boskayit.telno) == 0 )
		kayitsayisi--;
}