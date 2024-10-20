#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct DListNode {
    Element data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

// 리스트 초기화
DListNode* init() {
    return NULL; // 헤드 포인터는 NULL로 초기화
}

// 노드 생성 함수
DListNode* makeNode(Element e) {
    DListNode* node = (DListNode*)malloc(sizeof(DListNode));
    node->data = e;
    node->prev = node->next = NULL;
    return node;
}

// 삽입 함수
void insert(DListNode** head, int pos, Element e) {
    DListNode* node = makeNode(e);
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (pos == 1) { // 첫 번째 위치에 삽입
        node->next = *head; 
        if (*head != NULL) {
            (*head)->prev = node; // 기존 헤드의 prev를 새 노드로
        }
        *head = node; // 새 노드를 헤드로
    } else { // 두 번째 위치 이후에 삽입
        DListNode* p = *head;
        for (int i = 1; p != NULL && i < pos - 1; i++) {
            p = p->next;
        }

        if (p == NULL) { // pos가 리스트의 크기보다 클 때
            printf("Position out of range!\n");
            free(node);
            return;
        }

        node->next = p->next; // 새로운 노드의 다음을 p의 다음으로 설정
        node->prev = p; // 새로운 노드의 이전을 p로 설정

        if (p->next != NULL) {
            p->next->prev = node; // p의 다음 노드의 이전을 새로운 노드로 설정
        }
        p->next = node; // p의 다음을 새로운 노드로 설정
    }
}

// 삭제 함수
Element delete(DListNode** head, int pos) {
    if (*head == NULL || pos < 1) {
        printf("Invalid position!\n");
        return '\0'; // 잘못된 위치인 경우
    }

    DListNode* p = *head;
    for (int i = 1; p != NULL && i < pos; i++) {
        p = p->next; // 원하는 위치에 도달
    }

    if (p == NULL) { // pos가 리스트의 크기보다 클 때
        printf("Position out of range!\n");
        return '\0';
    }

    Element e = p->data; // 삭제할 데이터 저장
    if (p->prev != NULL) {
        p->prev->next = p->next; // 이전 노드의 다음을 삭제할 노드의 다음으로 설정
    } else {
        *head = p->next; // 헤드가 삭제될 경우
    }

    if (p->next != NULL) {
        p->next->prev = p->prev; // 다음 노드의 이전을 삭제할 노드의 이전으로 설정
    }

    free(p); // 메모리 해제
    return e; // 삭제한 데이터 반환
}

// 출력 함수
void print(DListNode* head) {
    for (DListNode* p = head; p != NULL; p = p->next) {
        printf("[%c] => ", p->data);
    }
    printf("NULL\n");
}

// 메인 함수
int main() {
    DListNode* head = init(); // 리스트 초기화

    insert(&head, 1, 'A'); print(head);
    insert(&head, 2, 'B'); print(head);
    insert(&head, 3, 'C'); print(head);
    insert(&head, 4, 'D'); print(head);

    printf("Delete [%c] : ", delete(&head, 1)); print(head);
    printf("Delete [%c] : ", delete(&head, 2)); print(head);

    return 0;
}
