/* @Author
* Student Name: Baran Kaya
* Student ID: 150130032
* Date: 25.12.2016
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <limits.h>
#define STACKSIZE 100
//#define LONG_MAX numeric_limits<int>::max()
//#define LONG_MIN numeric_limits<int>::lowest()

long int long_max = std::numeric_limits<long>::min();
long int long_min = std::numeric_limits<long>::max();

struct sNode{
	char data;
	long int number;
	sNode *next;	
};

struct qNode{
	long int data;
	qNode *next;	
};

//--------------------------------------------STACK-----------------------------------------

struct Stack{
	char element[STACKSIZE];
	int top;
	sNode *head;
	
	void create();
	void close();
	void push(char);
	void pushNumber(long int);
	char pop();
	long int popNumber();
	bool isemptyS();
};


void Stack::create(){
	head = NULL;
}


void Stack::close(){
	sNode *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}


void Stack::push(char newdata) {
	sNode *newnode = new sNode;
	newnode->data = newdata;
	newnode->number = NULL;
	newnode->next = head;
	head = newnode;
}


void Stack::pushNumber(long int newnum) {
	sNode *newnode = new sNode;
	newnode->number = newnum;
	newnode->data = NULL;
	newnode->next = head;
	head = newnode;
}


char Stack::pop() {
	sNode *topnode;
	char temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}


long int Stack::popNumber() {
	sNode *topnode;
	long int temp;
	topnode = head;
	head = head->next;
	temp = topnode->number;
	delete topnode;
	return temp;
}


bool Stack::isemptyS(){
	return head == NULL;	
}

//--------------------------------------------QUEUE-----------------------------------------

struct Queue{
	qNode *front;
	qNode *back;
	
	void create();
	void close();
	void enqueue(long int);
	long int dequeue();
	bool isemptyQ();
};


void Queue::create(){
	front = NULL;
	back = NULL;
}


void Queue::close(){
	qNode *p;
	while (front){
		p = front;
		front = front->next;
		delete p;
	}
}


void Queue::enqueue(long int newdata) {
	qNode *newnode = new qNode;
	newnode->data = newdata;
	newnode->next = NULL;
	if( isemptyQ() ){
		back = newnode;
		front = back;
	}
	else{
		back->next = newnode;
		back = newnode;
	}
}

/*
//QueueDataType Queue::dequeue(){
long int Queue::dequeue() {
	qNode *topnode;
	//QueueDataType temp;
	long int temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}*/

long int Queue::dequeue() {
	qNode *topnode;
	topnode = front;
	front = front->next;
	long int temp = topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isemptyQ(){
	return front == NULL;
}

using namespace std;

//--------------------------------------------MAIN-----------------------------------------

int main(){
	Stack s, numberS;
	Queue q;
	s.create();
	numberS.create();
	q.create();
	
	char value[100];
	memset(value, '\0', 100);
	string prefixStr, postfixStr, prefixSymbols, postfixSymbols; //prefixSymbols iþlemlerin çözümü için gerekli
	cout << "Initializing the interpreter..." << endl;
	int j = 0;

	while(1){
		
		cout << endl << ">> ";
		getline(cin, prefixStr);

		if( prefixStr == "exit" || prefixStr == "EXIT" ) //"exit" girilirse döngüyü bitirip programý kapatýr
			break;

		
		for (int i = 0; i < prefixStr.length()+1; i++) {	
			
			if (prefixStr[i] == ' ' || prefixStr.length() == i) {	//Boþlukta veya string sonunda value'nun içindekileri kontrol eder*
				if (prefixStr[i] == ' ') {//Sonda deðilse ve boþluk varsa atlamak için i++
					j = 0;
					i++;
				}

				if (strcmp(value, "abs") == 0) {
					s.push('B');
					prefixSymbols += "B ";
				}
				else if (strcmp(value, "sqrt") == 0) {
					s.push('S');
					prefixSymbols += "S ";
				}
				else if (strcmp(value, "sub") == 0) {
					s.push('-');
					prefixSymbols += "- ";
				}
				else if (strcmp(value, "div") == 0) {
					s.push('/');
					prefixSymbols += "/ ";
				}
				else if (strcmp(value, "exp") == 0) {
					s.push('E');
					prefixSymbols += "E ";
				}
				else if (strcmp(value, "log") == 0) {
					s.push('L');
					prefixSymbols += "L ";
				}
				else if (strcmp(value, "mod") == 0) {
					s.push('M');
					prefixSymbols += "M ";
				}
				else if (strcmp(value, "sum") == 0) {
					s.push('+');
					prefixSymbols += "+ ";
				}
				else if (strcmp(value, "product") == 0) {
					s.push('*');
					prefixSymbols += "* ";
				}
				else if (strcmp(value, "min") == 0) {
					s.push('N');
					prefixSymbols += "N ";
				}
				else if (strcmp(value, "max") == 0) {
					s.push('X');
					prefixSymbols += "X ";
				}
				else if (isdigit(value[0]) || strcmp(value, "ans") == 0 || strcmp(value, "inf") == 0 || strcmp(value, "-inf") == 0) {

					//SAYI, ANS VEYA INF

					if (isdigit(value[0])) { //sayý ise
						postfixStr += value;
						prefixSymbols += value;
						postfixSymbols += value;
					}
					else if (strcmp(value, "ans") == 0) {//ans ise
						postfixStr += " ans";
						prefixSymbols += "A ";
						postfixSymbols += " A";
					}
					else if (strcmp(value, "inf") == 0) {//inf ise
						postfixStr += " inf";
						prefixSymbols += "inf ";
						postfixSymbols += " inf";
					}
					else if (strcmp(value, "-inf") == 0) {//-inf ise
						postfixStr += " -inf";
						prefixSymbols += "-inf ";
						postfixSymbols += " -inf";
					}

					//OPERAND DEÐÝL ÝSE

					if (s.head != NULL/*!s.isemptyS()*/) { 

						//BINARY OPERANDS

						if (s.head->data == '-' || s.head->data == '/' || (s.head->data == 'O' && (s.head->next->data == '-' || s.head->next->data == '/'))) {
							while (!s.isemptyS() && s.head->data == 'O') {	//Ýki operand alan iþlemlerin iki operandý var mý yok mu kontrol için
								s.pop();
								if (s.head->data == '-') {
									postfixStr += " sub";
									postfixSymbols += " -";
								}
								else if (s.head->data == '/') {
									postfixStr += " div";
									postfixSymbols += " /";
								}
								s.pop();
							}
							s.push('O');//Ýlk operand ise O pushla
						}

						//UNARY OPERANDS

						if (s.head->data == 'B' || s.head->data == 'S' || (s.head->next != NULL && (s.head->data == 'O' && (s.head->next->data == 'B' || s.head->next->data == 'S')))) {
							if (s.head->data == 'O') {
								s.pop(); //pop O
								if (s.head->data == 'B') {
									postfixStr += " abs";
									postfixSymbols += " B";
								}
								else if (s.head->data == 'S') {
									postfixStr += " sqrt";
									postfixSymbols += " S";
								}
								s.pop(); //pop B or S

							}
							else if (s.head->next != NULL && (s.head->next->data == '+' || s.head->next->data == '*' || s.head->next->data == 'N' || s.head->next->data == 'X'))//BAÞTA O OLABÝLÝR
								if ((i) == prefixStr.length()) {
									if (s.head->data == 'B') {
										postfixStr += " abs";
										postfixSymbols += " B";
									}
									else if (s.head->data == 'S') {
										postfixStr += " sqrt";
										postfixSymbols += " S";
									}
									s.pop(); //pop B or S
								}
							else {
								if (s.head->data == 'B') {
									postfixStr += " abs";
									postfixSymbols += " B";
								}
								else if (s.head->data == 'S') {
									postfixStr += " sqrt";
									postfixSymbols += " S";
								}
								s.pop(); //pop B or S
							}
						}

						//UNARY/BINARY OPERANDS

						if (s.head->data == 'E' || s.head->data == 'L' || s.head->data == 'M' || (s.head->next != NULL && (s.head->data == 'O' && (s.head->next->data == 'E' || s.head->next->data == 'E' || s.head->next->data == 'M')))) {
							//Tek sayý varsa
							if (s.head->data == 'E' || s.head->data == 'L' || s.head->data == 'M') {
								if (s.head->data == 'E') {
									postfixStr += " exp";
									postfixSymbols += " E";
								}
								else if (s.head->data == 'L') {
									postfixStr += " log";
									postfixSymbols += " L";
								}
								else if (s.head->data == 'M') {
									postfixStr += " mod";
									postfixSymbols += " M";
								}
								s.pop();
							}
							//Ýki sayý varsa
							if (s.head->data == 'O') {
								while (!s.isemptyS() && s.head->data == 'O') {	//Ýki operand alan iþlemlerin iki operandý var mý yok mu kontrol için
									s.pop(); //O'yu çýkart
									if (s.head->data == 'E') {
										postfixStr += " exp";
										postfixSymbols += " E";
									}
									else if (s.head->data == 'L') {
										postfixStr += " log";
										postfixSymbols += " L";
									}
									else if (s.head->data == 'M') {
										postfixStr += " mod";
										postfixSymbols += " M";
									}
									s.pop();
								}
								s.push('O');//Ýlk operand ise O pushla
							}
						}

						//POLYNARY OPERANDS

						if (s.head->data == '+' || s.head->data == '*' || s.head->data == 'N' || s.head->data == 'X' || (s.head->next != NULL && ( s.head->data == 'O' && (s.head->next->data == '+' || s.head->next->data == '*' || s.head->next->data == 'N' || s.head->next->data == 'X') ) ) ) {
							if ((i) == prefixStr.length()) {
								if (s.head->data == 'O')
									s.pop(); //O'yu çýkart
								if (s.head->data == '+') {
									postfixStr += " sum";
									postfixSymbols += " +";
								}
								else if (s.head->data == '*') {
									postfixStr += " product";
									postfixSymbols += " *";
								}
								else if (s.head->data == 'N') {
									postfixStr += " min";
									postfixSymbols += " N";
								}
								else if (s.head->data == 'X') {
									postfixStr += " max";
									postfixSymbols += " X";
								}
								s.pop();
							}
						}
					}
				}

				memset(value, '\0', 100);
				postfixStr += " "; //Aralara boþluk yazdýrtma
				prefixSymbols += " ";
				postfixSymbols += " ";
			}
			if (prefixStr.length() != i) {
				value[j] = prefixStr[i]; //PrefixStrdeki boþluða kadar olan karakterleri value'ya yazdýrýr ve sonraki aþamada kontrol eder* 
				j++;
			}
		}
		cout << "Prefix: " << prefixStr << endl;
		cout << "Postfix: " << postfixStr << endl;
		cout << "Prefix with symbols: " << prefixSymbols << endl;
		cout << "Postfix with symbols: " << postfixSymbols << endl;
		//POSTFIX ÇEVÝRME SONU

		//PREFIX ÇÖZME

		int end = prefixSymbols.length() - 1;		//prefixSymbols String'i ters çevirme
		int start = 0;
		char temp;
		while (start < end)
		{
			temp = prefixSymbols[start];
			prefixSymbols[start] = prefixSymbols[end];
			prefixSymbols[end] = temp;
			start++;
			end--;
		}

		cout << "Reverse prefix symbols" << prefixSymbols << endl;

		char symbol[20];
		memset(symbol, '\0', 20);
		int a = 0;
		long int result = 0;

		for (int i = 0; i < postfixSymbols.length()+1; i++) {

			if (postfixSymbols[i] == ' ' || postfixSymbols.length() == i) {

				a = 0;
				result = 0;

				if (postfixSymbols.length() != i)
					i++;

				if ( isdigit(symbol[0]) ) {
					long int n = atoi(symbol);
					numberS.pushNumber(n);
				}

				else if (strcmp(symbol, "inf") == 0) {
					numberS.pushNumber(long_max);
				}

				else if (strcmp(symbol, "-inf") == 0) {
					numberS.pushNumber(long_min);
				}

				else if (symbol[0] == '-') {
					long int x = numberS.head->number;
					numberS.popNumber();
					long int y = numberS.head->number;
					numberS.popNumber();
					result = x-y;
					numberS.pushNumber(result);
				}

				else if (symbol[0] == '/') {
					long int x = numberS.head->number;
					numberS.popNumber();
					long int y = numberS.head->number;
					numberS.popNumber();
					if (x == long_max)
						result = long_max;
					else if (x == long_min)
						result = long_min;
					else if (y == long_max || y == long_min)
						result = 0;
					else
						result = x/y;
					numberS.pushNumber(result);
				}

				else if (symbol[0] == '+') {
					while (numberS.head)
						result += numberS.popNumber();
					numberS.pushNumber(result);
				}

				else if (symbol[0] == '*') {
					while (numberS.head)
						result *= numberS.popNumber();
				}

				else if (symbol[0] == 'A') {
					if(q.front)
						numberS.pushNumber(q.back->data);
					else {
						cout << "There is no previous answer!" << endl;
						break;
					}
				}

				else if (symbol[0] == 'B') {
					long int x = numberS.head->number;
					numberS.popNumber();
					result = abs(x);
					numberS.pushNumber(result);
				}

				else if (symbol[0] == 'S') {
					long int x = numberS.head->number;
					numberS.popNumber();
					result = sqrt(x);
					numberS.pushNumber(result);
				}

				else if (symbol[0] == 'N') {
					while (numberS.head) {
						long int x = numberS.head->number;
						numberS.popNumber();
						if(numberS.head) //popladýktan sonra hala kalan varsa result'ý deðiþtir
						result = fmin(x, numberS.head->number);
					}
				}

				else if (symbol[0] == 'X') {
					while (numberS.head) {
						long int x = numberS.head->number;
						numberS.popNumber();
						if (numberS.head) //popladýktan sonra hala kalan varsa result'ý deðiþtir
							result = fmax(x, numberS.head->number);
					}
				}

				else if (symbol[0] == 'E') {
					long int x = numberS.head->number;
					numberS.popNumber();
					if (numberS.head) {
						long int y = numberS.head->number;
						numberS.popNumber();
						result = pow(x, y);
					}
					else
						result = exp(x);
					numberS.pushNumber(result);
				}

				else if (symbol[0] == 'L') {
					long int x = numberS.head->number;
					numberS.popNumber();
					if (numberS.head) {
						long int y = numberS.head->number;
						numberS.popNumber();
						result = log(x) / log(y);
					}
					else
						result = log(x);
					numberS.pushNumber(result);
				}

				else if (symbol[0] == 'M') {
					long double resultD, ten = 10;
					long double x = numberS.head->number;
					numberS.popNumber();
					if (numberS.head) {
						long double y = numberS.head->number;
						numberS.popNumber();
						resultD = modfl(x, &y);
					}
					else
						resultD = modfl(x, &ten);
					numberS.pushNumber(resultD);
				}

				else {
					cout << "Syntax error!" << endl;
					break;
				}

				
				if(prefixStr.length() == i)
					q.enqueue(result);			//Sonucu queue ekle
				memset(symbol, '\0', 20);
			}

			if (postfixSymbols[i] != '\0' && postfixSymbols[i] != ' ') {
				symbol[a] = postfixSymbols[i];
				a++;
			}
		}
		cout << "Result:" << numberS.head->number << endl;
		//STACKLERÝ VE STRINGLERÝ BÝR SONRAKÝ ÝÞLEM ÝÇÝN TEMÝZLE
		s.close();
		s.create();
		numberS.close();
		numberS.create();
		prefixStr.clear();
		postfixStr.clear();
		prefixSymbols.clear();
		postfixSymbols.clear();
		j = 0;
	}
	cout << "Answer queue: ";
	while (q.front) //queue içinde eleman varsa yazdýr
		cout << q.dequeue() << " --> ";
	getchar();
	s.close();
	numberS.close();
	q.close();
	exit(1);	
}
