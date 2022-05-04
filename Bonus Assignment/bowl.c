#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t tid[5];
int counter=0;
pthread_mutex_t lock[4];

sem_t mutex;

void takeBowl(int i){
	if(sem_trywait(&mutex)==0){	//Philosopher tries to lock 1 of the 4 bowls, returns if not locked	
		printf("Philospher %d Eating\n",i);
		sleep(2);
        sem_post(&mutex);	//releasing the bowl lock
	}
}

void* phil_sit(void *n){
	int i=*((int *)n);
	printf("Philosopher %d seated", i);
	while(1){
		takeBowl(i);	//Trying to take the Bowl
		//sleep(1);
	}
}

int main(){
	if(sem_init(&mutex,0,4)!=0)
		perror("Error while initialising semaphore: ");
	int error=0;
	int i=0;
	while (i < 5) {
		int *n=malloc(sizeof(int*));
		if(n==NULL){
			perror("Error Allocating memory\n");
		}
		*n=i;
		error = pthread_create(&(tid[i]),NULL,phil_sit, n);
		if (error != 0)
			perror("Thread can't be created \n");
        i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	pthread_join(tid[4], NULL);

	sem_destroy(&mutex);
	return 0;
}