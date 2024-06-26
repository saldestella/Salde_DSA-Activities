/*
This Program is made with the idea of a Queue of using a Circular Array
Ref: Miro ni Bobby for the Illustrations
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 8

typedef struct {
    char elem[max];
    int rear, front;
} Queue;

void initQueue(Queue *Q) {
    // set front and rear
    Q->front = 0;
    Q->rear = max-1;
}

bool isEmpty(Queue Q) {
    return (Q.rear + 1) % max == Q.front;
}

bool isFull(Queue Q) {
    return (Q.rear + 2) % max == Q.front;
}

char front(Queue Q) {
    if(!isEmpty(Q)) {
        return Q.elem[Q.front];
    }
    return '\0'; //huhu idk why
    
    /*
    or
    return (!isEmpty(Q))? Q->elem[!->front]: '\0';
    */
}

char rear(Queue Q) {
    return (!isEmpty(Q))? Q.elem[Q.rear] : '\0';
    // unsay pulos nimo dear
}

void EnQ(Queue *Q, char x) {
    // Insert LAST | Insert Rear (IEar)
    if(!isFull(*Q)) { // check is full sa
        Q->rear = ((Q->rear+1) % max);
        // move rear index before inserting
        Q->elem[Q->rear] = x;
        return;
    } 
    printf("Queue is Full\n");
}

void DeQ(Queue *Q) {
    // Deletes First || (DeF)
    if(!isEmpty(*Q)) {
        Q->front = ((Q->front +1) % max);
        // move front index || not need to manipulate Q->elem
        return;
    }
        printf("Queue is Empty\n");
}

void displayQ(Queue Q) {
    if(!isEmpty(Q)) {
        int x = Q.front;
        printf("\nContent of Queue:\n [Index] | [Element]\n");
        for(; x != (Q.rear+1)%max; x = (x + 1) % max) {
            printf(" %7d | %3c\n", x, Q.elem[x]);
        }
        printf("End of Queue: \n");
    }
}

int main () {
    Queue Queue;
    
    initQueue(&Queue);
    EnQ(&Queue, 'a');
    EnQ(&Queue, 'b');
    EnQ(&Queue, 'c');
    displayQ(Queue);
    
    DeQ(&Queue);
    DeQ(&Queue);
    displayQ(Queue);
    
    EnQ(&Queue, 'd');
    displayQ(Queue);
    
    return 0;
}