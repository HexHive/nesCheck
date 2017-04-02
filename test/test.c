#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int* e; // simple pointer to an integer
	int* a; // array of integers (will use pointer arithmetic)
	int acc;
	int i0;

	printf("Welcome!\n");
	a = malloc(3 * sizeof(int));
	e = malloc(sizeof(int));

	// simple pointer dereference
	*e = 13;
	i0 = *e;

	// pointer as array of integers
	a[0] = 1;
	a[1] = 2;
	a[2] = 4;
	// a += 10;
	*a = 5;
	//a -= 10;

	// sum of array's elements
	i0 = 1;
	acc += *(a);
	acc += *(a + i0);
	acc += *(a + 2);
	a++; // move array pointer 1 position ahead
	acc += *(a);
	printf("acc = %d\n", acc);

	// cast of pointer to int
	i0 = (int)a;

	return 0;
}
