#include <stdio.h>

int main(){
	int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int sonuc[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

	int i, j;

	

		for( i=0; i<=2; i++ ){
			for( j=0; j<=2; j++ ){
				/*sonuc[0][0] = matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[1][0] + matrix[0][2] * matrix[2][0];
				sonuc[0][1] = matrix[0][0] * matrix[0][1] + matrix[0][1] * matrix[1][1] + matrix[0][2] * matrix[2][1];
				sonuc[0][2] = matrix[0][0] * matrix[0][2] + matrix[0][1] * matrix[1][2] + matrix[0][2] * matrix[2][2];
				sonuc[1][0] = matrix[1][0] * matrix[0][0] + matrix[1][1] * matrix[1][0] + matrix[1][2] * matrix[2][0];
				sonuc[1][1] = matrix[1][0] * matrix[0][1] + matrix[1][1] * matrix[1][1] + matrix[1][2] * matrix[2][1];
				sonuc[1][2] += matrix[1][j] * matrix[i][2];
				sonuc[2][0] += matrix[2][j] * matrix[i][0];
				sonuc[2][1] += matrix[2][j] * matrix[i][1];
				sonuc[2][2] += matrix[2][j] * matrix[i][2];*/
				sonuc[i][j] = matrix[i][0] * matrix[0][j] + matrix[i][1] * matrix[1][j] + matrix[i][2] * matrix[2][j];
	
			}
		}
	
	for( i=0; i<=2; i++ ){
		for( j=0; j<=2; j++ ){
			printf("%d  ", sonuc[i][j]);
		}
	}
}
