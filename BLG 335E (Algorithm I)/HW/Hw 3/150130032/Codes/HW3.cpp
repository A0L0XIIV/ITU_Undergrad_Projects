/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

//#define _CRT_SECURE_NO_WARNINGS

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "bookCharacter.h"
#include "Dictionary.h"
#include "List.h"
//#include "classes.h"
#include <chrono>
//#include <ctime>

using namespace std;

//------------------------------------------------MAIN------------------------------------------------

int main(){

	//File operations
	ifstream inputptr, lookupptr;
	inputptr.open("ds-set-input.txt");
	lookupptr.open("ds-set-lookup.txt");
	ofstream dictOut, listOut, bookOut;
	dictOut.open("ds-set-output-dict.txt");
	listOut.open("ds-set-output-list.txt");
	bookOut.open("ds-set-output-book.txt");

	//Definitions
	dictionary Dict, DictLookup;
	list Lst, LstLookup;
	string page, line, index, character;
	//char character;
	string total;
	long key;
	int counter = 0;

	auto S = chrono::high_resolution_clock::now();
	auto F = chrono::high_resolution_clock::now();
	//These are here because i could figure out their type so i used unneccesary time and type auto
	auto dictTime = F - S;
	auto listTime = F - S;
	auto dictLookup = F - S;
	auto listLookup = F - S;

	//------------------------------------------------INSERTION------------------------------------------------

	//Reading the input file
	if (!inputptr.is_open()) {
		cerr << "Input file could not be opened." << endl;
		exit(1);
	}
	else {
		while ( !inputptr.eof() ) {
			getline(inputptr, total);
			//cout << "total: " << total << endl;
			//Seperating the line
			istringstream lin;
			lin.str(total);
			getline(lin, page, '\t');
			getline(lin, line, '\t');
			getline(lin, index, '\t');
			lin >> character;
			counter++;
			if (counter >= 131071)
				break;
			bookCharacter BC( stoi(page), stoi(line), stoi(index), character[0] );
			

			//Dictionary
			//I tried to use chrono but ssh does not compile it with chrono so i decided to use basic time() function	
			auto dictStart = chrono::high_resolution_clock::now();

			Dict.addToHashTable(BC);

			auto dictFinish = chrono::high_resolution_clock::now();
			dictTime += (dictFinish - dictStart);

			//List
			auto listStart = chrono::high_resolution_clock::now();

			Lst.addVector(BC);

			auto listFinish = chrono::high_resolution_clock::now();
			listTime += (listFinish - listStart);
		}
	}

	//------------------------------------------------LOOKUP------------------------------------------------

	//Reading the lookup file
	if (!lookupptr.is_open()) {
		cerr << "Lookup file could not be opened." << endl;
		exit(1);
	}
	else {
		while (!lookupptr.eof()) {
			getline(lookupptr, total);
			//cout << "total: " << total << endl;
			//Seperating the line
			istringstream lin;
			lin.str(total);
			getline(lin, page, '\t');
			getline(lin, line, '\t');
			lin >> index;

			bookCharacter BCLookup(stoi(page), stoi(line), stoi(index));

			//Updating BCLookup's character from Dictionary
			auto lookupStart = chrono::high_resolution_clock::now();

			for (int i = 0; i < M; i++) {
				if (BCLookup.getKey() == Dict.getBookCharacter(i).getKey() ) {
					BCLookup.setCharacter(Dict.getBookCharacter(i).getCharacter() );
					//Writing to file
					dictOut << BCLookup.getPage() << "\t" << BCLookup.getLine() << "\t" << BCLookup.getIndex() << "\t" << BCLookup.getCharacter() << endl;
					break;
				}
			}

			auto lookupFinish= chrono::high_resolution_clock::now();
			dictLookup += (lookupFinish - lookupStart);



			//Updating BCLookup's character from List
			auto lookupStartL = chrono::high_resolution_clock::now();

			for (int i = 0; i < M; i++) {
				if (BCLookup.getKey() == Lst.getBookCharacter(i).getKey() ) {
					BCLookup.setCharacter(Lst.getBookCharacter(i).getCharacter());
					//Writing to file
					listOut << BCLookup.getPage() << "\t" << BCLookup.getLine() << "\t" << BCLookup.getIndex() << "\t" << BCLookup.getCharacter() << endl;
/*GEREKSIZ*/		bookOut << BCLookup.getCharacter();
 					break;
				}
			}

			auto lookupFinishL = chrono::high_resolution_clock::now();
			listLookup += (lookupFinishL - lookupStartL);
		}
	}

	std::cout << "DICTIONARY" << endl;
	cout << "Insertion finished after " << chrono::duration_cast<chrono::nanoseconds>(dictTime).count() << " nanoseconds." << endl << endl;
	cout << "Average number of collisions (first 1000) \t| " << Dict.getNumOfCollisions1000() << endl;
	cout << "Average number of collisions (first 10000) \t| " << Dict.getNumOfCollisions10000() << endl;
	cout << "Average number of collisions (first 100000) \t| " << Dict.getNumOfCollisions100000() << endl;
	cout << "Average number of collisions (overall) \t| " << Dict.getNumOfCollisions() << endl << endl;

	cout << "Lookup finished after " << chrono::duration_cast<chrono::nanoseconds>(dictLookup).count() << " nanoseconds." << endl << endl;

	cout << "LIST" << endl << endl;

	cout << "Insertion finished after " << chrono::duration_cast<chrono::nanoseconds>(listTime).count() << " nanoseconds." << endl;

	cout << "Lookup finished after " << chrono::duration_cast<chrono::nanoseconds>(listLookup).count() << " nanoseconds." << endl << endl;

	//Closing files
	inputptr.close();
	lookupptr.close();
	dictOut.close();
	listOut.close();
	bookOut.close();

	system("pause");
	return 0;
}

