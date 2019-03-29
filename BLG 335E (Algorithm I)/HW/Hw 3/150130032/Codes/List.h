/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include "bookCharacter.h"
#ifndef LIST_H
#define LIST_H

using namespace std;

class list {
	vector<bookCharacter> listVector;
public:
	list();
	list(bookCharacter bC);
	vector<bookCharacter> getVector();
	bookCharacter getBookCharacter(int position);
	void addVector(bookCharacter setBC);
};

//------------------------------------------------CONSTRUECTERS------------------------------------------------

list::list(){
	
}

list::list(bookCharacter bC) {
	listVector.push_back(bC);
}

//------------------------------------------------FUNCTIONS------------------------------------------------

vector<bookCharacter> list::getVector() {
	return listVector;
}

bookCharacter list::getBookCharacter(int position) {
	return listVector[position];
}

void list::addVector(bookCharacter bC) {
	listVector.push_back(bC);
}

#endif
