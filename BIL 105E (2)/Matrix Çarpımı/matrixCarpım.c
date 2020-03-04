#include <stdio.h>

int main(){
	int n, m, o, p, r;
	
	printf("Welcome to the Matrix Multiplication Calculator\n\n");
	printf("This is the program that calculates the [A]*[B]\n\n");
	printf("Enter 3 digits (n)(m)(o) that represents both matrix's size (n)(m) and (m)(o): \n");
	scanf("%d%d%d", &n, &m, &o);
	
	int matrix1[n][m];
	int matrix2[m][o];
	int sonuc[n][o];
	
	printf("Enter the values of first matrix: \n");
	for( p = 0; p < n; p++ ){
		for( r = 0; r < m; r++ ){
			printf("Row %d, Column %d: ", (p+1), (r+1) );
			scanf("%d", &matrix1[p][r] );
		}
	}
	printf("\n");
	printf("Enter the values of second matrix: \n");
	for( p = 0; p < m; p++ ){
		for( r = 0; r < o; r++ ){
			printf("Row %d, Column %d: ", (p+1), (r+1) );
			scanf("%d", &matrix2[p][r] );
		}
	}
	
	for( p = 0; p < n; p++ ){
		for( r = 0; r < o; r++ ){
			sonuc[p][r] = 0;
		}
	}
	
	int i, j, k;
	
	for( k=0; k<n; k++ ){
			for( i=0; i<m; i++ ){
				for( j=0; j<o; j++ ){
					sonuc[k][j] += matrix1[k][i] * matrix2[i][j];	
				}
			}	
	}
	
	for( i=0; i<n; i++ ){
		for( j=0; j<o; j++ ){
			printf("%4d  ", sonuc[i][j]);
			if(j == (o-1))
				printf("\n");
		}
	}
}
