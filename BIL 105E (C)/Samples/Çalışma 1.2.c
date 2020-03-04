#include <stdio.h>

int main(){
	
	int ID;
	char name[100];
	float grade;
	
	FILE *fPtr;
	
	if( (fPtr = fopen( "a.txt", "w" ))== NULL )
		printf("File could not be opened.");
	else{
		printf("Enter students ID, Name, Grade:");
		scanf("%d %s %f", &ID, name, &grade);
		
		while( !feof(stdin) ){
			printf("Enter students ID, Name, Grade:");
			scanf("%d %s %f", &ID, name, &grade);
			fprintf(fPtr, "%4d %-10s %5.2f\n",ID ,name, grade);
			
		}
	fclose(fPtr);
	}
	return 0;
}
