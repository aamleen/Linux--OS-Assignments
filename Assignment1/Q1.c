#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <errno.h>

#define O_RDONLY 00

void helper(char ch){
	int si= open("student_record.csv", O_RDONLY);	//opening the csv file in read mode
	char *buffer=(char *)calloc(1024,sizeof(char));  //buffer to store the csv file
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
	while(1)
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
		{	i=0; 
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
	for(int i=0;i<6;i++)
		printf("Assignment%d Total Marks: %d, \t Avg marks %f \n",i+1,ass_gn[i],ass_gn[i]/no_of_students);
	printf("--------------------------------\n");
}

int main()
{
	if (open("student_record.csv", O_RDONLY)==-1)
		printf("Can't open file\n");
	else {
		pid_t pid;
		int status;
		pid=fork();
		char ch;
		if(pid<0){
			printf("fork failed");
			return 0;
		}
		else if(pid==0){
			printf("In child process, evaulating section A : \n");
			helper('A');
		}
		else{
			printf("In parent process, evaulating section B: \n");
			helper('B');
		}
		
		if(pid>0){
			pid_t cpid=waitpid(pid,&status,0);
		}
		exit(0);
		
	}
	return 0;
}