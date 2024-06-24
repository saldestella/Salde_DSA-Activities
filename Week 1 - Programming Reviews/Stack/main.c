#include <stdio.h>
#include <stdlib.h>
#include "stack_array.h"
// #include "stack_linkedlist.h"


int main() {

    Stack stack;

    // initialize the stack
    initStack(&stack);

    // check if the stack is empty
    printf("\nIs the stack empty? %s\n", isEmpty(&stack) ? "Yes" : "No");

    // try to pop from empty stack
    printf("\nTrying to pop from the empty stack...\n");
    pop(&stack);
    
    //push elements to the stack
    printf("Pushing elements to the stack...\n");
    for (int i = 0; i < max; i++) {
        push(&stack, i);
        visualize(&stack);
    }

    // check if the stack is full
    printf("\nIs the stack full? %s\n", isFull(&stack) ? "Yes" : "No");

    // try to push when the stack is full
    printf("\nTrying to push to the full stack...\n");
    push(&stack, max);
    
    visualize(&stack);

    // peek at the top item
    printf("\nTop item of the stack: %d\n", peek(&stack));

    // visualizing temp_stack using pop/pull operations only *
    printf("\ntemp_stack (made using pop/push only): ");
    display(&stack);

    // pop items from the stack
    printf("\nPopping items from the stack...\n");
    while (!isEmpty(&stack)) {
        pop(&stack);
        visualize(&stack);
    }

    // check if the stack is empty
    printf("\n\nIs the stack empty? %s\n", isEmpty(&stack) ? "Yes" : "No");

    return 0;
}
