#include <stdio.h>

int main(){
	int ID;
	char nick[100];
	int level;
	
	FILE *Fptr;
	
	if( ( Fptr = fopen( "a.txt", "wb+") ) == NULL )
		printf("File could not be opened.");
	else{
		printf("Enter:");
		scanf("%d %s %d ",&ID, &nick, &level);
		
		while( !feof(stdin) ){
			fprintf(Fptr, "%d %s %d\n ",ID ,nick, level);
			printf("?");
			scanf("%d %s %d", &ID, &nick, &level);
		}
	fclose(Fptr);
	}
	return 0;
}
