#include <stdio.h>

int main(){
	
	int n = 50;
	
	printf("n = %d,   n adresi = %x\n",n,&n);
	
	int *ptrn = &n;
	
	printf("ptrn = %d, ptrn = %x, ptrn adresi = %x\n",*ptrn,ptrn,&ptrn);
}
