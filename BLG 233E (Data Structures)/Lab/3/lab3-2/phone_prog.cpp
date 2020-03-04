#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include "operations.h"

using namespace std;
Dizi defter;


void menu();
bool islem_yap(char);
void record_search();
void record_add();
void record_delete();
void record_update();
void record_list();


int main(){
    defter.kayitsayisi=0;
    defter.toplamkayit=3;
    defter.def = new Tel_Kayit[defter.toplamkayit];
    defter.def2 = new Tel_Kayit[defter.toplamkayit];
    bool bitir = false;
    char secim;
    while (!bitir) {
          menu();
          cin >> secim;
          bitir = islem_yap(secim);
    }
   //delete[] defter.def;
    //delete[] defter.def2;
	defter.freememory();
    return EXIT_SUCCESS;
}


void menu(){
     system("cls");
     cout << endl << endl;
     cout << "Phone Book Application - Nurefsan Sarikaya" << endl;
     cout << "Choose an option" << endl;
     cout << "S: Search Record" << endl;
     cout << "A: Add Record" << endl;
     cout << "U: Update Record" << endl;
     cout << "D: Delete Record" << endl;
     cout << "L: List" << endl;
     cout << "E: Exit" << endl;
     cout << endl;
     cout << "Enter your option {S, A, U, D, L, E} : ";
}


bool islem_yap(char secim){
     bool sonlandir=false;
     switch (secim) {
            case 'S': case 's':
                 record_search();
                 break;
            case 'A': case 'a':
                 record_add();
                 break;
            case 'U': case 'u':
                 record_update();
                 break;
            case 'D': case 'd':
                 record_delete();
                 break;
            case 'L': case 'l':
                 record_list();
                 break;
            case 'E': case 'e':
                 cout << "Are you sure that you want to terminate the program? (Y/N):";
                 cin >> secim;
                 if(secim=='Y' || secim=='y'){
						sonlandir=true;
				 }
                 break;
            default:
                    cout << "Error: You have made an invalid choice" << endl;
					cout << "Try again {S, A, U, D, L, E} :" ;
                    cin >> secim;
                    sonlandir = islem_yap(secim);
                    break;
}
return sonlandir;
}


void record_search(){
     char *ad;
     string name;
     cout << "Please enter the name of the person you want to search (press '*' for listing all):" << endl;
     cin.ignore(1000, '\n');
     cin >> name;
     ad = new char[name.length()+1];
     for(int i=0; i<name.length(); i++){
             *(ad+i) = name[i];
     }
     ad[name.length()] = '\0';
     if(defter.search(ad)==0){
         cout << "Record can not be found" << endl;
     }
     delete[] ad;
     getchar(); 
     getchar();
};


void record_add(){
     Tel_Kayit yenikayit;
     string name, number;
     cout << "Please enter the information of the person you want to save " << endl;
     cout << "Name : " ;
     cin.ignore(1000, '\n');
     cin >>name;
     yenikayit.ad=new char[name.length()+1];
     for(int i=0; i<name.length(); i++){
             *(yenikayit.ad+i) = name[i];
     }
     cout << "Phone number :";
     cin >> number;
     yenikayit.telno=new char[number.length()+1];
     for(int i=0; i<number.length(); i++){
             *(yenikayit.telno+i) = number[i];
     }
     yenikayit.ad[name.length()] = '\0';
	 yenikayit.telno[number.length()] = '\0';
     defter.add(&yenikayit);
     cout << "Record has been added" << endl;
     getchar();
 
};


void record_delete(){
     char *ad;
     int secim;
     string name;
     cout << "Please enter the name of the person you want to delete (press '*' for listing all):" << endl;
     cin.ignore(1000, '\n');
     cin >> name;
     ad = new char[name.length()+1];
     for(int i=0; i<name.length(); i++){
             *(ad+i) = name[i];
     }
     ad[name.length()] = '\0';
     int kisisayisi=defter.search(ad);
     if(kisisayisi==0){
         cout << "Record can not be found" << endl;
     }
     else {
          if (kisisayisi==1){
             cout << "Record has been found." << endl;
             cout << "Please enter the index of the record if you want to delete this contact (Press -1 to exit without deletion): " ;
          }
          else
              cout << "Please enter the index of the record that you want to delete (Press -1 to exit without deletion): " ;
              cin >> secim;
              if(secim==-1) return;
              defter.deletef(secim);
              cout << "Record has been deleted" <<endl;
     }
     delete[] ad;
     getchar();
};


void record_update(){
     char *ad;
     string name, number, isim_ara;
     int secim;
     cout << "Please enter the name of the person you want to update (press '*' for listing all):" << endl;
     cin.ignore(1000, '\n');
     cin >> isim_ara;
     ad = new char[isim_ara.length()+1];
     for(int i=0; i<isim_ara.length(); i++){
             *(ad+i) = isim_ara[i];
     }
     ad[isim_ara.length()] = '\0';
     int kisisayisi=defter.search(ad);
     delete[] ad;
     if(kisisayisi==0){
         cout << "Record can not be found" << endl;
     }
     else {
          if (kisisayisi==1){
                             cout << "Record has been found." << endl;
                             cout << "Please enter the index of the record if you want to update this contact (Press -1 to exit without updating) " ;
          }
          else
              cout << "Please enter the index of the record that you want to update (Press -1 to exit without updating): " ;
          cin >> secim;
          if(secim==-1) return;
          Tel_Kayit yenikayit;
          cout << "Please enter the up-to-date information" << endl;
          cout << "Name : " ;
          cin.ignore(1000, '\n');
          cin >>name;
          yenikayit.ad=new char[name.length()+1];
          for(int i=0; i<name.length(); i++){
             *(yenikayit.ad+i) = name[i];
          }
          cout << "Phone number :";
          cin >> number;
          yenikayit.telno=new char[number.length()+1];
          for(int i=0; i<number.length(); i++){
             *(yenikayit.telno+i) = number[i];
          }
          yenikayit.ad[name.length()] = '\0';
	      yenikayit.telno[number.length()] = '\0';
          defter.update(secim,&yenikayit);
          cout << "Record has been updated successfully" <<endl;
     }
     getchar();
};


void record_list(){     
     defter.list();
     getchar();
}
