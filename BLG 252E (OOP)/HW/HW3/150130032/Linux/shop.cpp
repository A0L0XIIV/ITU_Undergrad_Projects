/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
#include "shop.h"

using namespace std;

template <class Ctype>
Shop<Ctype>::Shop() {	//Constructer
	numOfItems = 0;
	shop_cost = 0;
	discount = 0;
	discount_amount = 0;
	discounted_cost = 0;
}

template <class Ctype>
Shop<Ctype>::Shop(Ctype dessert) {	//Constructer
	++numOfItems;
	shops = new Ctype[numOfItems];
	shops[numOfItems - 1] = dessert;
	shop_cost += (1.08 * dessert.get_cost()); //tax
}

template <class Ctype>
Shop<Ctype>::Shop(Shop<Ctype> &copyShop) {	//Copy constructer
	numOfItems = copyShop.numOfItems;
	shop_cost = copyShop.shop_cost;
	shops = new Ctype[numOfItems];
	for (int i = 0; i < numOfItems; i++)
		shops[i] = copyShop.shops[i];
}

template <class Ctype>
void Shop<Ctype>::add(Ctype dessert) {
	//this->Shop(dessert); --> call constructer OR:
	++numOfItems;
	Ctype *temp_shops = new Ctype[numOfItems];
	for (int i = 0; i < numOfItems - 1; i++)	//Copy the shops to new temp_shops
		temp_shops[i] = shops[i];
	temp_shops[numOfItems - 1] = dessert;
	delete[] shops;
	shops = temp_shops;
}

template <class Ctype>
void Shop<Ctype>::setDiscount(double percent) {
	if (percent > 30 || percent < 0) throw "Discount rate is out of range. (0-30)";
	else {
		discount = percent;
		discounted_cost = discount * shop_cost;
		discount_amount = shop_cost - discounted_cost;
	}
}

template <class Ctype>
ostream& operator <<(ostream& out, const Shop<Ctype>& shop) { 
	
	out << "********************** " << endl << "Number of items: " << shop.numOfItems << endl;
	for (int i = 0; i < shop.numOfItems; i++) {
		out << i + 1 << ":" << shop.shops[i] << endl;
	}
	out << "********************** " << endl;
	if (shop.discount == 0) {
		 out << "Total cost: " << shop.shop_cost << endl << "********************** " << endl;
	}
	else {
		out << "Total cost: " << shop.shop_cost << endl << "Discount: " << shop.discount <<"Discount amount: " 
			<< shop.discount_amount << "Discounted cost: " << shop.discount_amount << endl << "********************** " << endl;
	}
	return out;
};

template <class Ctype>
Ctype& Shop<Ctype>::operator[] (int index) const{
	if ( index < 0 || index > numOfItems - 1 )
		throw "We don't have enuogh desserts :(";
	return shops[index];
}

template <class Ctype>
Shop<Ctype>::~Shop() {
	delete[] shops;
}
