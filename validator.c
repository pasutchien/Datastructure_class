#include<stdio.h>
#include<stdlib.h>

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



enum operator {ADD, SUBTRACT, MULTIPLY};


//can be called with an operator perform an action on the stack
void calculator(enum operator o)
{
	int op1, op2;
	int result;
	switch(o)
	{
		case ADD:
			op1 = pop();
			op2 = pop();
			push(op1 + op2);
			break;
		case SUBTRACT:
			op1 = pop();
			op2 = pop();
			push(op1 - op2);
			break;
		case MULTIPLY:
			op1 = pop();
			op2 = pop();
			push(op1 * op2);
			break;
	}
}
int check(){
    static int i = 1;
    int count = 0;
    if(stack->entry != 1){
        return 0;
    }
    while(stack != NULL){
        if (i==1){
            if(count == 1 && stack->entry != 1){
                return 0;
            }
            if(stack -> entry == 1){
                pop();
            }
            else{
                i = stack->entry;
                pop();
                count = 1;
            }
        }
        else{
            if(stack->entry == i-1){
                i = stack->entry;
                pop();
            }
            else{
                return 0;
            }
        }
        }
    if(count == 1 && i == 1){
        return 1;
    }
    else{
        return 0;
    }
}


int main()
{
	// int result;
	// //regular notation
	// //(2 + 2)* 3 + 5 * (7 + 3)

	// //in postfix notation:
	// // 2 2 + 3 * 5 7 3 + * +
    
    // push(1);
    // push(1);
    // push(1);
    // push(2);
    // push(3);
    // push(4);
    // push(5);
    // push(1);
    // push(1);


    // result = check();
	// printf("Result %d, with %d terms left on stack\n",result, size());

	// return 0;

	int result;
	//regular notation
	//(2 + 2)* 3 + 5 * (7 + 3)

	//in postfix notation:
	// 2 2 + 3 * 5 7 3 + * +
	push(2);
	push(2);
	calculator(ADD);
	push(3);
	calculator(MULTIPLY);
	push(5);
	push(7);
	push(3);
	calculator(SUBTRACT);
	calculator(MULTIPLY);
	calculator(ADD);

	result=pop();

	printf("Result %d, with %d terms left on stack\n",result, size());

	return 0;
}