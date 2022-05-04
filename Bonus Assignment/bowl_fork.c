#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t tid[5];
pthread_mutex_t lock[5];	//for forks

sem_t mutex;	//for bowls

void takeForks(int i){
	if(pthread_mutex_trylock(&lock[i])==0){		//Trylock will immediately return, if the lock is not acquired
		if(pthread_mutex_trylock(&lock[(i+1)%5])==0){	//If 2nd fork (lock) not acquire, then unlocking the 1st fork
			printf("Philosopher %d eating\n",i);	//Philosopher gets both forks
            sleep(2);
			pthread_mutex_unlock(&lock[(i+1)%5]);
		}
		pthread_mutex_unlock(&lock[i]);
	}
}

void takeBowl(int i){
	if(sem_trywait(&mutex)==0){	//Philosopher tries to lock 1 of the 4 bowls, returns if not locked	
		takeForks(i);		//If bowl was taken, then going to take forks
        sem_post(&mutex);	//releasing the bowl lock
	}
}

void* phil_sit(void *n){
	int i=*((int *)n);
	while(1){
		takeBowl(i);	//Taking 1 out of 4 shared bowl-locks, then if succeed, acquiring 2 forks
		//sleep(1);
	}
}

int main(){
	if(sem_init(&mutex,0,4)!=0)	
		perror("Error while initialising semaphore: ");

    int i=0;
    for(int k=0;k<5;k++){
        if (pthread_mutex_init(&lock[i], NULL) != 0) {
            printf("\n mutex init has failed\n");
            return 1;
        }
    }


	int error=0;
	i=0;
	while (i < 5) {
		int *n=malloc(sizeof(int*));	//Philosopher no. 
		if(n==NULL){
			perror("Error Allocating Philosopher no.\n");
		}
		*n=i;
		error = pthread_create(&(tid[i]),NULL,phil_sit, n);	//Creating Philosphers
		if (error != 0)
			perror("Thread can't be created \n");
        i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	pthread_join(tid[4], NULL);

    for(i=0;i<5;i++)
	    pthread_mutex_destroy(&lock[i]);

	sem_destroy(&mutex);
	return 0;
}