#include <stdio.h>

/*Swapping technique used is to store the data of one field (say a) in a temporary variable 
and then storing the data of another field(b) in a. Now the data of a is overridden in a by data in b
Now storing the data of a (from temp var) in b. */

void var_swap(int n1, int n2)   //function to swap the variable
{
    printf("Before Swapping \n n1=%d \n n2=%d \n",n1,n2);
    int temp=n1;
    n1=n2;
    n2=n1;
    printf("After Swapping \n n1=%d \n n2=%d \n",n1,n2);
} 

int max(int n1, int n2) //function to return the maximum value among 2 values
{
    return n1>=n2 ? n1 : n2;
}

void printarray(int a1[], int a2[], int l1, int l2) //function to print array
{
    int i;
    printf("Array1: ");
    for(i=0;i<l1;i++)   
        printf("%d, ",a1[i]);
    printf("\n Array2: ");
    for(i=0;i<l2;i++)
        printf("%d, ",a2[i]);
    printf("\n");
    
}
void arr_swap(int a1[], int a2[], int l1, int l2)   //l1, l2 are lengths of array1 and array2
{
    printf("Before Swapping: \n");
    printarray(a1,a2,l1,l2);
    int i;
    int temp;
    for(i=0;i<max(l1,l2);i++)
    { /*Incase one array is bigger than the other, so swap should be done till the last element of bigger array,
        so running the swap loop till the bigger length */
        temp=a1[i];
        a1[i]=a2[i];
        a2[i]=temp;
    }
    temp=l2;    //swapping the length of both the arrays
    l2=l1;
    l1=temp;
    printf("After Swapping: \n");
    printarray(a1,a2,l1,l2);
}

void inputarray(int a1[], int le)   //function to take input in array
{
    for(int i=0;i<le;i++)
    {
        scanf("%d",&a1[i]);
    }
}

int main()
{
    int n1, n2;
    printf("Enter 2 variables: \n");    //Taking 2 variables
    scanf("%d",&n1);
    scanf("%d",&n2);
    var_swap(n1,n2);    //calling the function to swap varaibles and print it
    printf("Enter size of 2 arrays: \n");
    scanf("%d",&n1);
    scanf("%d",&n2);
    int temp=max(n1,n2);    //creating both the arrays with the max of either length of array, so that while swapping, uniformity is maintained.
    int a1[temp];
    int a2[temp];
    printf("Enter values of Array1: "); //Taking Array inpusts
    inputarray(a1,n1);
    printf("Enter values of Array2: ");     //Taking array inputs for 2nd array
    inputarray(a2,n2);
    arr_swap(a1,a2,n1,n2);  //calling function to swap and print the array
    return 0;
}
