#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

int nr = 0;
int arr[50];
int arrIndex = 0;
int numOfAppl = 0;
int isSleep[50];

void interview(void *ptr){
	int *i;
	i = (int *)ptr;
	arrIndex = *i;
	printf("Interviewer %d started interview with Applicant %d\n", *İ, arrIndex);
	int waitTime = arr[arrIndex];
	sleep(waitTime);
	printf("Interviewer %d finished interview with Applicant %d\n", *i, arrIndex);
	pthread_exit(NULL);
}

void reception(void *arg){
	int waitTime = nr;
	int i;
	for(i = 0; i<numOfAppl; İ++){
		sleep(waitTime);
		printf("Applicant %d's registeration is done\n", arrIndex);
	}
	pthread_exit(NULL);
}

int main( int argc, char **argv ){

//-----------------------------------------------READING INPUTS---------------------------------------

	FILE  *inF = fopen(argv[1], "r");
	char c[100];
	nr = atoi(argv[2]);
	fread(c, 100, 1, inF);
	
	printf("nr = %d\n",nr);
	int b;

	char temp[4];
	int i = 0, j = 0, k = 0;
	int endOfStr = 0;
	for(i = 0; i < 100; i++){
		if(c[i] == '\n' || endOfStr == 1){
			if(endOfStr==1)
				++endOfStr;
			j = 0;
			arr[k++] = atoi(temp);
			printf("Applicant %d applied to the receptionist (wait time = %d)\n", i, arr[k-1]);			
		}
		else if(c[i] == '\0')
			++endOfStr;
		else
			temp[j++] = c[i];			
	}
	numOfAppl = sizeof(arr);

//------------------------------------------PROCESS&THREAD---------------------------------------------------

	/*pthread_t rec, iv1, iv2, iv3;
	if(pthread_create(&rec, NULL, func, (void*) smt) ) {
		fprintf(stderr, "pthread_create receptionist failure\n");
		exit(-1);
	}
	if(pthread_create(&iv1, NULL, func, (void*) smt) ) {
		fprintf(stderr, "pthread_create interviewer 1 failure\n");
		exit(-1);
	}
	if(pthread_create(&iv2, NULL, func, (void*) smt) ) {
		fprintf(stderr, "pthread_create interviewer 2 failure\n");
		exit(-1);
	}
	if(pthread_create(&iv3, NULL, func, (void*) smt) ) {
		fprintf(stderr, "pthread_create interviewer 3 failure\n");
		exit(-1);
	}*/

//---------OR--------
	
	pthread_t th[4]; //0->Recept., 1->Int 1, 2->Int 2...

	if( pthread_create(&(th[0]), NULL, reception, NULL) ){   //Receptionist
		fprintf(stderr, "pthread_create receptionist failure\n");
		exit(-1);
	}	

	for(i= 1; i < 4; i++){  	//Interviewers
		int *ptrInt;
		ptrInt = &i;
		if( pthread_create(&(th[i]), NULL, interview, (void *)ptrInt) ){
			fprintf(stderr, "pthread_create %d failure\n", i);
			exit(-1);
		}
	}

	pthread_join( th[0], NULL );  //Wait for receptionist

	pthread_exit(NULL);

	printf("All applicants have interviewed succesfully.\n");

	return 0;
}






