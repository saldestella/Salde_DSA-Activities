#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack_array.h"

void initStack(Stack *S) {
    S->top = -1;
}

bool isEmpty(Stack *S) {
    return S->top < 0;
}

bool isFull(Stack *S) {
    return S->top >= (max-1);
}

void push(Stack *S, Data item) {
    if(isFull(S)) {
        printf("   * Push Unsuccessful. Stack is Full.*\n");
        return;
    }
    S->elem[++(S->top)] = item;
}

void pop(Stack *S) {
    if(isEmpty(S)) {
        printf("   * Pop Unsuccessful. Stack is Empty.*\n"); return;
    }
    S->top--;
}

Data peek(Stack *S) {
    return (isEmpty(S))? -1 : S->elem[S->top];
}

void display(Stack *S) {
    if(isEmpty(S)) {
        printf("   *Stack is Empty.*\n"); return;
    }
    Stack temp;
    initStack(&temp);
    
    printf("\n Popping Stack, Pushing Temp");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(S)) {
        push(&temp, peek(S));
        pop(S);
        printf("\n    | %3d   |", temp.elem[temp.top]);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");
    
    printf("\n\n Popping Temp, Pushing Stack");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(&temp)) {
        push(S, peek(&temp));
        printf("\n    | %3d   |", temp.elem[temp.top]);
        pop(&temp);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");

}

void visualize(Stack *S) {
    if(isEmpty(S)) {
        printf("   *Stack is Empty.*\n"); return;
    }
    int i;
    printf(" ========= ---> Top of Stack!");
    for(i = S->top ; i >= 0; i--) {
        printf("\n | %3d   |", S->elem[i]);
    }
    printf("\n ========= ---> Stack Begins Here!\n");
}