#include <stdio.h>
#include <stdlib.h>

struct Node  //Nodes to store the binary tree
{           
    int data;
    struct Node* left;  //stores the reference to left subtree (>root)
    struct Node* right; //stores the reference to right subtree (<root)
};

struct Node* insertion(struct Node* root, int data)
{
    if(root==NULL)  //if reached at the point of insertion, i.e. there is no next path to travel
    {
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));  //Allocating space to the record being inserted  
        temp->data=data;    //creating the record to return it so that it gets linked to the appropriate part of the tree
        temp->left=NULL;    //the record will be inserted at last, so no left or right subtree
        temp->right=NULL;
        return temp;
    }
    if(data<root->data) //if the value to be inserted is lees than that of root, then moving to the left subtree to insert
        root->left=insertion(root->left,data);  //linking the left subtree, so that the inserted record gets linked correctly
    else if(data>root->data)    //if the value to be inserted is more than that of root, then moving to the right subtree to insert
        root->right=insertion(root->right,data);    //linking the right subtree, so that the inserted record gets linked correctly
    else;   //if the data already exists then no need to insert

    return root;    //returning the root of th whole tree

}

struct Node* minNode(struct Node* head)     //function to return the minimum Node in the subtree with root as head
{//The minimum node will be the leftmost node in the subtree, so traversing to the extreme left, till we cant go any further left
    if(head->left==NULL)    //reached the left-most node, as the next left node is null
        return head;
    else
        return minNode(head->left); //traversing left
}
struct Node* deletion(struct Node* root, int x) //function to find and delete a node with a particular value
{
    if(root==NULL)  //if value not found in the appropriate expected position, so returning null
        return NULL;
    if (x<root->data)   //if value to be deleted is less than that at the root, then moving in left subtree
        root->left=deletion(root->left,x);
    else if (x>root->data)  //if value to be deleted is more than that at the root, then moving in right subtree
        root->right=deletion(root->right,x);
    else    //value has been found
    {
        if (root->left!=NULL && root->right!=NULL)  
        { /*if both (left and right) subtrees present, then we need to find the successor to replace the node
            Successor should be greater than all the values in left subtree, but less than all the values in right subtree
            So, we need to find the leftmost node(minimum) in the right subtree. This will satisfy the condition, 
            and we can replace the to-be-deleted node with the chosen node. 
            Then we need to delete that smallest node in the right subtree, as it has been replaced*/
            struct Node* min= minNode(root->right); //finding minnode in right subtree
            root->data=min->data;   //replacing data only
            root->right=deletion(root->right,min->data);    //calling the function again to delete the minimum node in right subtree
        }
        else if (root->left!=NULL)  //if left child present, but not right. So replacing the whole node by the left node. Since whole node is replaced, no need to delete the relaced node
            root=root->left;
        else if (root->right != NULL)   //if left child not present, but right is present. So replacing the whole node by the right node. Since whole node is replaced, no need to delete the relaced node
            root=root->right;
        else    //if no children, then just declare the node as null
            root=NULL;
    }
    return root;    //returning the root of the tree
}

int search(struct Node* root,int x)
{
    if(root==NULL)  //if not found return 0
        return 0;
    if(x==root->data)   //if element found return 1
        return 1;
    else if(x>root->data)
        return search(root->right,x);    //if element greater than node, going to right subtree
    else
        return search(root->left,x);    //if element less than node, going to left sutree
}

void preorder(struct Node* root)    //function for preorder traversal , i.e. Root->Left_Subtree->Right_Subtree
{
    if(root==NULL)  //if no next path is available so returning back
        return ;
    printf("%d, ",root->data);  //printing root
    preorder(root->left);   //moving to left subtree
    preorder(root->right);  //moving to right subtree
}

int main()
{
    int num;
    printf("Enter the no. to insert in BST: "); //1st operation will be insertion only
    scanf("%d",&num);
    struct Node* head=NULL; //Creating the root of the tree, and initialising with NULL
    head=insertion(head,num);   //will return the reference of the fist inserted node
    printf("Enter \n-1->exit \n1->insert \n2->delete \n3->PreOrder Traversal \n4->Search: \n");
    int choice=1;
    while (1)
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        if(choice==1)   //INSERTION 
        {
            printf("Enter number: ");
            scanf("%d",&num);
            head=insertion(head,num);   //returns the reference of the root node
        }
        else if(choice==2)
        {
            printf("Enter Number: ");
            scanf("%d",&num);
            head=deletion(head,num);    //returns the reference of the root node
        }
        else if(choice==3)
        {
            printf("Printing BST In PreOrder (Root,Left,Right): \n");
            preorder(head); //Passing the root of the tree
            printf("\n");
        }
        else if(choice==4)
        {
            int x;
            printf("Enter element to search: ");
            scanf("%d",&x);
            int res=search(head,x);
            if(x==0)
                printf("Element not found\n");
            else
                printf("Element exists in Tree\n");
        }
        else if(choice==-1)
            break;
        else
            printf("Invalid Choice \n");
    }
    return 0;
}