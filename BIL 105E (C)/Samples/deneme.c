#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char name[50];
	
	FILE *aPtr;
	
	if ( ( aPtr = fopen("a.txt", "w") ) == NULL )
		puts("File could not be opened.");
	else{
		printf("Enter:");
		scanf("%s", name);
		fprintf(aPtr, "%s", name);
	fclose(aPtr);
	}
	return 0;
}
