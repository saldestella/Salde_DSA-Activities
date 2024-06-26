#ifndef classWithdrawCircular
// #define classWithdrawCircular

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct{
    char firstName[20];
    char lastName[20];
}Name;

typedef struct{
    int month;
    int year;
}Birthdate;

typedef struct{
    Name name;
    Birthdate bdate;
    int age;
    int idNum;
    char gender;
    int yrLevel;
}studentInfo;

typedef struct{
    studentInfo classList[MAX];
    int top;
}classStack;

typedef struct node {
    studentInfo stud[MAX];
    int front;
    int rear;
}ReservedQ;

void initStack(classStack *s);
void initQueue(ReservedQ *q);
bool stack_push(classStack *s, studentInfo stud);
bool stack_pop(classStack *s);
studentInfo stack_peek(classStack s);
bool isEmptyStack(classStack s);
bool isFullStack(classStack s);
void displayStack(classStack s);
bool enqueue(ReservedQ *q, studentInfo stud);
bool dequeue(ReservedQ *q);
studentInfo front(ReservedQ q);
studentInfo rear(ReservedQ q);
bool isEmptyQueue(ReservedQ q);
bool isFullQueue(ReservedQ q);
void displayQueue(ReservedQ q);
void enroll(studentInfo stud, classStack *s, ReservedQ *q);
void withdraw(int id, classStack *s, ReservedQ *q);


#endif