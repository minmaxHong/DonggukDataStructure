#include <stdio.h>

// n^x
int power(int x, int n) {
	if (n == 0) {
		return 1;
	}

	else if (n % 2 == 0) {
		return power(x * x, n / 2);
	}

	else if (n % 2 == 1) {
		return x * power(x * x, (n - 1) / 2);
	}
}

int main() {

	int result = power(4, 3);

	printf("%d", result);

	return 0;
}