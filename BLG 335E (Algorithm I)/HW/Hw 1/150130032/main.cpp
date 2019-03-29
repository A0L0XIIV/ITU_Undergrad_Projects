/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <climits>
#include <ctime>
//#include <chrono>
#include "Cards2.h"

using namespace std;

//--------------------------------------------------CONSTRUCTORS--------------------------------------------------

Card::Card() {
	Name = '-';
	Class = '-';
	Rarity = '-';
	Set = '-';
	Type = '-';
	Cost = 0;
}

Card::Card(string name, string cls, string rarity, string set, string type, int cost) {
	Name = name;
	Class = cls;
	Rarity = rarity;
	Set = set;
	Type = type;
	Cost = cost;
}

CardManager::CardManager() {
	CardArray = NULL;
}

CardManager::CardManager(vector<Card> CD){
	//setCardDeck(CD);
	CardDeck = CD;
}

//--------------------------------------------------INSERTION SORTS--------------------------------------------------

void InsertionSortByType(vector<Card> &CD) {
	
	Card key;
	int i, j;
	string keyType;

	for (j = 1; j < CD.size(); j++) {
		key = CD[j];
		i = j - 1;

		keyType = key.getType();

		while (i >= 0 && CD[i].getType() > keyType) {
			CD[i + 1] = CD[i];
			i = i - 1;
		}
		CD[i + 1] = key;
	}
}

void InsertionSortFull(vector<Card> &CD) {

	Card key;
	int i, j;
	string keyClass, keyName;
	int keyCost;

	for (j = 1; j < CD.size(); j++) {
		key = CD[j];
		i = j - 1;

		keyClass = key.getClass();
		keyCost = key.getCost();
		keyName = key.getName();

		//Class is bigger than keys OR Classes are equal and Cost is bigger than keys OR Classes and Costs are equal and Name i bigger than keys
		while (i >= 0 && (CD[i].getClass() > keyClass || (CD[i].getClass() == keyClass && CD[i].getCost() > keyCost) || (CD[i].getClass() == keyClass && CD[i].getCost() == keyCost && CD[i].getName() > keyName))) {
			CD[i + 1] = CD[i];
			i = i - 1;
		}
		CD[i + 1] = key;
	}
}

//--------------------------------------------------MERGE SORTS--------------------------------------------------

void MergeFull(vector<Card> &CD, int p, int q, int r) {

	int i, j, k;

	int n = (q - p) + 1;
	int m = (r - q);

	Card* L = new Card[n + 1];
	Card* R = new Card[m + 1];

	for (i = 0; i < n; i++) {
		L[i] = CD[(p + i)];
	}
	for (j = 0; j < m; j++) {
		R[j] = CD[(q + j) + 1];
	}

	L[n].setClass("Zzz");
	R[m].setClass("Zzz");
	L[n].setName("Zzz");
	R[m].setName("Zzz");
	L[n].setCost(INT_MAX);
	R[m].setCost(INT_MAX);
	i = 0;
	j = 0;

	for (k = p; k <= r; k++) {
		if ( L[i].getClass() <= R[j].getClass() || (L[i].getClass() == R[j].getClass() && L[i].getName() <= R[j].getName()) || (L[i].getClass() == R[j].getClass() && L[i].getName() == R[j].getName() && L[i].getCost() <= R[j].getCost()) ) {
			CD[k] = L[i];
			i++;
		}
		else {
			CD[k] = R[j];
			j++;
		}
	}
	delete[] L;
	delete[] R;
}

void MergeFilter(vector<Card> &CD, int p, int q, int r) {

	int i, j, k;

	int n = (q - p) + 1;
	int m = (r - q);

	Card* L = new Card[n + 1];
	Card* R = new Card[m + 1];

	for (i = 0; i < n; i++) {
		L[i] = CD[(p + i)];
	}
	for (j = 0; j < m; j++) {
		R[j] = CD[(q + j) + 1];
	}

	L[n].setType("Zzz");
	R[m].setType("Zzz");
	i = 0;
	j = 0;

	for (k = p; k <= r; k++) {
		if (L[i].getType() <= R[j].getType()) {
			CD[k] = L[i];
			i++;
		}
		else {
			CD[k] = R[j];
			j++;
		}
	}
	delete[] L;
	delete[] R;
}

void MergeSort(vector<Card> &CD, int p, int r, string fullOrFilter) {

	if (p < r) {
		int q = (p + r) / 2;

		if (fullOrFilter == "full") {
			MergeSort(CD, p, q, "full");
			MergeSort(CD, q + 1, r, "full");
			MergeFull(CD, p, q, r);
		}
		else {
			MergeSort(CD, p, q, "filter");
			MergeSort(CD, q + 1, r, "filter");
			MergeFull(CD, p, q, r);
		}
	}
}

//--------------------------------------------------FUNCTIONS--------------------------------------------------

void CardManager::fullSort(string sortType) {
	//Class-cost-name sýrasýnda sýrala
	if(sortType == "-i"){
		InsertionSortFull(CardDeck);
	}
	else{
		MergeSort(CardDeck, 0, (CardDeck.size() -1), "full");
	}
	
}

void CardManager::filterSort(string sortType) {
	//Sadece type sýralama
	if(sortType == "-i"){
		InsertionSortByType(CardDeck);
	}
	else{
		MergeSort(CardDeck, 0, (CardDeck.size() -1), "filter");
	}
	
}

//--------------------------------------------------MAIN--------------------------------------------------

int main(int argc, char** argv) {
	//-full -i hs-set-10k.txt hs-set-10k-full.txt
	string fullOrFilter = argv[1];
	string insOrMerge = argv[2];
	char*readDoc = argv[3];
	char* writeDoc = argv[4];
	
	//File operations
	ifstream rfptr;
	rfptr.open(readDoc);
	ofstream wfptr;
	wfptr.open(writeDoc);
	
	//Card Manager and Card objects
	CardManager* CM;
	CM = new CardManager;
	Card CD;
	string name, cls, rarity, set, type, total;
	int cost;
	
	std::cout << "Reading file..." << endl;

	//Reading the file
	if (!rfptr.is_open()) {
		cerr << "File could not be opened." << endl;
		exit(1);
	}
	else {
		
		while (!rfptr.eof()) {

			getline(rfptr, total);
			//cout << "total: " << total << endl;
			//Seperating the line
			istringstream lin;
			lin.str(total);
			getline(lin, name, '\t');
			getline(lin, cls, '\t');
			getline(lin, rarity, '\t');
			getline(lin, set, '\t');
			getline(lin, type, '\t');
			lin >> cost;
			//cout << name << " - " << cls << " - " << rarity << " - " << set << " - " << type << " - " << cost << endl;
			CD.setName(name);
			CD.setClass(cls);
			CD.setRarity(rarity);
			CD.setSet(set);
			CD.setType(type);
			CD.setCost(cost);
			CM->addToCardDeck(CD);
		}
	}
	
	//I tried to use chrono but ssh does not compile it with chrono so i decided to use basic time() function	
	//auto start = chrono::high_resolution_clock::now();	
	double start = time(NULL);

	if(fullOrFilter == "-full"){	
		CM->fullSort(insOrMerge);
	} 
	else{
		CM->filterSort(insOrMerge);
	}

	//auto finish1 = chrono::high_resolution_clock::now();
	//std::cout << "Time elapsed: " << chrono::duration_cast<chrono::nanoseconds>(finish1 - start).count() << " nanoseconds." << endl;
	double finish = time(NULL);
	double timeEl = finish - start;
	std::cout << "Time elapsed: " << timeEl << endl;
	std::cout << "Writing to file..." << endl;

	//Writing to file
	Card yaz;
	for(int i = 0; i < CM->getCardDeck().size(); i++){
		yaz = CM->getCardDeck()[i];
		wfptr << yaz.getName() << "\t" << yaz.getClass() << "\t" << yaz.getRarity() << "\t" << yaz.getSet() << "\t" << yaz.getType() << "\t" << yaz.getCost() << "\t" << endl;
	}

	//Closing file and deleting dynamic object
	delete CM;
	rfptr.close();
	wfptr.close();

	return 0;
}
