/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
//#include "candy.cpp"

using namespace std;

class Candy {
	friend ostream& operator<<(ostream &out, const Candy &c);

	string name;
	double weight;
	double pricePerKg;
	double cost;
	Candy *candyBox;
public:
	Candy();
	Candy(string Cname, double Cweight, double CpricePerKg);
	double get_cost();
	~Candy();
};