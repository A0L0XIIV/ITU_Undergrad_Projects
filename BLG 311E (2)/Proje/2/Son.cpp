/*
GROUP MEMBERS:
BARAN KAYA				150130032
KADÝR ENES KARSLIOÐLU	150130047
NOTE: Program Visual Studio'da proje þeklinde yazýldý ve çalýþýyordu fakat, Dev-C++'da çalýþmýyordu. Linux deneme þansýmýz olmadý.
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

string gramer[MAX][MAX];  //grameri tutmak için
int numOfPro = 0;		//nonTerminal sayýsý (main ve diðer fonksiyonlarda olduðu için global)

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


string search_string(string sStr) //sStr'yi oluþturabilecek konkatlanmýþ stringleri bulur
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


string combine(string frstStr, string scndStr)  //birinci ve ikinci stringlerden oluþabilecek bütün kombinasyonlarý oluþturur (11,22,12,21)
{
	int i, j;
	string tempStr = frstStr, resultStr = "";
	for (i = 0; i < frstStr.length(); i++) {
		for (j = 0; j < scndStr.length(); j++)
		{
			tempStr = "";
			tempStr = tempStr + frstStr[i] + scndStr[j];
			resultStr = resultStr + search_string(tempStr);   //sonuç string üretilebilir mi üretilemez mi kontrol eder
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
	int i = -2, pt, sp, j, l, k, abc;		//i terminal ve nonTerminalleri kontrol ederken arttýðý için ve grammar matrixi içine 0'dan baþlayýp atmasý için -2
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
				if (Line.substr(sp + 1, 1) != gramer[i - 1][0]) {	//2 ayný nonTerminaller 2 satýrda olacaðý için 2 satýrdaki ayný deðil ise gramer'in içine at
					gramer[i][0] = Line.substr(sp + 1, 1); //baþtaki sayýlarý almamasý için substr boþluktan bir sonraki yani nonTerminalden baþlar
					//bonus[i] = Line.substr(0, sp);		//Bonus part için gereken sayýlar
					::numOfPro++;
				}
				else {	//Önceki nonTerminal ile ayný ise sað taradtakileri yine ayný gramer[i]'nin içine atmak için i-- ve aynýsý olduðu için same true
					i--;
					same = true;
				}
				Line = Line.substr(pt + 3, Line.length()); //Sað taraftakileri bölme
				if (same == false)	//Sol taraftaki nonTerminal ayný deðil ise
					gramer[i][1] = Line;
				else {				//Ayný ise
					gramer[i][2] = Line;
					same = false;
				}
			}

			i++;
		}

		string matrix[MAX][MAX], st;
		getline(wordfile, str);		//words.txt'ten kelimeleri okuma

		for (i = 0; i < str.length(); i++)       //Matrixe çapraz deðerleri atama
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

		for (k = 1; k < str.length(); k++)       //Matrixe kalan kýsýmlarý atama
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
			if (matrix[0][str.length() - 1].find(start[i]) <= matrix[0][str.length() - 1].length())   //Matrix'in en üstünde start sembolu olup olmadýðýný yani
			{																						//start sembolünden oluþturmaya baþlayýp baþlamadýðý kontrolü
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
