#include <stdio.h>

int main(){
	int n, p, r;
	
	printf("This is the program that calculates the [A]*[B] but A and B must be a square matrix...\n\n");
	printf("Enter the square matrix's size (n): \n");
	scanf("%d", &n);
	
	int matrix1[n][n];
	int matrix2[n][n];
	int sonuc[n][n];
	
	printf("Enter the values of first matrix: \n");
	for( p = 0; p < n; p++ ){
		for( r = 0; r < n; r++ ){
			printf("Row %d, Column %d: ", (p+1), (r+1) );
			scanf("%d", &matrix1[p][r] );
		}
	}
	printf("\n");
	printf("Enter the values of second matrix: \n");
	for( p = 0; p < n; p++ ){
		for( r = 0; r < n; r++ ){
			printf("Row %d, Column %d: ", (p+1), (r+1) );
			scanf("%d", &matrix2[p][r] );
		}
	}
	
	for( p = 0; p < n; p++ ){
		for( r = 0; r < n; r++ ){
			sonuc[p][r] = 0;
		}
	}
	
	int i, j, k;
	
	for( k=0; k<n; k++ ){
		for( i=0; i<n; i++ ){
			for( j=0; j<n; j++ ){
				sonuc[i][j] += matrix1[i][k] * matrix2[k][j];	
			}
		}
	}
	
	for( i=0; i<n; i++ ){
		for( j=0; j<n; j++ ){
			printf("%4d  ", sonuc[i][j]);
			if(j == (n-1))
				printf("\n");
		}
	}
}
