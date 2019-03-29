/* @Author
* Student Name: Baran Kaya
* Student ID : 150130032
* Date: 17.10.2015
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctype.h>
#include "record.h"

using namespace std;

typedef patient_record Record_list;
Record_list List;

patient_record Records[100];

const char *filename;
FILE *recordfile;

void show_menu();
bool process_selection(char);
void read_file();
void write_file();


int main()
{
	List.recordNumber = 0;
	read_file();
	bool finish = false;
	char selection;
	while (!finish) {
		show_menu();
		cin >> selection;
		finish = process_selection(selection);
	}
	write_file();
	return EXIT_SUCCESS;
}

void show_menu()
{
	system("clear || cls");
	cout << endl << endl;
	cout << "Please select the operation to perform and enter the operation code:" << endl;
	cout << "(P) Print all of the patient record," << endl;
	cout << "(B) Search the data by the branch name," << endl;
	cout << "(C) Search the data by the polyclinic number," << endl;
	cout << "(I) Insert a new patient record," << endl;
	cout << "(R) Remove the patient record," << endl;
	cout << "(E) Exit the program" << endl;
	cout << "Your selection is:" << endl;
}

bool process_selection(char selection)
{
	bool end = false;

	switch (selection) {
	case 'P': case 'p':
		List.print_records();
		break;
	case 'B': case 'b':
		char sch_name[20];
		cout << "Enter the branch name that you want to search:" << endl;
		cin >> sch_name;
		List.searchByName(sch_name);
		break;
	case 'C': case 'c':
		int sch_number;
		cout << "Enter the polyclinic number that you want to search:" << endl;
		cin >> sch_number;
		List.searchByNumber(sch_number);
		break;
	case 'I': case 'i':
		List.insert_record();
		break;
	case 'R': case 'r':
		List.remove_record();
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (Y/N):";
		cin >> selection;
		if (selection == 'Y' || selection == 'y')
			end = true;
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl << endl;
		show_menu();
		cin >> selection;
		end = process_selection(selection);
		break;
	}
	return end;
}


void read_file(){

	filename = "database.txt";
	recordfile = fopen(filename, "r+");

	if(recordfile == NULL){
		cerr << "File could not be opened" << endl;
		exit(1);
	}else{
		int i = 0;
		while(!feof(recordfile)){
			/*fread(&Records[i].name, sizeof(List.name), 1, recordfile);			//Dosyadan okuma denemelerim
			fread(&Records[i].doctorName, sizeof(List.doctorName), 1, recordfile);
			fread(&Records[i].diagnosis, sizeof(List.diagnosis), 1, recordfile);
			fread(&Records[i].patientNumber, sizeof(List.patientNumber), 1, recordfile);
			fread(&Records[i].polyclinicNumber, sizeof(List.polyclinicNumber), 1, recordfile);
			fread(&Records[i].branchName, sizeof(List.branchName), 1, recordfile);*/
			//getline(recordfile, Records[i]);

	fscanf(recordfile, "%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",(Records + i)->name,(Records + i)->doctorName,(Records + i)->diagnosis,&(Records + i)->patientNumber,&(Records + i)->polyclinicNumber,(Records + i)->branchName);
			i++;
			List.recordNumber ++;
			if(feof(recordfile))
				break;
			
		}
	}
	fclose(recordfile);
}


void write_file(){

	filename = "database.txt";
	recordfile = fopen(filename, "w+");

	if(recordfile == NULL){
		cerr << "File could not be opened" << endl;
		exit(1);
	}else{
		for(int i=0; i<List.recordNumber; i++){
			fprintf(recordfile, "%s\t%s\t%s\t%d\t%d\t%s\n",(Records + i)->name, (Records + i)->doctorName, (Records + i)->diagnosis, (Records + i)->patientNumber, (Records + i)->polyclinicNumber, (Records + i)->branchName);
		}
	}
	fclose(recordfile);
}


void Record_list::print_records(){

	int counter = 0;
	int number = 1;

	cout << List.recordNumber << endl;					//Buna gerek yok, kay�t say�s�n� g�sterir
	list();

	for(int i=0; i<100/*List.recordNumber*/; i++){
		cout << number << "." << (Records + i)->name << "\t" << (Records + i)->doctorName << "\t" << (Records + i)->diagnosis << "\t" << (Records + i)->patientNumber << "\t" << (Records + i)->polyclinicNumber << "\t" << (Records + i)->branchName << endl;
		
		//Bu k�s�m kay�tlar� yazd�r�rken her poliklinik numaras� i�in 10'ar adet yer ay�rarak yazd�r�r (Fakat dizinin i�inde NULL eleman olu�turmaz sadece yazd�r�rken bo� g�sterir [Dizinin i�inde her poliklinik numaras�na 10'ar yer ay�rma k�sm� en alt k�s�mdad�r])

		if( ( Records + i)->polyclinicNumber == (Records + i + 1)->polyclinicNumber )							//S�ralama yap�lm�� listede poliklinik numaralar� ayn� ise counter art�r�l�r
			counter++;
		else if( (Records + i)->polyclinicNumber != (Records + i + 1)->polyclinicNumber && counter != 10 ){		//Poliklinik numaralar� farkl� ise yan�i ba�ka numaraya ge�ti ise 10'dan eksik kalan say� kadar bo� yer yazd�r�l�r ve number art�r�l�r
			for(int j=0; j<(10-counter-1); j++){
				number++;
				cout << number << endl;
			}
			counter = 0;
		}
		number++;	
	}
	getchar();
	getchar();
}


void Record_list::searchByName(char *sch_name){

	bool found = false;

	for(int i=0; i<List.recordNumber; i++){
		if( strcmp((Records + i)->branchName, sch_name) == 0 ){
			cout << i << "." << (Records + i)->name << "\t" << (Records + i)->doctorName << "\t" << (Records + i)->diagnosis << "\t" << (Records + i)->patientNumber << "\t" << (Records + i)->polyclinicNumber << "\t" << (Records + i)->branchName << endl;
			found = true;
		}
	}
	if( found == false )
		cout << "There is no record that brach name = " << sch_name << endl;
	getchar();
	getchar();
}


void Record_list::searchByNumber(int sch_number){

	bool found = false;

	for(int i=0; i <List.recordNumber; i++){
		if( (Records + i)->polyclinicNumber == sch_number ){
			cout << i << "." << (Records + i)->name << "\t" << (Records + i)->doctorName << "\t" << (Records + i)->diagnosis << "\t" << (Records + i)->patientNumber << "\t" << (Records + i)->polyclinicNumber << "\t" << (Records + i)->branchName << endl;
			found = true;
		}
	}
	if( found == false )
		cout << "There is no record that polyclinic number = " << sch_number << endl;
	getchar();
	getchar();
}


void Record_list::insert_record(){

	patient_record newRecord;
	char select;
	int checkTen = 0;
	bool newPoliclinic = true;

	cout << "Do you want to add new record? (Y/N)" << endl;
	cin >> select;
	if( select == 'Y' || select == 'y' ){

		cout << "Enter name:" << endl;												//�smi okuma
		cin.ignore(1000, '\n');
		cin.getline(newRecord.name, sizeof(List.name));

		cout << "Enter doctor name:" << endl;										//Doktor ismi okuma
		//cin.ignore(1000, '\n');
		cin.getline(newRecord.doctorName, sizeof(List.doctorName));

		cout << "Enter diagnosis:" << endl;											//Te�his okuma
		//cin.ignore(1000, '\n');
		cin.getline(newRecord.diagnosis, sizeof(List.diagnosis));

		cout << "Enter patient number:" << endl;									//Hasta no. okuma
		cin >> newRecord.patientNumber;
		if( (1000 > newRecord.patientNumber) || (newRecord.patientNumber > 9999) ){ //Hasta no. 4 basamakl� m� kontrol etme
			cout << "The patient number must be an integer with 4 digits." << endl;
			cout << "Try to enter patient number again:" << endl;	
			cin >> newRecord.patientNumber;
		}

		cout << "Enter polyclinic number:" << endl;									//Poliklinik no. okuma
		cin >> newRecord.polyclinicNumber;
		for(int i=0; i<List.recordNumber; i++){										//Poliklinik numaras� daha �nceki kay�tlarda var ise o kay�tlardaki poliklini�e kay�tl� branch name newRecord'un branch name k�sm�na eklenir, 
			if( (Records + i)->polyclinicNumber == newRecord.polyclinicNumber ){
				strcpy(newRecord.branchName, (Records + i)->branchName);
				newPoliclinic = false;
				break;
			}
		}
		if(newPoliclinic == true){													//E�er �nceki kay�tlarda �yle bir poliklinik numaras� yok ise yeni branch name eklenebilir...
			cout << "Enter branch name:" << endl;
			cin.ignore(1000, '\n');
			cin.getline(newRecord.branchName, sizeof(List.branchName));
		}


		for(int i=0; i<List.recordNumber; i++){										//Yeni kayitta eklenen poliklinik numaras�yla ayn� olan ka� adet kayit oldu�unu bulup,
			if( newRecord.polyclinicNumber == (Records + i)->polyclinicNumber ){
				checkTen++;
			}
		}
		if(checkTen == 10){															//kayit say�s� ondan fazla ise kayit eklemez.
			cout << "This polyclinic is full, you cannot add more records." <<  endl; 
			getchar();
			getchar();
		}else{
			Records[List.recordNumber] = newRecord;
			List.recordNumber++;
			list(); 
		}
	}
}


void Record_list::remove_record(){

	patient_record emptyRecord = {"", "", "", NULL, NULL, ""};
	char delName[40];
	char select;

	cout << "Enter the name that you want to delete:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(delName, sizeof(delName));

	for(int i=0; i<List.recordNumber; i++){
		if( strncmp( (Records + i)->name, delName, sizeof(delName) ) == 0 ){						//Silinmek istenen kay�tt�n [numaras�n�] bulmak i�in arama

			cout << "Record has been found -->" << (Records + i)->name << "\t" << (Records + i)->doctorName << "\t" << (Records + i)->diagnosis << "\t" << (Records + i)->patientNumber << "\t" << (Records + i)->polyclinicNumber << "\t" << (Records + i)->branchName << endl;
			cout << "Do you want to delete this record (Y/N) ?" << endl;
			cin >> select;

			if(select == 'Y' || select == 'y'){
				Records[i] = emptyRecord;
				cout << "Record has been deleted." << endl;
				List.recordNumber--;
			}
			break;
		}
	}
	list();
}


void Record_list::list(){
	//Internal isimlerine g�re s�ralama ve sonra e�er internal isimleri ayn� ise poliklinik numaralar�na g�re s�ralama fonksiyonu
	patient_record temp;

	for(int j=0; j<List.recordNumber; j++){
		for(int i=0; i<List.recordNumber; i++){
			if( strcmp( (Records + i)->branchName, (Records + i + 1)->branchName ) > 0 && strcmp( (Records + i + 1)->branchName, "") != 0){			//Internal isimlerine g�re yer de�i�tirip s�ralama (Alfabetik ve bo� olup olmad���n�n kontrol�)
				temp = *(Records + i);
				*(Records + i) = *(Records + i + 1);
				*(Records + i + 1) = temp;
				
			}
		}
	}
	for(int j=0; j<List.recordNumber; j++){
		for(int i=0; i<List.recordNumber; i++){
			if( strcmp((Records + i)->branchName, (Records + i + 1)->branchName) == 0 && (Records + i)->polyclinicNumber > (Records + i + 1)->polyclinicNumber){	//Internal isimleri ayn� fakat poliklinik say�lar� farkl� ise k���kten b��y�e s�ralama
					temp = *(Records + i);
					*(Records + i) = *(Records + i + 1);
					*(Records + i + 1) = temp;
			}
		}
	}

	//Bu k�s�m dizinin i�inde her poliklinik numaras� i�in 10'ar adet yer ay�rmak i�in, fakat sadece program� �al��t�r�p print fonksiyonunu �a��r�nca d�zg�n
	//bit �ekilde �al���p di�er fonksiyonlarda hata verdi�i i�in bu k�sm� yorum olarak b�rak�yorum... (Bu k�s�m �al���r�ken print fonksiyonundaki bo�luk b�rakma gereksizdir)

	/*patient_record tempArray[100];
	patient_record emptyRecord = {"", "", "", NULL, NULL, ""};

	for(int i=0; i<100; i++)																	//tempArray dizisinin elemanlar�n� bo� olarak at�yoruz...
		*(tempArray + i) = emptyRecord;



	int counter = 0;
	int polyclinicTemp = Records->polyclinicNumber;												//policlinicTemp say�s�n� ilk kay�tt�n polyclinicNumber say�s�na e�itliyoruz
	int polyclinicCounter = 1;

	for(int i=0; i<List.recordNumber; i++){														//As�l Records dizisini tempArray dizisine att�k
		*(tempArray + i) = *(Records + i);
	}
	for(int i=0; i<100; i++){
		if( polyclinicTemp == (tempArray + i)->polyclinicNumber && (tempArray + i)->polyclinicNumber != NULL)		//polyclinicTemp say�s� ile dizinin polyclinicNumber say�lar� e�itse counter art�r�l�r, //temp array . bi�ey laz�m olabilir !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			counter++;
		else if(counter != 10 && polyclinicTemp != (tempArray + i)->polyclinicNumber){			//farkl� ise ilk farkl� olan kay�ttan itibaren b�t�n kay�tlar silinir ve sonra 10'ar bo�luklar b�rak�larak tempArray dizisinden tekrar al�narak Record dizisinde gerekli yerlere atan�r...
			int tutan = i;
			for(int j= ( ( 10*(polyclinicCounter-1) ) + counter); j<100; j++)					//polyclinicTemp say�s�na e�it olmayan policlinicNumber'l� kay�ttan itibaren b�t�n kay�tlar� siler
				Records[j] = emptyRecord;
			
			for(int k=0; k<100; k++)															//ka� kez d�md���n� polyclinicCounter tutar ve onun 10 kat� + counter kadar yer b�rakt�ktan sonraki k�s�ma tempArray'den ald��� kalan k�s�mlar� atar
				*(Records + (10*polyclinicCounter) + k) = *(tempArray + tutan + k);

			polyclinicTemp = (tempArray + i)->polyclinicNumber;									//policlinicTemp say�s�n� kontrol edilecek bir sonraki policlinicNumber say�s�na e�itliyor
			counter = 1;
			polyclinicCounter++;
		}
	}*/
}


