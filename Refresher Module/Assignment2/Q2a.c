#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node  //Nodes for Linked List
{           
    int rollno;
    int year;
    char name[25];
    char prog[50];
    struct Node* next;  //pointer to the next node, links the linked list
};


struct Node* insert(struct Node* head, char name[25], char prog[50], int rollno, int year)  //function to insert a node at the end of the linked list
{
    struct Node* record=(struct Node*)malloc(sizeof(struct Node));  //Allocating space to create a new node
        strncpy(record->name,name,strcspn(name,"\n"));  //Assigning the data to their respective fields
        strncpy(record->prog,prog,strcspn(prog,"\n"));
        record->rollno=rollno;
        record->year=year;
        record->next=NULL;  //The new node will be the last node, so no next node
    if(head==NULL)  
    {//If the head is null, then the list is empty, and we return the new record as the first node of the list.
        return record;}
    struct Node* temp=head; 
    /* If we have any next linked nodes, starting from the first node, then
        we traverse till the last node and add the record to the linked list, 
        by linking it to the previous node's next*/
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next= record; //Linking the last node to the record
    return head;    //returning the head of the linked list

}

void printRecord(int n, struct Node* head)  //Traverses the linked list and prints each entry in the linked order.
{
    if(head!=NULL)  //Recursiverly calling each Node till we encounter a NULL, which means the previous node was the last, and now we can return back
    {
        printf("\n Student %d : ",n);
        printf("Name: %s \n",head->name);
        printf("Roll No.: %d \n",head->rollno);
        printf("Year of Enrollment: %d \n",head->year);
        printf("Enrolled Program: %s \n",head->prog);
        return printRecord(n+1,head->next);
    }
}

struct Node* search(struct Node* head, int roll)
{
    if(head==NULL)  //previous node was the last node, and still the element was not found so element not in list
        return NULL;
    if(head->rollno==roll)  //if the element is found, returning that node (head will be changed recursively to point at each node)
        return head;
    return search(head->next,roll); //recursively calling and returning the Node, till the last node is encountered
}

struct Node* delete(struct Node* head, int roll)
{
    struct Node* temp=search(head, roll);   //Will store that if the element is present, and if yes, then its node
    if(temp==NULL)  //if element not present
        return NULL;
    if(temp==head)  //if searched node is the head
    {
        head=temp->next;    //head will now be the second node in the list
        free(temp);
        return head;    
    }
    temp=head;
    struct Node* prev=head; //to store the previous node to the one to be deleted
    while(temp!=NULL)
    {
        if(temp->rollno==roll)  //if element found
            break;
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL)  //if evaluated till the last node, but element was not found
        return head;
    prev->next=temp->next;  //if node was found, then linking its previous node to the searched node's next node
    free(temp);
    return head;    //returning the head of the list
}

int main()
{
    char name[25];  //stores the name
    char prog[50];  //stores the enrolled prog
    int rollNo, year;
    int choice=1;    //Stores the choice if the user for a particular operation, initialized 1 to enter the loop
    struct Node* head=NULL; //will hold the start pointer of linked list
    printf("Enter the respective no. to perform the respective operation: \n-1->EXIT  \n1->INSERT \n2->DELETE \n3->SEARCH DETAILS \n4->PRINT LIST\n");
    while (choice!=-1)  //choice will be -1 to exit
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();  
        /*There was some issue that after taking int input from scanf, some characters (\n) remain on screen and cause problem in the next input, 
        so getchar() will clear the stdin for the next input by absorbing the remaining characters*/
        if(choice==1)   //Insertion
        {
            printf("Enter name, enrollment program, rollNo. and year of joining (respectively): \n");
            fgets(name,25,stdin);
            fgets(prog,50,stdin);
            scanf("%d",&rollNo);
            scanf("%d",&year);
            getchar();  //Same reasons as mentioned above
            head=insert(head,name,prog,rollNo,year);
        }
        else if(choice==2)  //Deletion
        {
            int element;
            printf("Enter the roll no. to delete its records: ");
            scanf("%d",&element);
            if(search(head,element)==NULL)  //if element to be deleted not present
                printf("Record to be deleted does not exist!! \n");
            else
            {
                head=delete(head,element);  //taking input in head, because if the 1st node is deleted, head should be updated
                printf("Record Deleted \n");
            }
        }
        else if(choice==3)  //Search
        {
            int element;
            printf("Enter the roll no. to search its records: ");
            scanf("%d",&element);
            struct Node* temp=search(head,element);     //will store the searched node if found
            if(search(head,element)==NULL)  //if element was not found
                printf("Record does not exist!! \n");
            else
            {
                printf("Record found: \n");
                printf("Roll No.: %d\nName: %s\nProgram Enrolled: %s\nYear Enrolled: %d\n",temp->rollno,temp->name,temp->prog,temp->year);
            }
        }
        else if(choice==4)  //Print the linked list
        {
            printf("Printing Records: \n");
            printRecord(1, head);   //Passing 1 for student 1
        }
        else if(choice==-1)
        {
            printf("Exited Successfully\n");
            break;
        }
        else
            printf("Invalid Choice, Try again\n");
    }
    return 0;

}