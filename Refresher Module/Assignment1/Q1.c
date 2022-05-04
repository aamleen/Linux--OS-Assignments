#include <stdio.h>
#include <stdlib.h>

int main(int argv, char const *argc[])
{
    FILE* source=NULL;  //File pointer to store the source of file
    source=fopen(argc[1],"rb"); //opening file in binary rb mode, so that any type of file can be read
    if(source==NULL)    //if the source file was not found
    {
        printf("Error in opening file\n");
        return 0;
    }

    //Calculates the no. of characters in the source file
    fseek(source,0,SEEK_END);   
    size_t size=ftell(source);
    rewind(source); //moving the cursor back to the start of the file

    char* buffer;   //buffer to store the data of the source file
    buffer=(char*)malloc(sizeof(char)*size);    //allocating memory with size as the size of source file
    if(buffer==NULL)    //if buffer was not created properly
    {
        printf("Error in memory allocation to buffer\n");
        return 0;
    }

    size_t buffer_size=fread(buffer,1,size,source); //reading the file, and storing it in buffer. ALso returning the file size
    if(buffer_size != size)     //if file size do not match, there was a problem while reading
    {
        printf("Error in Reading File\n");
        return 0;
    }
    
    FILE* dest=NULL;    //File pointer to store the destination file
    dest = fopen(argc[2],"wb"); //opening the file in wb mode, to write to any type of file
    if(dest==NULL)      //if wrong destination given
    {
        printf("Proper format of output file not given\n");
        return 0;
    }
    fwrite(buffer,sizeof(char),size,dest);  //writing the buffer in the destination file
    //closing both the files
    fclose(dest);   
    fclose(source);
    free(buffer);   //cleaning the buffer
    return 0;
}
