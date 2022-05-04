#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include <ctype.h>

#include "msgs.h"

#define buffLen 50

struct message{
    int id;
    char msg[buffLen];
};

int helper(char* filename){
    int fifo_fd = errcheck(open(filename, O_RDONLY), "Error opening FIFO in P2!\n");
    int check_ind=0;
    for(int i=0;i<5;i++){
        struct message P1_msg;
        errcheck(read(fifo_fd, &P1_msg, sizeof(struct message)), "Error reading msg from P2!\n");
        if(check_ind<P1_msg.id)
            check_ind=P1_msg.id;
        printf("%d--> %s\n",P1_msg.id,P1_msg.msg);
    }
    errcheck(close(fifo_fd), "Error closing FIFO in P2!\n");
    return check_ind;
}

int main(int argc, char *argv[])
{
    char filename[]="Q2_FIFO";
    int fifo_fd;
    char P2_acknw[3];
    int check_ind=0;
    while(check_ind<50){
        check_ind=helper(filename);
        sprintf(P2_acknw,"%d",check_ind);
        fifo_fd = errcheck(open(filename, O_WRONLY), "Error opening FIFO in P2!\n");
        errcheck(write(fifo_fd, P2_acknw, sizeof(P2_acknw)), "Error while acknowledging from P2!\n");
        errcheck(close(fifo_fd), "Error closing FIFO!\n");
    }
    exit(EXIT_SUCCESS);
}