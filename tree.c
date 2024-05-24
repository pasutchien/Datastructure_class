#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define COUNT 10
struct btree_node
{
    int data;
    struct btree_node *left;
    struct btree_node *right;
};
//linked list
struct ll_node{
    struct btree_node *ID;
    struct ll_node *next;
    struct ll_node *prev;
};

struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;


void add_to_head(struct btree_node* t_node){
    struct ll_node *p = (struct ll_node *)malloc(sizeof(struct ll_node)); //when malloc you should set the pointer in the block to NULL all the time
    p->prev = NULL;
    p->next = NULL;
    if (head == NULL){
        p->ID=t_node;
        head = p;
        tail = p;
        length+=1;
        return;
    }
    else{
        p->ID = t_node;
        p->prev = head;
        head -> next = p;
        head = p;
        length += 1;
    }
}
void add_to_tail(struct btree_node* t_node){
    struct ll_node *p = (struct ll_node *)malloc(sizeof(struct ll_node));
    p->next = NULL;
    p->prev = NULL;
    if (tail == NULL){
        p->ID=t_node;
        head = p;
        tail = p;
        length +=1;
        return;
    }
    else{
        p -> ID = t_node;
        p -> next = tail;
        tail -> prev = p;
        tail = p;
        length += 1;
    }
}

void remove_from_head(){
    if (head != NULL){
        if(length > 1){
            head->prev->next = NULL;
            head = head->prev;
            length -= 1;
        }
        else{
            head = NULL;
            tail = NULL;
            length = 0;
        }
    }
}
void remove_from_tail(){
    if (tail != NULL){
        if(length>1){
            tail->next->prev = NULL;
            tail = tail->next;
            length -= 1;
        }
        else{
            head = NULL;
            tail = NULL;
            length = 0;
        }
    }
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
void remove_from_position(int index){
    if (index == 0){
        remove_from_head();
        return;
    }
    else if (index == length - 1){
        remove_from_tail();
        return;
    }
    else if(index < 0 || index >= length){
        return;
    }
    else{
        struct ll_node *p = head;
        for (int i = 0; i < index ; i ++){
            p = p->prev;
        }
        p->next->prev = p->prev;
        p->prev->next = p->next;
        length -= 1;
        }
        return;
}
void print_ll()
{
	struct ll_node *p;

	p = head;

	while(p != NULL)
	{
		//print node
		printf("%d ",p->ID->data);
		p = p->prev;
	}
	printf("\n");
}
void delete_whole_list()
{
	struct ll_node *to_free;
    length = 0;
	if(head == NULL)
	{
		return;
	}
	while(head != NULL)
	{
		to_free = head;
		head = head->prev;
		free(to_free);
        to_free = NULL;
	}
    tail = NULL;
}

//tree



int sum_btree(struct btree_node *root)
{
    if(root->left == NULL & root->right == NULL){
        return root->data;
    }
    return root->data + sum_btree(root->left) + sum_btree(root->right);
    
}

int count_node(struct btree_node *root){
    if (root == NULL)
    {
        return 0;
    }
    return 1 + count_node(root->left) + count_node(root->right);
}

int count_level(struct btree_node *root){
    if (root == NULL){
        return 0;
    }
    if(count_level(root->left) > count_level(root->right)){
        return 1+count_level(root->left);
    }
    else{
        return 1+count_level(root->right);
    }
}
void bottom_of_tree(struct btree_node* root){
    if(root->left == NULL && root->right == NULL){
        printf("%d, ", root->data);
        return;
    }
    if(root->left != NULL){
        bottom_of_tree(root->left);
    }
    if(root->right != NULL)
    {
        bottom_of_tree(root->right);
}
}
struct btree_node* add_node (int value){
    struct btree_node* result = (struct btree_node *)malloc(sizeof(struct btree_node));
    result->left = NULL;
    result->right = NULL;
    result -> data = value;
    return result;
}
struct btree_node* appendtree (struct btree_node *lefttree, struct btree_node *righttree){
    struct btree_node* root = (struct btree_node *)malloc(sizeof(struct btree_node));
    root->data = 0;
    root -> left = lefttree;
    root -> right = righttree;
    return root;
}
struct btree_node* breadth_search (struct btree_node *root, int value){
    add_to_head(root);
    struct btree_node *p;
    while (head != NULL){
        p = tail->ID;

        if (p-> data == value){
            delete_whole_list();
            return p;
        }
        if(p->left != NULL){
            add_to_head(p->left);
        }
        if(p->right != NULL){
            add_to_head(p->right);
        }
        
        remove_from_tail();

    }
    delete_whole_list();
    return NULL;
    
}
struct btree_node *x = NULL;
// struct btree_node * depth_search (struct btree_node *root, int value){
//     if (root->data == value){
//         x = root;
//     }
//     if(root->left !=NULL){
//     depth_search(root -> left, value);
//     }
//     if(root->right !=NULL){
//     depth_search(root->right, value);
//     }
//     return x;
// }
struct btree_node * depth_search (struct btree_node *root, int value) {
    if (root == NULL) {
        return NULL; // Base case: reached a leaf node without finding the value
    }

    if (root->data == value) {
        return root; // Found the value, return the node
    }

    // Recursively search in the left subtree
    struct btree_node *left_result = depth_search(root->left, value);
    if (left_result != NULL) {
        return left_result; // Value found in the left subtree, propagate the result up
    }

    // Recursively search in the right subtree
    struct btree_node *right_result = depth_search(root->right, value);
    if (right_result != NULL) {
        return right_result; // Value found in the right subtree, propagate the result up
    }

    return NULL; // Value not found in the subtree rooted at 'root'
}
int all_combinations_checked (struct btree_node *root) {
    if (root == NULL) {
        return 1; // Base case: reached a leaf node without finding the value
    }

    if ((root->left != NULL && root->right == NULL)|| (root->left ==NULL && root->right != NULL)) {
        return 0; // Found the value, return the node
    }

    // Recursively search in the left subtree
    int left_result = all_combinations_checked(root->left);
    if (left_result == 0) {
        return left_result; // Value found in the left subtree, propagate the result up
    }

    // Recursively search in the right subtree
    int right_result = all_combinations_checked(root->right);
    if (right_result == 0) {
        return right_result; // Value found in the right subtree, propagate the result up
    }

    return 1; // Value not found in the subtree rooted at 'root'
}
struct btree_node *dfs(struct btree_node *root, int value)
{
    if(root==NULL)
        return NULL;
    if(root->data == value){
        return root;}
    struct btree_node *found_l = dfs(root->left, value);
    if(found_l != NULL){
        return found_l;}
    else{
        return dfs(root->right, value);}
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
void reheap(struct btree_node* root){
    if(root ->left != NULL && root->right !=NULL){
        if (root-> data < root->left->data || root->data < root->right->data){
            if(root->left->data > root->right->data){
                int temp = root->left->data;
                root->left->data = root->data;
                root->data = temp;
            }
            else{
                int temp2 = root->right->data;
                root->right->data = root->data;
                root->data = temp2;
            }
        }
    }
    else if (root -> left != NULL && root->right == NULL){
        if(root->left->data > root -> data){
                int temp3 = root->left->data;
                root->left->data = root->data;
                root->data = temp3;
        }
    }
    else if (root-> left == NULL && root->right !=NULL){
        if(root->right->data > root ->data){
            int temp4 = root->right->data;
            root->right->data = root->data;
            root->data = temp4;
        }
    }
}

void heapify(struct btree_node* root){
    //construct linked list for all node
    struct btree_node* p = (struct btree_node *)malloc(sizeof(struct btree_node));
    
    p = root;
    add_to_head(p);
    struct ll_node *p2 = head;

    while (true){
        if(p->left != NULL){
            add_to_head(p->left);
        }
        if(p->right != NULL){
            add_to_head(p->right);
        }
        if (p2 == head){
            break;
        }
        p2 = p2->next;
        p = p2->ID;
    }
    //constructing linked list is done
    //loop from head to tail which is bottom to top
    struct ll_node *p3 = head;
    while (p3 != NULL){
        reheap(p3->ID);
        p3 = p3->prev;
    }
    delete_whole_list();
    if(root->left != NULL){
    heapify(root->left);
    }
    if(root->right != NULL){
    heapify(root->right);
    }
}

void heap_to_ll (struct btree_node *root){
    struct btree_node* p = (struct btree_node *)malloc(sizeof(struct btree_node));
    
    p = root;
    add_to_tail(p);
    struct ll_node *p2 = tail;

    while (true){

        if(p->left != NULL){
            add_to_tail(p->left);
        }
        if(p->right != NULL){
            add_to_tail(p->right);
        }
        if (p2 == tail){
            break;
        }
        p2 = p2->prev;
        p = p2->ID;
    }    
}
struct ll_node * swap(int i, int j){
    struct ll_node *p = head;
    struct ll_node *p2 = head;
    for (int x = 0; x < i; x ++){
        p =  p->prev;
    }
    for(int y = 0 ; y < j ; y++){
        p2 = p2->prev;
    }
    if (i==j){
        return p;
    }

    int temp = p->ID->data;
    p->ID->data = p2->ID->data;
    p2->ID->data = temp;
    return p2;
}
void heapsort(struct btree_node* root)
{
    heapify(root);
    print2D(root);
    heap_to_ll(root);
    int sorted[length]; 
    int tmp = length-1;
    for (int i = tmp ; i >= 0 ; i --){
        
        struct ll_node * x = swap(0,i);

        if(x != NULL){
        sorted[i] = x->ID->data;
        x->ID->data = -999;

        x ->ID = NULL;

        remove_from_tail();


        }

        struct ll_node * p = head;
        for (int j = 0 ; (2*j)+1 < length; j++){
        reheap(p->ID);
        p = p->prev;
        }

    }
    for(int i = 0 ; i < tmp+1 ; i ++){
        printf("%d, ", sorted[i]);
    }
    print2D(root);
}

//RECURSIVE PRINTING TREE PRACTICE
void printPostorder(struct btree_node* node) {
    if (node == NULL)
        return;
 
    // first recur on left subtree
    printPostorder(node->left);
 
    // then recur on right subtree
    printPostorder(node->right);
 
    // now deal with the node
    printf("%d ", node->data);
}
int print_postorder(struct btree_node* root){
    if(root==NULL){
        return 1;
    }

    if(print_postorder(root->left) == 1 && print_postorder(root->right)== 1){
        printf("%d, ",root->data);
        return 1;
    }

}
void printrighttoleft(struct ll_node *p);
void printlefttoright(struct ll_node* p){
    if(p == NULL){
        return;
    }
    int l = length;
    int i = length-1;
    while(i >= 0){
        struct btree_node* root = getfromposition(i);
        if(root->left != NULL){
            printf("%d, ", root->left->data);
            add_to_tail(root->left);
        }
        if(root->right != NULL){
            printf("%d, ", root->right->data);
            add_to_tail(root->right);
        }
        remove_from_position(i);
        i--;
    }
    printrighttoleft(head);
}
void printrighttoleft(struct ll_node *p){
    if(p==NULL){
        return;
    }
    int l = length;
    int i = length-1;
    while(i>=0){
        struct btree_node* root = getfromposition(i);
        if(root->right != NULL){
            printf("%d, ", root->right->data);
            add_to_tail(root->right);
        }
        if(root->left != NULL){
            printf("%d, ", root->left->data);
            add_to_tail(root->left);
        }
        remove_from_position(i);
        i--;
    }
    printlefttoright(head);        
}
void printspiral(struct btree_node* root){
    printf("%d, ", root->data);
    add_to_head(root);
    printlefttoright(head);
}
void printinorder(struct btree_node* root){
    if(root == NULL){
        return;
    }
    printinorder(root->left);
    printf("%d, ", root->data);
    printinorder(root->right);
}


int main (void){
    struct btree_node* root1 = add_node(1);
    root1->left = add_node(2);
    root1->right = add_node(8);
    // root1->right->left = add_node(6);
    // root1->right->right = add_node(9);
    root1->left->left = add_node(4);
    root1->left->left->left = add_node(5);
    root1->left->left->right = add_node(3);
    root1->left->right = add_node(7);
    // root1->left->right = add_node(5);
    struct btree_node * root2 = add_node(7);
    root2 ->left = add_node(8);
    root2->left->left = add_node(4);
    //root2->left->right = add_node(5);
    root2 -> right = add_node(9);
    root2 ->right ->left = add_node(12);
    root2->right->right = add_node(13);
    struct btree_node *root3 = appendtree(root1,root2);
    print2D(root1);
    // print_postorder(root3);
    // printPostorder(root3);
    bottom_of_tree(root1);
    //int x = count_level(root3);
    //printf("%d\n",x);
    //bottom_of_tree(root3);
    // int x = sum_btree(root3);
    // int count = count_node(root3);
    // int level = count_level(root3);
    // printf("level = %d\n", level);
    // printf("counted = %d\n", count);
    // printf("sum = %d\n", x);
    // print2D(root3);
    // struct btree_node*test = dfs(root3,13);
    // print2D(test);
    // struct btree_node *answer = depth_search(root3,0);
    // if (answer == NULL){ 
    //     printf("invalid number\n");
    // }
    // else{
    //     printf("%d\n", answer->data);
    //     print_ll();
    // }

    // struct btree_node* root4 = add_node(1);


}

//learn more on how to use malloc and free 
//and learn how to detect segmentation fault easily