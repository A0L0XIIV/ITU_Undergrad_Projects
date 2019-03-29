#include <stdio.h>

isPrime(int, int);

int main(){
	int n;
	
	printf("Enter the number:");
	scanf("%d", &n);
	
	if(isPrime(n, n-1) == 1)
		printf("The number is not prime");
	else
		printf("The number is prime");
	
}

isPrime(int a, int b){
	
	if(b == 1)
		return 0;
	else{
		if( a % b == 0 )
			return 1;
		else
			return isPrime(a, b-1);
	}
	
}
