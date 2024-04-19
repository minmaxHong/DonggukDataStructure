#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 스택 정의
typedef struct {
    int top;
    double data[MAX_SIZE];
} Stack;

// 스택 초기화
void initStack(Stack* stack) {
    stack->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// 스택에 값 푸시
void push(Stack* stack, double value, const char* type) {
    if (isFull(stack)) {
        printf("스택 오버플로우\n");
        exit(1);
    }
    stack->data[++(stack->top)] = value;
}

// 스택에서 값 팝
double pop(Stack* stack, const char* type) {
    if (isEmpty(stack)) {
        printf("스택 언더플로우\n");
        exit(1);
    }
    double value = stack->data[(stack->top)--];
    return value;
}

// 연산자 우선순위 반환
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

// 문자열 길이를 계산하는 함수
int my_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// 문자열에서 개행 문자를 제거하는 함수
void removeNewline(char* str) {
    int length = my_strlen(str);
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

// 스택 상태 출력
void printStackState(const char* type, Stack* stack) {
    printf("%s 스택: ", type);
    for (int i = 0; i <= stack->top; i++) {
        printf("%.0f ", stack->data[i]);
    }
    printf("\n");
}
// 중위 표현식을 후위 표현식으로 변환
void infixToPostfix(const char* infix, char* postfix) {
    Stack stack;
    initStack(&stack);

    int infixIndex = 0, postfixIndex = 0;

    while (infix[infixIndex] != '\0') {
        char ch = infix[infixIndex];

        if (ch >= '0' && ch <= '9') {
            // 연속된 숫자를 하나의 숫자로 처리
            char number[MAX_SIZE];
            int numberIndex = 0;

            // 숫자를 모아서 처리
            while (ch >= '0' && ch <= '9') {
                number[numberIndex++] = ch;
                infixIndex++;
                ch = infix[infixIndex];
            }

            // 숫자 문자열을 정수로 변환
            number[numberIndex] = '\0';
            int num = atoi(number);

            // 후위 표현식에 추가
            sprintf(postfix + postfixIndex, "%d ", num);
            postfixIndex += my_strlen(number) + 1;

            continue;
        }
        else if (ch == ' ') {
            // 중위 표현식에서 공백은 무시합니다.
        }
        else if (ch == '(') {
            push(&stack, (double)ch, "연산자");
        }
        else if (ch == ')') {
            while (!isEmpty(&stack) && (char)stack.data[stack.top] != '(') {
                postfix[postfixIndex++] = (char)pop(&stack, "연산자");
            }
            if (!isEmpty(&stack)) {
                pop(&stack, "연산자");
            }
        }
        else {
            // 연산자 처리
            while (!isEmpty(&stack) && getPrecedence((char)stack.data[stack.top]) >= getPrecedence(ch)) {
                postfix[postfixIndex++] = (char)pop(&stack, "연산자");
            }
            push(&stack, (double)ch, "연산자");
        }

        infixIndex++;
    }

    // 스택에 남은 연산자를 후위 표현식에 추가
    while (!isEmpty(&stack)) {
        postfix[postfixIndex++] = (char)pop(&stack, "연산자");
    }

    // 후위 표현식에 null 문자 추가
    postfix[postfixIndex] = '\0';
}

// 후위 표현식 계산
double evaluatePostfix(const char* postfix) {
    Stack stack;
    initStack(&stack);

    int index = 0;

    while (postfix[index] != '\0') {
        // 숫자 처리
        if (postfix[index] >= '0' && postfix[index] <= '9') {
            // 숫자 문자열을 정수로 변환
            char number[MAX_SIZE];
            int numberIndex = 0;

            while (postfix[index] >= '0' && postfix[index] <= '9') {
                number[numberIndex++] = postfix[index++];
            }

            number[numberIndex] = '\0';
            double num = atof(number);

            // 피연산자 스택에 푸시
            push(&stack, num, "피연산자");
            printStackState("피연산자", &stack);
        }
        else if (postfix[index] == ' ') {
            // 공백은 무시합니다.
            index++;
        }
        else {
            // 연산자 처리
            double b = pop(&stack, "피연산자");
            double a = pop(&stack, "피연산자");

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

            push(&stack, result, "피연산자");
            printStackState("피연산자", &stack);
            index++;
        }
    }

    return pop(&stack, "피연산자");
}


int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    // 중위 표현식 입력
    printf("중위 표현식을 입력하세요: ");
    fgets(infix, MAX_SIZE, stdin);

    // 문자열 끝의 개행 문자 제거
    removeNewline(infix);

    // 중위 표현식을 후위 표현식으로 변환
    infixToPostfix(infix, postfix);

    // 후위 표현식 출력
    printf("후위 표현식: %s\n", postfix);

    // 후위 표현식 계산
    double result = evaluatePostfix(postfix);

    // 결과 출력
    printf("최종 결과: %.2f\n", result);

    return 0;
}
