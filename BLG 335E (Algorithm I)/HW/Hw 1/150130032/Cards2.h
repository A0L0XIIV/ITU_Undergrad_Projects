#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

class Card {
	friend class CardManager;
	string Name;
	string Class;
	string Rarity;
	string Set;
	string Type;
	int Cost;
public:
	Card();
	Card(string name, string cls, string rarity, string set, string type, int cost);
	string getName() {
		return Name;
	}
	void setName(string N) {
		Name = N;
	}
	string getClass() {
		return Class;
	}
	void setClass(string C) {
		Class = C;
	}
	string getRarity() {
		return Rarity;
	}
	void setRarity(string R) {
		Rarity = R;
	}
	string getSet() {
		return Set;
	}
	void setSet(string S) {
		Set = S;
	}
	string getType() {
		return Type;
	}
	void setType(string T) {
		Type = T;
	}
	int getCost() {
		return Cost;
	}
	void setCost(int C) {
		Cost = C;
	}
};

class CardManager {
	Card* CardArray;
	vector<Card> CardDeck;

public:
	CardManager();
	CardManager(vector<Card> CD);

	void addToCardDeck(Card C) {
		CardDeck.push_back(C);
	}
	vector<Card> getCardDeck() {
		return CardDeck;
	}
	void setCardDeck(vector<Card> CD){
		CardDeck = CD;
	}
	void fullSort(string sortType);
	void filterSort(string sortType);
};
