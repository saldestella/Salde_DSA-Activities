#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "classWithdraw.h"

void initStack(classStack *s) {
	s->top = -1;
}

void initQueue(ReservedQ *q) {
    q->front = 0;
    q->rear = MAX-1;
}

bool stack_push(classStack *s, studentInfo stud) {
    if(!isFullStack(*s)) {
        s->classList[s->top] = stud;
        return 0;
    }
    printf("   * Push Unsuccessful. Stack is Full.*\n");
    return -1;
}

bool stack_pop(classStack *s) {
    if(!isFullStack(*s)) {
        s->top--;
        return 0;
    }    
    return 1;
}

studentInfo stack_peek(classStack s) {
    return s.classList[s.top];
}

bool isEmptyStack(classStack s) {
    return s.top < 0;
}

bool isFullStack(classStack s) {
    return s.top >= (MAX-1);
}

void displayStack(classStack s) {
    classStack temp;
    initStack(&temp);
    studentInfo info;
    
    while(!isEmptyStack(s)) {
        info = stack_peek(s);
        
        printf("Student Name: %s, %s\n", info.name.lastName, info.name.firstName);
        printf("ID Number: %d\n", info.idNum);
        printf("Gender: %c\n", info.gender);
        printf("Birthday: %d %d\n", info.bdate.month, info.bdate.year);
        printf("Age: %d\n", info.age);
        printf("Year Level: %d\n", info.yrLevel);
        printf("====================\n\n");
        
        stack_push(&temp, info);
        stack_pop(&s);
    }
    
    while(!isEmptyStack(temp)){
        stack_push(&s, stack_peek(temp));
        stack_pop(&temp);
        
    }   
}

bool enqueue(ReservedQ *q, studentInfo stud) {
    // insert Last
    if(!isFullQueue(*q)) {
        q->rear = ((q->rear + 1) % MAX);
        q->stud[q->rear] = stud;
        return 0;
    }
    printf("Queue is Full\n");
    return 1;
}

bool dequeue(ReservedQ *q) {
    if(!isEmptyQueue(*q)) {
        q->front = ((q->front + 1) % MAX);
        return 0;
    }
    printf("Queue is Empty\n");
    return 1;
}

studentInfo front(ReservedQ q){
    // if !isEmptyQueue(q);
    return q.stud[q.front];
}

studentInfo rear(ReservedQ q) {
    // if !isEmptyQueue(q);
    return q.stud[q.rear];
}

bool isEmptyQueue(ReservedQ q) {
    return ((q.rear + 1) % MAX == q.front)? 0: 1;
}

bool isFullQueue(ReservedQ q) {
    return ((q.rear + 2) % MAX == q.front)? 0: 1;
}

void displayQueue(ReservedQ q) {
    if(!isEmptyQueue(q)) {
        ReservedQ temp;
        initQueue(&q);
        studentInfo info;
        
        while(!isEmptyQueue(q)) {
            info = front(q);
            
            printf("Name: %s %s\n", info.name.firstName, info.name.lastName);
            printf("Birthdate: %d, %d\n", info.bdate.month, info.bdate.year);
            printf("Age: %d\n", info.age);
            printf("Gender: %c\n", info.gender);
            printf("ID Number: %d\n", info.idNum);
            printf("=============================\n\n");
            
            enqueue(&temp, info);
            dequeue(&q);
        }
        
        while(!isEmptyQueue(temp)) {
            enqueue(&q, front(temp));
            dequeue(&temp);
        }
    }
}

void enroll(studentInfo stud, classStack *s, ReservedQ *q){
    if(!isFullStack(*s)) {
        stack_push(s, stud);
        printf("Student Enrolled in Class!\n");
    } else {
        if(!isFullQueue(*q)) {
            enqueue(q, stud);
            printf("Student Waitlisted!\n");
        } else {
            printf("Enrolment Closed!\n");
            return;
        }
    }
}

void withdraw(int id, classStack *s, ReservedQ *q) {
    classStack temp;
    initStack(&temp);
    studentInfo info;

    if(!isEmptyStack(*s)) {
        while(!isEmptyStack(*s)) {
            info = stack_peek(*s);
            stack_pop(s);
            if(info.idNum != id) {
                stack_push(&temp, info);
            } else {
                printf("Student Withdrawn!\n");
            }
        }
        
        while(!isEmptyStack(temp)) {
            stack_push(s, stack_peek(temp));
            stack_pop(s);
        }
        
        if(!isEmptyQueue(*q)) {
            stack_push(s, front(*q));
            dequeue(q);
        }
    }
}