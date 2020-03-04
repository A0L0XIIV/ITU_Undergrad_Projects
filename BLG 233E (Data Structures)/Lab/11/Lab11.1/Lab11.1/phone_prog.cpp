#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "tree.h"

Tree book;

using namespace std;

void search_record() {
	char name[NAME_LENGTH];
	cout << "Please enter the name" << " of person you want to search for" << "(Press '*'for complete list) :" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	if (book.search(name) == 0) {
		cout << "Could not find record" << " matching search criteria" << endl;
	}
	getchar();
}


void add_record() {
	Phone_node newrecord;
	//LList *newList;
	//newrecord.head = NULL;
	//newList = NULL;
	//newrecord.head = newList;
	cout << "Please enter the information for the" << "person you want to record" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, NAME_LENGTH);
	cout << "Phone number :";

	//newList = newrecord.head;
	//newList->next = NULL;
	cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum1;//newrecord.head->phonenum;
	//strcpy(newList->phonenum, "asd");
	book.add(&newrecord);
	cout << "Record added" << endl;
	getchar();
}


void update_record() {
	char name[NAME_LENGTH];
	char choice;
	cout << "Please enter the name" << "of the person you want" << "to update : " << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	int personcount = book.search(name);
	if (personcount == 0) {
		cout << "Could not find" << "record matching" << "criteria" << endl;
	}
	else {
		cout << "Record found." << endl;
		cout << "Do you want to update ? " << "(y / n) ";
		do {
			cin >> choice;
		} while (choice != 'y' && choice != 'n');
		if (choice == 'n') return;
		Phone_node newrecord;
		cout << "Please enter current info" << endl;
		cout << "Name : ";
		cin.ignore(1000, '\n');
		cin.getline(newrecord.name, NAME_LENGTH);
		cout << "Phone number :";
		cin >> setw(PHONENUM_LENGTH) >> newrecord.head->phonenum;
		book.remove(name);
		book.add(&newrecord);
		cout << "Record successfully updated" << endl;
	}
	getchar();
}


void remove_record() {
	char name[NAME_LENGTH];
	char choice;
	cout << "Please enter name of person you want to delete:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	int personcount = book.search(name);
	if (personcount == 0) {
		cout << "Could not find record matching search criteria" << endl;
	}
	else {
		cout << "Is this the record you want to delete ? (y / n)";
		do {
			cin >> choice;
		} while (choice != 'y' && choice != 'n');
		if (choice == 'n') return;
		book.remove(name);
		cout << "Record removed" << endl;
	}
}

int main() {

	bool bitir = false;
	char secim;
	while (!bitir) {
		system("clear || cls");
		cout << endl << endl;
		cout << "Phone Book Application" << endl;
		cout << "Choose an option" << endl;
		cout << "S: Search Record" << endl;
		cout << "A: Add Record" << endl;
		cout << "U: Update Record" << endl;
		cout << "D: Delete Record" << endl;
		cout << "P: Print All Records" << endl;
		cout << "E: Exit" << endl;
		cout << endl;
		cout << "Enter your option {S, A, U, D, P, E} : ";
		cin >> secim;

		switch (secim) {
		case 'S': case 's':
			/*char bul[30];
			cout << "Please enter the name of the person you want to search (press '*' for listing all):" << endl;
			cin.ignore(1000, '\n');
			cin.getline(bul, 30);
			search_record(bul);*/
			search_record();
			break;
		case 'A': case 'a':
			add_record();
			break;
		case 'D': case 'd':
			remove_record();
			break;
		case 'U': case 'u':
			update_record();
			break;
		case 'P': case 'p':
			book.search("*");
		case 'E': case 'e':
			cout << "Are you sure that you want to terminate the program? (Y/N):";
			cin >> secim;
			if (secim == 'Y' || secim == 'y')
				bitir = true;
			break;
		default:
			cout << "Error: You have made an invalid choice" << endl;
			cout << "Try again {S, A, U, D, L, E} :";
			break;
		}
	}

}

