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
                printf(" + ");
            }
            // 변수가 존재하는 경우에만 출력
            if (poly.terms[i].variable[0] != 0 && poly.terms[i].variable[0] > 0) {
                if (poly.terms[i].coef > 0) {
                    printf("%.2f", poly.terms[i].coef);
                }
                else if (poly.terms[i].coef < 0) {
                    printf(" - ");
                    printf("%.2f", -poly.terms[i].coef);
                }
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

                int temp2 = A.terms[i].expon[0];
                A.terms[i].expon[0] = A.terms[i].expon[1];
                A.terms[i].expon[1] = temp2;
            }
        }
        exist_variable_cnt = 0;
    }

    // variable[0]이 비어있고 variable[1]이 있다면 variable[0]값에 variable[1]값을 매워주기 ex) "\0""x"
    // expon도 마찬가지
    char temp;
    int temp2;
    for (int i = 0; i < A.num_terms; ++i) {
        if (A.terms[i].variable[0] == '\0' && A.terms[i].variable[1] != '\0') {
            temp = A.terms[i].variable[1];
            A.terms[i].variable[1] = A.terms[i].variable[0];
            A.terms[i].variable[0] = temp;

            temp2 = A.terms[i].expon[1];
            A.terms[i].expon[1] = A.terms[i].expon[0];
            A.terms[i].expon[0] = temp2;
        }
    }
    return A;
}

int compare(const void* a, const void* b) {
    const struct Term* term1 = (const struct Term*)a;
    const struct Term* term2 = (const struct Term*)b;

    // 변수가 'x'인 항이 먼저 나오도록 정렬
    if (term1->variable[0] == 'x' && term2->variable[0] == 'x') {
    // x의 차수가 같을 때
    if (term1->expon[0] == term2->expon[0]) {
        // xy가 있는 경우
        if (term1->variable[1] == 'y' && term2->variable[1] != 'y') {
            return -1; // xy가 x보다 우선순위를 가져야 함
        }
        else if (term1->variable[1] != 'y' && term2->variable[1] == 'y') {
            return 1; // x가 xy보다 우선순위를 가져야 함
        }
    }
}

    else if (term1->variable[0] != 'x' && term2->variable[0] == 'x') {
        return 1;
    }

    // 변수가 'y'인 항이 먼저 나오도록 정렬
    if (term1->variable[0] == 'x' && term2->variable[0] != 'x') {
        return -1;
    }
    else if (term1->variable[0] != 'y' && term2->variable[0] == 'y') {
        return 1;
    }

    // 'x' 또는 'y'가 같은 경우
    if (term1->variable[0] == term2->variable[0]) {
        // xy가 먼저 나오도록 정렬
        if (term1->variable[1] == 'y' && term2->variable[1] == '\0') {
            return 1;
        }
        else if (term1->variable[1] == '\0' && term2->variable[1] == 'y') {
            return -1;
        }

        // x의 차수가 높은 것이 먼저 나오도록 정렬
        if (term1->expon[0] != term2->expon[0]) {
            return term2->expon[0] - term1->expon[0];
        }

        // y의 차수가 높은 것이 먼저 나오도록 정렬
        if (term1->variable[1] == 'y' && term2->variable[1] == 'y') {
            return term2->expon[1] - term1->expon[1];
        }
    }

    return 0;
}
// 변수끼리의 차수가 같은 항을 서로 계산하여 결과를 얻는 함수
struct Polynomial simplify(struct Polynomial result) {
    for (int i = 0; i < result.num_terms; ++i) {
        for (int j = i + 1; j < result.num_terms; ++j) {
            // 변수와 지수가 같은 항을 찾음
            if (result.terms[i].variable[0] == result.terms[j].variable[0] &&
                result.terms[i].variable[1] == result.terms[j].variable[1] &&
                result.terms[i].expon[0] == result.terms[j].expon[0] &&
                result.terms[i].expon[1] == result.terms[j].expon[1]) {
                // 계수를 더하고 한 쪽의 항을 삭제
                result.terms[i].coef += result.terms[j].coef;
                // 삭제된 항을 나중에 삭제하기 위해 coef를 0으로 설정
                result.terms[j].coef = 0;
            }
        }
    }

    // 삭제된 항들을 제거하고 결과 반환
    int newIndex = 0;
    for (int i = 0; i < result.num_terms; ++i) {
        if (result.terms[i].coef != 0) {
            result.terms[newIndex] = result.terms[i];
            newIndex++;
        }
    }
    result.num_terms = newIndex;

    return result;
}


int main() {
    struct Polynomial A;
    struct Polynomial B;

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

    // 곱하기
    struct Polynomial result = mat(A, B);

    // yx -> xy
    struct Polynomial yx2xyresult = yx2xy(result);

    // 다항식 내림차순 x, xy, y순서 && 내림차순
    qsort(yx2xyresult.terms, yx2xyresult.num_terms, sizeof(struct Term), compare);

    // 다항식 정리
    struct Polynomial simplifiedResult = simplify(yx2xyresult);
    printEach_polynomial(simplifiedResult);

    return 0;
}
