#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_tops(char,char);

//functions to manage stacks
int isfull1();
int isempty1();
char push1(char);
char pop1();
char peek1();

int isfull2();
int isempty2();
char push2(char);
char pop2();
char peek2();
void init_Stacks(char a[]);
void pushProduction(int code);

//stacks
char stack1[10];
char stack2[10];
int top1 = -1;
int top2 = -1;
char a,b;
char NT[] = {'A','B','C'};
char buff[10];

char action[9][10] = {
    "A->BwA",
    "A->e  ",
    "B->CxB",
    "B->yC ",
    "C->z  ",
    "Error ",
    "      ",
    "      ",
    "      "    
};


int main(int argc, char *argv[]){
        
    //check for command line inputs
    if(argc!= 2){
        printf("Incorrect number of arguments !");
        exit(0);
    }

    //place first arg in s1 and second in s2.
    //make sure $ is the last symbol in input while it
    //appears at bottom of the stack.

    init_Stacks(argv[1]);


   
    
    //display the header
    printf("STACK1 : %s\n",stack1);
    printf("STACK2 : %s\n",stack2);
    printf("\nTop of s1   Top of s2      Action             Stack1              Stack2\n");
    printf("-----------------------------------------------------------------------------\n");

    //push top of each stack

    while(1){
        char top_s1 = peek1();
        char top_s2 = peek2(); 
        int ret = compare_tops(top_s1,top_s2);

        if(top_s1 == '$' && top_s2 == '$'){
            printf("    %c          %c            %s             %s              %s\n",top_s1,top_s2,action[ret],stack1,stack2);
            printf("\nString is valid\n");
            exit(0);
        }   

        if(ret == 8){
            pop1();
        }

        if(ret == 5){
            printf("    %c          %c            %s             %s              %s\n",top_s1,top_s2,action[ret],stack1,stack2);
            printf("\nString is invalid\n");
            exit(0);
        }

        pushProduction(ret);
        if(ret == 7){
            pop1();
            pop2();
        }
        
        
        printf("    %c          %c            %s             %s              %s\n",top_s1,top_s2,action[ret],stack1,stack2);
        
    }

    //based on return value from compare_tops() function, print an
    //appropriate output
    return 0;
    
}




void init_Stacks(char argv1[]){
    //this function populates the stacks with the user input

    if(strlen(argv1) > 10){
        printf("Please enter a string with length < 10\n");
        exit(10);
    }

    if((argv1[strlen(argv1)-1] == '$')){

        int j = 0;

        while(j < strlen(argv1)+1){
            push2(argv1[strlen(argv1)-j]);
            j++;
        }

        j = 0;

        push1('$');
        push1('A');
    }
    else{
        printf("Please terminate input string with $\n");
        exit(0);
    }

    
}

int compare_tops(char a,char b){

//This function compares top of both stacks and returns an integer which
//is then used in main to determine what action to be printed on the
//output based on the parsing table. Consider it as a long switch or if-
//elseif statement ladder.

    if(a == 'A' && b == 'y') return 0;
    else if (a == 'A' && b == 'z') return 0;
    else if (a == 'A' && b == '$') return 1;
    else if (a == 'B' && b == 'y') return 3;
    else if (a == 'B' && b == 'z') return 2;
    else if (a == 'C' && b == 'z') return 4;
    else if (a == '$' && b == '$') return 6;
    else if (a == b) return 7;
    else if (a == 'e' && b == '$') return 8;
    else return 5;
}

void pushProduction(int code){
    // This function pushes appropriate production on stack1 after popping the top symbol. According to the top of stack1

    if(code == 0){
        pop1();
        push1('A');
        push1('w');
        push1('B');
    }
    else if(code == 1){
        pop1();
        push1('e');
    }
    else if(code == 2){
        pop1();
        push1('B');
        push1('x');
        push1('C');
    }
    else if(code == 3){
        pop1();
        push1('C');
        push1('y');
    }
    else if(code == 4){
        pop1();
        push1('z');
    }


}

// Following are functions to manage the stacks

int isempty1() {
    if(strlen(stack1) == 0) return 1;
    else return 0;
}
int isfull1() {
    if(strlen(stack1) == 10) return 1;
    else return 0;
}
char peek1() {
    return stack1[strlen(stack1)-1];
}
char pop1() {
    char popped;
	popped = stack1[strlen(stack1)-1];
	stack1[strlen(stack1)-1] = '\0';
	return popped;
}
char push1(char data) {
    if (isfull1() == 0){
        stack1[strlen(stack1)] = data;
    }
    return stack1[strlen(stack1)];
}

int isempty2() {
    if(strlen(stack2) == 0) return 1;
    else return 0;
}
int isfull2() {
    if(strlen(stack2) == 10) return 1;
    else return 0;
}
char peek2() {
    return stack2[strlen(stack2)-1];
}
char pop2() {
    char popped;
	popped = stack2[strlen(stack2)-1];
	stack2[strlen(stack2)-1] = '\0';
	return popped;
}
char push2(char data) {
    if (isfull2() == 0){
        stack2[strlen(stack2)] = data;
    }
    return stack2[strlen(stack2)];
}