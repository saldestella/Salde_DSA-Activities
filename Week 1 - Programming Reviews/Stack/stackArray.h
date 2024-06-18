#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <stdbool.h>
#define max 10
#define empty -1

typedef int Data;

typedef struct {
	Data elem[max];
	int top;		
	/* 
		"Top"
			> push = Top =+ 1
			> pop  = Top =- 1
			
		if Top is empty: top < 0
		ig Top is full: top == max
	*/
} Stack;

void initStack(Stack *list);		// set an empty stack
bool isEmpty(Stack list);			//check if stack is empty
bool isFull(Stack list);			//check if stack is full
void push(Stack *list, Data item);	//insert from the top
void pop(Stack *list);					//delete form the top
Data peek(Stack list);				//return the top
void display(Stack list);						// display the top
void visualize(Stack list);					//display the list


#endif

