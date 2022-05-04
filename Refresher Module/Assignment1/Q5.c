#include <stdio.h>
#include <stdlib.h>

int comp(const void* n1, const void* n2)    //compare function required by qsort to sort the array for binary search to work
{
    const unsigned int* x=n1;
    const unsigned int* y=n2;
     if(*x > *y)    //if value pointed by x is greater then, returning 1, if small then -1 and if equal then 0
       return 1;
     else
       return(*x < *y) ? -1: 0;
}

int binSearch(unsigned int x, unsigned int num[], int left, int right)
{
    /*In Binary Search, operating on a sorted array,
      We first find the middle element of the array, compare it with the required value,
      if the value matches the middle element, we return the index.
      if value to be searched is smaller, looking in the first half of array, else second half 
      Perform this till the array is reduced to nothing. If still not found, returning -1*/
    int mid=(int)(left+right)/2;
    while(left<=right)
    {
        mid=(int)(left+right)/2;
        if(num[mid]==x)
            return mid;
        else if(x>num[mid])
            left=mid+1;
        else
            right=mid-1;
    }
    return -1;
}

int main()
{
    int n;
    printf("Enter size of array: ");    //Taking the size of input array
    scanf("%d",&n);
    unsigned int num[n];    //Declaring array to store values
    long long int temp;
    printf("Enter array elements: ");
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&temp);    //Taking array input temporarily in long long int to check overflow
        if(temp<0 || temp>4294967295)   //if the entered value is not within the limits
        {
            printf("Overflow!! Exiting program \n");
            return 0;
        }
        num[i]=(unsigned int)(temp);    //typecasting to unsigned int and storing in array
    }
    qsort(num,n, sizeof(unsigned int),comp);    //Calling the inbuilt function to sort the array, in case not sorted
    printf("New Sorted Array: ");   //Printing the sorted array, so that index of found element can be appropriately refered in sorted array
    for(int i=0;i<n;i++)
        printf("%u, ",num[i]);
    printf("\n");
    unsigned int ele;
    printf("Enter element to search: ");
    scanf("%u",&ele);
    int res=binSearch(ele,num,0,n-1);   //Calling the function to search for the value ele, and storing the result in res
    if (res==-1)    //if res is -1, element was not found. else returned value is a index of successful search
        printf("Element Not found \n");
    else
        printf("Element Found at index %d in Sorted Array \n",res);
    return 0;
    
}
