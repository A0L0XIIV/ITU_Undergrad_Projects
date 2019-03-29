#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void romannumerals(int);
void romentonumber(char* romen);

int main(){
	
	int selection = 1;
	int number;
	char romen[100] = { 0 };

	
	while(selection != 0){
		
		printf("Enter 1 to Number to Romen Numeral,\nEnter 2 to Romen Numeral to Number,\nEnter 0 to terminate: ");
		scanf("%d", &selection);
		
		if(selection == 0)
			return 0;
		else if(selection == 1){
			printf("Enter a number: \n");
			scanf("%d", &number);
			
			romannumerals(number);
		}
		
		else if(selection == 2){
			printf("Enter a romen numeral: \n");
			scanf("%s", romen);
			
			romentonumber(romen);
		}
		
		puts(" ");
	}
	
	return 0;
}

void romannumerals(int number){
	
	int i;
	
	if(number < 1000){
		int hundredn = (number%1000)/100;
		
		for(i=0; i<hundredn; i++)
			printf("M");
		
		int tenn = (number%100)/10;
		
		if(tenn >= 5){
			
			printf("L");
			for(i=0; i<(tenn-5); i++)
				printf("X");
			
		}else{
			
			for(i=0; i<tenn; i++)
				printf("X");
		}
	
	
	if(number % 10 == 1)
		printf("I");
	else if(number % 10 == 2)
		printf("II");
	else if(number % 10 == 3)
		printf("III");
	else if(number % 10 == 4)
		printf("IV");
	else if(number % 10 == 5)
		printf("V");
	else if(number % 10 == 6)
		printf("VI");
	else if(number % 10 == 7)
		printf("VII");
	else if(number % 10 == 8)
		printf("VIII");
	else if(number % 10 == 9)
		printf("IX");
	}
		
}


void romentonumber(char *romen){
	
	int i;
	int number = 0;
	int lenght = strlen(romen);

	for(i=0; i<lenght; i++){
		if(romen[i] == 'C' || romen[i] == 'c')
			number += 1000;
		else if(romen[i] == 'M' || romen[i] == 'm')
			number += 100;
		else if(romen[i] == 'L' || romen[i] == 'l')
			number += 50;
		else if(romen[i] == 'X' || romen[i] == 'x')
			number += 10;
		else if(romen[i] == 'V' || romen[i] == 'v')	
			number += 5;	
		else if(romen[i] == 'I' || romen[i] == 'i'){
			
			number += 1;
			
			if(romen[i+1] == 'V' || romen[i+1] == 'v' || romen[i+1] == 'X' || romen[i+1] == 'x')
				
				number -= 2;
		}
			
	}
	
	printf("%d\n", number);
	
}
