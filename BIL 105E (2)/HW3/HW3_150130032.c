#include <stdio.h>																		//150130032 Baran Kaya
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 81


int user_menu(void);
void emptyccs(void);
int set_ccs(char **ccs);
char *sub_string (char *ccs, int begin_index, int end_index);
char *remove_string(char **ccs, int begin_index, int end_index);
int insert_string(char **ccs, char *insert, int begin_index);
int replace_string(char **ccs, char *find, char *replace);



int main(){

	char ccs[ SIZE ] = { 0 };
	int begin_index, end_index;
	int i;
	char insert[ SIZE ];
	char find[ SIZE ];
	char replace[ SIZE ];
	
	
	do{
	
		switch (user_menu()){
		
		
			case 0:	printf("Good bye\n");  
					return 0;
					break;
			
			
			case 1: printf("Enter CCS:");
					set_ccs(&ccs);
					break;
			
					
			case 2: if(ccs[0] == NULL)
						emptyccs();
					else{
						printf("Enter the BEGIN INDEX and END INDEX numbers:");
						scanf("%d%d", &begin_index, &end_index);
						sub_string(ccs, begin_index, end_index);
					}					
					break;
					
					
			case 3: if(ccs[0] == NULL)
						emptyccs();
					else{
						printf("Enter the BEGIN INDEX and END INDEX numbers:");
						scanf("%d%d", &begin_index, &end_index);
						remove_string(&ccs, begin_index, end_index);
					}
					break;
			
					
			case 4: if(ccs[0] == NULL)
						emptyccs();
					else{
						printf("Enter a new string for insertion:\n");
						fflush(stdin);
						fgets(insert,80,stdin);
						strtok(insert,"\n");
						printf("Enter the BEGIN INDEX number where the new string begins:");
						scanf("%d", &begin_index);
						insert_string(&ccs, insert, begin_index);
					}
					break;
			
					
			case 5: if(ccs[0] == NULL)
						emptyccs();
					else{
						printf("Find what:\n");
						fflush(stdin);
						fgets(find,80,stdin);
						strtok(find,"\n");
						printf("Replace with:");
						fflush(stdin);
						fgets(replace,80,stdin);
						strtok(replace,"\n");
						replace_string(&ccs, find, replace);
					}
					break;						
			
			
			default:	printf("Invalid selection, please try again.\n\n");
						break;	
		}
		
		
	}while(1);
	
}



int user_menu(void){																					//MENU FONKSIYONU
	
	printf("\t\t --------------------------------------\n");
	printf("\t\t | 0: Exit the program                |\n");
	printf("\t\t | 1: Set Current Character Sequence  |\n");
	printf("\t\t | 2: Get Substring                   |\n");
	printf("\t\t | 3: Remove Substring                |\n");
	printf("\t\t | 4: Insert                          |\n");
	printf("\t\t | 5: Replace                         |\n");
	printf("\t\t --------------------------------------\n\n");
	
	int selection;
	
	scanf("%d", &selection);
	
	switch(selection){

	case 0: return 0;
			break;
			
	case 1: return 1;
			break;
			
	case 2: return 2;
			break;
	
	case 3: return 3;
			break;
	
	case 4: return 4;
			break;
	
	case 5: return 5;
			break;
	}
}



void emptyccs(void){																					//CCS BOSKEN 1 HARICI BASKA FONK CAGRILIRSA
	printf("You have to set Current Character Sequence (CCS) before doing any operations!\n\n");
}



int set_ccs(char **ccs){																				//SET_CCS FONK
	
	char ccsorg[ SIZE ];
	char *pointer;
	fflush(stdin);
	fgets(ccsorg, 80, stdin);
	pointer = (char*)malloc(strlen(ccsorg) * sizeof(char));
	pointer = (char*)malloc(strlen(ccs) * sizeof(char));
	strcpy(pointer, ccsorg);
	strcpy(ccs, pointer);
	if(pointer==NULL){
		puts("Memory error.");
		return -1;
	}
	printf("CCS: %s", ccs);
	printf("\n\n");

}



char *sub_string (char *ccs, int begin_index, int end_index){											//SUB_STRING FONK
	
	if(begin_index < 0 || end_index > strlen(ccs)-1){
		puts("Inappropriate begin index or end index.");
		return NULL;
	}
	else{
		int i,j = 0;
		char *sub_string;
		char *subpointer; 
		sub_string = (char*)malloc(strlen(ccs));
		subpointer = (char*)malloc(end_index - begin_index + 1);	
		strcpy(sub_string, ccs);
		for( i = begin_index; i <= end_index; i++ ){
			*(subpointer + j) = *(sub_string + i);
			j++;
		}
		puts("");
		printf("\"CCS\":  %s",ccs);
		printf("Substring(%d)(%d):  ", begin_index, end_index);	
		for( i = 0; i <= strlen(subpointer); i++ ){
			printf("%c", *(subpointer + i) );
		}
		puts("");
		return subpointer;
			
	}
	
}



char *remove_string(char **ccs, int begin_index, int end_index){										//REMOVE_STRING FONK
	
	if(begin_index < 0 || end_index > strlen(ccs)-1){
		puts("Inappropriate begin index or end index.");
		return NULL;
	}
	else{
		int i, j = 0;
		char *removepointer;
		char *remove_string;
		remove_string = (char*)malloc(strlen(ccs));	
		removepointer = (char*)malloc(strlen(ccs) - (end_index - begin_index + 1));	
		strcpy(remove_string, ccs);
		for(i=0; i<=strlen(ccs); i++){
		
			*(removepointer + j) = *(remove_string + i);
			if( i < begin_index || i > end_index){
				j++;			
			}		
		
		}
		
		puts("");
		strcpy(ccs,removepointer);
		printf("CCS: %s",ccs);
		return ccs;
	}
}



int insert_string(char **ccs, char *insert, int begin_index){											//INSERT_STRING FONK
	
	if(begin_index < 0){
		puts("Inappropriate begin index.");
		return NULL;
	}
	else{
		int i, j = 0, k = 0;
		char *insertpointer;
		char *insert_string;
		insert_string = (char*)malloc(strlen(ccs));	
		insertpointer = (char*)malloc(strlen(ccs) + strlen(insert) - 1);
		
		if(insertpointer==NULL){
			puts("Memory error.");
			return -1;
		}	
		
		strcpy(insert_string, ccs);
		for(i=0; i<=( strlen(ccs) + strlen(insert) - 2 ); i++){
			
			if( i != begin_index /*&& *(insert_string + j) != '\0'*/) {
				*(insertpointer + i) = *(insert_string + j);
				if( j != strlen(insert_string)-2)
					j++;	
		
			}else{
				while( k < strlen(insert) ){
					*(insertpointer + i) = *(insert + k);
					k++;
					i++;
				}	
			}		
				
		}
			
		puts("");
		strncpy(ccs,insertpointer, ( strlen(insert_string) + strlen(insert) - 1));
		printf("%s",ccs);

		
	}
	
}



int replace_string(char **ccs, char *find, char *replace){													//REPLACE STRING FONK
	
		int i, j = 0, k = 0;
		int begin = -1;
		char *replacepointer;
		char *replace_string;
		replace_string = (char*)malloc(strlen(ccs));	
		replacepointer = (char*)malloc(strlen(ccs) + strlen(replace) - strlen(find) - 1);	
		
		if(replacepointer==NULL){
			puts("Memory error.");
			return -1;
		}
						
		strcpy(replace_string, ccs);
		
		for(i=0; i < (strlen(ccs) - 1); i++){		//kaçýncý elemandan baþladýðýný (begin) bulmak için
		
			if( strlen(find) <= 1){
				if( *(replace_string + i) == *find ){
					begin = i;
				}
			}
			else{
				if( *(replace_string + i) == *find && *(replace_string + i + 1) == *(find + 1) ){
					begin = i;		
				}
			}
			
		}
		
		if(begin != -1){
			
			for(i=0; i<=strlen(ccs); i++){				//find stringini çýkarmak için
			
				*(replacepointer + j) = *(replace_string + i);
				if( i < begin || i > begin + strlen(find) - 1 ){
					j++;			
				}		
			
			}
			
			j=0,k=0;
			for(i=0; i<( strlen(replacepointer) + strlen(replace) - 1 ); i++){			//replace yerine yerleþtirmek için
				
				if( i != begin){
					*(replacepointer + i) = *(replace_string + j);
					j++;														
				}
				else{
					while( k < strlen(replace) ){
						*(replacepointer + i) = *(replace + k);
						k++;
						i++;
					}
					i--;
					j += strlen(find);
				}
				
			}
			strcpy(ccs,replacepointer);
			printf("CCS: %s",ccs);
			return replacepointer;
			
		}
		else{
			puts("There is not a -find- string in this ccs, please try again.");
			return -1;
		}	
		
}





















































