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

	cout << List.recordNumber << endl;					//Buna gerek yok, kayýt sayýsýný gösterir
	list();

	for(int i=0; i<100/*List.recordNumber*/; i++){
		cout << number << "." << (Records + i)->name << "\t" << (Records + i)->doctorName << "\t" << (Records + i)->diagnosis << "\t" << (Records + i)->patientNumber << "\t" << (Records + i)->polyclinicNumber << "\t" << (Records + i)->branchName << endl;
		
		//Bu kýsým kayýtlarý yazdýrýrken her poliklinik numarasý için 10'ar adet yer ayýrarak yazdýrýr (Fakat dizinin içinde NULL eleman oluþturmaz sadece yazdýrýrken boþ gösterir [Dizinin içinde her poliklinik numarasýna 10'ar yer ayýrma kýsmý en alt kýsýmdadýr])

		if( ( Records + i)->polyclinicNumber == (Records + i + 1)->polyclinicNumber )							//Sýralama yapýlmýþ listede poliklinik numaralarý ayný ise counter artýrýlýr
			counter++;
		else if( (Records + i)->polyclinicNumber != (Records + i + 1)->polyclinicNumber && counter != 10 ){		//Poliklinik numaralarý farklý ise yanýi baþka numaraya geçti ise 10'dan eksik kalan sayý kadar boþ yer yazdýrýlýr ve number artýrýlýr
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

		cout << "Enter name:" << endl;												//Ýsmi okuma
		cin.ignore(1000, '\n');
		cin.getline(newRecord.name, sizeof(List.name));

		cout << "Enter doctor name:" << endl;										//Doktor ismi okuma
		//cin.ignore(1000, '\n');
		cin.getline(newRecord.doctorName, sizeof(List.doctorName));

		cout << "Enter diagnosis:" << endl;											//Teþhis okuma
		//cin.ignore(1000, '\n');
		cin.getline(newRecord.diagnosis, sizeof(List.diagnosis));

		cout << "Enter patient number:" << endl;									//Hasta no. okuma
		cin >> newRecord.patientNumber;
		if( (1000 > newRecord.patientNumber) || (newRecord.patientNumber > 9999) ){ //Hasta no. 4 basamaklý mý kontrol etme
			cout << "The patient number must be an integer with 4 digits." << endl;
			cout << "Try to enter patient number again:" << endl;	
			cin >> newRecord.patientNumber;
		}

		cout << "Enter polyclinic number:" << endl;									//Poliklinik no. okuma
		cin >> newRecord.polyclinicNumber;
		for(int i=0; i<List.recordNumber; i++){										//Poliklinik numarasý daha önceki kayýtlarda var ise o kayýtlardaki polikliniðe kayýtlý branch name newRecord'un branch name kýsmýna eklenir, 
			if( (Records + i)->polyclinicNumber == newRecord.polyclinicNumber ){
				strcpy(newRecord.branchName, (Records + i)->branchName);
				newPoliclinic = false;
				break;
			}
		}
		if(newPoliclinic == true){													//Eðer önceki kayýtlarda öyle bir poliklinik numarasý yok ise yeni branch name eklenebilir...
			cout << "Enter branch name:" << endl;
			cin.ignore(1000, '\n');
			cin.getline(newRecord.branchName, sizeof(List.branchName));
		}


		for(int i=0; i<List.recordNumber; i++){										//Yeni kayitta eklenen poliklinik numarasýyla ayný olan kaç adet kayit olduðunu bulup,
			if( newRecord.polyclinicNumber == (Records + i)->polyclinicNumber ){
				checkTen++;
			}
		}
		if(checkTen == 10){															//kayit sayýsý ondan fazla ise kayit eklemez.
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
		if( strncmp( (Records + i)->name, delName, sizeof(delName) ) == 0 ){						//Silinmek istenen kayýttýn [numarasýný] bulmak için arama

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
	//Internal isimlerine göre sýralama ve sonra eðer internal isimleri ayný ise poliklinik numaralarýna göre sýralama fonksiyonu
	patient_record temp;

	for(int j=0; j<List.recordNumber; j++){
		for(int i=0; i<List.recordNumber; i++){
			if( strcmp( (Records + i)->branchName, (Records + i + 1)->branchName ) > 0 && strcmp( (Records + i + 1)->branchName, "") != 0){			//Internal isimlerine göre yer deðiþtirip sýralama (Alfabetik ve boþ olup olmadýðýnýn kontrolü)
				temp = *(Records + i);
				*(Records + i) = *(Records + i + 1);
				*(Records + i + 1) = temp;
				
			}
		}
	}
	for(int j=0; j<List.recordNumber; j++){
		for(int i=0; i<List.recordNumber; i++){
			if( strcmp((Records + i)->branchName, (Records + i + 1)->branchName) == 0 && (Records + i)->polyclinicNumber > (Records + i + 1)->polyclinicNumber){	//Internal isimleri ayný fakat poliklinik sayýlarý farklý ise küçükten büüyðe sýralama
					temp = *(Records + i);
					*(Records + i) = *(Records + i + 1);
					*(Records + i + 1) = temp;
			}
		}
	}

	//Bu kýsým dizinin içinde her poliklinik numarasý için 10'ar adet yer ayýrmak için, fakat sadece programý çalýþtýrýp print fonksiyonunu çaðýrýnca düzgün
	//bit þekilde çalýþýp diðer fonksiyonlarda hata verdiði için bu kýsmý yorum olarak býrakýyorum... (Bu kýsým çalýþýrýken print fonksiyonundaki boþluk býrakma gereksizdir)

	/*patient_record tempArray[100];
	patient_record emptyRecord = {"", "", "", NULL, NULL, ""};

	for(int i=0; i<100; i++)																	//tempArray dizisinin elemanlarýný boþ olarak atýyoruz...
		*(tempArray + i) = emptyRecord;



	int counter = 0;
	int polyclinicTemp = Records->polyclinicNumber;												//policlinicTemp sayýsýný ilk kayýttýn polyclinicNumber sayýsýna eþitliyoruz
	int polyclinicCounter = 1;

	for(int i=0; i<List.recordNumber; i++){														//Asýl Records dizisini tempArray dizisine attýk
		*(tempArray + i) = *(Records + i);
	}
	for(int i=0; i<100; i++){
		if( polyclinicTemp == (tempArray + i)->polyclinicNumber && (tempArray + i)->polyclinicNumber != NULL)		//polyclinicTemp sayýsý ile dizinin polyclinicNumber sayýlarý eþitse counter artýrýlýr, //temp array . biþey lazým olabilir !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			counter++;
		else if(counter != 10 && polyclinicTemp != (tempArray + i)->polyclinicNumber){			//farklý ise ilk farklý olan kayýttan itibaren bütün kayýtlar silinir ve sonra 10'ar boþluklar býrakýlarak tempArray dizisinden tekrar alýnarak Record dizisinde gerekli yerlere atanýr...
			int tutan = i;
			for(int j= ( ( 10*(polyclinicCounter-1) ) + counter); j<100; j++)					//polyclinicTemp sayýsýna eþit olmayan policlinicNumber'lý kayýttan itibaren bütün kayýtlarý siler
				Records[j] = emptyRecord;
			
			for(int k=0; k<100; k++)															//kaç kez dömdüðünü polyclinicCounter tutar ve onun 10 katý + counter kadar yer býraktýktan sonraki kýsýma tempArray'den aldýðý kalan kýsýmlarý atar
				*(Records + (10*polyclinicCounter) + k) = *(tempArray + tutan + k);

			polyclinicTemp = (tempArray + i)->polyclinicNumber;									//policlinicTemp sayýsýný kontrol edilecek bir sonraki policlinicNumber sayýsýna eþitliyor
			counter = 1;
			polyclinicCounter++;
		}
	}*/
}


