#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include "diziislemleri.h"

using namespace std;

typedef Tel_Kayit telefon_kayit;
telefon_kayit tel_def;

typedef Dizi Veriyapisi;
Veriyapisi tel_defter;

void Dizi::olustur(){
	tel_defter.head = NULL;
	tel_defter.kayitsayisi = 0;	
	//dosyaokuma();					//YAZILACAK!!!!!!!!!!!!!!
}


void Dizi::ekle(Tel_Kayit *yenikayit){

	Tel_Kayit *newRecord, *traverse;
	newRecord = new Tel_Kayit;
	newRecord = yenikayit;
	newRecord->next = NULL;
	head = tel_defter.head;
	traverse = head;

	if( tel_defter.head == NULL ){
		tel_defter.head = newRecord;
		return;
	}

	if( strcmp( tel_defter.head->ad, newRecord->ad ) > 0 ){
		newRecord->next = head;
		head = newRecord;
		return;
	}

	while( traverse->next && strcmp( traverse->next->ad, newRecord->ad ) < 0 )
		traverse = traverse->next;

	if(traverse->next){								//Araya bir yerlere ekleme
		newRecord->next = traverse->next;
		traverse->next = newRecord;
	}else{											//Liste sonuna ekleme
		traverse->next = newRecord;
	}

	tel_defter.kayitsayisi++;
}


int Dizi::ara(char aranacak[]){

	int sayac=0;
	int bulunan=0,flag=0;
	Tel_Kayit *traverse, *tail;
	head = tel_defter.head;
	traverse = head;

	if( strcmp( aranacak, "*" ) == 0 ){
		while( traverse ){
			cout << "Ad: " << traverse->ad << "Telefon: " << traverse->telno << endl;
			traverse = traverse->next;
		}
		return 1;
	}
	
	while( traverse && strcmp( traverse->ad, aranacak ) != 0 ){
		tail = traverse;
		traverse = traverse->next;
	}

	if( traverse ){
		cout << "Ad: " << traverse->ad << "Telefon: " << traverse->telno << endl;
		//bulunan=i;
		flag=1;
	}
	return flag;
}


void Dizi::guncelle(char *kayitadi, Tel_Kayit *yenikayit){
	Dizi::sil(kayitadi);
	Dizi::ekle(yenikayit);
}


void Dizi::sil(char *kayitadi){
	Tel_Kayit *traverse, *tail;
	head = tel_defter.head;
	traverse = head;
	tail = head;

	while( traverse && strcmp( traverse->ad, kayitadi ) != 0 ){
		tail = traverse;
		traverse = traverse->next;
	}
	if( strcmp( traverse->ad, kayitadi ) == 0  ){
		tail->next = traverse->next;
		delete traverse;
	}
}


void Dizi::listele(){
	Tel_Kayit *traverse;
	head = tel_defter.head;
	traverse = head;

	while( traverse ){
		cout << "Ad: " << traverse->ad << "Telefon: " << traverse->telno << endl;
		traverse = traverse->next;
	}
}


void Dizi::listeyiSil(){
	Tel_Kayit *sil;
	head = tel_defter.head;
	if( head ){
		sil = head;
		head = head->next;
		delete sil;
	}
}

/*void Dizi::dosyayazma(){
	dosyaadi="teldefteri.txt";
	teldefteri = fopen( dosyaadi, "w+" );

	fseek(teldefteri, 0, SEEK_END);
	for(int i=0; i<kayitsayisi; i++){
		if(strcmp(k[i].ad, "") == 0){
			continue;
		}
		else{
			fwrite(k[i].ad,AD_UZUNLUK, 1, teldefteri);
			fwrite(k[i].telno, TELNO_UZUNLUK, 1, teldefteri);
		}
	}
	//fclose(teldefteri);

}

void Dizi::dosyaokuma(){							//ÝLK BAÞTA DOSYA YOK AMA SONRADAN OLUÞTURULUP OKUMAK GEREKÝYO
	dosyaadi = "teldefteri.txt";
	teldefteri = fopen(dosyaadi, "r+" );

	if(!teldefteri){
		if (!(teldefteri = fopen(dosyaadi, "w+"))){
			cerr << "File can not be opened" << endl;
			exit(1);
		}
	}	
	fseek(teldefteri, 0, SEEK_SET);
	while(!feof(teldefteri)){
		fread(&k, sizeof(k), 1, teldefteri);
		if(feof(teldefteri)) break;
	}
	

}*/




