#include <stdio.h>

int main(){

int  i, j, k=0, a;
	
	printf("Give me the baclava's height:'\n");
	printf("-->");
	scanf("%d", &a);
	printf("\n\n");
	
	for( i = 1; i <= a; ++i ){
		for( j = 1; j <= a-i; ++j){
			printf(" ");
		}
		for( ; k != 2*i-1; ++k){
			printf("*");
		}
		k=0;
		printf("\n");
	}
	for( i = a; i >= 1; --i ){
		for( j = a-i; j >= 1; --j){
			printf(" ");
		}
		if(i!=a){
			for( ; k != 2*i-1; ++k){
				printf("*");
			}
			k=0;
			printf("\n");
		}	
		
	}
	printf("\n\nCongrats BITCH U made it im suprised!!!\n\n");
	system("pause");
	return 0;
}
