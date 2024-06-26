/*
This Program is made with the idea of a Queue of using a Circular Linked List
Ref: Miro ni Bobby for the Illustrations
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 8

typedef struct node{
	char elem;
	struct node* next;
} nodeType, *nodePtr;

typedef struct{
	nodePtr front;
	nodePtr rear;
	int size;
} Queue;

/*	functions	*/
void initQueue(Queue *Q) {
	Q->front = NULL;
	Q->rear = NULL;
	Q->size = -1;
}

bool isEmpty(Queue Q) {
	return Q.front == NULL || Q.size < 0;
}

bool isFull(Queue Q) {
	return Q.size >= (max-1);
}

bool enqueue(Queue *Q, int data) {
	// insert at LAST;
	if(!isFull(*Q)) {
		nodePtr temp = malloc(sizeof(nodeType));
		if(temp != NULL) {
			temp->elem = data;
			temp->next = NULL;
			if(isEmpty(*Q)) {
				Q->front = Q->rear = temp;
			} else {
				Q->rear->next = temp;
				Q->rear = temp;
			}
			Q->rear->next = Q->front;
			Q->size++;
			return 0;
		}
	}
	return 1;
}

bool dequeue(Queue *Q) {
	if(!isEmpty(*Q)) {
		nodePtr temp = Q->front;
		Q->front = Q->front->next;
		free(temp);
		return 0;
	}
	return 1;
}

int front(Queue Q) {
	return (!isEmpty(Q))? Q.front->elem: -1;
}

int rear(Queue Q) {
	return (!isEmpty(Q))? Q.rear->elem: -1;
}

void display(Queue Q) {
	if(!isEmpty(Q)){
		printf("\nContent of Queue:]\n");
		nodePtr current = Q.front;
		while(current != Q.rear) {
			printf(" %d ", current->elem);
			current = current->next;
		}
        printf("\tEnd of Queue: \n");
	} else {
		printf("Queue Empty \n");
	}
}

/*	main function	*/
int main() {
	Queue q;
	initQueue(&q);
	
	printf("\n** Enqueued data **\n");
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	enqueue(&q, 4);
	enqueue(&q, 5);
	
	display(q);
	
	printf("\n** Dequeued data **\n");
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	
	display(q);
	
	printf("\nFront Data - %d\n", front(q));
	printf("Rear Data - %d\n", rear(q));
	
	return 0;
}
