#include <stdio.h>

void recursive(int n) {
	if (n == 0) {
		return;
	}
	recursive(n - 1);
	printf("%d\n", n);
}

int main() {

	recursive(3);

	return 0;
}