#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack_linkedlist.h"

void initStack(Stack *S) {
    S->top = NULL;
    S->ctr = -1;
}

bool isEmpty(Stack *S) {
    return S->top == NULL;
}

bool isFull(Stack *S) {
    return S->ctr >= (max-1);
}

void push(Stack *S, Data item){
    if(isFull(S)){
        printf("   * Push Unsuccessful. Stack is Full.*\n");
        return;
    }
    nodePtr temp = malloc(sizeof(nodeType));
        if(temp != NULL) {
            temp->elem = item;
            temp->next = S->top;
            S->top = temp;
            S->ctr++;
    }
}

void pop(Stack *S){
    if(isEmpty(S)) {
        printf("   * Pop Unsuccessful. Stack is Empty.*\n");
        return;
    }
    nodePtr temp = S->top;
    S->top = S->top->next;
    S->ctr--;
    free(temp);
}

Data peek(Stack *S){
    return (!isEmpty(S))? S->top->elem: -1;
}

void display(Stack *S){
    if(isEmpty(S)) {
        printf("\n   * Stack is Empty *"); return;
    }
    
    Stack temp;
    initStack(&temp);
    printf("\n Popping Stack, Pushing Temp");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(S)) {
        push(&temp, peek(S));
        pop(S);
        printf("\n    | %3d   |", temp.top->elem);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");
    
    printf("\n\n Popping Temp, Pushing Stack");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(&temp)) {
        push(S, peek(&temp));
        printf("\n    | %3d   |", temp.top->elem);
        pop(&temp);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");
}

void visualize(Stack *S){
    if(isEmpty(S)) {
        printf("\n   * Stack is Empty *"); return;
    }
    nodePtr temp = S->top;
    printf("\n    ========= ---> Top of Stack!");
    for(; temp != NULL; temp = temp->next) {
        printf("\n    | %3d   |", temp->elem);
    }
	printf("\n    ========= ---> Stack Begins Here!\n");
}