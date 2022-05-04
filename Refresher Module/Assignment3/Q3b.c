#include <stdio.h>
#include <stdlib.h>

//Height Balanced BST is AVL Tree, so implementing that

struct Node     //A node structure with data and height as parameters. Height stores the height/lvel of the node
{           
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};

 int max(int n1, int n2)    //function to return the maximum of 2 values
 {
    if(n1>n2)
        return n1;
    else
        return n2;
 }

 int height(struct Node* temp)    //return the stored height, and if null was passed then height is 0
 {
     if (temp==NULL)
        return 0;
    else
        return temp->height;
 }

struct Node* Rot_Right(struct Node* pivot)  //Rotates the tree to right
{
    /* In right rotate, the height of left subtree is decreased by 1 and that of right subtree is increased by 1
       The left child of the pivot is made the new root*/
    struct Node* mid=(struct Node*)malloc(sizeof(struct Node));
    struct Node* mid_right=(struct Node*)malloc(sizeof(struct Node));
    mid=pivot->left;    //left child of current root
    mid_right=mid->right;   //right subtree of the left child of root(mid)
    mid->right=pivot;   //left child of the root is made the new root, and previous root is made its right child
    pivot->left=mid_right;  //the right subtree of mid is now attached to the left of previous root
    pivot->height=1+max(height(pivot->left),height(pivot->right));  //updating the height of previous root
    mid->height=1+max(height(mid->left),height(mid->right));    //updating the height of new root
    return mid; //returning the new root
}

struct Node* Rot_Left(struct Node* pivot)
{ /*In left rotate, the height of left subtree is increased by 1 and that of right subtree is decreased by 1
    The right child of the pivot is made the new root*/
    struct Node* mid=(struct Node*)malloc(sizeof(struct Node));
    struct Node* mid_left=(struct Node*)malloc(sizeof(struct Node));
    mid=pivot->right;   //right child of current root
    mid_left=mid->left; //left subtree of the right child of root(root)
    mid->left=pivot;    //right child of the root is made the new root, and previous root is made its left child
    pivot->right=mid_left;  //the left subtree of mid is now attached to the right of the previous root
    pivot->height=1+max(height(pivot->left),height(pivot->right));  //updating the height of previous tree
    mid->height=1+max(height(mid->left),height(mid->right));    //updating the height of new root
    return mid; //returning the new root
}

int balance(struct Node* root)      //gives the difference between heights of left subtree and right subtree, to balance the side whichever is shorter
{
    if(root=NULL)       //if the root is itself null, then no left or right subtree so difference is 0
        return 0;
    return height(root->left)-height(root->right);
}

struct Node* insert(struct Node* root, int x)
{
    if(root==NULL)  //No further subtree present, so inserting after creating a node
    {
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));    //creating a node and inserting data
        temp->data=x;
        temp->height=1;
        temp->left=NULL;
        temp->right=NULL;
        return temp;
    }
    if(root->data==x)   //if the value is already present no need to insert
        return root;
    else if(root->data > x)   //if the value to be inserted is smaller than at the current root, so moving in left subtree
        root->left=insert(root->left,x);    //moving in left subtre and also linking them with their parents
    else                //if the value to be inserted is greater than at the current root, so moving in right subtree
        root->right=insert(root->right,x);      //moving in right subtree and also linking them with their parents
    
    root->height=1+max(height(root->right),height(root->left));     //Increasing the height of each parent in the path of inserting, as inserting a new node will increase the height of every parent by 1 
    printf("Here");
    //Finding if the tree is not balanced and further balancing it
    int bal=balance(root);      //Finding the balancing factor
    if(bal>1)   //if the tree is unbalanced and left subtree is bigger
    {
        if(x<root->left->data)  //if inserted element is in the left of left subtree, so just rotating the tree to right from current imbalaced node will balance the tree
            return Rot_Right(root);
        if(x>root->left->data)   
        {/*if inserted element is in the right of left subtree,
         then first we balance the left subtree by rotating it left, 
         and then we balance the current imbalanced node by rotating it right*/
            root->left=Rot_Left(root->left);    //Rotating the left subtree to left
            return Rot_Right(root);     //Rotating the tree at current node to right and returning the new root
        }
    }
    if(bal<-1)   //if the tree is unbalanced and right subtree is bigger
    {
        if(x>root->right->data)  
        {/*if inserted element is in the right of right subtree, 
        so just rotating the tree to left from current imbalaced node will balance the tree*/
            return Rot_Left(root);
        }
        if(x<root->left->data)   
        {/*if inserted element is in the left of right subtree,
         then first we balance the right subtree by rotating it right, 
         and then we balance the current imbalanced node by rotating it left*/
            root->right=Rot_Right(root->right);    //Rotating the left subtree to left
            return Rot_Left(root);     //Rotating the tree at current node to left and returning the new root
        }
    }
    return root;
}

struct Node* delete(struct Node* root, int x)
{
    if(root==NULL)      //value to be deleted is not found
        return root;
    if(x<root->data)    //Traversing in left subtree to find the value to be deleted 
        root->left=delete(root->left,x);
    else if(x>root->data)   //Traversing in right subtree
        root->right=delete(root->right,x);
    else    //element to be deleted found
    {
        if(root->left==NULL && root->right==NULL)   //if element has no children, simply delete it
        {
            root=NULL;
            return root;
        }
        if(root->right==NULL)   //element has only left children
            root=root->left;  //replacing the element by left child
        else    
        {/*either both children present or only the right child
           then the parent (to be deleted) will be replaced by the smallest element in the right subtree
           so finding and replacing by the leftmost leaf of the right subtree from current node*/
            struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
            temp=root->right;
            while (!(temp==NULL || root->left==NULL))
                temp=temp->left;
            root->data=temp->data;  //replacing the value at root by smallest in the right subtree
            root->right=delete(root->right,root->data);   //deleting the (smallest) leftmost leaf of right subtree
        }
    }
    root->height=1+max(height(root->left),height(root->right)); //Updating the height of current node

    
    int bal=balance(root);  //Calculating the balance factor

    if(bal>1)       //Left-Subtree is greater than Right
    {
        if(balance(root->left)>=0)  
        { /*Left of left subtree is either greater than or equal to its right sibling,   Left-Left case
            so just balancing the tree, by rotating the whole tree at current node to right to counter the bigger left side
            Then returning the updated root node*/
            return Rot_Right(root);
        }
        else
        { /*right subtree of left child is greater than left side,  Left-Right Case
            so balancing the subtree first by rotating the right part to left with left child as pivot,
            Then balancing the whole tree by rotating the whole tree to right with root as pivot,
            Then returning the updated root node.*/ 
            root->left=Rot_Left(root->left);
            return Rot_Right(root);
        }
    }
    if(bal<-1)  //Right sub-tree is greater
    {
        if(balance(root->right)<=0)  
        { /*Right of right subtree is either greater than or equal to its left sibling,   Right-Right case
            so just balancing the tree, by rotating the whole tree at current node to left to counter the bigger right side
            Then returning the updated root node*/
            return Rot_Left(root);
        }
        else
        { /*left subtree of right child is greater than right side,  Right-Left Case
            so balancing the subtree first by rotating the left part to right with right child as pivot,
            Then balancing the whole tree by rotating the whole tree to left with root as pivot,
            Then returning the updated root node.*/ 
            root->right=Rot_Right(root->right);
            return Rot_Left(root);
        }
    }
    return root;
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

void preorder(struct Node* root)    //Traversing in preorder fashion, root->left->right
{
    if(root==NULL)
        return ;
    printf("%d, ",root->data);  //printing the current nodes
    preorder(root->left);   //moving to left subtree
    preorder(root->right);  //moving to right subtree
}

int main()
{
    int num;
    printf("Enter the no. to insert in BST: ");
    scanf("%d",&num);
    struct Node* head=NULL;
    head=insert(head,num);
    printf("Enter \n-1->exit \n1->insert \n2->delete \n3->PreOrder Traversal \n4->Search: \n");
    int choice=1;
    while (1)   //always true loop, till user wants
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("Enter number: ");
            scanf("%d",&num);
            printf("Here");
            head=insert(head,num);
        }
        else if(choice==2)
        {
            printf("Enter Number: ");
            scanf("%d",&num);
            if(search(head,num)==1) //checking if the element is present in tree
            {
                struct Node* temp=delete(head,num);
                head=temp;
            }
            else
                printf("Element to be deleted not in Tree \n");
        }
        else if(choice==3)
        {
            printf("Printing BST In PreOrder (Root,Left,Right): \n");
            preorder(head);
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