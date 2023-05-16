/**
 * Author: Daniah Mohammed
 * St# 101145902
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <wait.h>

#define MICRO_SEC_IN_SEC 1000000

struct shared_use_st {
	int M[3][3];
    int D[3];
    int L[3];
    int largest, det;
};

int largest(int A, int B, int C){
    if (A >= B && A >= C)
        return A;
    if (B >= A && B >= C)
        return B;
    if (C >= A && C >= B)
        return C;
    return -1;
}

int main(){
    struct timeval start, end;
	pid_t pid;

    //start the timer
    gettimeofday(&start, NULL);

    //parent should fork all 3 process
    int i=1;

    while (i<4){
        pid = fork();
        if(pid ==0){
            break;
        }
        i++;
    }

    //allocating shared memo in every single child or only once? 
    void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff; 
	int shmid;

    //attaching and init the shared memo
    srand((unsigned int)getpid());    
	
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	//make shared memo accessable 
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	shared_stuff = (struct shared_use_st *)shared_memory;

    //initializing the matrix M
    shared_stuff->M[0][0]= 20;
    shared_stuff->M[0][1]= 20;
    shared_stuff->M[0][2]= 50;

    shared_stuff->M[1][0]= 10;
    shared_stuff->M[1][1]= 6;
    shared_stuff->M[1][2]= 70;

    shared_stuff->M[2][0]= 40;
    shared_stuff->M[2][1]= 3;
    shared_stuff->M[2][2]= 2;

    //printing the matrix
    if (i==1){
        printf("\n-------------------------------------------------------------------------------------\n");
        printf("\n                    Printing the 3x3 matrix M \n\n");
        //Read the elements of the 3x3 matrix
        for(int s=0;s<=2;s++) {
            
            for(int j=0;j<=2;j++) {
                printf("%d  ", shared_stuff->M[s][j]);
            }
            
            printf("\n");
        }
        printf("\n-------------------------------------------------------------------------------------\n");
    }
    

    switch (pid)
    {
    case -1: 
        perror("fork failed");
        exit(1);
        break;
    case 0:
        printf("\n-------------------------------------------------------------------------------------\n");
        printf("                      Child %d  process started excuting  \n\n", i);
        printf("Child[%d] --> pid = %d and ppid = %d\n\n", i, getpid(), getppid());
        printf("Child Process [%d]: working with element [%d] of D\n",i, i);

        shared_stuff -> D[i-1]= (shared_stuff -> M[0][i-1]) *(shared_stuff -> M[1][i%3] * shared_stuff -> M[2][(i+1)%3] - shared_stuff -> M[1][(i+1)%3] * shared_stuff -> M[2][i%3]);
        shared_stuff -> L[i-1]= largest(shared_stuff->M[i-1][0],shared_stuff->M[i-1][1],shared_stuff->M[i-1][2]);
        
        printf("\nThe value of D[%d]= %d\n", i, shared_stuff -> D[i-1]);
        printf("\nThe largest value in row [%d]= %d\n", i, shared_stuff -> L[i-1]);
        printf("\n-------------------------------------------------------------------------------------\n");

        break;
    
    default:
        //waiting for the 3 children to execute
        wait(NULL);
        wait(NULL);
        wait(NULL);

        printf("\n-------------------------------------------------------------------------------------\n");
        printf("                        Parent process started excuting  \n\n");
        printf("parent --> pid = %d\n", getpid());

        shared_stuff -> det = shared_stuff->D[0]+shared_stuff->D[1]+shared_stuff->D[2];
        shared_stuff -> largest = largest(shared_stuff->L[0], shared_stuff->L[1], shared_stuff->L[2]);
        printf("\nThe det value of the matrix M [R] = %d\n", shared_stuff->det);
        printf("\nThe largest value of the matrix M [L] = %d\n\n", shared_stuff->largest);

        //stopping the timer
        gettimeofday(&end, NULL);

        printf("\n-------------------------------------------------------------------------------------\n");
        printf("                        The time required to perform all operations operations  \n");

        printf("\n\nStart Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n", start.tv_sec + (double)start.tv_usec/MICRO_SEC_IN_SEC);

        printf("\nEnd Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n", end.tv_sec + (double) end.tv_usec/MICRO_SEC_IN_SEC);

        printf("\nElapsed Time: %ld micro sec\n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec))));

        printf("\n-------------------------------------------------------------------------------------\n");

        // Deattaching and clearing the shared memo
        if (shmdt(shared_memory) == -1) {	
            fprintf(stderr, "shmdt failed\n");	
            exit(EXIT_FAILURE);
        }
        if (shmctl(shmid, IPC_RMID, 0) == -1){
            fprintf(stderr, "shmctl(IPC_RMID) failed\n");
            exit(EXIT_FAILURE);	
        }
        break;
    }
}