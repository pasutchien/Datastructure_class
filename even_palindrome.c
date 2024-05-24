#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	char entry;
	struct stack_entry *down;
};

struct stack_entry *stack = NULL;

void push(char n)
{
	struct stack_entry *new_entry = (struct stack_entry *)malloc(sizeof(struct stack_entry));

	new_entry->entry = n;
	new_entry->down = stack;

	stack = new_entry;

	return;
}

char pop()
{
	if(stack == NULL)
	{
		printf("Error: attempting to pop empty stack\n");
		return '*';
	}

	char entry = stack->entry;

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
// int add(int i, int j){return i+j;}
// int subtract(int i, int j){return i-j;}
// int multiply(int i, int j){return i*j;}
// int divide(int i, int j){return i/j;}
// int calculate(int (*calc)(int,int)){
//     int j = pop();
//     int i = pop();
//     push((*calc)(i,j));
//     return 0;
// }

int even_palindrome(char* string, int length){
	for(int i = 0;i < length/2; i++){
		push(*(string+i));
	}
	int index = length/2;
	while(stack != NULL){
		char c = pop();
		if(c != *(string+index)){
			printf("%c / %c\n", c,*(string+index));
			return 0;
		}
		index ++;
	}
	return 1;
}
int a_n_b_n (char* string){
	int length = strlen(string);
	char first = *string;
	int i = 0;
	while(*(string+i) == first){
		push(*(string+i));
		i++;
	}
	int j = i;
	while(j < length){
		if(*(string + i) != *(string+j)){
			break;
		}
		char x = pop();
		if (x == '*'){
			return 0;
		}
		j++;
	}

	if (stack == NULL){
		return 1;
	}
	else{
		while(stack != NULL){
			pop(); //clear stack
		}
		return 0;
	}

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
	// push(2);
	// push(2);
	// calculate(&add);
	// push(3);
	// calculate(&multiply);
	// push(5);
	// push(7);
	// push(3);
	// calculate(&add);
	// calculate(&multiply);
	// calculate(&add);

	// result=pop();

	// printf("Result %d, with %d terms left on stack\n",result, size());

	result = a_n_b_n("aaabb");
	printf("%d\n", result);
	return 0;

}



