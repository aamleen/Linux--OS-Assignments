#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<errno.h>

#define PROJECT_PATHNAME "msg_passing_writer.c"
#define PROJECT_ID 20002
#define MSG_SIZE 512


struct msg_struct
{
    long type;
    long ind;
    char msg[512];
}message;


int main()
{
    key_t key = ftok(PROJECT_PATHNAME, PROJECT_ID); //creating unique key
    if(key==-1)
    {
        printf("Error generating msg key!\n%s\n", strerror(errno));
        return -1;
    }
    
    int qid = msgget(key, 0666|IPC_CREAT);  //using that unique key to create/get the message queue
    if(qid==-1)
    {
        printf("Error retrieving queue id!\n%s\n", strerror(errno));
        return -1;
    }

    struct msqid_ds buf;    //struct that will help in checking the status of the message queue

    int check_ind=0;    //to keep check how many msgs have arrived

    while(check_ind<50){
        do
        {
            if(msgrcv(qid, &message, MSG_SIZE, 1, MSG_NOERROR)==-1) //receiving the msg from the queue of type1(P1)
            {
                perror("Error recieving message!");
                exit(0);
            }
            
            printf("(%ld)--> %s\n", message.ind, message.msg);//printing the msgs
            if(check_ind<message.ind)
                check_ind=message.ind;
            
            if(msgctl(qid, IPC_STAT, &buf) == -1) //checking queue status
            {
                perror("Error retrieving msgctl info!");
                exit(0);
            }
            
        }while(buf.msg_qnum!=0);    //Receiving msgs of a type till the queue is not empty

        message.type=2; //Type2 msgs are acknowledgment from P2 to P1
        message.ind=check_ind;
        if(msgsnd(qid, &message, MSG_SIZE, 0)==-1)//sending acknowledgment
        {
            perror("Error sending acknowledgment to P1!");
            exit(0);
        }
    }
    printf("\n");
    
}
