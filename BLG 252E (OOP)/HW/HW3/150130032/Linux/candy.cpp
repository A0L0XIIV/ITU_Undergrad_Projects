/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
#include "candy.h"

using namespace std;

Candy::Candy() {
	name = "-";
	weight = 0;
	pricePerKg = 0;
	cost = 0;
}

Candy::Candy(string Cname, double Cweight, double CpricePerKg) {
	name = Cname;
	weight = Cweight;
	pricePerKg = CpricePerKg;
	cost = pricePerKg * weight;
}

double Candy::get_cost() {
	return cost;
}

ostream &operator<<(ostream &out, const Candy &c) { //<< overload
	out << c.name << "#" << c.weight << "Cost: " << c.cost << endl;
	return out;
}

Candy::~Candy() {
	delete candyBox;
}