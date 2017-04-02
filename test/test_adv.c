#include <stdlib.h>

int sum2(int *a) {
	int i;
	int acc = 0;

	for (i=0; i<100; i++)
		acc += a[i];

	return acc;
}

int sum(int **a) {
	int i;
	int acc = 0;

	for (i=0; i<100; i++)
		acc += **(a + i);

	return acc;
}

int main(void) {
	int **a;
	int tot;

	a = malloc(100 * sizeof(int*));

	tot = sum(a);

	printf("tot is %d\n", tot);

	return 0;
}
