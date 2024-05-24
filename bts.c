#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"FSM_library.h"
//----------------------------------------------BTS---------------------------------------------------
int card(){
    int random_number = rand()%10;
    if (random_number >= 0 && random_number <=4){
        return 1; //card has been read
    }
    else{
        return 0; //card has not been read
    }
}
int person(){
    int random_number = rand()%10;
    if (random_number >= 0 && random_number <=4){
        return 1; //person is in gate
    }
    else{
        return 0; //person is not in gate
    }
}
int cardread(struct FSM* fsm){
    if (card()== 1){
        return get_state_id(fsm,"open_without_person");
    }
    else{
        return get_state_id(fsm,"close");
    }
}
int personpass(struct FSM* fsm){
    if(person()== 1){
        return get_state_id(fsm,"open_with_person");
    }
    else{
        return get_state_id(fsm,"open_without_person");
    }
}
int personpassed(struct FSM* fsm){
    if(person()== 0){
        return get_state_id(fsm,"close");
    }
    else{
        return get_state_id(fsm,"open_with_person");
    }
}
//-------------------------------------------DETECT SEQUENCE 11010--------------------------
int number(){
    return rand()%2;
}
int start(struct FSM* fsm){
    int num = number();
    printf("num = %d\n", num);
    if (num == 0){
        return get_state_id(fsm, "0_correct");
    }
    else{
        return get_state_id(fsm, "1_correct");
    }
}
int one(struct FSM* fsm){
    int num = number();
    printf("num = %d\n", num);
    if(num == 0){
        return get_state_id(fsm,"0_correct");
    }
    else{
        return get_state_id(fsm,"2_correct");
    }
}
int two(struct FSM* fsm){
    int num = number();
    printf("num = %d\n", num);
    if(num == 0){
        return get_state_id(fsm,"3_correct");
    }
    else{
        return get_state_id(fsm,"2_correct");
    }
}
int three(struct FSM* fsm){
    int num = number();
    printf("num = %d\n", num);
    if(num == 0){
        return get_state_id(fsm,"0_correct");
    }
    else{
        return get_state_id(fsm,"4_correct");
    }
}
int four(struct FSM* fsm){
    int num = number();
    printf("num = %d\n", num);
    if(num == 0){
        printf("Sequence Correct!\n");
        return get_state_id(fsm,"0_correct");
    }
    else{
        return get_state_id(fsm,"1_correct");
    }
}

//-------------------------------Vending machine-----------------------------------------------------
int selectitem(){
    int myNum;
        // Ask the user to type a number
    printf("Type a number to select item: \n");

    // Get and save the number the user types
    scanf("%d", &myNum);

    // Output the number the user typed
    return myNum;
}

int pay(){
    int myNum;
        // Ask the user to type a number
    printf("Type 1 to pay and Type 0 to reselect: \n");

    // Get and save the number the user types
    scanf("%d", &myNum);

    // Output the number the user typed
    return myNum;
}
int dispense(){
    int random_number = rand()%10;
    if (random_number >= 0 && random_number <=5){
        return 1; //dispensed
    }
    else{
        return 0; //have not dispensed
    }
}
int change(){
    int random_number = rand()%10;
    if (random_number >= 0 && random_number <=5){
        return 1; //change dispensed
    }
    else{
        return 0; //change hasnt been dispensed
    }
}
int item_selected(struct FSM* fsm){
    int select = selectitem();
    if (select>0 && select < 10){
        return get_state_id(fsm,"selected");
    }
    else{
        printf("item not in stock");
        return get_state_id(fsm,"idle");
    }
}
int payed(struct FSM* fsm){
    int p = pay();
    if (p==1){
        return get_state_id(fsm,"dispensing");
    }
    else if (p==0){
        return get_state_id(fsm,"idle");
    }
    else{
        return get_state_id(fsm,"selected");
    }
}
int dispensed(struct FSM *fsm){
    if (dispense() == 1){
        return get_state_id(fsm,"dispensing_change");
    }
    else{
        return get_state_id(fsm,"dispensing");
    }
}
int change_dispensed(struct FSM* fsm){
    if (change()== 1){
        printf("Process completed\n");
        return get_state_id(fsm,"idle");
    }
    else{
        return get_state_id(fsm,"dispensing_change");
    }
}
int main(){
    struct FSM* fsm = new_FSM("vending_machine");
    add_state(fsm, "idle");
    add_state(fsm, "selected");
    add_state(fsm, "dispensing");
    add_state(fsm, "dispensing_change");

    add_stf(fsm, &item_selected, "idle");
    add_stf(fsm, &payed, "selected");
    add_stf(fsm, &dispensed, "dispensing");
    add_stf(fsm, &change_dispensed, "dispensing_change");
    set_current_state(fsm,"idle");

    // struct FSM* fsm = new_FSM("detect11010");
    // add_state(fsm,"0_correct");
    // add_state(fsm,"1_correct");
    // add_state(fsm,"2_correct");
    // add_state(fsm,"3_correct");
    // add_state(fsm,"4_correct");

    // add_stf(fsm, &start, "0_correct");
    // add_stf(fsm, &one, "1_correct");
    // add_stf(fsm, &two, "2_correct");
    // add_stf(fsm, &three, "3_correct");
    // add_stf(fsm, &four, "4_correct");

    // set_current_state(fsm, "0_correct");

    //action



    // struct FSM* fsm = new_FSM("BTS");
    // add_state(fsm,"close");
    // add_state(fsm,"open_without_person");
    // add_state(fsm,"open_with_person");

    // add_stf(fsm, &cardread, "close");
    // add_stf(fsm, &personpass, "open_without_person");
    // add_stf(fsm, &personpassed, "open_with_person");

    // set_current_state(fsm,"close");
	
    //action
    
    printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
    printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
    printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
    printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
	printf("State %s\n",get_current_state(fsm));
	transition(fsm);
}//