#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node //Nodes for Doubly-Linked List
{           
    int rollno;
    int year;
    char name[25];
    char prog[50];
    struct Node* next;  //pointer to store the address of next linked node
    struct Node* prev;  //pointer to store the address of previous linked node
};


struct Node* insert(struct Node* head, char name[25], char prog[50], int rollno, int year)
{
    struct Node* record=(struct Node*)malloc(sizeof(struct Node));  //Allocating space to create a new node
        strncpy(record->name,name,strcspn(name,"\n"));  //Assigning the data to their respective fields
        strncpy(record->prog,prog,strcspn(prog,"\n"));
        record->rollno=rollno;
        record->year=year;
        record->next=NULL;  //The new node will be the last node, so no next node
        record->prev=NULL;  //Not yet assigned the previous node, becuase we are just creating a node right now
    if(head==NULL)  
    {//If the head is null, then the list is empty, and we return the new record as the first node of the list.
        return record;}
    struct Node* temp=head; 
    /* If we have any next linked nodes, starting from the first node, then
        we traverse till the last node and add the record to the linked list, 
        by linking it to the previous node's next*/
    while(temp->next!=NULL)
        temp=temp->next;
    record->prev=temp;  //linking the current record's prev to the last node
    temp->next= record; //linking the last node to the record
    return head;    //returning the head of the linked list
}

void printRecord(int n, struct Node* head, int order)   
{ /*Prints the linked list in both fashions ,i.e. Reverse and forward:
    For reverse: if order is -1, then first we traverse till the last of the list, then start printing while retracing our calls back until we reach back to the first call, which was made in the starting of the list
    For forward: if order is 0, the we first print the node of the starting pointer and then move to the next node, and this carries till we reach the last node, from where we retact back, but this time printing hsa already been done, so we just return*/
    if(head!=NULL)
    {
        if(order == -1)
            printRecord(n+1,head->next,-1);  //First moving till the last, and then printing while retracing from the last to the head node
        printf("\n Student %d : ",n);
        printf("Name: %s \n",head->name);
        printf("Roll No.: %d \n",head->rollno);
        printf("Year of Enrollment: %d \n",head->year);
        printf("Enrolled Program: %s \n",head->prog);
        if(order == 0)  //if forward printing, then the record has been printed and moving to the next node after that, so in a normal fashion.
            return printRecord(n+1,head->next,0);
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
    struct Node* temp=search(head, roll);   //calling search to find out if the element to be deleted exissts
    if(temp==NULL)  //if record not found
    {
        printf("Record to be deleted not found!\n");
        return head;  //Not deleting anything and returning the original head of the list
    }
    if(temp==head)  //if the record to be deleted is the head, then changing the head to point to the next node
        head=head->next;
    /*To delete the node from anywhere in the linked list, we need to interlink the next and previous nodes of the deleted node, and then delete it
        So, the next pointer of the previous node will now point to the next node of the to-be deleted node
        Also, the prev pointer of the next node, will now point to the previous node of to-be deleted node 
        This willl change the linking of previous and next nodes, but the link from to-be deleted node will also point to them still
        To remove this, the to-be deleted node will be deleted using free(), so that all its fields get erased*/
    if(temp->prev!=NULL)    //for prev.next, prev should not be null
        temp->prev->next=temp->next;
    if(temp->next!=NULL)    //for next.prev, next shoud not be null
        temp->next->prev=temp->prev;
    free(temp); //deleting the to-be deleted node
    return head;    //returning the head of the linked list
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
            head=delete(head,element);  //taking input in head, because if the 1st node is deleted, head should be updated
                printf("Record Deleted \n");
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
            int order=0;
            printf("Enter -1 to print in reverse order and 0 to print in normal order: ");
            scanf("%d",&order);
            printf("-------------------------------------------------------------\nPrinting Records: \n");
            printRecord(1, head, order);
            printf("-------------------------------------------------------------\n");   
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