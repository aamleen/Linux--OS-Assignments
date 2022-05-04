#include <stdio.h>
#include <stdlib.h>

/*The general structure of the program is that an array of double pointers store the pointer to each row, which in turn can be assumed as a 1d array
  So, while filing or printing the array, we iteratre over each double pointer, and 
  for the corresponding double pointer, we iterate over the array, whose 1st cell's pointer is stored in the corresponding double pointer*/
    
void customMat(int** mat, int rows, int col[rows])
{
    int i,j;
    int fill=rand()%10+1;   //generating a random no. between 1-10, to fill the matrix
    
    for(i=0;i<rows;i++)
    {
        for(j=0;j<col[i];j++)
        { /* *(mat+i) iterates over the value stored in each double pointer cell, i.e the reference to each row's array
            then, iterating over each cell in the row, by adding j to the pointer of the 1d array (row)*/
            *(*(mat+i)+j)=fill; 
        }
    }
    printf("Displaying the matrix: \n");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<col[i];j++)
        {
            printf("%d",*(*(mat+i)+j));
        }
        printf("\n");
    }
}

int main()
{
    int i,j;
    int **mat;  //double-pointers to store the pointer
    int rows=6; 
    mat=calloc(rows,sizeof(int*)); //Allocating space for 6 double pointers, each of which will point to the pointer of a 1-d array (row)
    int col[6]={7,4,6,3,7,2};   //no. of columns in each row
    for(i=0;i<rows;i++)
    { // Now we allocate memory for each of the 1d array (rows), and store its pointer in the corresponding array of double pointers
        *(mat+i)=calloc(col[i],sizeof(int));  
    }
    customMat(mat,rows,col);    //calling the function to populate the matrix and print it
    return 0;
}
