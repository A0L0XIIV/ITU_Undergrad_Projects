/*----------------*\
|	Baran	   |
|	KAYA	   |
|     150130032	   |
\*----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>
#include <semaphore.h>

#define KEYSHM 15951


unsigned int space = 0;
unsigned int nr = 0;
int arr[10][4];
unsigned int arrIndex = 0;
unsigned int numOfAppl = 0;
unsigned int applIndex = 0;
int Applicant[20];
unsigned int i, j, k;
int waitTime = 0;

//------------------------------------------------SH. MEM. INT's------------------------------------------------

int segment_id = 0;	//shared memory id
int *status;		//shared memory array


//-------------------------------------SEMAPHORES------------------------------------------

sem_t mutex;		//Status (shared memory) mutex
sem_t mutex_trainer;	//Trainer mutex
sem_t applicant; 	//Applicant queue

void create(){
	sem_init(&mutex,0,1);		//Mutex -> 1
	sem_init(&mutex_trainer,0,1);	//Mutex -> 1
	sem_init(&applicant,0,0);	//Applicant number -> 0 at start
}

//-------------------------------------TRAIN FUNC---------------------------------------

void* train(void *ptr){
	int *num;
	num = (int *) ptr;

	//Locate shared memory for applicant status
	if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0) ) < 0 ){		
		printf("Error! Shared memory failure! (trial.c -> train func.)\n");
		exit(1);
	}
	//Attach shared memory to trainers' threats
	if( (status = (int *)shmat(segment_id, 0, 0) ) == (int *) -1 ){
		printf("Error! Shared memory attachment failure! (trial.c -> train func.)\n");
		exit(1);
	}

	sem_wait(&mutex_trainer);
	for( ; k < numOfAppl; ){/*This loop's purpose is training all applicants. If there is no loop, 
				trainers can train only 4 applicants. Because thread functions finishes
				its job and returns to the end of the pthread_create func.*/
		//Wait for applicant
		sem_wait(&applicant);

		printf("Trainer %d started training with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);
		if( arr[k][3] == 1 ){		//Accept
			sem_wait(&mutex);
			status[k] = 4;
			sem_post(&mutex);
		}
		else if( arr[k][3] == 0 ){	//Reject
			sem_wait(&mutex);
			status[k] = 3;
			sem_post(&mutex);
		}
		waitTime = arr[k][1];		//Read wait time
		sleep(waitTime);
		printf("Trainer %d finished training with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);

		k++;//Every trainer increase the k value for taking the corrcet arr[k][x] value.
	
	}
	sem_post(&mutex_trainer);

	//Detaching shared memory
	shmdt((void *) status);
}

//-------------------------------------MAIN---------------------------------------

int main( int argc, char **argv ){

	create(); //Create semaphores

//-----------------------------------------------READING INPUTS---------------------------------------

	FILE *inF = fopen(argv[1], "r");
	//FILE *inF = fopen("input.txt", "r");
	char c[100];
	fread(c, 100, 1, inF);

	char temp[10];
	int i = 0, j = 0, k = 0, m = 0;
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
				arr[m][k++] = atoi(temp);
				if(k%4 == 0){
					printf("Applicant %d, m = %d, k = %d  (wait times= %d, %d), (Bools = %d %d)\n", k/4, m, k, arr[m][k-4], arr[m][k-3], arr[m][k-2], arr[m][k-1]);
					m++;
					k = 0;
				}			
			}
			for(j=0;j<10;j++)
				temp[j]='\0';
			j = 0;
		}

		else if(c[i] == '\0')
			++endOfStr;

		else if(c[i]==' '){
			space = 1;
			arr[m][k++] = atoi(temp);
			for(j=0;j<10;j++)
				temp[j]='\0';
			j = 0;
		}

		else
			temp[j++] = c[i];	
		
	}
	numOfAppl = m;
	printf("Applicant number = %d\n\n", numOfAppl);

//-------------------------------------------------TRAINER THREADS-------------------------------------------

	pthread_t trainer[4]; //4 trainers

	//Creating trainers
	for(i= 0; i < 4; i++){  	
		int *ptrInt;
		ptrInt = &i;
		if( pthread_create(&(trainer[i]), NULL, train, (void *)ptrInt) ){
			fprintf(stderr, "pthread_create trainer %d failure\n", i);
			exit(-1);
		}
	}

	pthread_join( trainer[0], NULL ); 	//Wait each other
	pthread_join( trainer[1], NULL ); 	//Wait each other
	pthread_join( trainer[2], NULL ); 	//Wait each other
	pthread_join( trainer[3], NULL );  	//Wait each other

	printf("Training process is done.\n");

	pthread_exit(NULL);

//----------------------------------------------------------------------------------------------------

	//Destroy semaphores
	sem_destroy(&mutex);
	sem_destroy(&mutex_trainer);
	sem_destroy(&applicant);
	return 0;
}





