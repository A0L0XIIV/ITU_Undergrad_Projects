#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students{
	int ID;
	char name[50];
	float grade1, grade2, grade;
}student;

int main(){
	
	FILE *fptr;
	
	int i, n;
	float total = 0;
	float average = 0;
	
	struct Students s[100];
	
	printf("Enter student number: ");
	scanf("%d", &n );
	
	for( i = 1; i <= n; i++ ){

		printf("Enter student ID, Name, grade1 and grade2: ");
		scanf("%d %s %f %f",&s[i].ID, &s[i].name, &s[i].grade1, &s[i].grade2);
		s[i].grade = 0.4 * (s[i].grade1) + 0.6 * (s[i].grade2);
		total += (0.4 * (s[i].grade1) + 0.6 * (s[i].grade2));
		average = total / n;
	}
	
	printf("\n\n");
	printf("Average = %.2f\n\n", average);
	printf("Passed:\n\n");
	for( i = 1; i <= n; i++ ){
		if( s[i].grade > average ){
			printf("%5d %10s %3.2f\n",s[i].ID, s[i].name, s[i].grade);
		}
	}
	printf("\n");
	printf("Failed:\n\n");
	for( i = 1; i <= n; i++ ){
		if( s[i].grade < average ){
			printf("%5d %10s %3.2f\n",s[i].ID, s[i].name, s[i].grade);
		}
	}
	
	if( (fptr = fopen("a.txt", "wb+")) == NULL )
		printf("File could not be opened.\n");
	else{
		fprintf(fptr, "%.2\n\n", average);
		fprintf(fptr, "Passed:\n\n");
		for( i = 1; i <= n; i++ ){
			if( s[i].grade > average ){
				fprintf(fptr, "%5d %10s %3.2f\n",s[i].ID, s[i].name, s[i].grade);	
			}
		}
		fprintf(fptr, "\n");
		fprintf(fptr, "Failed:\n\n");
		for( i = 1; i <= n; i++ ){
			if( s[i].grade < average ){
				fprintf(fptr, "%5d %10s %3.2f\n",s[i].ID, s[i].name, s[i].grade);	
			}
		}
		fclose(fptr);
	}
	
	return 0;
}

