#include <stdio.h>

unsigned int recursion(unsigned int);
unsigned int recpol(unsigned int);

int main(){
	
	unsigned int n;
	int i;
	
	printf("Enter the recursion level of dreams: ");
	scanf("%u", &n);
	
	printf("To live in a dream\n");
	recursion(n);
	
	
}

unsigned int recursion (unsigned int a){
	int i;
	if( a == 1 ){
		for(i=1; i<=a; i++)
			printf("***");
		printf("as a rank %d thief within a dream\n", a );
		return 1; //recpol(a);
	}
	else{
		for(i=1; i<=a; i++)
			printf("***");
		printf("as a rank %d thief within a dream\n", a );
		return ( recursion(a-1) );
	}
}

/*unsigned int recpol (unsigned int b){
	int c;
		
	if( c == (b+1) ){
		printf("caught by the police of rank %d\n", c );
		return 1;
	}
	else{
		printf("caught by the police of rank %d\n", c );	
		return recpol(c+1);
	}
}*/

