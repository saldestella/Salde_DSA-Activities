#include <stdio.h>
#include <stdlib.h>
#include "stackArray.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Stack list;
	
	initStack(&list);

	push(&list, 3);
	push(&list, 5);
	push(&list, 2);
	push(&list, 7);
	
	printf("\nVISUALIZE STACK\n");
	visualize(list);
	
	printf("\nVISUALIZE STACK\n");
	visualize(list);
	
	
	printf("\nDISPLAY STACK\n");
	display(list);

	printf("\nVISUALIZE STACK\n");
	visualize(list);
	
//	freeStack(list);
	
	printf("\ntest");
	return 0;
}