#include <stdio.h>

int main(){
	int h, i, j;
	printf("Ucgen icin yukseklik:");
	scanf("%d", &h);
	
	for(i=1; i<=h; i++){
		for(j=0; j<h-i; j++) 
			printf(" ");
		for(j=0; j<2*i-1; j++)
			printf("*");
		printf("\n");
			
	}
	return 0;
}
