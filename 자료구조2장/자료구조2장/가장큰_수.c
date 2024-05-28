#define MAX_ELEMENTS 100
#include <stdio.h>

int scores[MAX_ELEMENTS];

int get_max_scores(int n) {
	int max_score = scores[0];
	int i;

	for (i = 1; i < n; i++) {
		if (max_score < scores[i]){
			max_score = scores[i];
		}
	}
	return max_score;
}

int main() {

	int n, i;

	printf("Enter The number of student : ");
	scanf_s("%d", &n);

	for (i = 0; i < n; i++) {
		printf("Enter the Scores {%d} student: ", i + 1);
		scanf_s("%d", &scores[i]);
	}

	int max_score = get_max_scores(n);

	printf("MAX SCORES : %d", max_score);



	return 0;
}