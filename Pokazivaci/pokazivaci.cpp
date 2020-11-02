#include <stdio.h>

void funkcija(int *a) {
	*a = *a + 1;
	printf("\na = %d %d", *a, a);
}

int f1(int a)
{
	return a + 1;
}

void f2(int **pa, int *b) {
	*pa = b;
}

void main() {

	int a = 6;
	int b = 10;

	printf("\n%d %d", a, &a);
	printf("\n%d %d", b, &b);

	int *pa = &a;

	// pa = &b;
	// funkcija(&a);
	// a = f1(a);

	f2(&pa, &b);

	printf("\n%d %d", a, &a);
}