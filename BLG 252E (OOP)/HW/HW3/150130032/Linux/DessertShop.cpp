/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
/*#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"*/
#include "shop.cpp"
#include "candy.cpp"
#include "cookie.cpp"
#include "icecream.cpp"
using namespace std;


int main() {
	Cookie cookie1("Chocolate Chip Cookies", 10, 180); //(name, pieces, priceperdozen)
	Cookie cookie2("Cake Mix Cookies", 16, 210);

	Shop<Cookie> cookieShop(cookie1);
	cookieShop.add(cookie2);
	cout << cookieShop << endl;

	//Catch an exception here while trying to access the element at(2)
	try {
		cout << cookieShop[2] << endl;
	}
	catch (const char* errorMes) {
		cout << endl << errorMes << endl;
	}

	Icecream icecream1("Chocolate ice cream", 1.5, 170); //(name, litre, priceperlitre)
	Shop<Icecream> icecreamShop(icecream1);
	cout << icecreamShop << endl;

	//Catch an exception here while trying to set the discount to(50)
	try {
		icecreamShop.setDiscount(50);
	}
	catch (const char* errorMes) {
		cout << endl << errorMes << endl;
	}

	Candy candy2("Gummi bears", 12, 89); //(name, weight, priceperkg)
	Candy candy3("Hanukkah gelt", 8, 110);

	Shop<Candy> candyShop(candy2);
	candyShop.add(candy3);

	candyShop.setDiscount(15);
	cout << candyShop << endl;

	/*You will also
	1) Read dessert stock and customer order from "stock.txt" and "order.txt", respectively.
	2) Write the total cost with 10% discount to "checkout.txt".
	Expected output for checkout:

	!!! We don't have 7 (Orange Jelly Candy)s.
	!!! We don't have 11 (Chocolate ice cream)s.
	-----------------------
	Number of items:2
	1: Chocolate Chip Cookies #2 Cost: 100

	2: Cake Mix Cookies #10 Cost: 150

	**********************
	Total cost: 270.0
	Discount: 10%
	Discount amount: -27.0
	Discounted cost: 243.0
	**********************

	//FILE OPERATIONS

	/*ifstream stock_file;
	ifstream order_file;
	ofstream checkout_file;

	stock_file.open("stock.txt");
	order_file.open("order.txt");
	checkout_file.open("checkout.txt");

	string s, o, c;
	int i = 0, j = 0;
	int type = 0;
	string name;
	double number, pricepernumber;

	while(getline(stock_file, s)){
		//cout << s << endl;
		switch(type){
			case 1:
				Cookie c(name, number, pricepernumber);
				cookieShop.add(c);
				break;
			case 2:
				Candy c(name, number, pricepernumber);
				candyShop.add(c);
				break;
			case 3:
				Icecream i(name, number, pricepernumber);
				icecreamShop.add(i);
				break;
		}
	}
	
	while(getline(order_file, o, '\t')){
		//cout << o << endl;
		if(o == c.name)
	}

	//Write to the checkout.txt
	cout << cookieShop << endl;
	cout << icecreamShop << endl;
	cout << candyShop << endl;

	stock_file.close();
	order_file.close();
	checkout_file.close();*/

}
