#include <stdio.h>
#include <string.h>

int main(){
	char cumle[20], kopya[20];
	
	printf("Bir cumle giriniz: ");
	fgets(cumle, 20, stdin);
	printf("Girilen cumle: %s\n", cumle);
	printf("Uzunlugu: %d\n", strlen(cumle));
	
	strcpy(kopya, cumle);
	printf("kopyasi: %s\n", kopya);
	
	return 0;
}
