#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void printResult(int result[],int size );			//Definition of print function


int main(){
	
    int array[300]; 								//Definitions
	int N, number, size, hold;
	int i, j, a;
	int x;

		printf("               ************************************************** \n");
		printf("              ***                                              ***\n");
		printf("             ***      Welcome to the Factorial Calculator!      ***\n");
		printf("              ***                                              ***\n");
		printf("               ************************************************** \n\n");
		printf(" -> Enter N: ");						//Selecting N
       	scanf("%d", &number);
		/*printf("Start from (N-x)!: ");            //You can choose x
       	scanf("%d", &x);*/
       	x = 2;
       	printf("\n");
       	
		for( N = number-x; N <= number; N++ ){		//(N-2)!, (N-1)! and N! loop

			array[0] = 1;  							
			size = 1;    			
			hold = 0;
			 
			for( i = 1; i <= N; i++ ){				//factorial calculations
				
			    for( j = 0; j < size; j++ ){
			    	
			       a = array[j] * i + hold; 
			       array[j] = a % 10;
			       hold = a / 10;
				    
			    }
			    
			     for( ;hold > 0; size++ ){
				  
			       array[size] = hold % 10;
			       hold = hold / 10;
			       			    
			     }
			     
			}
			
			printf(" -> %d! = ", N);					//printing N! =
	
				if( N == number-2 )					//based on the right
					printf("  ");
				
				if( N == number-1 )
					printf(" ");
		
			printResult( array, size );			//printing result of factorial
			
		}
			printf("\n\n		  >------------------------------------------<\n");
			printf("		  |           Thank You & Good Bye           |\n");
			printf("		  >------------------------------------------<\n");
      	
    return 0;	
}													//end of main


void printResult( int result[], int size ) {		//print function

	int index = size - 1;
	
	for (; index >= 0; index-- ){					//calculations of array
    	
    	if( ( (index + 1) % 3 ) == 0 && (index != size - 1) ){
    		
    		printf(",");
		}
		
    	printf("%d",result[index]);					//result
    	
	}
	if( size <= 55 )								//if result is too big, it will add newlines
		printf("\n");
		
	else
		printf("\n\n");  
}
