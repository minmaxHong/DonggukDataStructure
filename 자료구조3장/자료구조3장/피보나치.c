#include <stdio.h>

int fib_iter(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}

	int p = 0;
	int pp = 1;
	int result = 1;

	for (int i = 2; i <= n; ++i) {
		result = p + pp;
		p = pp;
		pp = result;
	}
	return result;
}

int main() {

	int result = fib_iter(3);

	printf("%d", result);

	return 0;
}