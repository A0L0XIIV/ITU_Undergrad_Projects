#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <stdlib.h>
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
	Phone_Record newrecord;
	cout << "Please enter the information for the" << "person you want to record" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, NAME_LENGTH);
	cout << "Phone number :";
	cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
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
				Phone_Record newrecord;
			cout << "Please entercurrent info" << endl;
			cout << "Name : ";
			cin.ignore(1000, '\n');
			cin.getline(newrecord.name, NAME_LENGTH);
			cout << "Phone number :";
			cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
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


