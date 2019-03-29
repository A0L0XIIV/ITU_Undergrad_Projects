/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include "bookCharacter.h"
#ifndef DICTIONARY_H
#define DICTIONARY_H

#define M 131071

using namespace std;

class dictionary {
	//bookCharacter** hashTable;
	bookCharacter* hashTable;
	unsigned int numberOfCollisions;
	unsigned int currentElementsCollision;
	unsigned int numberOfElements;
	unsigned int numberOfCollisions1000;
	unsigned int numberOfCollisions10000;
	unsigned int numberOfCollisions100000;

public:
	//------CONSTRUECTERS------
	dictionary();
	dictionary(unsigned long key, bookCharacter bC) {
		hashTable[key] = bC;
	}
	~dictionary() {
		delete[] hashTable;
	}
	//------FUNCTIONS------
	unsigned int getNumOfCollisions() {
		return numberOfCollisions;
	}
	unsigned int getNumOfCollisions1000() {
		return numberOfCollisions1000;
	}
	unsigned int getNumOfCollisions10000() {
		return numberOfCollisions10000;
	}
	unsigned int getNumOfCollisions100000() {
		return numberOfCollisions100000;
	}
	unsigned int getNumOfElements() {
		return numberOfElements;
	}
	bookCharacter getBookCharacter(unsigned int position){
		return hashTable[position];
	}
	void addToHashTable(bookCharacter bC);
	unsigned int hashFunction(unsigned long key);
	unsigned int probingCollision(unsigned int h);
};

//------------------------------------------------COUNSTRUCTER------------------------------------------------

dictionary::dictionary() {
	hashTable = new bookCharacter[M];
	bookCharacter nullBookCharacter;
	for (int i = 0; i < M; i++) {
		hashTable[i] = nullBookCharacter;
	}
	numberOfCollisions = 0;
	currentElementsCollision = 0;
	numberOfElements = 0;
	numberOfCollisions1000 = 0;
	numberOfCollisions10000 = 0;
	numberOfCollisions100000 = 0;
}

//------------------------------------------------FUNCTIONS------------------------------------------------

void dictionary::addToHashTable(bookCharacter bC) {
	//Getting key from bC object and sending the key to hashFunction
	unsigned long key = bC.getKey();
	unsigned int position = hashFunction(key);

	//adding bC to hashTable
	while (true) {
		//If there is no collision -> checks the current positions' bookCharacter objects character (\0)
		if (hashTable[position].getCharacter() == '\0') {
			hashTable[position] = bC;

			currentElementsCollision = 0;
			numberOfElements++;

			break;
		}
		//If there is a collision
		else {
			numberOfCollisions++;
			currentElementsCollision++;

			if (numberOfElements < 1000)
				numberOfCollisions1000++;
			if (numberOfElements < 10000)
				numberOfCollisions10000++;
			if (numberOfElements < 100000)
				numberOfCollisions100000++;

			position = probingCollision(position);
		}
	}
	return;
}

unsigned int dictionary::hashFunction(unsigned long k) {
	unsigned int h;
	double A = (sqrt(5) - 1) / 2;
	//h = floor( M * ( (k * A)% 1 ) );
	double step2;
	double step1 = k*A;
	double step4 = modf(step1, &step2);
	//double step1 = modf( (k * A), &step2);//Get fractional part into the step2 -> mod1
	double step3 = M * step4;
	h = floor(step3);

	return h;
}

unsigned int dictionary::probingCollision(unsigned int h) {
	unsigned int newH;

	//newH = h + 7i + 3i^2 (mod M)
	//newH = ( h + 7 * currentElementsCollision + (3 * pow(currentElementsCollision, 2)) ) % M;
	double step1 = (h + 7 * currentElementsCollision + (3 * pow(currentElementsCollision, 2)));
	newH = fmod(step1, M);//Mod function

	return newH;
}

#endif
