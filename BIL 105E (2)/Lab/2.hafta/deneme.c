#include <stdio.h>

int main(){

int i, j;
int height, width, thickness;

printf("Height, width and thickness:");
scanf("%d %d %d",&height, &width, &thickness);

for(i=0; i<=thickness; ++i){
	for(j=0; j<=width; ++j);{
		printf("*");
	
	}
}

}
