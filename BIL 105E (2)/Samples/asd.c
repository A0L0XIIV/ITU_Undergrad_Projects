#include <stdio.h>

double cos(int x, int n);

int main(){
	int x, n;
	scanf("%d%d", &x, &n);
	cos(x,n);
	printf("%f", cos(x, n) );
	
}double cos(int x, int n){
	int i, j, sign = 1, fact;
	double c;
	if(n==1)
		c = 0;
	else{
		for(i=1; i<=n; i++){
			sign *= -1;
			fact = 1;
			for(j=1; j <= 2*(i-1); j++)
				fact *= j;
			c += ( (sign * pow(x, 2*(i-1)) ) / fact );
			printf("%f\n", c);
		}
	}
	puts("");
	return 1-c;
}
