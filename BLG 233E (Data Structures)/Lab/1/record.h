#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Tel_Kayit
{
	/*int *ad_uzunluk, *telno_uzunluk;
	ad_uzunluk = new int;
	*ad_uzunluk = 30;
	telno_uzunluk = new int;
	*telno_uzunluk = 15;*/
	char *ad = new char[30];
	char *telno = new char[15];

	//char ad[ad_uzunluk];
	//char telno[telno_uzunluk];
	void kayit_ara(char[]);
	void kayit_ekle();
	void kayit_guncelle(int kayitno, Tel_Kayit *);
	void kayit_sil(int kayitno);
};