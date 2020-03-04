#include <stdio.h>

int asal(int a);
int armstrong(int b);

int main(){
	
	int x;
	
	printf("Enter a number:");
	scanf("%d", &x);
	
	if(asal(x) == 1)
		printf("true");
	else
		printf("false");
	
	

}

int asal(int a){

	int i;
	int y=1;
	for(i=2; i<a; i++){
		if(a%i == 0){
			y=0;
			break;				
		}
	}
	return y;
	
}

int armstrong(int b){
	
	int i;
	
	for(i=1 ;;)
		a = a/10;
	
}
