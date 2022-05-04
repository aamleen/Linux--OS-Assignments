#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <errno.h>

#include <signal.h>
#include <assert.h>
#include <errno.h>

pid_t S1pid;
void handlerSR(int iSig){
    unsigned int rand_no;
    asm("rdrand %0":"=a"(rand_no));

    union sigval val;
    val.sival_int=rand_no;
    printf("SR_Random no. is: %u\n",val.sival_int);
    if(sigqueue(S1pid,SIGTERM,val)==-1)    
        perror("Error while queuing ");
}

int main(int argc, char const *argv[]){
    S1pid=atoi(argv[1]);
    printf("Pid of SR is: %d\n",getpid());
    printf("Pid of S1 recieved in SR is: %d\n\n",S1pid);
    
    struct sigaction sAction;
    sAction.sa_flags=SA_SIGINFO;
    sAction.sa_handler=&handlerSR;
    sigemptyset(&sAction.sa_mask);
    if(sigaction(SIGALRM, &sAction, NULL)==-1){
        perror("Error ");
        return 0;
    }

    struct itimerval sTimer;
    sTimer.it_value.tv_sec=1;
    sTimer.it_value.tv_usec=0;

    sTimer.it_interval.tv_sec=1;
    sTimer.it_interval.tv_usec=0;

    if(setitimer(ITIMER_REAL,&sTimer,NULL)==-1){
        perror("Error in timeer ");
        return 0;
    }
    
    while(1){
        sleep(1);
    }
    exit(0);
}