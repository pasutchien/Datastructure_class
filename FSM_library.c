#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "FSM_library.h"

struct FSM;


struct state
{
	char *name;
	//unique ID
	int id;
	//function pointer to state transition function
		//returns ID of target state
	int (* stf)(struct FSM *fsm);
	struct state *next;
};


struct FSM
{
	char *name;
	//number of states
	int state_count;

	//current state
	struct state *current;

	//list of states
	struct state *states;
	//list of transitions
};



/***********************************************
*
*	Functions for building a state machine
* 
* **********************************************/

//initializes an empty state machine with a given name
struct FSM *new_FSM(char *n);

//adds a new state to state machine, with given name
void add_state(struct FSM *fsm, char *n);


//adds a new state transition function to a state with given name
void add_stf(struct FSM *fsm, int (* stf)(struct FSM *fsm) ,char *n);






/***********************************************
*
*	Functions for operating on a built state machine
* 
* **********************************************/

void set_current_state(struct FSM *fsm, char *n);
char *get_current_state(struct FSM *fsm);

int get_state_id(struct FSM *fsm, char *n);


struct state *get_state_by_id(struct FSM *fsm, int n);


//applies current state's transition function, modifies current state
void transition(struct FSM *fsm);














struct FSM *new_FSM(char *n)
{
	struct FSM *fsm;
	fsm = (struct FSM *)malloc(sizeof(struct FSM));

	//initializations
	fsm->current = NULL;
	fsm->states = NULL;

	fsm->state_count = 0;

	fsm->name = (char *)malloc(strlen(n)+1); 
	strcpy(fsm->name,n);

	return fsm;
}

//adds a new state to state machine, with given name
void add_state(struct FSM *fsm, char *n)
{
	struct state *s;

	s = (struct state *)malloc(sizeof(struct state));

	s->name = (char *)malloc(strlen(n)+1);
	strcpy(s->name,n);

	/*
		Missing error handling:
			ensure we do not repeat state names
	*/
    if(get_state_id(fsm,n) != -999){
        return;
    }

	s->id = fsm->state_count;
	fsm->state_count++;

	s->stf = NULL;

	s->next = fsm->states;
	fsm->states = s;
}



void set_current_state(struct FSM *fsm, char *n)
{
	struct state *s;

	s = fsm->states;
    if(s==NULL){
        printf("State not found\n");
        return;
    }
	while(strcmp(s->name,n)!=0)
	{
		if (s->next== NULL){
            printf("State not found\n");
            return;
        }
        s=s->next;

	}
	fsm->current = s;
}

char *get_current_state(struct FSM *fsm)
{
	return fsm->current->name;
}


int get_state_id(struct FSM *fsm, char *n)
{
	struct state *s;

	s = fsm->states;
    if(s==NULL){
        //printf("State not found\n");
        return -999;
    }
	
    while(strcmp(s->name,n)!=0)
	{
        if(s->next== NULL){
            //printf("State not found\n");
            return -999;
        }
		s=s->next;

	}
	return s->id;
}

struct state *get_state_by_id(struct FSM *fsm, int n)
{
	struct state *s;

	s = fsm->states;
    if(s==NULL){
        printf("State not found\n");
        return NULL;
    }
	while((s->id)!=n)
	{
        if(s->next== NULL){
            printf("State not found\n");
            return NULL;
        }
		s=s->next;

	}
	return s;
}


void add_stf(struct FSM *fsm, int (* stf)(struct FSM *fsm) ,char *n)
{
	struct state *s;

	s = fsm->states;
    if(s==NULL){
        printf("State not found\n");
        return;
    }
	while(strcmp(s->name,n)!=0)
	{
        if(s->next== NULL){
            printf("State not found\n");
            return;
        }
		s=s->next;

	}
	s->stf = stf;
}

void transition(struct FSM *fsm)
{
	int target_id;

	target_id = (*((fsm->current)->stf))(fsm);

	fsm->current = get_state_by_id(fsm,target_id);
}


int on_stf(struct FSM *fsm)
{
	/*
		More generally: would test all relevant inputs
		Decide which state we're supposed to go to (by name)
		return with "get_state_id" to get id of corresponding name
	*/
	return get_state_id(fsm, "off");
}
int off_stf(struct FSM *fsm)
{
	return get_state_id(fsm, "on");
}



/*
int main()
{

	//Construct the state machine
	struct FSM *fsm = new_FSM("light");
    add_state(fsm, "on");
	add_state(fsm, "off");

	add_stf(fsm, &on_stf ,"on");
	add_stf(fsm, &off_stf ,"off");

	set_current_state(fsm, "off");


	//Operate it
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);

	return 0;
}
*/