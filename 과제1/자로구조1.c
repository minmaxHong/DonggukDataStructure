#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101
#define MAX_VARIABLES 2

// ���׽� �� �� ǥ��
struct Term {
    float coef; // ���� ���
    char variable[MAX_VARIABLES]; // ���� ����
    int expon[MAX_VARIABLES]; // ���� ����
};

// ���׽� ǥ��
struct Polynomial {
    struct Term terms[MAX_TERMS]; // �� ǥ��
    int num_terms; // ���� ����
};

// ���׽� ���� ����
void printEach_polynomial(struct Polynomial poly) {
    int i;
    int term_printed = 0; // �̹� ���� ��µǾ����� ���θ� ��Ÿ���� �÷���

    for (i = 0; i < poly.num_terms; ++i) {
        if (poly.terms[i].coef != 0) { // ���� �����ϴ� ��쿡�� ���
            if (poly.terms[i].coef > 0 && term_printed) { // ù��° ���� �ƴϰ� +��ȣ�̸� �߰�
                printf(" + ");
            }
            // ������ �����ϴ� ��쿡�� ���
            if (poly.terms[i].variable[0] != 0 && poly.terms[i].variable[0] > 0) {
                if (poly.terms[i].coef > 0) {
                    printf("%.2f", poly.terms[i].coef);
                }
                else if (poly.terms[i].coef < 0) {
                    printf(" - ");
                    printf("%.2f", -poly.terms[i].coef);
                }
                // ���� ���
                for (int j = 0; j < MAX_VARIABLES; ++j) {
                    if (poly.terms[i].variable[j] != 0) {
                        printf("%c", poly.terms[i].variable[j]);

                        // ������ 1���� ū ��쿡�� ���
                        if (poly.terms[i].expon[j] > 1) {
                            printf("^%d", poly.terms[i].expon[j]);
                        }
                    }
                }
            }
            else {
                // ������ ���� ���
                printf(" %.2f", poly.terms[i].coef);

                if (poly.terms[i].variable[1] != 0) {
                    printf("%c^%d", poly.terms[i].variable[1], poly.terms[i].expon[1]);
                }
            }
            term_printed = 1; // ���� ��µǾ����� ǥ��
        }
    }
    // ������ �� ���
    if (!term_printed) {
        ; // ��� ���� ���� ���
    }
    printf("\n");
}

// ���׽� ����
struct Polynomial mat(struct Polynomial A, struct Polynomial B) {
    struct Polynomial result;
    result.num_terms = 0;

    for (int i = 0; i < A.num_terms; ++i) {
        for (int j = 0; j < B.num_terms; ++j) {
            // ������ ���� ��
            if (A.terms[i].variable[0] == B.terms[j].variable[0]) {
                result.terms[result.num_terms].coef = A.terms[i].coef * B.terms[j].coef;
                result.terms[result.num_terms].variable[0] = A.terms[i].variable[0];
                result.terms[result.num_terms].expon[0] = A.terms[i].expon[0] + B.terms[j].expon[0];
                result.terms[result.num_terms].variable[1] = 0; // ������ �ϳ��� ���, �� ��° ������ 0���� ����
                result.terms[result.num_terms].expon[1] = 0; // ������ �ϳ��� ���, �� ��° ������ 0���� ����
                result.num_terms++;
            }
            // ������ �ٸ� ��
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

// yx -> xy�� ������
struct Polynomial yx2xy(struct Polynomial A) {
    // �ϴ� yx���� �˾ƺ���
    int exist_variable_cnt = 0;
    for (int i = 0; i < A.num_terms; ++i) {
        if (A.terms[i].variable[0] >= 'a' && A.terms[i].variable[0] <= 'z') {
            exist_variable_cnt++;
        }
        if (A.terms[i].variable[1] >= 'a' && A.terms[i].variable[1] <= 'z') {
            exist_variable_cnt++;
        }
        // ���⼭ ���� variable[0] = 'x'�� ���� ��ȿ
        // variable[0] = 'y'�� ���� �ٲ������
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

    // variable[0]�� ����ְ� variable[1]�� �ִٸ� variable[0]���� variable[1]���� �ſ��ֱ� ex) "\0""x"
    // expon�� ��������
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

    // ������ 'x'�� ���� ���� �������� ����
    if (term1->variable[0] == 'x' && term2->variable[0] == 'x') {
    // x�� ������ ���� ��
    if (term1->expon[0] == term2->expon[0]) {
        // xy�� �ִ� ���
        if (term1->variable[1] == 'y' && term2->variable[1] != 'y') {
            return -1; // xy�� x���� �켱������ ������ ��
        }
        else if (term1->variable[1] != 'y' && term2->variable[1] == 'y') {
            return 1; // x�� xy���� �켱������ ������ ��
        }
    }
}

    else if (term1->variable[0] != 'x' && term2->variable[0] == 'x') {
        return 1;
    }

    // ������ 'y'�� ���� ���� �������� ����
    if (term1->variable[0] == 'x' && term2->variable[0] != 'x') {
        return -1;
    }
    else if (term1->variable[0] != 'y' && term2->variable[0] == 'y') {
        return 1;
    }

    // 'x' �Ǵ� 'y'�� ���� ���
    if (term1->variable[0] == term2->variable[0]) {
        // xy�� ���� �������� ����
        if (term1->variable[1] == 'y' && term2->variable[1] == '\0') {
            return 1;
        }
        else if (term1->variable[1] == '\0' && term2->variable[1] == 'y') {
            return -1;
        }

        // x�� ������ ���� ���� ���� �������� ����
        if (term1->expon[0] != term2->expon[0]) {
            return term2->expon[0] - term1->expon[0];
        }

        // y�� ������ ���� ���� ���� �������� ����
        if (term1->variable[1] == 'y' && term2->variable[1] == 'y') {
            return term2->expon[1] - term1->expon[1];
        }
    }

    return 0;
}
// ���������� ������ ���� ���� ���� ����Ͽ� ����� ��� �Լ�
struct Polynomial simplify(struct Polynomial result) {
    for (int i = 0; i < result.num_terms; ++i) {
        for (int j = i + 1; j < result.num_terms; ++j) {
            // ������ ������ ���� ���� ã��
            if (result.terms[i].variable[0] == result.terms[j].variable[0] &&
                result.terms[i].variable[1] == result.terms[j].variable[1] &&
                result.terms[i].expon[0] == result.terms[j].expon[0] &&
                result.terms[i].expon[1] == result.terms[j].expon[1]) {
                // ����� ���ϰ� �� ���� ���� ����
                result.terms[i].coef += result.terms[j].coef;
                // ������ ���� ���߿� �����ϱ� ���� coef�� 0���� ����
                result.terms[j].coef = 0;
            }
        }
    }

    // ������ �׵��� �����ϰ� ��� ��ȯ
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

    // ���ϱ�
    struct Polynomial result = mat(A, B);

    // yx -> xy
    struct Polynomial yx2xyresult = yx2xy(result);

    // ���׽� �������� x, xy, y���� && ��������
    qsort(yx2xyresult.terms, yx2xyresult.num_terms, sizeof(struct Term), compare);

    // ���׽� ����
    struct Polynomial simplifiedResult = simplify(yx2xyresult);
    printEach_polynomial(simplifiedResult);

    return 0;
}
