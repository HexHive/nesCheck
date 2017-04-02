#include <stdlib.h>

typedef int numero;
typedef numero* myintptr;

int main(void) {
	int **a;
	int i;
	int acc;
	int **p;
	int *e;

	myintptr weird;
	char x[10];

	a = malloc(100 * sizeof(int*));
	x[2] = 'a';

	acc = 0;
	for (i=0; i<100; i++) {
		p = a + i;
		e = *p;
		while ((int) e % 2 == 0) {
			e = *(int**)e;
		}
		acc += ((int)e >> 1);
	}

	return 0;
}
