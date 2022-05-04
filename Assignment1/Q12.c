#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

#define O_RDONLY 00

float overall_total[7]={0,0,0,0,0,0,0};

void section_average(char ch){
    int si= open("student_record.csv", O_RDONLY);	//opening the csv file in read mode
    char* buffer=(char *)calloc(1024,sizeof(char));  //buffer to store the csv file
    if(buffer==NULL){
		printf("Error while allocating memory\n");
		return;
	}
    int row = 0;    //store the row no. currently accessing
    int column = 0; //store the column no. currently accessing
    float no_of_students=0; //as we move, it will store the total no. of students in Sec A and B
    int ass_gn[6] = {0,0,0,0,0,0};  //will store the total marks in each assignment
    printf("Section %c: \n",ch);
    int i=0;
    while (1)//reads each line from the csv file, and stores it in the buffer, till EOF file is reached, and Null is returned
    {
        int flag=read(si,&buffer[i],1);
        if(flag!=1){
			if(flag==-1){
				printf("Error in Reading the file");
				return;
			}
			else
				break;
		}
        if(buffer[i]!='\n')
        {
            i++;
            continue;
        } 
        column = 1;	//column value reset after each row
        row++;
        if (row == 1)	//skipping row1 as it will contain the labels
        {    i=0;
            continue;
        }
        char* value = strtok(buffer, ",");	//splits the rows using ',' as delimitter and stores it in value. Therefore we get each column in a row
        while (value) //runs till the end of line(\n), i.e last column in a row is encountered 
        {
            if (column == 2) {
                if(*value!=ch)//if its not section A, then breaking the loop, and moving to the next row
                {
                    value = strtok(NULL, ",");
                    break;
                }
                no_of_students+=1.0;
            }
            // Column 3 to 8 contain the assignment marks, so adding all of them in an array
            if (column >= 3 && column<=8) {
                ass_gn[column-3]+=atoi(value);
            }
            value = strtok(NULL, ",");	//breaking the string after reading each cell
            column++;	//moving to next column
        }
        i=0;
    }
    overall_total[6]+=no_of_students;
    for(int i=0;i<6;i++){
        printf("Assignment%d Total Marks: %d, \t Avg marks %f \n",i+1,ass_gn[i],ass_gn[i]/no_of_students);
        overall_total[i]+=ass_gn[i];
    }
    printf("--------------------------------\n");
}

void* helper(void* ch){
    int fd= open("student_record.csv", O_RDONLY);	//opening the csv file in read mode
    char* buffer=(char *)calloc(1024,sizeof(char));  //buffer to store the csv file
    if(buffer==NULL){
		printf("Error while allocating memory\n");
		return ;
	}
    int row = 0;    //store the row no. currently accessing
    int column = 0; //store the column no. currently accessing
    float no_of_students=0; //as we move, it will store the total no. of students in Sec A and B
    int ass_gn[6] = {0,0,0,0,0,0};  //will store the total marks in each assignment
    printf("Section A: \n");
    int i=0;
    while (1)//reads each line from the csv file, and stores it in the buffer, till EOF file is reached, and Null is returned
    {
        int flag=read(fd,&buffer[i],1);
        if(flag!=1){
			if(flag==-1){
				printf("Error in Reading the file");
				return;
			}
			else
				break;
		}
        if(buffer[i]!='\n')
        {
            i++;
            continue;
        } 
        column = 1;	//column value reset after each row
        row++;
        if (row == 1)	//skipping row1 as it will contain the labels
        {    i=0;
            continue;
        }
        char* value = strtok(buffer, ",");	//splits the rows using ',' as delimitter and stores it in value. Therefore we get each column in a row
        while (value) //runs till the end of line(\n), i.e last column in a row is encountered 
        {
            if (column == 2) {
                if(*value!='A')//if its not section A, then breaking the loop, and moving to the next row
                {
                    value = strtok(NULL, ",");
                    break;
                }
                no_of_students+=1.0;
            }
            // Column 3 to 8 contain the assignment marks, so adding all of them in an array
            if (column >= 3 && column<=8) {
                ass_gn[column-3]+=atoi(value);
            }
            value = strtok(NULL, ",");	//breaking the string after reading each cell
            column++;	//moving to next column
        }
        i=0;
    }
    overall_total[6]+=no_of_students;
    for(int i=0;i<6;i++){
        printf("Assignment%d Total Marks: %d, \t Avg marks %f \n",i+1,ass_gn[i],ass_gn[i]/no_of_students);
        overall_total[i]+=ass_gn[i];
    }
    printf("--------------------------------\n");
}

int main()
{
	
	if (open("student_record.csv", O_RDONLY)==-1)
		printf("Can't open file\n");
	else {
		pthread_t thread;
        pthread_create(&thread, NULL,helper,"A");
    
        section_average('B');
        pthread_join(thread, NULL);

        

        printf("Overall Stats: \n");
        for(int i=0;i<6;i++)
            printf("Assignment %d: %f\n",i+1,overall_total[i]/overall_total[6]);
	}
	return 0;
}
