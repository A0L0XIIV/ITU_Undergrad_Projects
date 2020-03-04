#include <stdio.h>

int main () {
	int ID;
	char name[100];
	float grade;
	
	FILE *fPtr;
	
	if( (fPtr = fopen("a.txt", "r"))==NULL )
		printf("File could not be opened.\n");
	else{
		printf("ID   Name    Grade\n");
		while( !feof(fPtr) ){
			fscanf(fPtr, "%d %s %f", &ID, name, &grade);
			printf("%4d %6s %.2f\n",ID ,name, grade);
		}
		fclose(fPtr);
	}
	return 0;
}
