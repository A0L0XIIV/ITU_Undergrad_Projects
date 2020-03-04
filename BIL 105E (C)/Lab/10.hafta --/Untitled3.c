#include <stdio.h>

int main(){
	char *cumle = "Bugun hava cok guzel",
	     *kelime = cumle;
	int i = 1;
	
	printf("Cumle: %s\n", cumle);
	
	printf("%d. kelime: ", i++);
	while(*kelime != '\0'){
		if(*kelime == ' ')
			printf("\n%d. kelime: ", i++);
		else
			printf("%c", *kelime);
		kelime++;
	}
	printf("\n");
	
	return 0;
}
