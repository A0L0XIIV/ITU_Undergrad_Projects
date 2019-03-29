#include <stdio.h>											//Baran Kaya 150130032
#include <stddef.h>
#include <stdlib.h>
#include <math.h>


typedef struct people {
	int personId;
	double height;
	double weight;
	double BMI;
} person;
	
	
int main(int argc, char* argv[]){
	
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	double threshold = atof(argv[3]);
	//int N, M;
	//double threshold;
	FILE *inputfile, *outputfile;
	int i, j, k, l;
	double hold, hold2, hold3, hold4;
	person pep;
	
	printf("Enter the total number of people: ");
	scanf("%d", &N);
	printf("Enter the number of people whose BMI values are the farthest from the threshold: ");
	scanf("%d", &M);
	printf("Enter the threshold value: ");
	scanf("%lf", &threshold);
	
	int *num;
	num = (int *) malloc (N * sizeof(int));
	
	double *dub, *dub2, *dub3, *dub4;						//ENOUGH SPACE FOR DOUBLE VALUES
	dub = (double *) malloc (N * sizeof(double));
	dub2 = (double *) malloc (N * sizeof(double));
	dub3 = (double *) malloc (N * sizeof(double));
	dub4 = (double *) malloc (N * sizeof(double));
	
	char *str, *str2, *str3;								//ENOUGH SPACE FOR CHAR VALUES (STR -> READING FILE)
	str = (char *)malloc(N * sizeof(char));
	str2 = (char *)malloc(N * sizeof(char));
	str3 = (char *)malloc(N * sizeof(char));
			
	inputfile = fopen("height_weight.txt", "r");			//FILE OPEN
	
	for( i = 0; i < N+1 /*!feof(inputfile)*/; i++ ){
		
		int j=0;
		fscanf(inputfile, "%s %s %s", str, str2, str3);		//READING FILE
		//printf("\n %4s %4s %4s", str, str2, str3);
														
		pep.personId = atoi(str);							//ASSIGNING FILE VALUES TO STRUCT
		pep.height = atof(str2);
		pep.weight = atof(str3);
		pep.BMI = pep.weight / pow(pep.height/100,2);
		
		
		*(num + i) = pep.personId;
		*(dub + i) = pep.height;
		*(dub2 + i) = pep.weight;
		*(dub3 + i) = pep.BMI;
		*(dub4 + i) = fabs( threshold - *(dub3 + i) );

		//printf(" %5d  %4.3f  %4.3f  %4.3f", pep.personId, pep.height, pep.weight, pep.BMI, dub4[i]);		

	}
	

	
	for( i = 1; i < N+1; i++ ){

		//printf("\n%d %.3f %.3f %.3f", *(num+i), *(dub+i), *(dub2+i), *(dub3+i));
		
		for( j = 0; j < N - i + 1; j++ ){				//BUBBLE SORT BY THRESHOLD-IBM VALUES
			if( *(dub4+j) > *(dub4+j+1) ){
				
				hold4 = *(dub4+j);						//SORTING THE THRESHOLD-IBM VALUES
				*(dub4+j) = *(dub4+j+1);
				*(dub4+j+1) = hold4;
				
				hold3 = *(dub3+j);						//SORTING THE IBM VALUES
				*(dub3+j) = *(dub3+j+1);
				*(dub3+j+1) = hold3;
				
				hold2 = dub2[j];						//SORTING THE WEIGHT VALUES
				dub2[j] = dub2[j+1];
				dub2[j+1] = hold2;
				
				hold = dub[j];							//SORTING THE HEIGHT VALUES
				dub[j] = dub[j+1];
				dub[j+1] = hold;
				
				l = num[j];								//SORTING THE PERSON ID'S
				num[j] = num[j+1];
				num[j+1] = l;
			}
		}
		//printf("\t\t%d %.3f %.3f %.3f %.3f", *(num+i), *(dub+i), *(dub2+i), *(dub3+i), *(dub4+i));
		
		
	}
	for( i = 1; i < N+1; i++ ){							//BUBBLE SORT BY THRESHOLD-IBM VALUES
		for( j = 0; j < N - i; j++){
			if(dub4[j] > dub4[j+1]){
				
				hold4 = *(dub4+j);						//SORTING THE THRESHOLD-IBM VALUES
				*(dub4+j) = *(dub4+j+1);
				*(dub4+j+1) = hold4;
				
				hold3 = dub3[j];						//SORTING THE IBM VALUES
				dub3[j] = dub3[j+1];
				dub3[j+1] = hold3;
				
				hold2 = dub2[j];						//SORTING THE WEIGHT VALUES
				dub2[j] = dub2[j+1];
				dub2[j+1] = hold2;
				
				hold = dub[j];							//SORTING THE HEIGHT VALUES
				dub[j] = dub[j+1];
				dub[j+1] = hold;
				
				l = num[j];								//SORTING THE PERSON ID'S
				num[j] = num[j+1];
				num[j+1] = l;
			}
		}
		//printf("\n--%d %.3f %.3f %.3f %.3f", *(num+i), *(dub+i), *(dub2+i), *(dub3+i), *(dub4+i));
	}
	
	for(i = N; i > N-M; i-- ){							//PRINTING #M VALUES
	
		printf("\n%5d %8.3f %8.3f %8.3f %8.3f", *(num+i), *(dub+i), *(dub2+i), *(dub3+i), *(dub4+i));
		
	}
	
	fclose(inputfile);								//INPUT FILE CLOSE
	
	
	outputfile = fopen("output.txt", "w");			//OUTPUT FILE OPEN
	
	for(i = N; i > N-M; i-- ){							//PRINTING #M VALUES IN THE OUTPUT FILE
	
		fprintf(outputfile, "%5d %8.1f %8.1f %8.3f %8.3f\n", *(num+i), *(dub+i), *(dub2+i), *(dub3+i), *(dub4+i));
	
	}
	fclose(outputfile);								//OUTPUT FILE CLOSE
	
}

