#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
typedef struct{
	int capacity;
	int size;
	int front;
	int end;
	void **elements;
}Queue;*/

//void add(int);
//int remove(void);

int Queue[100];
int front = -1;
int rear = -1;

int ha;
int hb;
int space = 0;
int nr = 0;
int arr[100];
int arrIndex = 0;
int numOfAppl = 0;
int isSleep[50];


int main( int argc, char **argv ){

//-----------------------------------------------READING INPUTS---------------------------------------

	FILE  *inF = fopen(argv[1], "r");
	char c[100];
	fread(c, 100, 1, inF);

	char temp[10];
	int i = 0, j = 0, k = 0;
	int endOfStr = 0;
	for(i = 0; i < 100; i++){
		if(c[i] == '\n' || endOfStr == 1){
			if(endOfStr==1)
				++endOfStr;
			if(space == 0){
				nr = atoi(temp);
				printf("nr = %d\n",nr); 
			}
			else{
				arr[k++] = atoi(temp);
				if(k%4 == 0)
					printf("Applicant %d  (wait times= %d, %d), (Bools = %d %d)\n", k%4, arr[k-4], arr[k-3], arr[k-2], arr[k-1]);			
			}
			for(j=0;j<10;j++)
				temp[j]='\0';
			j = 0;
		}

		else if(c[i] == '\0')
			++endOfStr;

		else if(c[i]==' '){
			space = 1;
			arr[k++] = atoi(temp);
		}

		else{
			ha = (int) (c[i] - '0');printf("ha = %d\t",ha);
			hb = atoi(&c[i]);printf("hb = %d\t",hb);
			if(isdigit(hb))printf("OK\n");
			printf("Before j = %d\t", j);
			temp[j++] = c[i];
			printf("temp[%d] = %d, temp[%d] = %d\n",j,temp[j], j-1, temp[j-1]);	
		}		
	}
	numOfAppl = sizeof(arr);



	return 0;
}

/*void add(int number){
	if(rear == 100-1)
	printf("Error, queue is full!\n");
	else{
		if(front == -1)
			front = 0;
		rear += 1;
		Queue[rear] = number;
	}
	return;
}

int remove() {
	if(front == -1 || front > rear){
		//printf("Error! (queue) \n");
		//return -1;
		throw "ERROR!";
	}
	else{
		return Queue[front];
		front += 1;
	}
}*/





