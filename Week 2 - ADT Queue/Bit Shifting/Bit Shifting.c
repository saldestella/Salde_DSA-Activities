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
	(n != 0)?  ((*B)|= (1<<pos)) : ((*B) &= ~(1<<pos));
}
	// Changes the bit value based on the bit position

void checkBit(Set B, Bit pos) {
	printf("\n  Bit Position %d is %d", pos, ((B & (1<<pos))? 1:0));
}
	// Checks the bit value based on the bit position

int main() {
    unsigned char numBits = 0;
    int n;
    
    printf(" %12s    | %s", "Binary", "Decimal");
        
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