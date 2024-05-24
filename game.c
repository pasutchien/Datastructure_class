#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define COUNT 10
#define SHOOT 1
#define JUMP 2

struct btree_node
{
	//data
	int points;

	int highest;
	int level;

	//pointers
	struct btree_node *right; //jump
	struct btree_node *left; //shoot

	struct btree_node* parent;
};

//returns the reward for specific action at this point in time
//returns 0, 1, or -infinity points
int reward(int action, int steps)
{
	//static unsigned int steps = 0;
	unsigned int p = 0x18352037;
	unsigned int d = 0x11111111;

	int reward;

	//death if you shoot at wrong time
	if(((d >> steps)&1) && (action == SHOOT))
	{	
		reward = INT_MIN;
	}
	else
	{
		if(action == SHOOT)
		{
			if((p >> steps)&1)
				reward = 1;
			else
				reward = 0;
		}
		else
		{
			reward = 0;
		}
	}

	//steps++;

	return reward;
}


struct btree_node *root = NULL;


int count = 0;
//Builds a decision binary tree for up to x steps: max 64
void train(unsigned int steps, struct btree_node *current)
{
	if(current->level == steps){
		return;
	}
	struct btree_node* left = (struct btree_node*)malloc(sizeof(struct btree_node));//shoot
	struct btree_node* right = (struct btree_node*)malloc(sizeof(struct btree_node));//jump
	left ->left = NULL;
	left -> right = NULL;
	left->parent = NULL;
	right->left = NULL;
	right->right = NULL;
	right->parent = NULL;
	if (count == 0){
		current->level = 0;
		count++;
	}
	right->level = current->level +1;
	left->level = current->level +1;
	int scoreL = reward(SHOOT,left->level);
	int scoreR = reward(JUMP, right->level);
	left->points=scoreL;
	right->points=scoreR;
	current->left = left;
	current->right = right;
	
	left->parent = current;
	right->parent = current;
	
	if(scoreL != INT_MIN){
		train(steps,current->left);
	}
	if(scoreR != INT_MIN){
		train(steps,current->right);
	}
}

int calculate_score(struct btree_node *current)
{
	if(current -> left== NULL && current -> right ==NULL){
		current->highest = current->points;
		return current->points;
	}
	if(calculate_score(current->left)>calculate_score(current->right)){
		current->highest = current->points + calculate_score(current->left);
		return current->points+calculate_score(current->left);
	}
	else{
		current->highest = current->points + calculate_score(current->right);
		return current->points + calculate_score(current->right);
	}
}


void print_best_strategy(struct btree_node *current)
{
	if(current == NULL)
		return;
	//in case they're both null
	if((current->left == NULL) && (current->right == NULL))
	{
		return;
	}
	//if left is NULL
	if((current->left == NULL))
	{
		printf("J ");
		print_best_strategy(current->right);
		return;
	}
	//if right is NULL
	if((current->right == NULL))
	{
		printf("S ");
		print_best_strategy(current->left);
		return;
	}

	if((current->left)->highest > (current->right)->highest)
	{
		printf("S ");
		print_best_strategy(current->left);
	}
	else
	{
		printf("J ");
		print_best_strategy(current->right);
	}
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
    printf("%d\n", root->highest);
 
    // Process left child
    print2DUtil(root->left, space);
}
void print2D(struct btree_node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}






int main()
{
	//creates root, representing beginning position of game
	root = (struct btree_node *)malloc(sizeof(struct btree_node));

	root->highest = 0;
	root->points = 0;

	root->left = NULL;
	root->right = NULL;

	train(5,root);
	printf("Trained\n");

	// //What's the highest score we achieved?
	calculate_score(root);
	print2D(root);
	printf("%d %d\n", root->left->highest,root->right->highest);
	printf("High score: %d\n",root->highest);

	printf("Best strategy:\n");
	print_best_strategy(root);
	printf("\n");

	return 0;
}