/*----------------*\
|	Baran	   |
|	KAYA	   |
|     150130032	   |
\*----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>

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
unsigned int i;

//-------------------------------------MAIN---------------------------------------

int main( int argc, char **argv ){

numOfAppl = atoi( argv[2] );	//Taking number of applicants

int segment_id = 0;	//shared memory id
int *status; 		//status[numOfAppl]; //shared memory array (status for each appl.)

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

		//if status is (1,3,4) deteach the process and exit
		if(status[applIndex] == 1 || status[applIndex] == 3 || status[applIndex] == 4){ 
			//kill the process?? kill(Appl[applIndex], ??)
			//exit(1) ???
		}
		shmdt((void *) status);
		//increasing pointer index
		applIndex++;
	}

//----------------------------------------------------------------------------------------------------

	//Destroy shared memory
	shmctl(segment_id, IPC_RMID, 0);

	return 0;
}





