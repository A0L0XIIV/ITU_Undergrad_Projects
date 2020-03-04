#define _CRT_SECURE_NO_WARNINGS

#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H
#include <stdio.h>
#include "record.h"

struct Dosya
{
	const char *dosyaadi;
	FILE *teldefteri;
	void olustur();
	void kapat();
	void ekle(Tel_Kayit *);
	int ara(char[]);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_Kayit *);

	void onar();
	const char *tempdosyaadi;
	FILE *temp;
};
#endif