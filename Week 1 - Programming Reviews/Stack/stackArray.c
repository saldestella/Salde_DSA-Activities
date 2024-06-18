#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackArray.h"

void initStack(Stack *list){
	list->top = -1;
}	
// set an empty stack

bool isEmpty(Stack list) {
	return list.top <= empty;
}
//check if stack is empty

bool isFull(Stack list){
	return list.top >= (max-1);
}		
//check if stack is full

void push(Stack *list, Data item) {
	if(!isFull(*list)){
		list->elem[++(list->top)] = item;
		printf("Data: %d Pushed Successfully!\n", item);
	} else {
        printf("\nStack is full. Cannot push %d\n", item);
    }

}
//insert from the top

void pop(Stack *list) {
	if(!isEmpty(*list)){
		list->top--;
		printf("\nPopped Successfully!\n");
	}
}
//delete form the top

Data peek(Stack list){
	return list.elem[list.top];
}
//return the top

void display(Stack list) {
	if(isEmpty(list)) {
		printf("\nStack is Empty");
		return;
	}
	
	Stack temp;
	initStack(&temp);
	
	printf("Temp Stack (To check for errors)\n");
	while(!(isEmpty(list))){
		push(&temp, peek(list));
		printf("%d ", peek(temp));
		pop(&list);
	}
	
	printf("\nThe original Stack\n");
	while(!(isEmpty(temp))){
		printf("%d ", peek(temp));
		pop(&temp);
	}
	printf("\n");
	
}
// display the top

void visualize(Stack list) {
	if(isEmpty(list)) {
		printf("\nStack is Empty");
		return;
	}
	
	int i;
	printf(" ========= ---> Top of Stack!");
	for(i = list.top; i > empty; i--) {
		printf("\n | %3d   |", list.elem[i]);
	}
	printf("\n ========= ---> Stack Begins Here!\n");
}	
//display the list