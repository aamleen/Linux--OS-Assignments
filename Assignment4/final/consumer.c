#include <stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

#define sys_reader 449

int main(){

    for(int i=0;i<100;i++){
        long long* buff=malloc(2*sizeof(long long));    //buffer to recieve the bytes from reader
        if(buff==NULL)
            perror("Error initialising buffer");
        long res=syscall(sys_reader,buff);  //calling reader syscall to read the bytes
        printf("Consumed: %lld \n",*buff);   
        sleep(2);
    }
}