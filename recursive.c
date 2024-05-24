#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
struct ll_node{
    char* ID;
    struct ll_node *next;
    struct ll_node *prev;
};

struct ll_node *head = NULL;
struct ll_node *tail = NULL;
int length = 0;

void add_to_head(char* x){
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



int arr[10] = {2,-2,3,4,1,9,-7,5,10,10};
void printls(){
    for (int i= 0; i < 10 ; i ++){
        printf("%d",arr[i]);
    }
    printf("\n");    
}

int quicksearch(int k,int start, int end){
    if(start <= (k-1) && (k-1) <= end){
        ;
    }
    else{
        printf("input valid index!");
        return 0;
    }
    int pivot = arr[end];
    int j = start;
    int index = j;

    for (j; j<end;j++){
        if(arr[j] < pivot){
            int temp = arr[index];
            arr[index] = arr[j];
            arr[j] = temp;
            index++;

        }        
    }

    int tmp = arr[index];
    arr[index] = pivot;
    arr[end] = tmp;
    printls();

    if(k-1 == index){
        return pivot;
    }
    else if(k-1 < index){
        return quicksearch(k,start,index-1);
    }
    else{
        return quicksearch(k,index+1,end);
    }
}

int split_multiply(int x,int y, int n){
    if (n==1){
        return x*y;
    }
    int m = n/2;
    int a = x/(int)pow(10,m);
    int b = x % (int)(pow(10,m));
    int c = y/(int)pow(10,m);
    int d = y%(int)pow(10,m);

    int e = split_multiply(a,c,m);
    int f = split_multiply(b,c,m);
    int g = split_multiply(a,d,m);
    int h = split_multiply(b,d,m);
    return pow(10,2*m)*e + pow(10,m)*(f+g) + h;
}

int pingalapower(int a, int n){
    if (n==0){
        return 1;
    }
    else if(n%2 == 0 && n>0){
        int x = n/2;
        return pingalapower(a,x)*pingalapower(a,x);
    }
    else if(n%2 == 1 && n > 0){
        int x = n/2;
        return pingalapower(a,x)*pingalapower(a,x)*a;
    }
    else{
        printf("invalid n");
        return 0;
    }
}

void Baguenaudier (int n){
    if(n==0){
        return;
    }
    if(n == 1){
        printf("1, ");
        return;
    }
    if (n == 2){
        printf("2, 1, ");
        return;
    }
    if(n== -1){
        printf("1, ");
        return;
    }
    if(n==-2){
        printf("1, 2, ");
        return;
    }
    if(n>0){
        Baguenaudier(n-2);//let position 1 to n-2 be zero
        printf("%d, ",n); //so that, we can flip the first position to be 0
        Baguenaudier(-(n-2));//then we need to reverse all the zero back to one
        Baguenaudier(n-1); //we now have 011111111 (a smaller problem)
    }
    else{
        Baguenaudier(n+1); //reverse the 4 lines above making it print from back to front
        Baguenaudier(-(n+2));
        printf("%d, ", abs(n));
        Baguenaudier(n+2);
    }
}
void function(char *myString)
{
  for (int i = 0; i < strlen(myString); i++) {
    // Access each char in the string
    printf("myString[%d] = %c\n", i, myString[i]);
  }
    printf("%c\n",myString[0]);
}
int count = 0;
char* cutString(const char* original, int i, int j) {
    int length = strlen(original);
    if (i < 0 || j < 0 || i >= length || j >= length || i > j) {
        printf("Invalid indices\n");
        return NULL;
    }

    int cutLength = j - i + 2; // Length of the cut string (+1 for null terminator)
    char* cut = malloc(sizeof(char) * cutLength);
    if (cut == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strncpy(cut, original + i, j - i + 1); // Copy characters from original to cut string
    cut[cutLength - 1] = '\0'; // Add null terminator

    return cut;
}
char* reversedstr;

int palindrome(char* string){
    if (strlen(string)==1){
        return 1;
    }
    if (count == 0){
        //reverse the string
        reversedstr = malloc(sizeof(char)*(strlen(string)+1));    
        add_to_head(string);
        for (int i = 0; i < strlen(string); i++) {
            reversedstr[i] = string[strlen(string) - 1 - i];
        }
            reversedstr[strlen(string)] = '\0'; // Add null terminator
    count++;
    }
    // for (int i = 0; i < strlen(reversedstr); i++) {
    // // Access each char in the string
    //     printf("myString[%d] = %c\n", i, reversedstr[i]);
    // }
    for(int i = 0; i+strlen(string) <= strlen(reversedstr); i++){
        char* str = cutString(reversedstr,i,i+strlen(string)-1);
        if(strcmp(string,str) == 0){
            return strlen(string);
        }
    }
    remove_from_tail();

    add_to_head(cutString(string,0,strlen(string)-2));
    add_to_head(cutString(string,1,strlen(string)-1));

    return palindrome(tail->ID);

}
int main (void){
    Baguenaudier(6);
    printf("\n");
    int x = palindrome("111101101001");
    char*test = cutString("1110",0,2);
    function(test);
    printf("%d\n",x);
}