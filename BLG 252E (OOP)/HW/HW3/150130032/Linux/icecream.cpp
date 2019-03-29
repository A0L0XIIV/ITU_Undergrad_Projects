/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
#include "icecream.h"

using namespace std;

Icecream::Icecream() {
	name = "-";
	litre = 0;
	pricePerLitre = 0;
	cost = 0;
}

Icecream::Icecream(string Cname, double Clitre, double CpricePerLitre) {
	name = Cname;
	litre = Clitre;
	pricePerLitre = CpricePerLitre;
	cost = pricePerLitre * litre;
}

double Icecream::get_cost() {
	return cost;
}

ostream &operator<<(ostream &out, const Icecream &i) { //<< overload
	out << i.name << "#" << i.litre << "Cost: " << i.cost << endl;
	return out;
}

Icecream::~Icecream() {
	delete icecreamCup;
}