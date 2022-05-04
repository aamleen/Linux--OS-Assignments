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

int errcheck(int return_value, const char* msg)
{
    if(return_value < 0)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        return return_value;
    }
}

void helper(char* filename,int start_ind,char* P1msgs[]){
    int fifo_fd = errcheck(open(filename, O_WRONLY), "Error opening FIFO to write in P1!\n");
    for(int i=start_ind;i<(start_ind+5);i++){
        if(i>50)
            break;
        char mesg[10]="";
        
        struct message P1_msg;
        strncpy(P1_msg.msg,P1msgs[i],sizeof(P1msgs[i]));
        P1_msg.id=i;
        errcheck(write(fifo_fd, &P1_msg, sizeof(struct message)), "Error while sending msg to P2!\n");
    }
    errcheck(close(fifo_fd), "Error closing FIFO in P1!\n");
}

int main(int argc, char *argv[])
{
    char filename[]="Q2_FIFO";
    errcheck(mkfifo(filename, 0777), "Error creating FIFO!\n");

    int fifo_fd;
    char P2_ret[3];
    int check_ind=0;
    
    char* P1msgs[52];
    for(int i=0;i<52;i++){
        P1msgs[i]=(char*)malloc(6);
        if(P1msgs[i]==NULL){
            perror("Error in allocating memory to string array");
            exit(0);
        }
        generate_msg(P1msgs[i]);
    }

    while(check_ind<50){
        helper(filename,check_ind+1,P1msgs);
        fifo_fd = errcheck(open(filename, O_RDONLY), "Error opening FIFO in P1!\n");
        errcheck(read(fifo_fd, P2_ret, sizeof(P2_ret)), "Error reading acknowledgment in P1!\n");
        check_ind=atoi(P2_ret);
        printf("P2 Acknw--> %d\n",check_ind);
        errcheck(close(fifo_fd), "Error closing FIFO!\n");
    }

    errcheck(remove(filename), "Error removing FIFO!\n");
    exit(EXIT_SUCCESS);
}