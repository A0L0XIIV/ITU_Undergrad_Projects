/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
//#include "shop.cpp"
/*#include "candy.h"
#include "cookie.h"
#include "icecream.h"*/

using namespace std;

template <class Ctype>
class Shop;

template <class Ctype>
ostream& operator<<(ostream &out, const Shop<Ctype> &shop);

template <class Ctype>
class Shop {
	

	int numOfItems;
	double shop_cost;
	double discount;
	double discount_amount;
	double discounted_cost;
	Ctype *shops;	//Dynamic array for shops
	
public:
	friend ostream& operator<< <> (ostream &out, const Shop<Ctype> &shop);
	Shop();
	Shop(Ctype dessert);
	Shop(Shop<Ctype>&copyShop);	//Copy const.
	void setDiscount(double percent);
	void add(Ctype dessert);
	Ctype& operator[](int) const;
	~Shop();
};
