#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include<fcntl.h>

#include "qu.h"

sem_t lock,empty,full;



int main(){
sem_t *lock=sem_open("lock", O_CREAT | O_EXCL, 0600, 1);
    if(lock==SEM_FAILED)	{
		sem_unlink("lock");
        perror("Error while creating semaphore");
        
    }

    sem_t *full=sem_open("full", O_CREAT | O_EXCL, 0600, 0);
    if(full==SEM_FAILED){	
        sem_unlink("full");
		perror("Error while creating semaphore");
        
        }

    sem_t *empty=sem_open("empty", O_CREAT | O_EXCL, 0600, 2);
    if(empty==SEM_FAILED)	{
		sem_unlink("empty");
        perror("Error while creating semaphore");
        
        }
            
    for(int i=0;i<100;i++){
        printf("Waiting");
        sem_wait(full);
    sem_wait(lock);
    printf("Consuming\n");
    sem_post(empty);
    sem_post(lock);
}

    /* if(sem_init(&lock,0,1)!=0)	
		perror("Error while initialising semaphore: ");
    if(sem_init(&empty,0,2)!=0)	
		perror("Error while initialising semaphore: ");
    if(sem_init(&full,0,0)!=0)	
		perror("Error while initialising semaphore: ");

    pthread_t p,c;
    if (pthread_create(&p,NULL,prod, NULL) != 0)
        perror("Thread can't be created \n");
    if (pthread_create(&c,NULL,cons, NULL) != 0)
        perror("Thread can't be created \n");
    
    pthread_join(p,NULL);
    pthread_join(c,NULL); */

    /* sem_destroy(lock);
    sem_destroy(full);
    sem_destroy(empty); */

    return 0;
}


