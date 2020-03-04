#include <stdio.h>

int main(){
	char cumle[20], *ptr;
	int fark = 'a' - 'A';
	
	printf("Bir cumle giriniz: ");
	fgets(cumle, 20, stdin);
	ptr = cumle;
	printf("Girilen cumle: %s\n", ptr);
	
	printf("Buyuk Harflerle: ");
	while(*ptr != '\0'){
		if((*ptr >= 'a') && (*ptr <= 'z'))
			printf("%c", *ptr - fark);
		else
			printf("%c", *ptr);
		ptr++;
	}
	printf("\n");
	
	return 0;
}
