#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <fcntl.h>
#include <time.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>


#define sys_manual_delay 449

int main(){
    pid_t pid=fork();
    if(pid==1)
        perror("Error while creating child process");
    else if(pid==0){
        time_t begin,finish;
        time(&begin);
        for(long long i=0;i<__LONG_LONG_MAX__;i++){

        }
        time(&finish);
        printf("Original Parent takes: %lf\n",(double)(finish-begin));
    }
    else{
        time_t begin,finish;
        time(&begin);
        if(syscall(sys_manual_delay,getpid(),1000));
        for(long long i=0;i<INT_MAX;i++){

        }
        time(&finish);
        printf("Child process with modified vruntime takes: %lf\n",(double)(finish-begin));
    }
}