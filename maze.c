#include<stdio.h>
#include<stdlib.h>
//comment this in Windows/MacOS: unistd is Linux specific
//lookup required header file for usleep() in your OS
#include<unistd.h>

#define SIDE 22

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

unsigned char map[SIDE][SIDE] = 
	{
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1','X', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1'}, //(9,17)
		{'1','1', '1', '1', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0', '1', '0', '1'},
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', 'O', '1'} ,
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
unsigned char initialmap[SIDE][SIDE] = 
	{
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1','X', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1'}, //(9,17)
		{'1','1', '1', '1', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '0', '0', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0', '1', '0', '1'},
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', 'O', '1'} ,
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};

// void reset_map()
// {
// 	int i, j;
// 	for(j=SIDE-1; j >=0; j--)
// 	{
// 		for(i=0; i <SIDE; i++)
// 		{
// 			if(map[i][j] == 'O')
// 				map[i][j] = '0';
// 		}
// 	}	
// 	map[SIDE-2][SIDE-2] = 'O';
// }	

void reset_map()
{
    for(int i= 0 ; i<SIDE;i++){
        for(int j = 0; j < SIDE;j++){
            map[i][j] = initialmap[i][j];
        }
    }
}


void print_map()
{
	int i, j;

	for(j=SIDE-1; j >=0; j--)
	{
		printf("1 ");
		for(i=0; i <SIDE; i++)
		{
			if(map[i][j] != '0')
			{
				if(map[i][j] == 'X')
					printf(RED "X " RESET);
				else
				{	
					if(map[i][j] == 'O')
						printf(GREEN "O " RESET);
					else
						printf("%c ",map[i][j]);
				}
			}
			else
				printf("  ");
		}	
		printf("1 ");
		printf("\n");
	}
}



void left_wall_solve()
{
	int position_before[2] = {SIDE-1, SIDE-2};
    int position[2] = {SIDE-2, SIDE-2};
    while(map[1][1] != 'O')
	{

        int temp_x = position[0];
        int temp_y = position[1];
        

        if(position_before[1] == position[1] && position_before[0] == position[0]+1){
            //heading left
            position_before[0] = temp_x;
            position_before[1] = temp_y;
            if (map[position[0]-1][position[1]] == 'X'){
                map[position[0]-1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
            }

            else if (map[position[0]][position[1]-1] == '0'){
                map[position[0]][position[1]-1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]-1;

            }
            else if(map[position[0]-1][position[1]] == '0' ){
                //go straight 
                map[position[0]-1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]-1;
            }
                else if (map[position[0]][position[1]-1] == '0'){
                //turn right
                map[position[0]][position[1]-1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]-1;

            }
            else{
                //turn around
                map[position[0]][position[1]+1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]+1; 
            }
        }
        else if (position_before[1] == position[1] && position_before[0] == position[0]-1){
            //heading right
            position_before[0] = temp_x;
            position_before[1] = temp_y;
            if (map[position[0]][position[1]+1] == '0'){
                map[position[0]][position[1]+1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]+1;
            }
            else if(map[position[0]+1][position[1]] == '0'){
                //go straight 
                map[position[0]+1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]+1;
            }
            else if (map[position[0]][position[1]-1] == '0'){
                //turn right
                map[position[0]][position[1]-1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]-1;

            }
            else{
                //turn around
                map[position[0]-1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]-1; 
            }
        }
        else if (position_before[0] == position[0] && position_before[1] == position[1]-1){
            //heading up
            position_before[0] = temp_x;
            position_before[1] = temp_y;
            if (map[position[0]-1][position[1]] == '0'){
                map[position[0]-1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]-1;

            }
            else if(map[position[0]][position[1]+1] == '0'){
                //go straight 
                map[position[0]][position[1]+1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]+1;
            }
            else if (map[position[0]+1][position[1]] == '0'){
                //turn right
                map[position[0]+1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]+1;

            }
            else{
                //turn around
                map[position[0]][position[1]-1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]-1; 
            }
        }
        else{
            //heading down
            position_before[0] = temp_x;
            position_before[1] = temp_y;
            if (map[position[0]+1][position[1]] == '0'){
                map[position[0]+1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]+1;

            }
            else if(map[position[0]][position[1]-1] == '0'){
                //go straight 
                map[position[0]][position[1]-1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]-1;
            }
            else if (map[position[0]-1][position[1]] == '0'){
                //turn right
                map[position[0]-1][position[1]] = 'O';
                map[position[0]][position[1]] = '0';
                position[0] = position[0]-1;

            }
            else{
                //turn around
                map[position[0]][position[1]+1] = 'O';
                map[position[0]][position[1]] = '0';
                position[1] = position[1]+1; 
            }
        }
        usleep(125000);
		print_map();
	}

}


struct graph_node;     
struct edge
{
    //distance
    int distance;
    //pointer to target nodes
    struct graph_node *node1;
    struct graph_node *node2;
};
struct graph_node
{
    //position
    int x;
    int y;
    //distance from start to this node
    int distance;
    //Links to 4 other nodes
    struct edge *up;
    struct edge *down;
    struct edge *left;
    struct edge *right;
    //node with the least distance to get to this node
    struct graph_node *prev;
};

struct ll_node{
    struct graph_node *ID;
    struct ll_node *next;
    struct ll_node *prev;
};


struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;

struct ll_node*head2 = NULL;
struct ll_node*tail2 = NULL;
int length2 = 0;

//functions for linked list
void add_to_head(struct graph_node* x){
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

void add_to_head2(struct graph_node* x){
    struct ll_node *p = (struct ll_node *)malloc(sizeof(struct ll_node)); //when malloc you should set the pointer in the block to NULL all the time
    p->prev = NULL;
    p->next = NULL;
    if (head2 == NULL){
        p->ID=x;
        head2 = p;
        tail2 = p;
        length2+=1;
        return;
    }
    else{
        p->ID = x;
        p->prev = head2;
        head2 -> next = p;
        head2 = p;
        length2 += 1;
    }
}


void delete_whole_list2()
{
	struct ll_node *to_free;
    length2 = 0;
	if(head2 == NULL)
	{
		return;
	}
	while(head2 != NULL)
	{
		to_free = head2;
		head2 = head2->prev;
		free(to_free);
        to_free = NULL;
	}
    tail2 = NULL;
}
struct graph_node* id_on_list2(int x, int y){
    struct ll_node *p  = head2;
    while (p != NULL){
        if(p->ID != NULL){
            if(p->ID->x == x && p->ID->y == y){
                return p->ID; //data is found
            }
        }
        p = p->prev;
    }
    return NULL; //no data
}

void add_to_tail(struct graph_node* z){
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
struct graph_node* id_on_list(int x, int y){
    struct ll_node *p  = head;
    while (p != NULL){
        if(p->ID->x == x && p->ID->y == y){
            return p->ID; //data is found
        }
        p = p->prev;
    }
    return NULL; //no data
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
void print_ll()
{
	struct ll_node *p;

	p = head;

	while(p != NULL)
	{
		//print node
		printf("(%d, %d)",p->ID->x, p->ID->y);
		p = p->prev;
	}
	printf("\n");
}
void print_ll2()
{
	struct ll_node *p;

	p = head2;

	while(p != NULL)
	{
		//print node
		printf("(%d, %d)",p->ID->x, p->ID->y);
		p = p->prev;
	}
	printf("\n");
}
struct graph_node* remove_from_position(int index){
    struct graph_node* res;
    if (index == 0){
        res = head->ID;
        remove_from_head();
        return res;
    }
    else if (index == length - 1){
        res = tail->ID;
        remove_from_tail();
        return res;
    }
    else if(index < 0 || index >= length){
        return NULL;
    }
    else{
        struct ll_node *p = head;
        for (int i = 0; i < index ; i ++){
            p = p->prev;
        }
        res = p->ID;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        length -= 1;
        }
        return res;
}
struct graph_node* remove_min_from_ll(){
    int min = 999;
    struct ll_node *p = head;
    while(p != NULL){
        if (p->ID->distance < min){
            min = p->ID->distance;
        }
        p = p->prev;
    }
    if (min == 999){
        return NULL;
    }
    struct ll_node* p2 = head;
    int i;
    for(i = 0 ; i < length ; i++){
        if(p2->ID->distance == min){
            break;
        }
        p2 = p2->prev;
    }
    struct graph_node* res = remove_from_position(i);
    return res;

}
void printmarktograph(int i){
    {
	struct ll_node *p;
    if (i==1){p = head;}
    else if (i==2){p = head2;}
	
	while(p != NULL)
	{
		//print node
        //printf("(%d,%d) %d", p->ID->x, p->ID->y, p->ID->distance);
		map[p->ID->x][p->ID->y] = 'X' ;
		p = p->prev;
	}
    printf("\n");
	print_map();
    reset_map();
    printf("\n");
}

}
struct graph_node *new_node(int x, int y)
{
	struct graph_node *new = (struct graph_node *)malloc(sizeof(struct graph_node));

	new->x = x;
	new->y = y;
    new->distance = 9999;
	new->up = new->down =new->right =new->left = NULL;

	return new;
}
struct edge *new_edge(struct graph_node* node1, struct graph_node* node2){
    struct edge* new = (struct edge*)malloc(sizeof(struct edge));
    new->distance = abs(node1->x - node2->x) + abs(node1->y - node2->y);
    new->node1 = node1;
    new->node2 = node2;
    return new;
}

int is_corner(int x, int y)
{
    if(map[x-1][y] == '1' && map[x-1][y-1] == '1' && map[x][y-1] == '1'){
        //lower left corner
        return 1;
    }
    if(map[x-1][y] == '1' && map[x-1][y+1] == '1' && map[x][y+1] == '1'){
        //upper left corner
        return 1;
    }
    if(map[x+1][y] == '1' && map[x+1][y+1] == '1' && map[x][y+1] == '1'){
        //upper right corner
        return 1;
    }
    if(map[x+1][y] == '1' && map[x+1][y-1] == '1' && map[x][y-1] == '1'){
        //lower right corner
        return 1;
    }
    //open corner
    if(map[x-1][y-1] == '1' && map[x-1][y] =='0' && map[x][y-1] == '0'){
        //lower left
        return 1;
    }
    if(map[x-1][y+1] == '1' && map[x-1][y] =='0' && map[x][y+1] =='0'){
        //upper left
        return 1;
    }
    if(map[x+1][y+1] == '1' && map[x+1][y] =='0' && map[x][y+1] == '0'){
        //upper right
        return 1;
    }
    if(map[x+1][y-1] == '1' && map[x+1][y] == '0' && map[x][y-1] == '0'){
        //lower right
        return 1;
    }
    return 0;
}


void build_graph(struct graph_node *root)
{
    
    add_to_head(root);
    add_to_head2(root);
    // int k =0;
    // int count = 0;
    while(head != NULL){
 
        root = head->ID;
        // if(root->x == 18 && root->y == 4){
        //     if(root->left != NULL){
        //     printf("NOT NULL\n");
        //     count += 1;
        //     }
        // }

        // if (count == 2){
        //     break;
        // }
        if (root->left == NULL){
            int i = root->x;
            int j = root->y;
            // if(root->x == 18 && root->y == 4){
            //     printf("NULL\n");
            //     count += 1;
            // }
            while(map[i-1][j] != '1'){
                //go left until hit a border or find an edge
                if(is_corner(i-1,j) == 1){
                    // if(root->x == 18 && root->y == 4){
                    // printf("addedl\n");}
                    if(id_on_list2(i-1,j) == NULL){
                    struct graph_node* new = new_node(i-1,j);
                    struct edge* edge = new_edge(root, new);
                    root->left = edge;
                    new->right = edge;
                    add_to_tail(new);        
                    add_to_head2(new);
                    }
                    else{
                    struct graph_node* new = id_on_list2(i-1,j);
                    struct edge* edge = new_edge(root,new);
                    root->left = edge;
                    new->right = edge;
                    }
                break;
                }
                i = i-1;
            }
            // if(root->x == 18 && root->y == 4){
            // k++;
            // }
        }
        if (root->right == NULL){
            int i = root->x;
            int j = root->y;
            while(map[i+1][j] != '1'){
                //go right until hit corner
                if(is_corner(i+1,j) == 1){
                    if(id_on_list2(i+1,j) == NULL){
                        struct graph_node* new = new_node(i+1,j);
                        struct edge * edge = new_edge(root,new);
                        root->right = edge;
                        new->left = edge;
                        add_to_tail(new);
                        add_to_head2(new);
                    }
                    else{
                        struct graph_node *new = id_on_list2(i+1,j);
                        struct edge * edge = new_edge(root,new);
                        root->right = edge;
                        new->left = edge;
                    }
                    break;
                }
                i = i+1;
            }
        }
        if(root->up == NULL){
            int i = root->x;
            int j = root->y;
            while(map[i][j+1] != '1'){
                //go up until hit corner
                if(is_corner(i,j+1) == 1){
                    if(id_on_list2(i,j+1)== NULL){
                        struct graph_node* new = new_node(i,j+1);
                        struct edge * edge = new_edge(root,new);
                        root->up = edge;
                        new->down = edge;
                        add_to_tail(new);
                        add_to_head2(new);
                    }
                    else{
                        struct graph_node* new = id_on_list2(i,j+1);
                        struct edge* edge = new_edge(root,new);
                        root->up = edge;
                        new->down = edge;
                    }
                    break;      
                }
                j = j+1;
            }
        }
        if(root->down == NULL){
            int i = root->x;
            int j = root->y;
            while(map[i][j-1] != '1'){
                //go down until hit corner
                if(is_corner(i,j-1) == 1){
                    // if(root->x == 18 && root->y == 4){
                    // printf("addedd\n");}
                    if(id_on_list2(i,j-1)== NULL){
                        struct graph_node* new = new_node(i,j-1);
                        struct edge * edge = new_edge(root,new);
                        root->down = edge;
                        new->up = edge;
                        add_to_tail(new);
                        add_to_head2(new);
                    }
                    else{
                        struct graph_node* new = id_on_list2(i,j-1);
                        struct edge* edge = new_edge(root,new);
                        root->down = edge;
                        new->up = edge;
                    }
                    break;     
                }
                j = j-1;
            }
        }
        remove_from_head();
    }
    printf("%d\n" ,length2);
    delete_whole_list();
    //print_map();
    delete_whole_list2();

}


/*
	Target is at position 0,0
*/


void dijkstra (struct graph_node* start, int end_x, int end_y){
    //fringe
    //printf("%d\n", length2);
    add_to_head(start);
    start->distance = 0;
    while(head != NULL){
        start = remove_min_from_ll();

        if(start -> left != NULL && start->left->node1 != NULL && start->left->node2 != NULL){
            struct graph_node* l;
            if(start->left->node1 == start){l = start->left->node2;}
            else{l = start->left->node1;}
            if(l->distance > (start->distance + start->left->distance ))
            {
                l->distance = start->distance + start->left->distance;
                l->prev = start;
            }
            if(id_on_list2(l->x, l->y) == NULL){
                add_to_tail(l);
            }
        }
        if(start-> right != NULL){

            struct graph_node* r;
            if(start->right->node1 == start){r = start->right->node2;}
            else{r = start->right->node1;}
            if(r->distance > (start->distance + start->right->distance)){
                r->distance = start->distance + start->right->distance;
                r->prev = start;
            }
            if(id_on_list2(r->x, r->y) == NULL){
                add_to_tail(r);
            }
        }
        if(start->up != NULL){
            struct graph_node *u;
            if(start->up->node1 == start){u = start->up->node2;}
            else{u = start->up->node1;}
            if(u->distance > start->distance + start->up->distance){
                u->distance = start->distance + start->up->distance;
                u->prev = start;
            }
            if(id_on_list2(u->x, u->y) == NULL){
                add_to_tail(u);
            }
        }
        if(start->down != NULL){
            struct graph_node *d;
            if(start->down->node1 == start){d = start->down->node2;}
            else{d = start->down->node1;}
            if(d->distance > start->distance + start->down->distance){
                d->distance = start->distance + start->down->distance;
                d->prev = start;
            }
            if(id_on_list2(d->x, d->y) == NULL){
                add_to_tail(d);
            }
        }
        add_to_head2(start);
    }
    delete_whole_list();
    struct graph_node *end = id_on_list2(end_x, end_y);
    if (end == NULL){
        printf("Choose an appropriate end point");
        return; 
    }
    else{
        while(end != NULL){
            add_to_head(end);
            end = end->prev;
        }
        //print_ll();
        printmarktograph(1);
    }
    delete_whole_list();
    //delete_whole_list2();
}
int main()
{
	reset_map();
    
	print_map();
	//left_wall_solve();
	//we know first node: start position
    struct graph_node *root = new_node(SIDE-2, SIDE-2);
    build_graph(root);
    dijkstra(root,1,1);
    //printf("%d\n", length2);
    return 0;
}