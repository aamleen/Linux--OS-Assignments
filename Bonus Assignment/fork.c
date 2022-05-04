#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[5];
pthread_mutex_t lock[5];

void eat(int i){
	if(pthread_mutex_trylock(&lock[i])==0){	//Take 1st left fork if availale,if not return and try in next iteration
		if(pthread_mutex_trylock(&lock[(i+1)%5])==0){	//Take the 2nd fork if available. If not return & release the 1st fork too
			printf("Philosopher %d eating\n",i);
			sleep(2);	//Eating
			pthread_mutex_unlock(&lock[(i+1)%5]);	//Releasing the right fork
		}
		pthread_mutex_unlock(&lock[i]);		//Releasing the left fork
	}
}

void* phil_sit(void *n){
	int i=*((int *)n);
	printf("Philosopher %d Seated\n",i);
	while(1){
		eat(i);	
	}
}

int main(void)
{
	int i = 0;
	int error;

    for(int k=0;k<5;k++){
		if (pthread_mutex_init(&lock[i], NULL) != 0) {
			perror("Initialisng Mutexes failed");
		}
    }

	while (i < 5) {
		int *n=malloc(sizeof(int*));
		if(n==NULL){
			perror("Error Allocating Philosopher no.");
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

    for(int i=0;i<5;i++)
		pthread_mutex_destroy(&lock[i]);

	return 0;
}
