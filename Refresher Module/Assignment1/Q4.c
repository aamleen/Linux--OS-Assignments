#include <stdio.h>

void reverse(char str[150])     //function to reverse the string
{
    int len=0;
    int i=0;
    while(str[i]!='\n' && str[i]!='\0')     //loop to calculate the length of the string entered. Length will be till \n or \0 is encountered
    {
        len++;
        i++;
    }
    char rev[len+1];    //declaring a character array with size as len+1
    for(i=0;i<len;i++)  
    { /*For reversing the string, we store each character of the string starting from the last till 0 in a character array, 
        starting from 0 to len, i.e. in a reversed order.*/
        rev[i]=str[len-i-1];
    }
    rev[len]='\0';  //Adding the last element as \0, so that it is known that the string terminates here.
    
    printf("Original String: %s",str);  //Printing original string
    printf("Reverse String : %s \n",rev);   //Printing reversed string
}
int main()
{
    char str[150];  //Declaring a char array to store the string of maximum 150 length
    printf("Enter the string: ");
    fgets(str,150,stdin);   //Taking input in str from stdin, of maximum 150 chars
    reverse(str);   //Calling function to reverse the string
    return 0;
}
