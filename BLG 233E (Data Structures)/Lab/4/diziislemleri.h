#define CRT_SECURE_NO_WARNINGS
#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H
#include <stdio.h>
#include <iostream>
#include "kayit.h"

struct Dizi{

	char *dosyaadi;
	FILE *teldefteri;

	Tel_Kayit temp[1];

	void olustur();
	void ekle(Tel_Kayit *);
	int ara(char []);
	void sil(char *kayitadi);
	void guncelle(char *kayitadi, Tel_Kayit *);
	void listele();

	int kayitsayisi;
	void dosyayazma();
	void dosyaokuma();
	void listeyiSil();

	Tel_Kayit * head;
};
#endif