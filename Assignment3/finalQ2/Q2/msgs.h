#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void generate_msg(char mesg[6]){
    for(int j=0;j<5;j++){
        char ch=(rand()%(122-97+1))+97;
        mesg[j]=ch;
    }
    mesg[5]='\0';
}

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
