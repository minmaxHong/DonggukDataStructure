#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101
#define MAX_VARIABLES 2

// 다항식 각 항 표현
struct Term {
    float coef; // 항의 계수
    char variable[MAX_VARIABLES]; // 항의 변수
    int expon[MAX_VARIABLES]; // 항의 지수
};

// 다항식 표현
struct Polynomial {
    struct Term terms[MAX_TERMS]; // 항 표현
    int num_terms; // 항의 개수
};

// 다항식 정보 보기
void printEach_polynomial(struct Polynomial poly) {
    int i;
    int term_printed = 0; // 이미 항이 출력되었는지 여부를 나타내는 플래그

    for (i = 0; i < poly.num_terms; ++i) {
        if (poly.terms[i].coef != 0) { // 항이 존재하는 경우에만 출력
            if (poly.terms[i].coef > 0 && term_printed) { // 첫번째 항이 아니고 +부호이면 추가
                printf(" +");
            }

            // 변수가 존재하는 경우에만 출력
            if (poly.terms[i].variable[0] != 0) {
                printf(" %.2f", poly.terms[i].coef);

                // 변수 출력
                for (int j = 0; j < MAX_VARIABLES; ++j) {
                    if (poly.terms[i].variable[j] != 0) {
                        printf("%c", poly.terms[i].variable[j]);

                        // 지수가 1보다 큰 경우에만 출력
                        if (poly.terms[i].expon[j] > 1) {
                            printf("^%d", poly.terms[i].expon[j]);
                        }
                    }
                }
            }
            else {
                // 변수가 없는 경우
                printf(" %.2f", poly.terms[i].coef);

                if (poly.terms[i].variable[0] == 0) {
                    ;
                }
                if (poly.terms[i].variable[1] != 0) {
                    printf("%c^%d", poly.terms[i].variable[1], poly.terms[i].expon[1]);
                }
            }
            term_printed = 1; // 항이 출력되었음을 표시
        }
    }

    // 마지막 항 출력
    if (!term_printed) {
        ; // 모든 항이 없는 경우
    }
    printf("\n");
}
// 다항식 곱셈
struct Polynomial mat(struct Polynomial A, struct Polynomial B) {
    struct Polynomial result;
    result.num_terms = 0;

    for (int i = 0; i < A.num_terms; ++i) {
        for (int j = 0; j < B.num_terms; ++j) {
            // 변수가 같을 때
            if (A.terms[i].variable[0] == B.terms[j].variable[0]) {
                result.terms[result.num_terms].coef = A.terms[i].coef * B.terms[j].coef;
                result.terms[result.num_terms].variable[0] = A.terms[i].variable[0];
                result.terms[result.num_terms].expon[0] = A.terms[i].expon[0] + B.terms[j].expon[0];
                result.terms[result.num_terms].variable[1] = 0; // 변수가 하나일 경우, 두 번째 변수는 0으로 설정
                result.terms[result.num_terms].expon[1] = 0; // 변수가 하나일 경우, 두 번째 지수는 0으로 설정
                result.num_terms++;
            }
            // 변수가 다를 때
            else {
                result.terms[result.num_terms].coef = A.terms[i].coef * B.terms[j].coef;
                result.terms[result.num_terms].variable[0] = A.terms[i].variable[0];
                result.terms[result.num_terms].expon[0] = A.terms[i].expon[0];
                result.terms[result.num_terms].variable[1] = B.terms[j].variable[0];
                result.terms[result.num_terms].expon[1] = B.terms[j].expon[0];
                result.num_terms++;
            }
        }

        
    }
    return result;
}
// yx -> xy로 돌리기
struct Polynomial yx2xy(struct Polynomial A) {
    // 일단 yx인지 알아보기
    int exist_variable_cnt = 0;
    for (int i = 0; i < A.num_terms; ++i) {
        if (A.terms[i].variable[0] >= 'a' && A.terms[i].variable[0] <= 'z') {
            exist_variable_cnt++;
        }
        if (A.terms[i].variable[1] >= 'a' && A.terms[i].variable[1] <= 'z') {
            exist_variable_cnt++;
        }
        // 여기서 이제 variable[0] = 'x'가 들어가면 무효
        // variable[0] = 'y'가 들어가면 바꿔줘야함
        if (exist_variable_cnt == 2) {
            if (A.terms[i].variable[0] == 'y') {
                char temp = A.terms[i].variable[0];
                A.terms[i].variable[0] = A.terms[i].variable[1];
                A.terms[i].variable[1] = temp;
            }
        }
        exist_variable_cnt = 0;
    }
    return A;
}

int main() {

    struct Polynomial A;
    struct Polynomial B;

    printf(" == A == \n");
    A.num_terms = 3;
    A.terms[0].coef = 3;
    A.terms[0].variable[0] = 'y';
    A.terms[0].expon[0] = 7;

    A.terms[1].coef = 4;
    A.terms[1].variable[0] = 'x';
    A.terms[1].expon[0] = 4;

    A.terms[2].coef = -1;
    A.terms[2].variable[0] = 0;
    A.terms[2].expon[0] = 0;

    printEach_polynomial(A);

    printf("== B == \n");
    B.num_terms = 3;
    B.terms[0].coef = 5;
    B.terms[0].variable[0] = 'x';
    B.terms[0].expon[0] = 4;

    B.terms[1].coef = -3;
    B.terms[1].variable[0] = 'y';
    B.terms[1].expon[0] = 2;

    B.terms[2].coef = 7;
    B.terms[2].variable[0] = 0;
    B.terms[2].expon[0] = 0;

    printEach_polynomial(B);

    // 곱하기
    struct Polynomial result = mat(A, B);
    printf("== 다항식 곱셈 결과 == \n");
    printEach_polynomial(result);

    // yx -> xy
    struct Polynomial yx2xyresult = yx2xy(result);
    printf("== 다항식 yx -> xy로 정리 결과 == \n");
    printEach_polynomial(yx2xyresult);
    
    // 다항식 내 계산
    
    
    
    
    return 0;
}
