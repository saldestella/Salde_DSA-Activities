#ifndef STACK_ARRAY_H
// #define STACK_ARRAY_H

#include <stdbool.h>
#define max 5

typedef int Data;

typedef struct node {
    Data elem[max];
    int top;
} Stack;

void initStack(Stack *S);           //  initializes Stack setting it to NULL and count negative
bool isEmpty(Stack *S);             //  checks if Stack is Empty
bool isFull(Stack *S);              //  checks if Stack is Full
void push(Stack *S, Data item);     //  inserts an item on top of Stack
void pop(Stack *S);                 //  deletes an item on top of Stack
Data peek(Stack *S);                //  returns the item on top of Stack
void display(Stack *S);             //  Displays Stack and its reverse order w/o using temp = temp->next
void visualize(Stack *S);           //  Displays Stack 

#endif