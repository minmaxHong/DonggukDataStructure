#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101
#define MAX_VARIABLES 2

// �ϴ� ������ �ִ� �͸� ����� �غ��� !

// ���׽� ��
struct Term {
    float coef; // ���� ���
    char* variable; // ���� ����
    int expon; // ���� ����
};

// ���׽� ǥ��
struct Polynomial {
    struct Term terms[MAX_TERMS]; // �� ǥ��
    int num_terms; // ���� ����
};

// ���׽� �Է�
struct Polynomial inputPolynomial() {
    struct Polynomial poly;
    printf("���׽��� ���� ������ �Է��ϼ���: ");
    scanf_s(" %d", &poly.num_terms);

    // ������ ���� �Ҵ�
    for (int i = 0; i < poly.num_terms; ++i) {
        poly.terms[i].variable = malloc(2 * sizeof(char));
        if (poly.terms[i].variable == NULL) 
            printf("���� �Ҵ� ���� !!!!");
            exit(1);
        }
    }

    for (int i = 0; i < poly.num_terms; ++i) {
        printf("���׽��� %d��° ���� ����� �Է��ϼ���: ", i + 1);
        scanf_s("%f", &poly.terms[i].coef);

        printf("���׽��� %d��° ���� ������ �Է��ϼ���: ", i + 1);
        scanf_s(" %c", &poly.terms[i].variable);

        printf("���׽��� %d��° ���� ������ �Է��ϼ���: ", i + 1);
        scanf_s("%d", &poly.terms[i].expon);
    }
    return poly;
}



// ���׽� ���� ����
void printEach_polynomial(struct Polynomial poly) {
    int i = 0;
    for (i = 0; i < poly.num_terms - 1; ++i) {
        if (poly.terms[i].coef > 0 && i != 0) { // ù��° ���� +��ȣ�̸�, �Ⱥ��̰Բ�
            printf("+");
        }
        printf("%.2f%c^%d", poly.terms[i].coef, poly.terms[i].variable, poly.terms[i].expon);
    }
    // ����� ���
    if (poly.terms[i].expon == 0) {
        if (poly.terms[i].coef > 0) {
            printf("+");
        }
        printf("%.2f", poly.terms[poly.num_terms - 1].coef);
    }
    printf("\n");
}

int main() {

    // =====================================================
    struct Polynomial A;

    // A ���׽� �Է�
    printf("== A ���׽� ���� �Է� ==\n");
    A = inputPolynomial();

    // A ���׽� �������� 



    // A ���׽� ���� ����
    printf("A�� ���׽� ���� : ");
    printEach_polynomial(A);
    // =====================================================



    // =====================================================
    // ���׽� B �ʱ�ȭ
    struct Polynomial B;
    printf("\n== B ���׽� ���� �Է� ==\n");
    B = inputPolynomial();
    printf("B�� ���׽� ���� : ");
    printEach_polynomial(B);
    // =====================================================
    printf("\n");

    // =====================================================
    // ���� A, B ����
    struct Polynomial multiply_A_B;
    //multiply_A_B = multiplyPolynomial(A, B);
    //printEach_polynomial(multiply_A_B);

    // =====================================================

    return 0;
}