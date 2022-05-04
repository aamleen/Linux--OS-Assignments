#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node   //Nodes to implement stacks and queues using linked list
{           
    int rollno;
    int year;
    char name[25];
    char prog[50];
    struct Node* next;
};

//--------------STACK IMPLEMENTATION----------------------

struct Node* push(struct Node* head, char name[25], char prog[50], int rollno, int year)
{ //Inserting a record in the front of the linked list, and updating the head pointer of the list
    struct Node* record=(struct Node*)malloc(sizeof(struct Node));
        strncpy(record->name,name,strcspn(name,"\n"));
        strncpy(record->prog,prog,strcspn(prog,"\n"));
        record->rollno=rollno;
        record->year=year;
        record->next=NULL;
    if(head==NULL)  //if stack is empty, then returning the record as the 1st entry
    {
        head=record;
        return head;
    }
    record->next=head;  //Inserting a node before the head, and linking its next pointer to the current head node
    head=record;    //Making the inserted node as the head
    return head;    //returning the new head
}

struct Node* pop(struct Node* head)
{ //For stack implementation, pop needs to delete the head of the linkedlist and make the next node as the new head
    if(head==NULL)  //If stackunderflow, nothing can be deleted
    {
        printf("Can not be deleted in empty stack \n");
        return head;    //returning the head of the original head only
    }
    struct Node* temp=head->next;   //if atleast 1 record present, then changing the head to its next node (might be NULL)
    free(head); //deleting the current head
    return temp;    //returning head->next as new head
}


//-------------------------QUEUE IMPLEMENTATION------------------------------

struct Node* enqueue(struct Node* head, char name[25], char prog[50], int rollno, int year) //insertion in queue
{ /*To enqueue, inserting the new record before the head of the linked list, and then linking it with the current head
    Then making the inserted record as the new head*/
    //Same implementation as pop(), so refer there for better comments understanding
    struct Node* record=(struct Node*)malloc(sizeof(struct Node));
        strncpy(record->name,name,strcspn(name,"\n"));
        strncpy(record->prog,prog,strcspn(prog,"\n"));
        record->rollno=rollno;
        record->year=year;
        record->next=NULL;
    if(head==NULL)
    {
        head=record;
        return head;
    }
    record->next=head;
    head=record;
    return head;
}

struct Node* dequeue(struct Node* head)
{/*To dequeue(delete a node): traversing to the last node of the list, and deleting the record from there*/
    if(head==NULL)  //if queue empty
    {
        printf("Can not dequeue in empty queue \n");
        return head;
    }
    if(head->next==NULL)    //If only 1 record present in the queue, so after deleting it will become empty, so returning NULL
    {
        free(head);
        return NULL;
    }
    //Creating a temporary pointer temp, to traverse to the last of the linked list (i.e. when the node will be null)
    struct Node* temp=head;
    struct Node* prev=head; //to store the previous node to the one to be deleted
    while(temp->next!=NULL)
    {
        prev=temp;
        temp=temp->next;
    }
    prev->next=temp->next;  //Delinking the last nodes, i.e. the 2nd last node is now made the last node
    free(temp); //deleting the last node
    return head;    //returning the head of the list
}

struct Node* search(struct Node* head, int roll)
{
    if(head==NULL)  //previous node was the last node, and still the element was not found so element not in list
        return NULL;
    if(head->rollno==roll)  //if the element is found, returning that node (head will be changed recursively to point at each node)
        return head;
    return search(head->next,roll); //recursively calling and returning the Node, till the last node is encountered
}

void printRecord(int n, struct Node* head)  //function to print both queue or stack
{
    if(head!=NULL)
    {
        printf("\n Student %d : ",n);
        printf("Name: %s \n",head->name);
        printf("Roll No.: %d \n",head->rollno);
        printf("Year of Enrollment: %d \n",head->year);
        printf("Enrolled Program: %s \n",head->prog);
        return printRecord(n+1,head->next);
    }
}

struct Node* input(struct Node* head,int cho)   
{/*function to take input of data from the user, then inserting it in:
    Queue (enqueue): if cho = 1
    Stack (push): if cho = 0*/  
    char name[25];
    char prog[50];
    int rollNo, year;
    printf("Enter name, enrollment program, rollNo. and year of joining (respectively): \n");
    getchar();
    fgets(name,25,stdin);
    fgets(prog,50,stdin);
    scanf("%d",&rollNo);
    scanf("%d",&year);
    //getchar(); 
    if(cho==0)
        head=push(head,name,prog,rollNo,year);
    else
        head=enqueue(head,name,prog,rollNo,year);
    return head;    //returning the head of the queue or stack after inserting it
}

int main()
{
    int cho,choice;
    printf("Enter 1 for QUEUE and 0 STACK: ");
    scanf("%d",&cho);
    if(cho==0)  //STACK
    {
        printf("Enter the no. as per choice:\n-1)Exit \n0)Push \n1)Pop \n2)Display \n3) Search Record \n");
        choice=0;   //initializing to 0, so that it can enter the while loop atleast once
        struct Node* top=NULL;  //top will hold the reference to the starting of the linked list, where both insertion and deletion happen
        while(choice!=-1)
        {
            printf("Enter choice:");
            scanf("%d",&choice);
            switch (choice) //swaitch case that will match accordingly
            {
            case 0:
                top=input(top,0);   //calling function to take input. Passing 0 to tell that it is a stack
                break;
            case 1:
                top=pop(top);   //poping (deleting)
                break;
            case 2:
                printf("Printing the Stack \n");
                printRecord(1,top); //passing 1 for 1st record
                break;
            case 3:
                {int roll=-1;
                printf("Enter roll no. to find the records:");
                scanf("%d",&roll);
                struct Node* temp=search(top,roll);  //will store the searched node if found
                if(temp==NULL)  //if element not found
                    printf("No record found!!\n");
                else
                {
                    printf("Record found: \n");
                    printf("Roll No.: %d\nName: %s\nProgram Enrolled: %s\nYear Enrolled: %d\n",temp->rollno,temp->name,temp->prog,temp->year);
                }
                break;}
            case -1:
                    printf("Exited succefully \n");
                    break;
            default:
                printf("Invalid Choice\n");
                break;
            }
        }//Switch ends
    }//stack ends
    else if(cho==1) //QUEUE
    {
        printf("Enter the no. as per choice: \n-1)Exit \n0)Enqueue \n1)Dequeue \n2)Display \n3) Search Records\n ");
        choice=0;
        struct Node* front=NULL;    //points to the starting of the queue, where insertion will happen
        while(choice!=-1)
        {
            printf("Enter choice:");
            scanf("%d",&choice);
            switch (choice)
            {
            case 0:
                front=input(front,1);   //passing 1 to tell its queue
                break;
            case 1:
                front=dequeue(front);   //deleting from the last of the queue
                break;
            case 2:
                printf("Printing the Queue \n");
                printRecord(1,front);
                break;
            case 3:
                {int roll=-1;
                printf("Enter roll no. to find the records:");
                scanf("%d",&roll);
                struct Node* temp=search(front,roll);  //will store the searched node if found
                if(temp==NULL)  //if element not found
                    printf("No record found!!\n");
                else
                {
                    printf("Record found: \n");
                    printf("Roll No.: %d\nName: %s\nProgram Enrolled: %s\nYear Enrolled: %d\n",temp->rollno,temp->name,temp->prog,temp->year);
                }
                break;
                }
            case -1:
                    printf("Exited succefully \n");
                    break;
            default:
                printf("Invalid Choice\n");
                break;
            }
        }
    }
    else    //Neither stack nor queue
        printf("Invalid Choice!!\n");

    return 0;

}