#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ���� ����
typedef struct {
    int top;
    double data[MAX_SIZE];
} Stack;

// ���� �ʱ�ȭ
void initStack(Stack* stack) {
    stack->top = -1;
}

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// ������ ���� á���� Ȯ��
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// ���ÿ� �� Ǫ��
void push(Stack* stack, double value, const char* type) {
    if (isFull(stack)) {
        printf("���� �����÷ο�\n");
        exit(1);
    }
    stack->data[++(stack->top)] = value;
}

// ���ÿ��� �� ��
double pop(Stack* stack, const char* type) {
    if (isEmpty(stack)) {
        printf("���� ����÷ο�\n");
        exit(1);
    }
    double value = stack->data[(stack->top)--];
    return value;
}

// ������ �켱���� ��ȯ
int getPrecedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

// ���ڿ� ���̸� ����ϴ� �Լ�
int my_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// ���ڿ����� ���� ���ڸ� �����ϴ� �Լ�
void removeNewline(char* str) {
    int length = my_strlen(str);
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

// ���� ���� ���
void printStackState(const char* type, Stack* stack) {
    printf("%s ����: ", type);
    for (int i = 0; i <= stack->top; i++) {
        printf("%.0f ", stack->data[i]);
    }
    printf("\n");
}
// ���� ǥ������ ���� ǥ�������� ��ȯ
void infixToPostfix(const char* infix, char* postfix) {
    Stack stack;
    initStack(&stack);

    int infixIndex = 0, postfixIndex = 0;

    while (infix[infixIndex] != '\0') {
        char ch = infix[infixIndex];

        if (ch >= '0' && ch <= '9') {
            // ���ӵ� ���ڸ� �ϳ��� ���ڷ� ó��
            char number[MAX_SIZE];
            int numberIndex = 0;

            // ���ڸ� ��Ƽ� ó��
            while (ch >= '0' && ch <= '9') {
                number[numberIndex++] = ch;
                infixIndex++;
                ch = infix[infixIndex];
            }

            // ���� ���ڿ��� ������ ��ȯ
            number[numberIndex] = '\0';
            int num = atoi(number);

            // ���� ǥ���Ŀ� �߰�
            sprintf(postfix + postfixIndex, "%d ", num);
            postfixIndex += my_strlen(number) + 1;

            continue;
        }
        else if (ch == ' ') {
            // ���� ǥ���Ŀ��� ������ �����մϴ�.
        }
        else if (ch == '(') {
            push(&stack, (double)ch, "������");
        }
        else if (ch == ')') {
            while (!isEmpty(&stack) && (char)stack.data[stack.top] != '(') {
                postfix[postfixIndex++] = (char)pop(&stack, "������");
            }
            if (!isEmpty(&stack)) {
                pop(&stack, "������");
            }
        }
        else {
            // ������ ó��
            while (!isEmpty(&stack) && getPrecedence((char)stack.data[stack.top]) >= getPrecedence(ch)) {
                postfix[postfixIndex++] = (char)pop(&stack, "������");
            }
            push(&stack, (double)ch, "������");
        }

        infixIndex++;
    }

    // ���ÿ� ���� �����ڸ� ���� ǥ���Ŀ� �߰�
    while (!isEmpty(&stack)) {
        postfix[postfixIndex++] = (char)pop(&stack, "������");
    }

    // ���� ǥ���Ŀ� null ���� �߰�
    postfix[postfixIndex] = '\0';
}

// ���� ǥ���� ���
double evaluatePostfix(const char* postfix) {
    Stack stack;
    initStack(&stack);

    int index = 0;

    while (postfix[index] != '\0') {
        // ���� ó��
        if (postfix[index] >= '0' && postfix[index] <= '9') {
            // ���� ���ڿ��� ������ ��ȯ
            char number[MAX_SIZE];
            int numberIndex = 0;

            while (postfix[index] >= '0' && postfix[index] <= '9') {
                number[numberIndex++] = postfix[index++];
            }

            number[numberIndex] = '\0';
            double num = atof(number);

            // �ǿ����� ���ÿ� Ǫ��
            push(&stack, num, "�ǿ�����");
            printStackState("�ǿ�����", &stack);
        }
        else if (postfix[index] == ' ') {
            // ������ �����մϴ�.
            index++;
        }
        else {
            // ������ ó��
            double b = pop(&stack, "�ǿ�����");
            double a = pop(&stack, "�ǿ�����");

            double result;
            switch (postfix[index]) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            }

            push(&stack, result, "�ǿ�����");
            printStackState("�ǿ�����", &stack);
            index++;
        }
    }

    return pop(&stack, "�ǿ�����");
}


int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    // ���� ǥ���� �Է�
    printf("���� ǥ������ �Է��ϼ���: ");
    fgets(infix, MAX_SIZE, stdin);

    // ���ڿ� ���� ���� ���� ����
    removeNewline(infix);

    // ���� ǥ������ ���� ǥ�������� ��ȯ
    infixToPostfix(infix, postfix);

    // ���� ǥ���� ���
    printf("���� ǥ����: %s\n", postfix);

    // ���� ǥ���� ���
    double result = evaluatePostfix(postfix);

    // ��� ���
    printf("���� ���: %.2f\n", result);

    return 0;
}
