/*
GROUP MEMBERS:
BARAN KAYA				150130032
KAD�R ENES KARSLIO�LU	150130047
NOTE: Program Visual Studio'da proje �eklinde yaz�ld� ve �al���yordu fakat, Dev-C++'da �al��m�yordu. Linux deneme �ans�m�z olmad�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <iomanip>
#include <fstream>
#define MAX 100

using namespace std;

string gramer[MAX][MAX];  //grameri tutmak i�in
int numOfPro = 0;		//nonTerminal say�s� (main ve di�er fonksiyonlarda oldu�u i�in global)

string concat(string frstStr, string scndStr)   //tek nonTerminalleri konkatlar
{
	int i;
	string resultStr = frstStr;
	for (i = 0; i < scndStr.length(); i++)
	{
		if (resultStr.find(scndStr[i]) > resultStr.length())
			resultStr += scndStr[i];
	}
	return (resultStr);
}


string search_string(string sStr) //sStr'yi olu�turabilecek konkatlanm�� stringleri bulur
{
	int j, k;
	string resultStr = "";
	for (j = 0; j < numOfPro; j++)
	{
		k = 1;
		while (gramer[j][k] != "")
		{
			if (gramer[j][k] == sStr)
			{
				resultStr = concat(resultStr, gramer[j][0]);	//sonucu konkatlar
			}
			k++;
		}
	}
	return resultStr;
}


string combine(string frstStr, string scndStr)  //birinci ve ikinci stringlerden olu�abilecek b�t�n kombinasyonlar� olu�turur (11,22,12,21)
{
	int i, j;
	string tempStr = frstStr, resultStr = "";
	for (i = 0; i < frstStr.length(); i++) {
		for (j = 0; j < scndStr.length(); j++)
		{
			tempStr = "";
			tempStr = tempStr + frstStr[i] + scndStr[j];
			resultStr = resultStr + search_string(tempStr);   //sonu� string �retilebilir mi �retilemez mi kontrol eder
		}
	}
	return resultStr;
}


int main() {

	cout << "CYK ALGORITHM PROGRAM" << endl;

	ifstream grammarfile, wordfile; //in
	ofstream resultfile;			//out
	grammarfile.open("grammar.txt");
	wordfile.open("words.txt");
	resultfile.open("results.txt");
	string Line, Word, bonus[100];
	char nonTerminal[100];
	char terminal[100];
	int i = -2, pt, sp, j, l, k, abc;		//i terminal ve nonTerminalleri kontrol ederken artt��� i�in ve grammar matrixi i�ine 0'dan ba�lay�p atmas� i�in -2
	string str, resultStr, pResStr, start;
	bool same = false;

	while (!wordfile.eof()) {
		i = -2;
		while (!grammarfile.eof()) {
			abc = 0;
			getline(grammarfile, Line);
			//grammarfile >> Line;

			if (i == -2) {//Terminals
				for (int j = 0; j < Line.length(); j++) {
					if (Line[j] != ' ' || Line[j] != '\n' || Line[j] != '\0')
						terminal[abc++] = Line[j];
				}
			}
			else if (i == -1) {//Non Terminals
				start = Line[0];
				for (int j = 0; j < Line.length(); j++) {
					if (Line[j] != ' ' || Line[j] != '\n' || Line[j] != '\0')
						nonTerminal[abc++] = Line[j];
				}
			}
			else {//Grammar
				pt = Line.find("->");
				sp = Line.find(" ");
				if (Line.substr(sp + 1, 1) != gramer[i - 1][0]) {	//2 ayn� nonTerminaller 2 sat�rda olaca�� i�in 2 sat�rdaki ayn� de�il ise gramer'in i�ine at
					gramer[i][0] = Line.substr(sp + 1, 1); //ba�taki say�lar� almamas� i�in substr bo�luktan bir sonraki yani nonTerminalden ba�lar
					//bonus[i] = Line.substr(0, sp);		//Bonus part i�in gereken say�lar
					::numOfPro++;
				}
				else {	//�nceki nonTerminal ile ayn� ise sa� taradtakileri yine ayn� gramer[i]'nin i�ine atmak i�in i-- ve ayn�s� oldu�u i�in same true
					i--;
					same = true;
				}
				Line = Line.substr(pt + 3, Line.length()); //Sa� taraftakileri b�lme
				if (same == false)	//Sol taraftaki nonTerminal ayn� de�il ise
					gramer[i][1] = Line;
				else {				//Ayn� ise
					gramer[i][2] = Line;
					same = false;
				}
			}

			i++;
		}

		string matrix[MAX][MAX], st;
		getline(wordfile, str);		//words.txt'ten kelimeleri okuma

		for (i = 0; i < str.length(); i++)       //Matrixe �apraz de�erleri atama
		{
			resultStr = "";
			st = "";
			st += str[i];
			for (j = 0; j < numOfPro; j++)
			{
				k = 1;
				while (gramer[j][k] != "")
				{
					if (gramer[j][k] == st)
					{
						resultStr = concat(resultStr, gramer[j][0]);
					}
					k++;
				}
			}
			matrix[i][i] = resultStr;
		}

		for (k = 1; k < str.length(); k++)       //Matrixe kalan k�s�mlar� atama
		{
			for (j = k; j < str.length(); j++)
			{
				resultStr = "";
				for (l = (j - k); l < j; l++)
				{
					pResStr = combine(matrix[j - k][l], matrix[l + 1][j]);
					resultStr = concat(resultStr, pResStr);
				}
				matrix[j - k][j] = resultStr;
			}
		}

		for (i = 0; i < start.length(); i++) {
			if (matrix[0][str.length() - 1].find(start[i]) <= matrix[0][str.length() - 1].length())   //Matrix'in en �st�nde start sembolu olup olmad���n� yani
			{																						//start sembol�nden olu�turmaya ba�lay�p ba�lamad��� kontrol�
				cout << "YES" << endl;
				resultfile << "YES\n";
				break;
			}
			else {
				cout << "NO" << endl;
				resultfile << "NO\n";
				break;
			}
		}
	}
	getchar();
	grammarfile.close();
	wordfile.close();
	resultfile.close();
	return 0;
}
