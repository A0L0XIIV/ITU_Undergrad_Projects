/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
//#include "icecream.cpp"

using namespace std;

class Icecream {
	friend ostream& operator<<(ostream &out, const Icecream &i);

	string name;
	double litre;
	double pricePerLitre;
	double cost;
	Icecream *icecreamCup;
public:
	Icecream();
	Icecream(string Cname, double Clitre, double CpricePerLitre);
	double get_cost();
	~Icecream();
};