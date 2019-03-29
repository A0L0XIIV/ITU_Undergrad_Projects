#include <stdio.h>

//#define ROW 4
//#define COL 5

	int row = 4; 
	int col = 5;
int search(int, int, int, int array[row][col]);

int main() {
	int n;
	int row = 4; 
	int col = 5;
	int array[4][5] = { { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15 }, { 16, 17, 18, 19, 20 } };
					
	printf("Enter the value that function will search: ");
	scanf("%d", &n);
	int i,j;
	for( i = 0; i < row; i++ ){
		for( j = 0; j < col; j++ ){
			printf("%d\n", array[i][j]);
		}
	}
	//search(n, row, col, array[row][col]);
	printf("n has been found at %d", search( n, row, col, array[row][col] ) );
	if( search(n, row, col, array[row][col]) == -1 )
		printf("This array does not contain %d value.", n);
	else
		printf("n has been found at %d", search( n, row, col, array[row][col] ) );										
}

int search(int n, int row, int col, int array[row][col]){
	int i,j;
	for( i = 0; i < row; i++ ){
		for( j = 0; j < col; j++ ){
			if( array[i][j] == n )
				return n;
			else
				return -1;
		}
	}
}
