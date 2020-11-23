#include <stdio.h>

// 1 - 100
void funkcija(int n) {
	if (n <= 100) {
		printf("\n%d", n);
		funkcija(n + 1);
	}
}

// 100 - 1
void funkcija2(int n) {
	if (n <= 100) {
		funkcija2(n + 1);
		printf("\n%d", n);
	}
}

// a = 365
void obrnuto(int a) {
	
}

// 2, 5 = 2 + 3 + 4 + 5 
int zbroj(int a, int b) {
	if (a <= b)
		return a + zbroj(a + 1, b);
	return 0;
}

void main()
{
	funkcija2(1);
	obrnuto(365);

	// 5
	// 6
	// 3
}