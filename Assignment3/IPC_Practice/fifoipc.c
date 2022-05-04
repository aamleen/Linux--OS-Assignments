#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

int main(){
    const char *a[2];
a[0] = "blah";
a[1] = "hmm";
}