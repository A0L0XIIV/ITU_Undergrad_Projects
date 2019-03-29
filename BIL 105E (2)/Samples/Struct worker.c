#include <stdio.h>
#define SIZE 10

struct workers{
	char name[20];
	char surname[20];
	int number;
	int salary;
}workers[SIZE], *wPtr;  //Bunlara gerek yok, bunlar yazýlmadan da çalýþýyor

int main(){
	int i;
	
	struct workers worker[SIZE];
	struct workers *wPtr;
	
	
	printf("Enter workers name, surname, number and salary: \n");
	
	for( i=0; i<=SIZE; i++){
		
		wPtr = &worker[i];
		
		scanf("%s %s %d %d", &worker[i].name, &worker[i].surname, &worker[i].number, &worker[i].salary);
		printf("Worker %d Name: %s Surname: %s Number: %d Salary: %d\n", i, worker[i].name, worker[i].surname, (*wPtr).number, wPtr->salary);
		
	}	
}
