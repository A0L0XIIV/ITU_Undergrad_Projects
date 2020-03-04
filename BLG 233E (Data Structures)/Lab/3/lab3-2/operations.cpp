#include "operations.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
                  
using namespace std;

void Dizi::add(Tel_Kayit *ykptr){
     (def+kayitsayisi)->ad = ykptr->ad; 
     (def+kayitsayisi)->telno = ykptr->telno;
     kayitsayisi++;
     if(kayitsayisi==toplamkayit) {
              def2 = new Tel_Kayit[2*toplamkayit];
              for(int i=0; i<toplamkayit; i++){
                      *(def2+i) = *(def+i);
              }
              delete[] def;
              toplamkayit = 2 * toplamkayit;
              def = new Tel_Kayit [toplamkayit];
                    for(int i=0; i<toplamkayit; i++){
                      *(def+i)= *(def2+i);   }
              delete[] def2;   
     }   
     list(); 
}
int Dizi::search(char aranacak[]){
    int i=0;
    bool tumu=false;
    int flag=0;
    if(strcmp(aranacak,"*")==0)
        tumu=true;
    for(int i=0;i<kayitsayisi;i++){
            if(!tumu && strcmp((def+i)->ad,aranacak)!=0)
               continue;
               cout<<i+1<<". "<<(def+i)->ad<<" "<<(def+i)->telno<<endl;
               flag=1;            
    }
    return flag;   
}

void Dizi::update(int kayitno, Tel_Kayit *ykptr){
     int indisno;
     indisno=kayitno-1;
     *(def+indisno) = *ykptr;
     list();
     }
     
     
void Dizi::deletef(int kayitno){
     Tel_Kayit temp;
     temp.ad = ""; 
     temp.telno = "";
     int indisno;
     indisno=kayitno-1;
     *(def+indisno) = temp;
     //Onarmak için
	 def2 = new Tel_Kayit[toplamkayit];     
	 
	 for(int i=0; i<kayitsayisi; i++) {
           if (strncmp((def+i)->ad, "", strlen((def+i)->ad)) == 0) {
               *def++;
               kayitsayisi--; 
            }
               *(def2+i) = *(def+i);
		}
     
          for(int i=0; i<kayitsayisi; i++) {
              *(def+i) = *(def2+i);
               }
		delete[] def2;
}

void Dizi::list(){
     Tel_Kayit temp;
     int i, j;
     for (i=1; i<kayitsayisi; i++)
     {
         for (j=0; j<kayitsayisi-i; j++)
         {
             if(strcmp((def+j)->ad,(def+j+1)->ad)>=0)
             {
                       temp = *(def+j);
                       *(def+j) = *(def+j+1);
                       *(def+j+1) = temp;
             }
         }
     }
     for(i=0;i<kayitsayisi;i++)
             cout<<i+1<<". "<<(def+i)->ad<<" "<<(def+i)->telno<<endl;   
     getchar();
}

void Dizi::freememory(){

	for(int i=0; i<kayitsayisi; i++){
		delete[] (def + i)->ad;
		delete[] (def + i)->telno;
	}

	delete[] def;

}