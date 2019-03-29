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
char cApplIndex[10];
int Applicant[20];
unsigned int i, j, k;
int waitTime = 0;

//------------------------------------------------SH. MEM. INT's------------------------------------------------

int segment_id = 0;	//shared memory id
int *status;	//shared memory array


//-------------------------------------SEMAPHORES------------------------------------------

sem_t mutex;			//Status (shared memory) mutex
sem_t mutex_interviewer;	//Interviewer mutex
sem_t applicant; 		//Applicant -> applicant.c
sem_t applicant_queue; 		//Applicant queue

void create(){
	sem_init(&mutex,0,1);		//Mutex -> 1
	sem_init(&mutex_interviewer,0,1);//Mutex -> 1
	sem_init(&applicant,0,0);	//Applicant number -> 0 at start
	sem_init(&applicant_queue,0,0);	//Applicant queue -> 0 at start
}
}

//-------------------------------------RECEPTION FUNC---------------------------------------

void* reception(void *arg){

	//Locate and attach the shared memory once only because, these threads are in the same process.

	//Locate shared memory for applicant status
	if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0) ) < 0 ){		
		printf("Error! Shared memory failure! (hr.c -> reception)\n");
		exit(1);
	}
	//Attach shared memory to receptionist threat
	if( ( status = (int *)shmat(segment_id, 0, 0) ) == (int *) -1 ){
		printf("Error! Shared memory attachment failure! (hr.c -> reception)\n");
		exit(1);
	}

	for(j = 0; j < numOfAppl; j++){/*This loop's purpose is training all applicants. If there is no loop, 
					trainers can train only 4 applicants. Because thread functions finishes
					its job and returns to the end of the pthread_create func.*/
		//Wait any applicant
		sem_wait(&applicant);
		printf("Applicant (pid = %d) applied to receptionist.\n", Applicant[arrIndex]);
		sem_wait(&mutex);
		status[j] = 0;	//change applicant status to zero
		sem_post(&mutex);

		if( arrIndex != numOfAppl )
			++arrIndex;	//increase arrIndex

		//Wait nr seconds
		sleep(nr);

		printf("Applicant (pid = %d) registeration is done.\n", Applicant[arrIndex-1]);
		sem_post(&applicant_queue);
	}

	//Detach shared memory
	shmdt((void *) status);

	printf("Registeration process is done.\n");
	pthread_exit(NULL);
}

//-------------------------------------INTERVIEW FUNC---------------------------------------

void* interview(void *ptr){
	int *num;
	num = (int *) ptr;

	//Unnecessary part -> receptionist already locate and attached the shared memory...	
		
	/*//Locate shared memory for applicant status
	if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0) ) < 0 ){		
		printf("Error! Shared memory failure! (hr.c -> interview)\n");
		exit(1);
	}
	//Attach shared memory to interviewers' threats
	if( (status = (int *)shmat(segment_id, 0, 0) ) == (int *) -1 ){
		printf("Error! Shared memory attachment failure! (hr.c -> interview)\n");
		exit(1);
	}*/

	sem_wait(&mutex_interviewer);
	for( ; k < numOfAppl; ){/*This loop's purpose is training all applicants. If there is no loop, 
				trainers can train only 4 applicants. Because thread functions finishes
				its job and returns to the end of the pthread_create func.*/

		//Wait any applicant
		sem_wait(&applicant_queue);

		printf("Interviewer %d started interview with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);
		if( arr[k][2] == 1 ){		//Accept
			sem_wait(&mutex);
			status[k] = 2;
			sem_post(&mutex);
			sem_post(&appl_go_trainer);//Go trainer
		}
		else if( arr[k][2] == 0 ){	//Reject
			sem_wait(&mutex);
			status[k] = 1;
			sem_post(&mutex);
		}
		waitTime = arr[k][0];		//Read wait time
		sleep(waitTime);
		printf("Interviewer %d finished interview with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);
		k++;
	
	}
	sem_post(&mutex_interviewer);

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

//-------------------------------------------------HR THREADS-------------------------------------------

	pthread_t receptionist;
	pthread_t interviewer[3]; //1->Int 1, 2->Int 2...
	
	//Creating receptionist
	if( pthread_create(&receptionist, NULL, reception, NULL ) ){   //Receptionist
		fprintf(stderr, "pthread_create receptionist failure\n");
		exit(-1);
	}

	//Creating interviewers
	for(i= 0; i < 3; i++){  	//Interviewers
		int *ptrInt;
		ptrInt = &i;
		if( pthread_create(&(interviewer[i]), NULL, interview, (void *)ptrInt) ){
			fprintf(stderr, "pthread_create interviewer %d failure\n", i);
			exit(-1);
		}
	}

	pthread_join( receptionist, NULL );  	//Wait for receptionist
	pthread_join( interviewer[0], NULL ); 	//Wait each other
	pthread_join( interviewer[1], NULL ); 	//Wait each other
	pthread_join( interviewer[2], NULL ); 	//Wait each other

	printf("Interview process is done.\n");

	pthread_exit(NULL);

//----------------------------------------------------------------------------------------------------

	//Destroy semaphores
	sem_destroy(&mutex);
	sem_destroy(&mutex_interviewer);
	sem_destroy(&applicant);
	sem_destroy(&applicant_queue);
	return 0;
}





