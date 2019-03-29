/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include <cstdlib>
#include <iostream>
#include <cstring>
#ifndef bookCharacter_H
#define bookCharacter_H


using namespace std;

class bookCharacter {
	int page;
	int line;
	int index;
	char character;
	unsigned long key;
public:
	bookCharacter();
	bookCharacter(int P, int L, int I, char C);
	bookCharacter(int P, int L, int I);
	int getPage();
	void setPage(int newPage);
	int getLine();
	void setLine(int newLine);
	int getIndex();
	void setIndex(int newIndex);
	char getCharacter();
	void setCharacter(char newCharacter);
	unsigned long getKey();
	void setKey();
};

//------------------------------------------------CONSTRUECTERS------------------------------------------------

bookCharacter::bookCharacter() {
	page = 0;
	line = 0;
	index = 0;
	character = '\0';
	key = 0;
}

//For insertion
bookCharacter::bookCharacter(int P, int L, int I, char C) {
	page = P;
	line = L;
	index = I;
	character = C;
	key = index + 100 * line + 10000 * page;
}

//For lookup
bookCharacter::bookCharacter(int P, int L, int I) {
	page = P;
	line = L;
	index = I;
	character = '\0';
	key = index + 100 * line + 10000 * page;
}

//------------------------------------------------FUNCTIONS------------------------------------------------

int bookCharacter::getPage() {
	return page;
}

void bookCharacter::setPage(int P) {
	page = P;
}

int bookCharacter::getLine() {
	return line;
}

void bookCharacter::setLine(int L) {
	line = L;
}

int bookCharacter::getIndex() {
	return index;
}

void bookCharacter::setIndex(int I) {
	index = I;
}

char bookCharacter::getCharacter() {
	return character;
}

void bookCharacter::setCharacter(char C) {
	character = C;
}

unsigned long bookCharacter::getKey() {
	return key;
}

void bookCharacter::setKey() {
	key = index + 100 * line + 10000 * page;
}

#endif
