#include <string.h>
#define MAX_LINES 100

void findAcrosticStr(char **lines, unsigned int linescount, unsigned int i, char *returnStr);

int main(){
	char *poem[MAX_LINES]={"An acrostic poem", 
						   "Creates a chellange",
						   "Random words on a theme",
						   "Or whole sentences that ryhme",
						   "Select your words carefully",
						   "To form a word from top to bottom",
						   "Is the aim of this poetry style",
						   "Choose a word then go!"
						  };
	
	char acrostic[MAX_LINES+1];
	findAcrosticStr(poem, MAX_LINES, 28, acrostic);
	printf("%s", acrostic);
	return 0;
}
void findAcrosticStr(char **lines, unsigned int linescount, unsigned int i, char *returnStr){
	int c;
	for(c=0; ((c<linescount)&&(lines[c]!=NULL)); c++){
		if(i<=strlen(lines[c]))
			*returnStr++ = *(lines[c]+i-1);
		else
			*returnStr++ = '?';
	}
	*returnStr = '\0';
}
