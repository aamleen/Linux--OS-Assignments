#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include<errno.h>
#include "msgs.h"

#define PROJECT_PATHNAME "msg_passing_writer.c"
#define PROJECT_ID 20002
#define MSG_SIZE 512


struct msg_struct
{
    long type;
    long ind;   //stores the id of msg
    char msg[512];  //stores the actual msg
}message;


void helper(int qid,int start_ind,char* P1msgs[]){
    
    for(int i=start_ind;i<(start_ind+5);i++){   
        if(i>50)
            break;
        strcpy(message.msg,P1msgs[i]);  //adding the string to the msg to be sent
        message.type=1; //Type1 means msg from P1 to P2
        message.ind=i;  //index of the msg
        if(msgsnd(qid, &message, MSG_SIZE, 0)==-1)  //sending the msg to P2
        {
            perror("Error Sending msg to P2!!");
            exit(0);
        }
    }
}

int main()
{   
    key_t key = ftok(PROJECT_PATHNAME, PROJECT_ID); //generating the same unique key for queue
    if(key==-1)
    {
        perror("Error generating msg key in P1");
        return -1;
    }

    int qid = msgget(key, 0666|IPC_CREAT);  //generating queue ID in 0666 Mode
    if(qid==-1)
    {
        perror("Error generating queue ID");
        return -1;
    }

    char* P1msgs[52];   //Array of 52 random strings with size of each as 5
    for(int i=0;i<52;i++){
        P1msgs[i]=(char*)malloc(6);
        if(P1msgs[i]==NULL){
            perror("Error in allocating memory to string array");
            exit(0);
        }
        generate_msg(P1msgs[i]);    //calling method in msgs.h to create random string
    }

    int check_ind=0;
    struct msqid_ds buf; //struct to check the status of message queue
    while(check_ind<50){
        helper(qid,check_ind+1,P1msgs); //calling helper func to write to P2
        if(msgrcv(qid, &message, MSG_SIZE, 2, MSG_NOERROR)==-1) //receiving acknowledgment(Type=2) from P2
        {
            perror("Error receiving acknowledgment from P2");
            return -1;
        }
        check_ind=message.ind;
        printf("P2 Acknw--> %ld\n",message.ind);
        if(msgctl(qid, IPC_STAT, &buf) == -1) // checking queue status
        {
            perror("Error retrieving msg..");
            return -1;
        }
    }
    msgctl(qid, IPC_RMID, NULL); //Removing message queue, as after reading the last acknowledgment from P2, queue will not be required
    return 0; 

}
