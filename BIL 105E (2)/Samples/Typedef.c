#include <stdio.h>
#define SIZE 10

typedef struct workers{
	char name[20];
	char surname[20];
	int number;
	int salary;
}Workers;

int main(){
	int i;
	
	Workers worker[SIZE];
	Workers *wPtr;
	
	
	printf("Enter workers name, surname, number and salary: \n");
	
	for( i=0; i<=SIZE; i++){
		
		wPtr = &worker[i];
		
		scanf("%s %s %d %d", &worker[i].name, &worker[i].surname, &worker[i].number, &worker[i].salary);
		printf("Worker %d Name: %s Surname: %s Number: %d Salary: %d\n", i, worker[i].name, worker[i].surname, (*wPtr).number, wPtr->salary);
		
	}	
}
