#include <stdio.h>
#include <stdlib.h>

struct ll_node{
    unsigned int ID;
    struct ll_node *next;
    struct ll_node *prev;
};

struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;

void add_to_head(unsigned int x){
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

int id_on_list(unsigned int y){
    struct ll_node *p  = head;
    while (p != NULL){
        if(p->ID == y){
            return 0; //data is found
        }
        p = p->prev;
    }
    return 1; //no data
}

void add_to_tail(unsigned int z){
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
void add_to_position(int index, unsigned int x){
    if(index == 0){
        add_to_head(x);
        return;
    }
    else if(index == length){
        add_to_tail(x);
        return;
    }
    else if(index <0 || index > length){
        return;
    }
    else{
        struct ll_node *p = head;

        for (int i = 0; i < index ; i ++){
            p = p->prev;
        }
        struct ll_node *q = p->next;
        
        struct ll_node *new = (struct ll_node *)malloc(sizeof(struct ll_node));
        new->prev = NULL;
        new->next = NULL;
        
        new -> ID = x;
        q->prev = new;
        p->next = new;
        new->next = q;
        new->prev = p;
        length += 1;
        return;

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


int occur(struct ll_node* p, int n){
    if(p == NULL){
        return 0;
    }
    if (p->ID == n){
        return 1+occur(p->prev,n);
    }
    else{
        return occur(p->prev,n);
    }
}
void reverse(struct ll_node* i, struct ll_node* j){
    if(i==j){
        return;
    }
    int tmp = i->ID;
    if(i->prev==j){
        i->ID = j->ID;
        j->ID = tmp;
        return;
    }
    i->ID = j->ID;
    j->ID = tmp;
    reverse(i->prev,j->next);

}
int getfromposition(int index){
    if (head==NULL){
        return;
    }
    struct ll_node*p = head;
    for (int i =0;i<index;i++){
        p = p->prev;
    }
    return p->ID;
}
void print_ll()
{
	struct ll_node *p;

	p = head;

	while(p != NULL)
	{
		//print node
		printf("%d ",p->ID);
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
int main()
{
	//test removing from empty head
    add_to_head(9);
    printf("length: %d\n",length);
    print_ll();
    add_to_tail(3);
    printf("length: %d\n",length);
    print_ll();
    add_to_position(1,5);
    printf("length: %d\n",length);
    print_ll();
    add_to_head(6);
    printf("length: %d\n",length);
    print_ll();
    remove_from_position(3);
    printf("length: %d\n",length);
    add_to_head(9);
    add_to_head(9);
    add_to_head(9);
    add_to_tail(6);
    add_to_tail(6);
    add_to_tail(6);
    add_to_tail(6);
    reverse(head,tail);
    printf("%d %d\n",head->ID,tail->ID);
    reverse(head,tail);
    
    print_ll();

    printf("%d\n", occur(head, 7));
}