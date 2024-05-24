#include <stdio.h>
#include <stdlib.h>
#define STRAIGHT 0
#define LEFT 1
#define RIGHT 2

//linked list

struct path_node{
int score;
int step;
int totalscore;
struct path_node *left;
struct path_node *right;
struct path_node *straight;
};
struct path_node *root = NULL;
struct path_node *current = NULL;

struct ll_node{
    struct path_node *ID;
    struct ll_node *next;
    struct ll_node *prev;
};

struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;

void add_to_head(struct path_node* x){
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


void add_to_tail(struct path_node* z){
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
void remove_from_head(){
    if (head != NULL){
        if(length > 1){
            head->prev->next = NULL;
            head = head->prev;
            length -= 1;
        }
        else if (length == 1){
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


void path_choice (struct path_node*root, int step, int direction, int score){
    struct path_node *new = (struct path_node *)malloc(sizeof(struct path_node));
    new -> step = step;
    new -> score = score;
    new -> left = NULL;
    new -> right = NULL;
    new -> straight = NULL;    

    if (step == 1 ){
        new -> totalscore = score;
        if (direction == LEFT){
            root -> left = new;            
        } 
        if (direction == RIGHT){
            root -> right = new;
        }
        if (direction == STRAIGHT){
            root -> straight = new;

        }
        return;
    }
    if (root->step == step-1){
        new->totalscore = root->totalscore + score;

        if (direction == LEFT){
            root -> left = new;
        } 
        if (direction == RIGHT){
            root -> right = new;
        }
        if (direction == STRAIGHT){
            root -> straight = new;
        }
        return;
    }
    if(root->left !=NULL){
    path_choice(root -> left, step, direction, score);
    }
    if(root->right !=NULL){
    path_choice(root->right, step, direction, score);
    }
    if(root->straight !=NULL){
    path_choice(root->straight, step, direction, score);

    }
}

void path_restart(){
    root = (struct path_node *)malloc(sizeof(struct path_node));
    root->step = 0;
    root-> left = NULL;
    root-> straight = NULL;
    root->right = NULL;
    current = root;
}
int step (int score){
    add_to_head(root);
    struct path_node *p = (struct path_node *)malloc(sizeof(struct path_node));
    p = root;
    while (head != NULL){
        if (p-> totalscore == score){
            delete_whole_list();
            return p->step;
            free(p);
        }
        if(p->left != NULL){
            add_to_head(p->left);
        }
        if(p->right != NULL){
            add_to_head(p->right);
        }
        if(p->straight != NULL){
            add_to_head(p->straight);
        }
        
        remove_from_tail();
        if (tail == NULL){
            return 0;
        }
        p = tail->ID;
    }
    delete_whole_list();
    return 0;

    free(p);
}
int main (void){
    path_restart();
    path_choice(root,1, STRAIGHT, 0);
    path_choice(root,2, LEFT, 1);
    path_choice(root,2, STRAIGHT, 1);
    path_choice(root,2, RIGHT, 2);
    path_choice(root,3, STRAIGHT, 1);
    path_choice(root,3, RIGHT, 2);
    path_choice(root,4, RIGHT, 3);
    path_choice(root,3, LEFT, 5);
    int x = step(2);
    printf("%d\n", x);
}