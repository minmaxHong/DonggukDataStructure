#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    printf("리스트: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void swapNodes(struct Node** head, int pos1, int pos2) {
    if (pos1 == pos2) {
        return;
    }

    int count = 0;
    struct Node* temp = *head;
    struct Node* node1 = NULL;
    struct Node* node2 = NULL;

    while (temp != NULL) {
        if (count == pos1) {
            node1 = temp;
        }
        else if (count == pos2) {
            node2 = temp;
        }
        temp = temp->next;
        count++;
    }

    if (node1 == NULL || node2 == NULL) {
        printf("입력한 인덱스가 범위를 초과하거나 유효하지 않습니다.\n");
        return;
    }

    if (node1->prev != NULL)
        node1->prev->next = node2;
    if (node2->prev != NULL)
        node2->prev->next = node1;
    if (node1->next != NULL)
        node1->next->prev = node2;
    if (node2->next != NULL)
        node2->next->prev = node1;

    struct Node* tempPrev = node1->prev;
    node1->prev = node2->prev;
    node2->prev = tempPrev;

    struct Node* tempNext = node1->next;
    node1->next = node2->next;
    node2->next = tempNext;

    if (*head == node1)
        *head = node2;
    else if (*head == node2)
        *head = node1;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int num;
    char input[100];
    printf("자연수 리스트를 입력하세요 (최대 20개, -1 입력 시 종료): ");
    fgets(input, sizeof(input), stdin);

    char* token = input;
    while (sscanf(token, "%d", &num) == 1 && num != -1) {
        if (num < 1) {
            printf("Error: 잘못된 입력이 있습니다. 자연수만 입력해 주세요.\n");
            freeList(head);
            return 1;
        }
        struct Node* newNode = createNode(num);
        if (head == NULL) {
            head = newNode;
        }
        else {
            struct Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        // Find the next token (skip spaces)
        while (*token && *token != ' ' && *token != '\n') {
            token++;
        }
        if (*token) {
            token++;
        }
    }

    printList(head);

    do {
        int pos1, pos2;
        printf("위치 변경 (형식: 인덱스1 인덱스2, 종료: q): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'q') {
            break;
        }
        sscanf(input, "%d %d", &pos1, &pos2);
        swapNodes(&head, pos1, pos2);
        printList(head);
    } while (1);

    printf("최종 결과: ");
    printList(head);

    freeList(head);
    return 0;
}
