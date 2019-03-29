#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define PI 3.14159265

int main (){
	char option, c;
	int n, m, i;
	float f, g;
	static float z = 0, memoryValue = 0;
	int a, b;
	char u[50];

	long factorial (int n);
	float absolute(float n);
	float power(float n, float m);
	long long int exponent(long long int n);
	double cosine(double n);
	double sine(double n);
	float degree(float f);
	float clean(float f);
	float memory(float z);
	
	
    printf("\n\t ---------------------------------- ");
    printf("\n\t|               MENU               |");
    printf("\n\t|                                  |");
    printf("\n\t|      + --> ADD                   |");
	printf("\n\t|      - --> SUBTRACT              |");
    printf("\n\t|      * --> MULTIPLY              |");
	printf("\n\t|      / --> DIVIDE                |");
	printf("\n\t|      %% --> MODULUS               |");
	printf("\n\t|      F --> FACTORÝAL             |");
	printf("\n\t|      S --> SINE                  |");
	printf("\n\t|      N --> COSINE                |");
	printf("\n\t|      T --> TANGENT               |");
	printf("\n\t|      E --> EXPONENT              |");
	printf("\n\t|      W --> POWER                 |");
	printf("\n\t|      A --> ABSOLUTE              |");
	printf("\n\t|      P --> PI                    |");
	printf("\n\t|      M --> MEMORY                |");
	printf("\n\t|      R--> MEMORY RETURN          |");    
	printf("\n\t|      L--> MEMORY CLEAN           |"); 
	printf("\n\t|      C --> CLEAN                 |");              
	printf("\n\t|      Q --> QUIT                  |");
	printf("\n\t|                                  |");
	printf("\n\t ---------------------------------- ");
    

	//ilk girilen deðer sayý olana kadar döngü içinde çalýþýr bu böyle biþey denedim ama istersen kullanýrsýn
	/*do{
		printf("\nEnter user input: ");
		scanf("%s", &u);
	} while(!(isdigit(u[0])!=0 || u[0] == '-')) ;*/
	
	printf("\nEnter user input: ");
		scanf("%s", &u);
	if(isdigit(u[0])!=0 || u[0] == '-'){
		z = atof(u);	
	}
	else {
		printf("Please start here.\n\n");
	}
		

	for(option ;option != 'Q';){
	     	
		printf("\nEnter user input: ");
		scanf ("%s", &option);
	
		if(option == '+' || option == '-' || option == '*' || option == '/' || option == 'F' || option == 'S' || option == 'N' || option == 'C' || option == 'L'
		|| option == 'T' || option == 'E' || option == 'W' || option == 'A' || option == 'P' || option == '%' || option == 'Q' || option == 'R' || option == 'M'){
		
			switch (option) {
				
				 case '+'://ADD
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								double a = atof(u);
								z = z + a;
							}
							else
								printf("Invalid input for the operator (+).\nPlease enter any number after the (+) operator.\n");
							break;
				
				 case '-': // SUBTRACT
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								double a = atof(u);
								z = z - a;
							}
							else
								printf("Invalid input for the operator (-).\nPlease enter any number after the (-) operator.\n");
							break;

				 case '*': // MULTIPLY
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								double a = atof(u);
								z = z * a;
							}
							else
								printf("Invalid input for the operator (*).\nPlease enter any number after the (*) operator.\n");
							break;
				
				 case '/': // DIVIDE
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								double a = atof(u);
								if (a == 0){
									printf("\nError: division by zero!\n");
									printf("Please try again...\n");
									continue;	             
								} 
								else 
									z = z / a;
							}
							else
								printf("Invalid input for the operator (/).\nPlease enter any number after the (/) operator.\n");						
							break;

				case '%': //MODULUS
							b = z;
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								if (a == 0){
									printf("\nError: division by zero!\n");
									printf("Please try again...\n");
									continue;									
								}
								else
									z = b % a;
							}
							else
								printf("Invalid input for the operator (%%).\nPlease enter any number after the (%%) operator.\n");								
							break;
				         
				case 'F': //FACTORIAL
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = factorial (a);
							}
							else
								printf("Invalid input for the operator (F).\nPlease enter any number after the (F) operator.\n");	
							break;
							 
				case 'S': //SINE
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = sine(degree(a));
							}
							else
								printf("Invalid input for the operator (S).\nPlease enter any number after the (S) operator.\n");	
							break;
							 
				case 'N': //COSINE
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = cosine(degree(a));
							}
							else
								printf("Invalid input for the operator (N).\nPlease enter any number after the (N) operator.\n");
							break;
							 
				case 'T': //TANGENT
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								if(a == 90 || a == 270){
									printf("Infinite..\n");
									continue;
								}
								else
									z = sine (degree(a) ) / cosine( degree(a) );
							}
							else
								printf("Invalid input for the operator (T).\nPlease enter any number after the (T) operator.\n");							
							break;
							 
				case 'E': //EXPONENT
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = z * exponent(a);
							}
							else
								printf("Invalid input for the operator (E).\nPlease enter any number after the (E) operator.\n");
							break;
							 
				case 'W': //POWER
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = power(z, a);
							}
							else
								printf("Invalid input for the operator (W).\nPlease enter any number after the (W) operator.\n");							
							break;
							 
				case 'A': //ABSOLUTE
							printf("Enter user input: ");
							scanf("%s", &u);
							if(isdigit(u[0])!=0 || u[0] == '-'){
								int a = atof(u);
								z = absolute(a);
							}
							else
								printf("Invalid input for the operator (A).\nPlease enter any number after the (A) operator.\n");
							break;
							
				case 'P': //PI
							printf("PI =  ");
							z = PI;
							break;
				
				case 'L':   //MEMORY CLEAN
							memoryValue = 0;
							printf("Memory Cleaned\n");
							continue;
							
				case 'R': //MEMORY RETURN
							//memoryValue = memory(z);
							printf("%6.3f\n", memoryValue);
							continue;
							//break;
							
				case 'M':  //MEMORY
							memoryValue = memory(z);
							printf("%6.3f  stored to memory\n",memoryValue);
							continue;
				
				case 'C':   //CLEAN
							z = clean(f);
							break;
							
				case 'Q': //QUIT
							printf("QUIT..");
							return 0;
							break;

				default: 
						continue;
						return 0;
	
			} // switch 
			
			printf("%6.3f\n", z);
		
		}
		else{
			printf("\nInvalid character. Choose from the operators below:\n\n");
			printf("-------------------------------------------------------------------------\n");
			printf("add (+), subtract (-), divide(/), multiply(*), modulus (%%), absolute (A)\n");
			printf("power (W), factorial (F), sine (S), cosine (N), tangent (T), exponent (E)\n");
 			printf("PI (P), Memory (M), Clear (C), Memory Clear (L), Memory Return (R)\n");
 			printf("Quit (Q)\n");
 			printf("-------------------------------------------------------------------------\n");
 		}
	} // for

return 0;
}	// main


long factorial (int n){        //factorial funciton
	if (n >= 0){
		long f = 1;
	
		for (; n >= 1; n--) f *= n;
	
		return f;
	}
	else{
		printf("Invalid value! Only positive integers.\n");
		return 0;
	}
}    //factorial funciton end


float absolute(float n){     //absolute function
	if(n >= 0)
		return n;
	else 
		return n*-1;
}    //absolute function end


float power(float n, float m){    //power function
	long long int a = 1;
	for(;m != 0; --m)
		a *= n;
	return a;
}   //power function end


long long int exponent(long long int n){    //exponent function
	long long int a = 1;
	for(;n != 0; --n)
		a *= 10;
	return a;
}   //exponent function end


float degree(float f){    //radius to degree function
	float a;
	if(f <= 360){
		a = f*PI/180;
		return a;
		}
	else{
		int b; 
		b = f / 360;
		a = (f-360*b)*PI/180;
		return a;
		}
	
}                        //radius to degree function end


double sine(double n){     //sine function
	double j = 1, i, a = 0, factorial = 1, b = n;
	for(i = 1; i < 50; i += 2){
		if(i > 1.0){
			j = j * -1;
			factorial = factorial * i * (i-1);
			b *= n * n;
		}
		a += j * b / factorial;
	}
	return a;
}    //sine function end


double cosine(double n){    //cosine funciton
	double j = 1, i, a = 1, factorial = 1, b = 1.0;
	for(i = 2; i < 50; i += 2){
			j = j * -1;
			factorial = factorial * i * (i-1);
			b *= n * n;
		
		a += j * b / factorial;
	}
	return a;
}    //cosine funciton end


float clean(float f){    //clean function
	f = 0;
	return f;
}   //clean function end


float memory(float z){   //memory function
	static float a;
	a = z;
	float *pa = &a;
	return *pa;
}   //memory function end
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
