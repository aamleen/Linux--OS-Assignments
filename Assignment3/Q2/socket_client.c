#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "msgs.h"

char *socket_path = "/Q2";

struct message{
    int id;
    char msg[50];
};

int main(int argc, char *argv[]) {

    struct sockaddr_un addr;    //struct for socket
    char* P1msgs[52];   //Array of 52 random strings with size of each as 5
    for(int i=0;i<52;i++){
        P1msgs[i]=(char*)malloc(6);
        if(P1msgs[i]==NULL){
            perror("Error in allocating memory to string array");
            exit(0);
        }
        generate_msg(P1msgs[i]);    //calling method in msgs.h to create random string
    }
    if (argc > 1) 
        socket_path=argv[1];
    int s_fd= socket(AF_UNIX, SOCK_STREAM, 0);  //creating a socket
    if (s_fd == -1) {
        perror("socket error");
        exit(-1); 
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1); 

    if(connect(s_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){ //connecting the cline to the server
        perror("connect error");
        exit(-1);
    }
    struct message P1_msg;  //structure of message to be passed
    for(int j=0;j<10;j++){
        for(int i=5*j+1;i<=5*(j+1);i++){
            strcpy(P1_msg.msg,P1msgs[i]);   //copying the string to the message
            P1_msg.id=i; //Addint the id of the string
            if(write(s_fd, &P1_msg,sizeof(struct message))==-1) {    //writing to the server
                perror("Write error");
                exit(-1);
            }
        }
        char P2_ackw[3];
        if(read(s_fd, P2_ackw, sizeof(P2_ackw))==-1) {  //reading acknowledgment from P2(server)
            perror("Read error");
            exit(-1);
        }
        printf("P2--> %s\n",P2_ackw);//Printing the acknowledgment

    }

    return 0;
}