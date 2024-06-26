#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mySet.h"

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
		if(a.elems[x] &  !b.elems[x]) {
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
