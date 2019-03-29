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
int f = 1;
unsigned int i, j, k, l, m, n;
unsigned int waitTime_i = 0;
unsigned int waitTime_t = 0;

//-------------------------------------SHARED MEMORY---------------------------------------

int segment_id = 0;	//shared memory id
int *status; 		//status[numOfAppl]; //shared memory array (status for each appl.)

//-------------------------------------SEMAPHORES------------------------------------------

sem_t mutex;	//Status (shared memory) mutex
sem_t mutex_interviewer;
sem_t mutex_trainer;
sem_t applicant; //Applicant queue
sem_t appl_go_trainer;
sem_t appl_go_interviewer;

void create(){
	sem_init(&mutex,0,1);			//Mutex -> 1
	sem_init(&mutex_interviewer,0,1);	//Mutex -> 1
	sem_init(&mutex_trainer,0,1);		//Mutex -> 1
	sem_init(&applicant,0,0);		//Applicant number -> 0 at start
	sem_init(&appl_go_trainer,0,0);
	sem_init(&appl_go_interviewer,0,0);
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
		status[j] = 0;//change applicant status to zero
		sem_post(&mutex);	
		if( arrIndex != numOfAppl )
			++arrIndex;	//increase arrIndex
		

		//Wait nr seconds
		sleep(nr);

		if(Applicant[arrIndex-1] != 0)
			printf("Applicant (pid = %d) registeration is done.\n", Applicant[arrIndex-1]);
		sem_post(&appl_go_interviewer);
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

	//Locate shared memory for applicant status
	if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0) ) < 0 ){		
		printf("Error! Shared memory failure! (hr.c -> interview)\n");
		exit(1);
	}
	//Attach shared memory to interviewers' threats
	if( (status = (int *)shmat(segment_id, 0, 0) ) == (int *) -1 ){
		printf("Error! Shared memory attachment failure! (hr.c -> interview)\n");
		exit(1);
	}
	sem_wait(&mutex_interviewer);

	for( ; k < numOfAppl; ){/*This loop's purpose is training all applicants. If there is no loop, 
				trainers can train only 4 applicants. Because thread functions finishes
				its job and returns to the end of the pthread_create func.*/

		//Wait any applicant
		sem_wait(&appl_go_interviewer);

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
		waitTime_i = arr[k][0];	//Read wait time
		sleep(waitTime_i);
		printf("Interviewer %d finished interview with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);
		k++;

		//Int applIndex -> *char cApplIndex for sending with exec function
		snprintf(cApplIndex, sizeof(cApplIndex), "%d", applIndex);
		//Exec -> calling Trial program for training
		execl("./trial", cApplIndex, (char *)NULL);

		
	}
	sem_post(&mutex_interviewer);

	//Detaching shared memory
	shmdt((void *) status);	
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
	for( ; m < numOfAppl; ){/*This loop's purpose is training all applicants. If there is no loop, 
				trainers can train only 4 applicants. Because thread functions finishes
				its job and returns to the end of the pthread_create func.*/
		//Wait for applicant
		sem_wait(&appl_go_trainer);

		printf("Trainer %d started training with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);
		if( arr[m][3] == 1 ){		//Accept
			sem_wait(&mutex);
			status[m] = 4;
			sem_post(&mutex);
		}
		else if( arr[m][3] == 0 ){	//Reject
			sem_wait(&mutex);
			status[m] = 3;
			sem_post(&mutex);
		}
		waitTime_t = arr[m][1];		//Read wait time
		sleep(waitTime_t);
		printf("Trainer %d finished training with Applicant %d (status of applicant %d: %d)\n",*num, k, k, status[k]);

		k++;//Every trainer increase the k value for taking the corrcet arr[k][x] value.

	}
	sem_post(&mutex_trainer);

	//Detaching shared memory
	shmdt((void *) status);
}

//-------------------------------------MAIN---------------------------------------

int main( int argc, char **argv ){

numOfAppl = atoi( argv[2] );	//Taking number of applicants

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


//------------------------------------------------CREATING SHARED MEMORY------------------------------------------------

	//Creating shared memory for evey child -> number of shared memory (int size) -> num. of applicants

	if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0700|IPC_CREAT) ) < 0 ){		
		printf("Error! Shared memory failure! (applicant.c)\n");
		exit(1);
	}

//-------------------------------------------------APPLICANT FORK-------------------------------------------

	for(i=0; i<numOfAppl; i++){	//Creating applicants(Process)
		if(f>0)
			f=fork();
		if(f==-1){
			printf("Applicant fork error!\n");
			exit(1);
		}
		if(f==0)
			break;
		else{
			Applicant[i] = f;
			printf("Applicant %d's pid = %d\n", i+1, f);
		}	
	}

//-------------------------------------------------CHILD PROCESS-------------------------------------------

	if(f == 0){
		//Locating shared memory for evey child -> eveyone's key is different (+1)
		if( (segment_id = shmget(KEYSHM, numOfAppl * sizeof(int), 0) ) < 0 ){//size of int -> status		
			printf("Error! Shared memory failure! (applicant.c)\n");
			exit(1);
		}
		//attaching every element to the child
		if( (status = (int *)shmat(segment_id, 0, 0) ) == (int *) -1){
			printf("Error! Shared memory attachment failure! (applicant.c)\n");
			exit(1);
		}
		//assigning to null
		status[applIndex] = -1;

		sem_post(&applicant);

		//if status is (1,3,4) deteach the process and exit
		if(status[applIndex] == 1 || status[applIndex] == 3 || status[applIndex] == 4){ 
			//kill the process?? kill(Appl[applIndex], ??)
			//exit(1) ???
		}
		shmdt((void *) status);
		//increasing pointer index
		applIndex++;
	}

//-------------------------------------------------HR THREADS-------------------------------------------

	pthread_t receptionist;
	pthread_t interviewer[3]; //1->Int 1, 2->Int 2...
	
	//Creating receptionist
	if( pthread_create(&receptionist, NULL, reception, NULL ) ){   //Receptionist
		fprintf(stderr, "pthread_create receptionist failure\n");
		exit(-1);
	}

	//Creating interviewers
	for(l= 0; l < 3; l++){  	//Interviewers
		int *ptrInt;
		ptrInt = &l;
		if( pthread_create(&(interviewer[l]), NULL, interview, (void *)ptrInt) ){
			fprintf(stderr, "pthread_create interviewer %d failure\n", l);
			exit(-1);
		}
	}

	pthread_join( receptionist, NULL );  	//Wait for receptionist
	pthread_join( interviewer[0], NULL ); 	//Wait each other
	pthread_join( interviewer[1], NULL ); 	//Wait each other
	pthread_join( interviewer[2], NULL ); 	//Wait each other

	printf("Interview process is done.\n");

	pthread_exit(NULL);

//-------------------------------------------------TRAINER THREADS-------------------------------------------

	pthread_t trainer[4]; //4 trainers

	//Creating trainers
	for(m= 0; m < 4; m++){  	
		int *ptrInt;
		ptrInt = &m;
		if( pthread_create(&(trainer[m]), NULL, train, (void *)ptrInt) ){
			fprintf(stderr, "pthread_create trainer %d failure\n", m);
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
	sem_destroy(&mutex_interviewer);
	sem_destroy(&mutex_trainer);
	sem_destroy(&applicant);
	sem_destroy(&appl_go_interviewer);
	sem_destroy(&appl_go_trainer);
	
	//Destroy shared memory
	shmctl(segment_id, IPC_RMID, 0);
	
	return 0;
}














