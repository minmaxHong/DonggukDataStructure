#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101
#define MAX_VARIABLES 2

// 일단 예제에 있는 것만 제대로 해보자 !

// 다항식 항
struct Term {
    float coef; // 항의 계수
    char* variable; // 항의 변수
    int expon; // 항의 지수
};

// 다항식 표현
struct Polynomial {
    struct Term terms[MAX_TERMS]; // 항 표현
    int num_terms; // 항의 개수
};

// 다항식 입력
struct Polynomial inputPolynomial() {
    struct Polynomial poly;
    printf("다항식의 항의 개수를 입력하세요: ");
    scanf_s("%d", &poly.num_terms);
    
    // 변수는 동적 할당
    for (int i = 0; i < poly.num_terms; ++i) {
        poly.terms[i].variable = malloc(2 * sizeof(char));
        if (poly.terms[i].variable == NULL) {
            printf("동적 할당 오류 !!!!");
            exit(1);
        }
    }

    for (int i = 0; i < poly.num_terms; ++i) {
        printf("다항식의 %d번째 항의 계수를 입력하세요: ", i + 1);
        scanf_s("%f", &poly.terms[i].coef);

        printf("다항식의 %d번째 항의 변수를 입력하세요: ", i + 1);
        scanf_s(" %c", &poly.terms[i].variable);

        printf("다항식의 %d번째 항의 지수를 입력하세요: ", i + 1);
        scanf_s("%d", &poly.terms[i].expon);
    }
    return poly;
}

// 다항식 정보 보기
void printEach_polynomial(struct Polynomial poly) {
    int i = 0;
    for (i = 0; i < poly.num_terms - 1; ++i) {
        if (poly.terms[i].coef > 0 && i != 0) { // 첫번째 항이 +부호이면, 안보이게끔
            printf("+");
        }
        printf("%.2f%c^%d", poly.terms[i].coef, poly.terms[i].variable, poly.terms[i].expon);
    }
    // 상수항 출력
    if (poly.terms[i].expon == 0) {
        if (poly.terms[i].coef > 0) {
            printf("+");
        }
        printf("%.2f", poly.terms[poly.num_terms - 1].coef);
    }
    printf("\n");
}

// 다항식 곱셈
// 일단 같은 변수만 조합해서 해보자
struct Polynomial multiplyPolynomial(struct Polynomial A, struct Polynomial B) {
    struct Polynomial result;
    result.num_terms = 0;

    for (int i = 0; i < A.num_terms; ++i) {
        for (int j = 0; j < B.num_terms; ++j) {
            if (strcmp(A.terms[i].variable, B.terms[j].variable) == 0) {
                result.terms[result.num_terms].coef = A.terms[i].coef * B.terms[j].coef;

                result.terms[result.num_terms].variable = malloc(2 * sizeof(char));
                strcpy(result.terms[result.num_terms].variable, A.terms[i].variable);
                result.terms[result.num_terms++].expon = A.terms[i].expon + B.terms[j].expon;
            }
        }
    }
    return result;
}
int main() {

    // =====================================================
    struct Polynomial A;

    // A 다항식 입력
    printf("== A 다항식 정보 입력 ==\n");
    A = inputPolynomial();

    // A 다항식 정보 보기
    printf("A의 다항식 정보 : ");
    printEach_polynomial(A);
    // =====================================================



    // =====================================================
    // 다항식 B 초기화
    struct Polynomial B;
    printf("\n== B 다항식 정보 입력 ==\n");
    B = inputPolynomial();
    
    // B다항식 정보 보기 
    printf("B의 다항식 정보 : ");
    printEach_polynomial(B);
    // =====================================================
    printf("\n");

    // =====================================================
    // 다항 A, B 곱셈
    struct Polynomial multiply_A_B;
    multiply_A_B = multiplyPolynomial(A, B);
    printEach_polynomial(multiply_A_B);

    // =====================================================

    return 0;
}
