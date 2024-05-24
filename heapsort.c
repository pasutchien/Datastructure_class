#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define COUNT 10

struct ll_node{
    struct btree_node *ID;
    struct ll_node *next;
    struct ll_node *prev;
};

struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;
struct btree_node
{
    int data;
    struct btree_node *left;
    struct btree_node *right;
};
void add_to_head(struct btree_node* x){
    struct ll_node *p = (struct ll_node *)malloc(sizeof(struct ll_node)); //when malloc you should set the pointer in the block to NULL all the time
    p->prev = NULL;
    p->next = NULL;
    if (head == NULL){
        p->ID=x;
        head = p;
        tail = p;
        length+=1;
        return;
    }
    else{
        p->ID = x;
        p->prev = head;
        head -> next = p;
        head = p;
        length += 1;
    }
}
void add_to_tail(struct btree_node* z){
    struct ll_node *p = (struct ll_node *)malloc(sizeof(struct ll_node));
    p->next = NULL;
    p->prev = NULL;
    if (tail == NULL){
        p->ID=z;
        head = p;
        tail = p;
        length +=1;
        return;
    }
    else{
        p -> ID = z;
        p -> next = tail;
        tail -> prev = p;
        tail = p;
        length += 1;
    }
}
void print_ll()
{
	struct ll_node *p;

	p = head;

	while(p != NULL)
	{
		//print node
		printf("%d ",(p->ID)->data);
		p = p->prev;
	}
	printf("\n");
}
struct btree_node* getfromposition(int index){
    if (head==NULL){
        return NULL;
    }
    struct ll_node*p = head;
    for (int i =0;i<index;i++){
        p = p->prev;
    }
    return p->ID;
}
struct btree_node* add_node (int value){
    struct btree_node* result = (struct btree_node *)malloc(sizeof(struct btree_node));
    result->left = NULL;
    result->right = NULL;
    result -> data = value;
    return result;
}

void reheap (struct btree_node* root){
    if (root->left == NULL && root->right == NULL){ //No children
        return;
    }
    else if(root->left != NULL && root->right != NULL){ //2 children
        struct btree_node *p;
        if(root->left->data > root->right->data){
            p = root->left;
        }
        else{
            p = root->right;
        }
        if(p->data > root->data){
            int temp = root->data;
            root->data = p->data;
            p->data = temp;
            reheap(p);
        }
        else{
            return;
        }
    }
    else{ //1 children
        struct btree_node* p;
        if(root->left != NULL){
            p = root->left;
        }
        else{
            p = root->right;
        }
        if(p->data > root->data){
            int temp = root->data;
            root->data = p ->data;
            p->data = temp;
            reheap(p);
        }
        else{
            return;
        }
    }
}
int heapify(struct btree_node* root){
    if (root == NULL){
        return 1;
    }
    if (heapify(root->left) == 1 && heapify(root->right) == 1)
    {
        reheap(root);
        return 1;
    }
}

struct btree_node* array_to_tree( int num[], int length){
    struct btree_node* root = add_node(num[0]);
    add_to_head(root);
    struct ll_node* p = head;
    
    for (int i = 1; i< length; i ++)
    {
        while(true){
            if(p->ID->left == NULL){
                struct btree_node* new = add_node(num[i]);
                p->ID->left = new;
                add_to_tail(new);
                break;
            }
            else if(p->ID->right == NULL){
                struct btree_node* new = add_node(num[i]);
                p->ID->right = new;
                add_to_tail(new);
                break;
        }
        p = p->prev;
        }
    }
    return root;
}
void print2DUtil(struct btree_node* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}
void print2D(struct btree_node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int* heapsort(int num [], int length ){
    struct btree_node* root = array_to_tree(num,length);
    int* result = (int*)malloc(length * sizeof(int));
    heapify(root);
    for (int i = length-1; i >= 0; i --){
        result[i] = root->data;
        struct btree_node* last = getfromposition(i);
        head->ID->data = last->data;
        last->data = -999;
        reheap(root);
        
        //print_ll();
    }
    return result;
}


int main(void){
    int array[10] = {2,5,-3,-13,6,5,8,10,0,7};
    int size = sizeof(array) / sizeof(array[0]);
    printf("%d\n", size);
    int* result = heapsort(array,10);
    for ( int i = 0; i< 10 ; i++){
        printf("%d ", result[i]);
    }
    printf("\n");

    // Printing the binary tree
    return 0;
}