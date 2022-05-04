#include <stdio.h>

void A(){
    unsigned long num;
    extern void B(unsigned long num);
    printf("In function A \n");
    num=478560413000L;
    B(num);
    printf("Checking if B returns back to A");  //if the control ever comes back from B to A, so this line will be printed. So ideally this line should not print
    
}

int main(int argc, char const *argv[])
{
    A();
    return 0;
}
