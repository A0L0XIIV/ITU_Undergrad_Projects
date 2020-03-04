#include <stdio.h>

int main(){
	char kelime[15], *ptr;
	
	printf("Bir kelime giriniz: ");
	scanf("%s", kelime); printf("%s\n", kelime);
	
	for (ptr = kelime; *ptr != '\0'; ptr++){
		printf("%c", *ptr);
	};
	printf("\n");
	
	while(ptr-- != kelime){
		printf("%c", *ptr);
	};
	printf("\n");
	
	return 0;
}
