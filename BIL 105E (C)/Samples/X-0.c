#include <stdio.h>
#include <stdlib.h>

char matrix[3][3];
char check(void);;
void init_matrix(void);
void get_player1_move(void);
void get_player2_move(void);
void disp_matrix(void);

int main(){
	char done;
	
	printf("~~~~This is a game of X-0~~~~\n\n");
	
	done=' ';
	init_matrix();
	
	do{
		disp_matrix();
		get_player1_move();
		done=check();
		if(done!=' ')break;
		disp_matrix();
		get_player2_move();
		done=check();
	}while(done==' ');
	if(done=='x')printf("Player1 won the game!\n");
	if(done=='0')printf("Player2 won the game!\n");
	disp_matrix();
	
	return 0;
}
void init_matrix(void)
{
	int i, j;
	
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)matrix[i][j]=' ';
}
void get_player1_move(void)
{
	int x, y;
	
	printf("\n(PLAYER 1) Enter X-Y coordinates for your move: ");
	scanf("%d%*c%d", &x, &y);
	x--, y--;
	
	if(matrix[x][y]!=' '){
		printf("Invalid move! Try again");
		get_player1_move();
	}
	else matrix[x][y]='x';
}
void get_player2_move(void)
{
	int x, y;
	
	printf("\n(PLAYER 2) Enter X-Y coordinates for your move: ");
	scanf("%d%*c%d", &x, &y);
	x--, y--;
	
	if(matrix[x][y]!=' '){
		printf("Invalid move! Try again");
		get_player2_move();
	}
	else matrix[x][y]='0';
}
void disp_matrix(void)
{
	int t;
	
	for(t=0; t<3; t++){
		printf(" %c | %c | %c ", matrix[t][0], matrix[t][1], matrix[t][2]);
		if(t!=2)printf("\n---|---|---\n");
	}
	printf("");
}
char check(void)
{
	int i;
	
	for(i=0; i<3; i++)
		if(matrix[i][0]==matrix[i][1]&&matrix[i][0]==matrix[i][2])return matrix[i][0];
	for(i=0; i<3; i++)
		if(matrix[0][i]==matrix[1][i]&&matrix[0][i]==matrix[2][i])return matrix[0][i];
	if(matrix[0][0]==matrix[1][1] && matrix[1][1]==matrix[2][2]) return matrix[0][0];
	if(matrix[0][2]==matrix[1][1] && matrix[1][1]==matrix[2][0]) return matrix[0][2];
	
	return ' ';
}
