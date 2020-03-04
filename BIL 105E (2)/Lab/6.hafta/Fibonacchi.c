#include <stdio.h>

unsigned long long int fibonachi(unsigned int);
int main(){
	
	unsigned int n;
	
	printf("Enter a number:");
	scanf("%u", &n);
	
	printf("Fibonacchi %u is %llu", n, fibonachi(n) );

}

unsigned long long int fibonachi(unsigned int n){
	if(n == 0)
		return 0;
	else if ( n == 1 )
		return 1;
	else 
		return ( fibonachi(n-1) + fibonachi(n-2) );
}
