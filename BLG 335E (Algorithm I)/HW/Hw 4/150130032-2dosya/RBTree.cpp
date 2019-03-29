/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Classes.h"

using namespace std;

int main(int argc, char** argv)
{
	//File operations
	if (argc != 2) {
		cout << "Invalid arguments." << endl;
		return 0;
	}
	string filename = argv[1];
	ifstream inputptr;
	inputptr.open(filename);


	//Definitions
	unsigned int i = 0;
	TreeNode* newNodes[20];
	RedBlackTree* RBT = new RedBlackTree();
	string name, gender, age;
	string total;


	//Reading the input file
	if (!inputptr.is_open()) {
		cerr << "Input file could not be opened." << endl;
		exit(1);
	}
	else {
		while (!inputptr.eof()) {
			getline(inputptr, total);
			//cout << "total: " << total << endl;
			//Seperating the line
			istringstream lin;
			lin.str(total);
			getline(lin, name, '\t');
			getline(lin, gender, '\t');
			lin >> age;

			char G = gender[0];
			newNodes[i] = new TreeNode(name, G, stoi(age));
			RBT->insert(newNodes[i]);
			i++;
		}
	}

	RBT->countGenders();
	RBT->print();
	unsigned int x;
	cout << "Enter the number for (x)th woman: ";
	cin >> x;
	cout << "(" << x << ")th woman: " << RBT->NthWoman(x) << endl;
	cout << "Enter the number for (x)th man: ";
	cin >> x;
	cout << "(" << x << ")th man: " << RBT->NthMan(x) << endl;

	//Closing files
	inputptr.close();
	delete RBT;
	for(int j=0; j<i; j++)
		delete newNodes[j];

	system("pause");
	return 0;
}

