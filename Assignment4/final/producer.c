#include <stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

#define sys_writer 448

int main(){

    for(int i=0;i<100;i++){
        int fd=open("/dev/urandom",O_RDONLY);   //opening the file to read random nos.
        if(fd==-1)
            perror("Error Opening urandom file");
        long long* buff=malloc(2*sizeof(long long));    //buffer in which random nos. will be read
        if(buff==NULL){
            perror("Error initialising buffer");
        }
        int s=read(fd,buff,8);  //reading 8 bytes
        if(s==-1)
            perror("Error reading urandom");
        long long val=*buff;
        if(syscall(sys_writer,val)!=0)  //Passing the value to kernel writer syscall
            printf("Problem in syscall\n");
        printf("Produced: %lld\n",val);
        sleep(2);
    }
}