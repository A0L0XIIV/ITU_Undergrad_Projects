#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H
#include <stdio.h>
struct Tel_Kayit{
       char *ad;
       char *telno;
};

struct Dizi{
       Tel_Kayit *def;
       Tel_Kayit *def2;
       void add(Tel_Kayit *);
       int search(char []);
       void deletef(int kayitno);
       void update(int kayitno, Tel_Kayit *);
       void list();
       int kayitsayisi;
       int toplamkayit;
	   void freememory();
};


#endif
