#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#define AD_UZUNLUK 30
//#define TELNO_UZUNLUK 15

struct Tel_Kayit
{
	/*int *ad_uzunluk, *telno_uzunluk;
	ad_uzunluk = new int;
	*ad_uzunluk = 30;
	telno_uzunluk = new int;
	*telno_uzunluk = 15;*/

	/*char *ad = new char[30];
	char *telno = new char[15];*/

	//Tel_Kayit *def;
	//Tel_Kayit *def2;

	/*int kayitsayisi;
	int toplamkayit;
	char ad[AD_UZUNLUK];
	char telno[TELNO_UZUNLUK];*/
	char *ad;
	char *telno;
	/*int kayit_ara(char[]);
	void kayit_ekle();
	void kayit_guncelle(int kayitno, Tel_Kayit *);
	void kayit_sil();
	void listele();
	void onar();*/
};struct Fonksiyon{	Tel_Kayit *def;
	Tel_Kayit *def2;	int kayitsayisi;
	int toplamkayit;	int kayit_ara(char[]);
	void kayit_ekle();
	void kayit_guncelle(int kayitno, Tel_Kayit *);
	void kayit_sil();
	void listele();
	void onar();}