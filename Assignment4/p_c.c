#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include<fcntl.h>



sem_t lock,empty,full;

struct queu{
  long long buffer[2*sizeof(long long)];
  int front;
}Queue;


void producer(){
    sem_wait(&empty);
    sem_wait(&lock);
    int fd=open("/dev/urandom",O_RDONLY);
    if(fd==-1)
        perror("Error");
    long long* buff=calloc(2,8);
    if(buff==NULL){
      perror("Buffer");
    }
    int s=read(fd,buff,8);
    printf("Produced: %lld: \n",*buff);
    Queue.buffer[Queue.front++]=*buff;
    close(fd);
    sem_post(&full);
    sem_post(&lock);
}

void consumer(){
    sem_wait(&full);
    sem_wait(&lock);
    long long buff=Queue.buffer[--Queue.front];
    printf("%lld \n",buff);
    sem_post(&empty);
    sem_post(&lock);
}


void* prod(){
    for(int i=0;i<100;i++){
        producer();
    }
}

void* cons(){
    for(int i=0;i<100;i++){
        consumer();
    }
}

int main(){
        
    
    if(sem_init(&lock,0,1)!=0)	
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
    pthread_join(c,NULL);

    sem_destroy(&lock);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;

    
}


