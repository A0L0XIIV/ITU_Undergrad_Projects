#include <stdio.h>
#define SIZE 3

int main(){
	char matrix[SIZE][SIZE] = { {'_','_','_'}, {'_','_','_'}, {'_','_','_'} };
	int a, i, j, c, r;
	
	for( a = 0; a < 9; a++ ){
		if( a % 2 == 0 || a == 0)
			printf("First player: \n");
		else
			printf("Second player: \n");
		scanf("%d %d", &r, &c);
		
		for( i = 0; i < SIZE; i++ ){
			for( j = 0; j < SIZE; j++ ){
				printf("%c", matrix[i][j]);
			}
			if( (j+1) % 3 == 0 )
				printf("\n");
		}
		printf("\n\n");
		if( a % 2 == 0 || a == 0 )
			matrix[r][c] = 'X';
		else 
			matrix[r][c] = 'O';
		for( i = 0; i < SIZE; i++ ){
			if( matrix[i] == 'X' ){
				printf("Player 1 wins!");
			}	
			else if( matrix [i] == 'O' ){
				printf("Player 2 wins!");
			}
			else{
				break;
			} 
		}
		for( i = 0; i < SIZE; i++){
			for( j = 0; j < SIZE; j++){
				if( matrix[j] == 'X' ){
					printf("Player 1 wins!");
				}
				else if( matrix [j] == 'O' ){
					printf("Player 2 wins!");
				}
				else{
					break;
				} 
			}
		}
		if( matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X' || matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X')
			printf("Player 1 wins!");
		else if( matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O' || matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O')
			printf("Player 2 wins!");
		else
			continue;
	}
	return 0;
}
