#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

char *socket_path = "/Q2";

struct message{
    int id;
    char msg[50];
};

int helper(int client_){
    int check_ind=0;
    struct message P1_msg;
    for(int i=0;i<5;i++){
        int read_=read(client_,&P1_msg,sizeof(struct message));  //Reading the msg from client
        if(read_==-1){
            perror("Error while reading the msg");
            exit(-1);
        }
        else if (read_ == 0) {  //Client writing stopped/end of file
            return -1;
        }
        else if( read_ > 0) {
            if(check_ind<P1_msg.id) //updating the highest ID received
                check_ind=P1_msg.id;
            printf("%d--> %s\n",P1_msg.id,P1_msg.msg);
        }
        else{}
    }
    return check_ind;   //returning the highest recieved Index
}

int main(int argc, char *argv[]) {

    struct sockaddr_un addr;
    if (argc > 1) 
        socket_path=argv[1];
    int s_fd=socket(AF_UNIX, SOCK_STREAM, 0);
    if (s_fd== -1) {
        perror("socket error");
        exit(-1); 
    }

    memset(&addr, 0, sizeof(addr)); //Adding paths and types to the socket
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    unlink(socket_path); //unlinking, if the same socket was linked previously

    if (bind(s_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){   //binding the socket with server
        perror("Binding error");
        exit(-1); 
    }

    if (listen(s_fd, 5) == -1) {    //server in listening mode
        perror("listening error"); 
        exit(-1); 
    }
    int check_ind=0;
    printf("ID String\n");
    while(1){
        int client_ = accept(s_fd, NULL, NULL); //connecting/accepting response from client
        if ( client_ == -1) {
            perror("accept error");
            continue;
        }
        while(check_ind<=50){
            check_ind=helper(client_);  //calling to read msgs from P1 and print
            char P2_ackw[3];    //to pass the acknowledgment
            sprintf(P2_ackw,"%d",check_ind);
            if(write(client_, P2_ackw, sizeof(P2_ackw)) == -1) {    //Writing acknowledgment to the client(P1)
                perror("Error while acknowledging from P2");
                exit(-1);
            }
            if(check_ind==-1){  //if EOF/Client closed
                close(client_);
                break;
            }
        }
        break;
        
    }

    return 0;
}