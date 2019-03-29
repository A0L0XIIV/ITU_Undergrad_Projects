/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
#include "cookie.h"

using namespace std;

Cookie::Cookie() {
	name = "-";
	number = 0;
	pricePerDozen = 0;
	cost = 0;
}

Cookie::Cookie(string Cname, double Cpieces, double CpricePerDozen) {
	/*if (number == 0)
		cookieJar = new Cookie[10];
	this = cookieJar[number];*/
	name = Cname;
	number = Cpieces;
	pricePerDozen = CpricePerDozen;
	cost = pricePerDozen * number;
}

double Cookie::get_cost(){	//Get cost for shop_cost
	return cost;
}

ostream &operator<<(ostream &out, const Cookie &c) { //<< overload
	out << c.name << "#" << c.number << "Cost: " << c.cost << endl;
	return out;
}

Cookie::~Cookie() {
	delete cookieJar;
}