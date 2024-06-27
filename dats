/////////////////////////////////////
/////// DICTIONARY///////////////////////////////////////////#DICTIONARY#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure for storing blocks data
typedef struct {
    char blocks[20];
    int count;
} mc_blocks;

// Node structure for linked list in hash table
typedef struct node {
    mc_blocks data;
    struct node* next;
} Node, *NodePtr;

// Hash table structure
typedef struct {
    NodePtr *dict;
    int count;
    int max;
    int threshold;
} MyDictionary;

// Access list to track data access order
typedef struct {
    NodePtr front;
    NodePtr rear;
} AccessList;

void initDictionary(MyDictionary *md);
void initAccessList(AccessList *al);
void insertInto(MyDictionary *md, AccessList *al, mc_blocks data);
int hash(char blocks[], int max);
bool enqueue(AccessList *al, mc_blocks data);
bool dequeue(AccessList *al);
bool isEmpty(AccessList al);
mc_blocks front(AccessList al);
void visualize(MyDictionary md);
bool search(MyDictionary md, char data[]);
void resize(MyDictionary *md, AccessList *al);
mc_blocks retrieve(MyDictionary md, char data[]);
void delete(MyDictionary *md, AccessList *al, char data[]);
void updateData(MyDictionary *md, AccessList *al, char data[], char uData[]);
bool removeNode(NodePtr *head, char data[]);

void initDictionary(MyDictionary *md) {
    md->max = 10; // Default size
    md->count = 0;
    md->threshold = 7; // Resize threshold
    md->dict = (NodePtr*) malloc(md->max * sizeof(NodePtr));
    for (int i = 0; i < md->max; i++) {
        md->dict[i] = NULL;
    }
}

void initAccessList(AccessList *al) {
    al->front = NULL;
    al->rear = NULL;
}

int hash(char blocks[], int max) {
    unsigned long hash = 5381;
    int c;
    while ((c = *blocks++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % max;
}

void insertInto(MyDictionary *md, AccessList *al, mc_blocks data) {
    int index = hash(data.blocks, md->max);
    NodePtr newNode = (NodePtr) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = md->dict[index];
    md->dict[index] = newNode;
    md->count++;
    if (md->count > md->threshold) {
        resize(md, al);
    }
    enqueue(al, data);
}

bool enqueue(AccessList *al, mc_blocks data) {
    NodePtr newNode = (NodePtr) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (al->rear != NULL) {
        al->rear->next = newNode;
    }
    al->rear = newNode;
    if (al->front == NULL) {
        al->front = newNode;
    }
    return true;
}

bool dequeue(AccessList *al) {
    if (al->front == NULL) {
        return false;
    }
    NodePtr temp = al->front;
    al->front = al->front->next;
    if (al->front == NULL) {
        al->rear = NULL;
    }
    free(temp);
    return true;
}

bool isEmpty(AccessList al) {
    return al.front == NULL;
}

void resize(MyDictionary *md, AccessList *al) {
    int oldSize = md->max;
    md->max *= 2;
    NodePtr *newDict = (NodePtr*) malloc(md->max * sizeof(NodePtr));
    for (int i = 0; i < md->max; i++) {
        newDict[i] = NULL;
    }

    for (int i = 0; i < oldSize; i++) {
        NodePtr temp = md->dict[i];
        while (temp != NULL) {
            NodePtr next = temp->next;
            int index = hash(temp->data.blocks, md->max);
            temp->next = newDict[index];
            newDict[index] = temp;
            temp = next;
        }
    }
    free(md->dict);
    md->dict = newDict;
}

bool search(MyDictionary md, char data[]) {
    int index = hash(data, md.max);
    NodePtr current = md.dict[index];
    while (current != NULL) {
        if (strcmp(current->data.blocks, data) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

mc_blocks retrieve(MyDictionary md, char data[]) {
    int index = hash(data, md.max);
    NodePtr current = md.dict[index];
    while (current != NULL) {
        if (strcmp(current->data.blocks, data) == 0) {
            return current->data;
        }
        current = current->next;
    }
    mc_blocks empty = {"", 0};
    return empty; // Return an empty block if not found
}

void delete(MyDictionary *md, AccessList *al, char data[]) {
    int index = hash(data, md->max);
    if (removeNode(&(md->dict[index]), data)) {
        md->count--;
        NodePtr prev = NULL;
        NodePtr current = al->front;
        while (current != NULL) {
            if (strcmp(current->data.blocks, data) == 0) {
                if (prev == NULL) { // Deleting the front
                    dequeue(al);
                } else {
                    prev->next = current->next;
                    if (current->next == NULL) { // Deleting the rear
                        al->rear = prev;
                    }
                    free(current);
                }
                break;
            }
            prev = current;
            current = current->next;
        }
    }
}

bool removeNode(NodePtr *head, char data[]) {
    NodePtr current = *head;
    NodePtr prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data.blocks, data) == 0) {
            if (prev == NULL) { // Removing the first node
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false; // Data not found
}

void updateData(MyDictionary *md, AccessList *al, char data[], char uData[]) {
    delete(md, al, data);
    mc_blocks newData = { "", 64 };
    strcpy(newData.blocks, uData);
    insertInto(md, al, newData);
}

void visualize(MyDictionary md) {
    printf("Current State of Dictionary:\n");
    for (int i = 0; i < md.max; i++) {
        NodePtr temp = md.dict[i];
        if (temp != NULL) {
            printf("Index %d:\n", i);
            while (temp != NULL) {
                printf("  %s - %d\n", temp->data.blocks, temp->data.count);
                temp = temp->next;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    MyDictionary md;
    AccessList al;

    initDictionary(&md);
    initAccessList(&al);

    mc_blocks data[] = {
        {"sand", 64}, {"grass", 64}, {"wool", 64}, {"wood", 64},
        {"lapis", 64}, {"diamond", 64}, {"planks", 64}, {"wood", 64}
    };

    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        insertInto(&md, &al, data[i]);
        printf("Inserted %s -- %d units\n", data[i].blocks, data[i].count);
    }

    visualize(md);
    delete(&md, &al, "wood");
    visualize(md);
    updateData(&md, &al, "diamond", "emerald");
    visualize(md);

    return 0;
}

/////////////////////////////////////
/////// QUEUE LINKED LIST///////////////////////////////////////////QUEUE LINKED LIST
#include <stdio.h>QUEUE LINKED LIST
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

/////////////////////////////////////
/////// QUEUE CIRCULAR///////////////////////////////////////////
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

/////////////////////////////////////
/////// STACK LINKED LIST//////////////////////////////////////////#ifndef STACK_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 5

typedef int Data;

typedef struct node {
    Data elem;
    struct node *next;
} nodeType, *nodePtr;

typedef struct {
    nodePtr top;
    int ctr;
} Stack;

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
        printf("   * Push Unsuccessful. Stack is Full.*\n");
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
        printf("   * Pop Unsuccessful. Stack is Empty.*\n");
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
        printf("\n   * Stack is Empty *"); return;
    }
    
    Stack temp;
    initStack(&temp);
    printf("\n Popping Stack, Pushing Temp");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(S)) {
        push(&temp, peek(S));
        pop(S);
        printf("\n    | %3d   |", temp.top->elem);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");
    
    printf("\n\n Popping Temp, Pushing Stack");
    printf("\n    ========= ---> Top of Stack!");
    while(!isEmpty(&temp)) {
        push(S, peek(&temp));
        printf("\n    | %3d   |", temp.top->elem);
        pop(&temp);
    }
    printf("\n    ========= ---> Stack Begins Here!\n");
}

void visualize(Stack *S){
    if(isEmpty(S)) {
        printf("\n   * Stack is Empty *"); return;
    }
    nodePtr temp = S->top;
    printf("\n    ========= ---> Top of Stack!");
    for(; temp != NULL; temp = temp->next) {
        printf("\n    | %3d   |", temp->elem);
    }
	printf("\n    ========= ---> Stack Begins Here!\n");
}

/////////////////////////////////////
/////// BIT SHIFTING //////////////////////////////////////////#BIT SHIFTING
#include <stdio.h>

typedef unsigned char Set;
typedef int Bit;

/*
TASK(s):
	Display:
		bit 2 to 1
		bit 5 to 1
		bit 6 to 1
		bit 5 to 0
		
	Check if Bit is 1 or 0;
*/

int bitEquivalent(Set B) {
	int val = 0, pow = 0;
	for(; B > 0; B>>=1, pow++) {
		if(B & 1) {
			val += (1<<pow);
		}
	}
	return val;
}
	// Converts the Bits to its Decimal(Base10) Equivalent

void display(Set B) {
	Set mask = 1 << (sizeof(Set) * 8-1);
	printf("\n");
	for(; mask > 0; mask >>= 1) {
		printf(" %d", ((B & mask) != 0)? 1: 0);
	}
	int value = bitEquivalent(B);
	printf(" | %6d", value);
}
	// Display the Bits

void setBit(Set *B, Bit pos, Bit n) {
	(n != 0)?  ((*B)|= (1<<pos)) : ((*B) &= ~(1<<pos));
}
	// Changes the bit value based on the bit position

void checkBit(Set B, Bit pos) {
	printf("\n  Bit Position %d is %d", pos, ((B & (1<<pos))? 1:0));
}
	// Checks the bit value based on the bit position

int main() {
    unsigned char numBits = 0;
    int n;
    
    printf(" %12s    | %s", "Binary", "Decimal");
        
    display(numBits);

    setBit(&numBits, 2, 1);
    display(numBits);

    setBit(&numBits, 5, 1);
    display(numBits);

    
    setBit(&numBits, 6, 1);
    display(numBits);
    
    setBit(&numBits, 5, 0);
    display(numBits);
	
	printf("\n");
    for(n = 0; n < 8; n++) {
        checkBit(numBits, n);
    }
    
    return 0;
}

/////////////////////////////////////
/////// SETS ///////////////////////////////////////////#SETS
#define MAX 20

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char String[5];

typedef struct {
	bool elems[MAX];
	int count;
} Set;

Set newSet() {
	// create a new set;
	Set new;
	memset(new.elems, false, MAX);
	new.count = 0;
	return new;
}

bool addElement(Set *s, int item) {
	// check is item with MAX bounds, OR if item index exists , OR item is a negative number
	if(item >= MAX || s->elems[item] || item < 0) {
		return false;
	} 
	// start adding elem
	s->elems[item] = true;
	s->count++;
	return true;
}

bool removeElement(Set *s, int item) {
	// item == index
	// check is item with MAX bounds, OR if item index exists , OR item is a negative number
	if(item >= MAX || s->elems[item] || item < 0) {
		return false;
	} 
	// start deleting by setting elem at item-index at '0'
	s->elems[item] = true;
	s->count--;
	return true;
}

void displaySet(Set s) {
	if(s.count == 0) {
		printf("\nSET IS EMPTY\n");
		return;
	}
	int x;
	printf(" ===================\n");
	printf(" Content of Set:\n [Index] | [Element]\n");
	for(x = 0; x < MAX; x++) {
		printf(" %7d | %3d\n", x, s.elems[x]);
	}
	printf(" ===================\n\n");
	
}

/*

typedef char String[5];

typedef struct {
	bool elems[MAX];
	int count;
}Set;

*/
Set unionSet(Set a, Set b) {
	// A + B
	Set c = newSet();
	int x;
	for(x = 0; x < MAX; x++) {
		if(a.elems[x] || b.elems[x]) {
			c.elems[x] = true;
			c.count++;
		}
	}
	return c;
}

Set intersectionSet(Set a, Set b) {
	// A & B
		Set c = newSet();
	int x;
	for(x = 0; x < MAX; x++) {
		if(a.elems[x] & b.elems[x]) {
			c.elems[x] = true;
			c.count++;
		}
	}
	return c;
}

Set differenceSet(Set a, Set b) {
	// A - B
		Set c = newSet();
	int x;
	for(x = 0; x < MAX; x++) {
		if(a.elems[x] &  !b.elems[x]) {
			c.elems[x] = true;
			c.count++;
		}
	}
	return c;
}

Set symmetricDiffSet(Set a, Set b) {
	//if A and B are different: 0,1 = true: 0,0 = false
	Set c = newSet();
	int x;
	for(x = 0; x < MAX; x++) {
		if(a.elems[x] != b.elems[x]) {
			c.elems[x] = true;
			c.count++;
		}
	}
	return c;

}

/////////////////////////////////////
///////OPEN HASHING JE///////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OpenHashing.h"

// Simple polynomial rolling hash function for strings
int hashFunction(char* lastName, int max) {
    int p = 31;
    int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;

    for (char* c=lastName; *c != '\0'; ++c) {
        hash_value = (hash_value + (*c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value % max;
}

Dictionary* initDictionary(int max) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->array = (SType**)calloc(max, sizeof(SType*));
    dict->count = 0;
    dict->max = max;
    return dict;
}

int addStudent(Dictionary* dict, Student s) {
    int index = hashFunction(s.studentName.lastName, dict->max);
    SType* newNode = (SType*)malloc(sizeof(SType));
    newNode->student = s;
    newNode->link = dict->array[index];
    dict->array[index] = newNode;
    dict->count++;
    return index;
}

Student* getStudent(Dictionary* dict, int id) {
    for (int i = 0; i < dict->max; i++) {
        SType* node = dict->array[i];
        while (node != NULL) {
            if (node->student.studentID == id) {
                return &(node->student);
            }
            node = node->link;
        }
    }
    return NULL;
}

int deleteStudent(Dictionary* dict, int id) {
    for (int i = 0; i < dict->max; i++) {
        SType* node = dict->array[i];
        SType* prevNode = NULL;
        while (node != NULL) {
            if (node->student.studentID == id) {
                if (prevNode == NULL) {
                    dict->array[i] = node->link;
                } else {
                    prevNode->link = node->link;
                }
                free(node);
                dict->count--;
                return 1;
            }
            prevNode = node;
            node = node->link;
        }
    }
    return 0;
}

void visualize(Dictionary* dict) {
    for (int i = 0; i < dict->max; i++) {
        printf("Index %d:\n", i);
        SType* node = dict->array[i];
        while (node != NULL) {
            printf("    ID: %d, Name: %s %s %s\n",
                node->student.studentID,
                node->student.studentName.firstName,
                node->student.studentName.middleName,
                node->student.studentName.lastName);
            node = node->link;
        }
    }
}

void clearDictionary(Dictionary* dict) {
    for (int i = 0; i < dict->max; i++) {
        SType* node = dict->array[i];
        while (node != NULL) {
            SType* temp = node;
            node = node->link;
            free(temp);
        }
    }
    free(dict->array);
    free(dict);
}
