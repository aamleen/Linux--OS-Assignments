#include <stdio.h>
#include <math.h>   //to calculate power
#include <string.h>     //to compare the strings using strcmp
#include <stdlib.h>     //to parse input arguments to float

void add(float a, float b)
{
    printf("%f\n",a+b);     //prints the sum of 2 nos.
} 

void sub(float a, float b)  //prints the difference of 2 nos.
{
    printf("%f\n",a-b);
} 

void mul(float a, float b)  //prints the product of 2 nos.
{
    printf("%f\n",a*b);
} 

void divi(float a, float b)    //prints the quotient of 2 nos.
{
    printf("%f\n",a/b);     //function named divi, because div already exists in stdlib.h
}  

void expo(float a, float b)     //calculate the exponent of a^b. exp() already in math.h, so declaring as expo
{
    printf("%f\n",powf(a,b));
} 

int main(int argc, char *argv[])
{
    void (*func[5])(float, float)={add,sub,mul,divi,expo};      
    /*void function pointer, of the type that takes 2 input float
      Here each cell stores the address to the function, so the function can be directly called by calling the particular cell*/
    if(argc!=4)     //argument should be ./<executable_file name> operation_name operand1 operand2
    {    printf("Invalid arguments given. Correct order is eg- sub 7 8 \n");
        return 0;
    }
    float a=(float)(atof(argv[2]));     //parsing both the operands to float
    float b=(float)(atof(argv[3]));
    if(strcmp("add",argv[1])==0)    //if operation (stored in argv[1]) is add 
    {
        func[0](a,b);   //func[0] stores the address to add function, so calling that and passing the arguments
    }
    else if(strcmp("sub",argv[1])==0)   //if operation (stored in argv[1]) is sub
    {
        func[1](a,b);   //func[1] stores the address to sub function, so calling that and passing the arguments
    }
    else if(strcmp("mul",argv[1])==0)   //if operation (stored in argv[1]) is mul
    {
        func[2](a,b);   //func[2] stores the address to mul function, so calling that and passing the arguments
    }
    else if(strcmp("div",argv[1])==0)   //if operation (stored in argv[1]) is div
    {
        if(b==0)    //if denominator is zero, can not be divided
        {
            printf("Denominator can not be 0 \n");  
            return 0;
        }
        func[3](a,b);   //func[3] stores the address to div function, so calling that and passing the arguments
    }
    else if(strcmp("exp",argv[1])==0)   //if operation (stored in argv[1]) is exp
    {
        func[4](a,b);   //func[4] stores the address to exp function, so calling that and passing the arguments
    }
    else    //if the operation is wrong
        printf("Invalid Choice \n");
     
    return 0;

}