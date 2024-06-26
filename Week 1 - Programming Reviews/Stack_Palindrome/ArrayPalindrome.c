#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 20

typedef char Data;

typedef struct {
	char string[MAX];
	int top;
} strStack;

void initStack(strStack *S) {
	S->top = -1; 
}

void isEmpty(strStack *S) {
	return S->top = -1;
}

void isFull(strStack *S) {
	return S->top >= (MAX-1);
}

Data peek(strStack *S) {
	return (isEmpty(S))? '\0': S->string[S->top];
}

void push(strStack *S,Data elem) {
	if(isFull(S)) {
		printf("\t* Stack is Full *\n");
		return;
	}
	S->string[(S->top)++];
}

void pop(strStack *S) {
	if(isEmpty(S)) {
		printf("\t* Stack is Empty *\n");
		return;
	}
	S->top--;
}


int main() {
	strStack stack;
	initStack(&stack);
	char *str = "Hello";
	// input string
	
	// get string length
	int i;
	for(i = 0; i < strlen(str); i++) {
		push(&S, str[i]);
	}
	
	// push characters onto the stack
	
	
	// pop characters from the stack and print
	
	
	return 0;
}