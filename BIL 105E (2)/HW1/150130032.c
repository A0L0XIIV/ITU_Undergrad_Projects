#include <stdio.h>                                       //Baran Kaya 150130032  kayabaran@itu.edu.tr
#include <stdlib.h>
#include <time.h>

int main(){
	int N, S=0, W, P;
	int score1=0, score2=0;
	int round_counter=0;
	int pass_counter;
	int captured_team;
	srand(time(NULL));
	
	printf("Enter number of players per team:\n");
	scanf("%d", &N);
	
	printf("Enter the probability for a successfull pass (0-100):\n");
	scanf("%d", &P);
	
	printf("Enter number of passes to win a single round:\n");
	scanf("%d", &W);
	
	printf("Enter target score:\n");
	scanf("%d", &S);
	
	printf("\n");
	printf("---O---OO---OOO--- THE GAME HAS BEEN STARTED ---OOO---OO---O--- \n\n");
	
	for(; score1 < S && score2 < S;){                                  										//Round sayac�
	
		round_counter++;
		printf("\n\n");
		printf("--------------------- ROUND-%d ---------------------\n\n", round_counter);
		
		int random_team_selector = ( rand() % 2 ) + 1;
		int player_selector_1 = rand() % N + 1;
		
		
		if(random_team_selector == 1)                                                         			//Tak�m se�me: 1. tak�m ��karsa
			printf("\tTeam 1 is selected\n\n");
		else	
			printf("\tTeam 2 is selected\n\n");												  			//Tak�m se�me: 2. tak�m ��karsa
			
														
		printf("\tPlayer %d", player_selector_1);							  								//1. rastgele oyuncu se�imi
			
		for(pass_counter = 1; pass_counter < W;){										  				//Pas sayac�
		
			int player_selector_2 = rand() % N + 1;
			captured_team = random_team_selector % 2 + 1;  //Topu �alan tak�m
				
			if( (( rand() % 100 )  + 1) <= P ){																//Pas y�zdesi tutarsa
						

				do																						//Rastgele oyuncu atama
					player_selector_2 = (rand() % N + 1);
				while(player_selector_1 == player_selector_2);				
					player_selector_1 = player_selector_2;
							
				printf(" -> Player %d", player_selector_2 );    
					
				pass_counter++;
					
				if(pass_counter == W){																			//Gerekli pas say�s� sa�lan�p gol at�l�rsa
					if(captured_team % 2 + 1 == 1){																	//1. tak�m gol atarsa
						score1++;
						puts("\n");
						printf("\tSuccess! New score of Team 1 is %d", score1);
					}
					else{																							//2. tak�m gol atarsa
						score2++;
						puts("\n");
						printf("\tSuccess! New score of Team 2 is %d", score2);
					}
				}
				
			}											
			else{																								//Pas y�zdesi tutmazsa, di�er tak�m topu al�r
														
				printf("\n\n");
				if(captured_team == 1)
					printf("\tTeam 1 captured the ball!\n\n");     													//1. tak�m topu �alarsa
				else
					printf("\tTeam 2 captured the ball!\n\n");														//2. tak�m topu �alarsa
			
				pass_counter = 1;
				random_team_selector++;
				printf("\tPlayer %d", player_selector_1);															//Topu �alan tak�m i�in rastgele oyuncu atama
			}
					
		}
		
		if(score1 == S || score2 == S){																		//Skorlardan biri S'ye e�itlernirse 
		
			printf("\n\n\n");
			printf("GAME OVER: Team %d reached the target score (%d) and won the game.", captured_team % 2 + 1, S);   //Oyun sonu yaz�s�
		
		}
		
	}
	
	printf("\n\n");
	
}
