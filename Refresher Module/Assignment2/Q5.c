#include <stdio.h>

void BubbleSort(int arr[],int len,int order)    //order will tell if we have to sort ascending or descending
{/*In bubble sort, we compare each consecutive element in the array and sort them accordingly,
    Doing this will result in the largest element moving to the last location.
    Repeating the process, after every successful iteration, the desired element will reach the last position in the unsorted sub-array
    To achieve this we run the outer loop for n times. For each iteration in the outer loop, we run the inner loop till the last element in the unsorted-subarray
    In the inner loop, we compare consecutively and then swap accordingly.*/
    for(int i=0;i<len-1;i++)
    {
        for(int j=0;j<len-i-1;j++)
        {
            if(order==1)
            {
                if(arr[j]>arr[j+1]) //comparing consecutively and swapping if needed
                {
                    int temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
            else
            {
                if(arr[j]<arr[j+1])
                {
                    int temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        }
    }
}

void SelectionSort(int arr[],int len,int order)
{/*In Selection sort, for each iteration i, we scan the array from ith position to last pos.
    The smallest(largest for descending) no. found is then swapped with the 1st position, after the 1st scan is over.
    In this way the required element is moved to the starting of the array. 
    Then repeating this n times, will make required elements reach in the desired position in the front sorted subarray, till we run the loop in the later unsorted array*/
    int i,j, min_max;
    for(i=0;i<len;i++)
    {
        min_max=i;
        for(j=i+1;j<len;j++)
        {
            if(order==1)
            {
                if(arr[j]<arr[min_max]) //if the next smallest element is found, it's index is stored to swap later
                    min_max=j;
            }
            else
            {
                if(arr[j]>arr[min_max]) //if the next largest element found
                    min_max=j;
            }
        }
        if(order==1)
        {
            if(arr[min_max] < arr[i])   //if the smallest element found in subarray is smaller than the element to be swapped, then swap
            {
                int temp=arr[i];
                arr[i]=arr[min_max];
                arr[min_max]=temp;
            }
        }
        else
        {
            if(arr[min_max] > arr[i])   //if the largest element found in subarray is larger than the element to be swapped, then swap
            {
                int temp=arr[i];
                arr[i]=arr[min_max];
                arr[min_max]=temp;
            }
        }
    }
}

int main()
{
    int choice, len, i;
    printf("Enter 1 for Bubble sort and 0 for Selection Sort: ");
    scanf("%d",&choice);    //taking ans storing user choice
    if(choice !=0 && choice!=1)     //if choice is neither 1 nor 0
    {
        printf("Wrong choice \n");
        return 0;
    }
    printf("Enter size of array: ");
    scanf("%d",&len);
    printf("Enter array elements (int): ");
    int arr[len];   //Declaring an array with a length as len
    for(i=0;i<len;i++)  //Taking array inputs
        scanf("%d",&arr[i]);
    //while calling the sorting functions, no need to return and store the sorted array because we are sorting in the original array only using pointers (reference value)
    int order; 
    printf("Enter 1 for ascending order, and -1 for descending order: ");
    scanf("%d",&order);
    if(choice==1)   
        BubbleSort(arr,len,order);    //calling function to bubble sort
    else if(choice==0)
        SelectionSort(arr,len,order); //calling function to do selection sort on the array
    else
        printf("No Sorting DOne");
    
    printf("Printing the New Array: "); //arr now contains the sorted array
    for(i=0;i<len;i++)
        printf("%d, ",arr[i]);
    printf("\n");
    return 0;
}