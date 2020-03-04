#include <stdio.h>

int main(){
	int ID;
	char nick[100];
	int level;
	
	FILE *Fptr;
	
	if( ( Fptr = fopen( "a.txt", "rb") ) == NULL )
		printf("File could not be opened.");
	else{
		printf("ID   Nick   Level\n");
		fscanf(Fptr, "%d %s %d ",&ID, nick, &level);
		
		while( !feof(Fptr) ){
			printf("%d  %5s  %d\n",ID ,nick, level);
			fscanf(Fptr, "%d %s %d", &ID, nick, &level);
		}
	fclose(Fptr);
	}
	return 0;
}
