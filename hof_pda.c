#include<stdio.h>
#include<stdlib.h>
int my_array[10] = {1,2,3,4,5,6,7,8,9,10};

void map(int (*func)(int)){
    for (int i = 0; i < 10; i ++){
        my_array[i] = (*func)(my_array[i]);
    }

}
int minusone(int i){return i-1;}
int multtwo(int i){return i*2;}

// int main(void){
//     map(&multtwo);
//     for(int i = 0; i<10; i++){
//         printf("%d," , my_array[i]);
//     }
//     printf("\n");
// }

//-------------------------------------------------PDA---------------------------------------------

struct stack_entry
{
	int entry;
	struct stack_entry *down;
};

struct stack_entry *stack = NULL;

void push(int n)
{
	struct stack_entry *new_entry = (struct stack_entry *)malloc(sizeof(struct stack_entry));

	new_entry->entry = n;
	new_entry->down = stack;

	stack = new_entry;

	return;
}

int pop()
{
	if(stack == NULL)
	{
		printf("Error: attempting to pop empty stack\n");
		return -1;
	}

	int entry = stack->entry;

	struct stack_entry *old_entry = stack;

	stack = stack->down;

	free(old_entry);

	return entry;
}

int size()
{
	int result = 0;
	struct stack_entry *entry = stack;
	while(entry != NULL)
	{
		result++;
		entry = entry->down;
	}
	return result;
}
int add(int i, int j){return i+j;}
int subtract(int i, int j){return i-j;}
int multiply(int i, int j){return i*j;}
int divide(int i, int j){return i/j;}
int calculate(int (*calc)(int,int)){
    int j = pop();
    int i = pop();
    push((*calc)(i,j));
    return 0;
}

int main (void){
    //A+B/C*(D+E)-F -> ABC/DE+*+F-
    // push(3); //A
    // push(10); //B
    // push(5); //C
    // calculate(&divide);
    // push(2); //D
    // push(3); //E
    // calculate(&add);
    // calculate(&multiply);
    // calculate(&add);
    // push(5);
    // calculate(&subtract);
    // printf("%d\n", stack->entry);

	int result;
	//regular notation
	//(2 + 2)* 3 + 5 * (7 + 3)

	//in postfix notation:
	// 2 2 + 3 * 5 7 3 + * +
	push(2);
	push(2);
	calculate(&add);
	push(3);
	calculate(&multiply);
	push(5);
	push(7);
	push(3);
	calculate(&subtract);
	calculate(&multiply);
	calculate(&add);

	result=pop();

	printf("Result %d, with %d terms left on stack\n",result, size());

	return 0;

}



