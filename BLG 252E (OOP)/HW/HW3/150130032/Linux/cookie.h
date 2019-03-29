/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <cstdlib>
#include <string>
//#include "cookie.cpp"

using namespace std;

class Cookie {
	friend ostream& operator<<(ostream &out, const Cookie &c);

	string name;
	double number;
	double pricePerDozen;
	double cost;
	Cookie *cookieJar;
public:
	Cookie();
	Cookie(string Cname, double Cpieces, double Cpieceperdozen);
	double get_cost();
	~Cookie();
};