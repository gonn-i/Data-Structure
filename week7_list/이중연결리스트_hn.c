#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct DListNode {
    Element data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

typedef struct {
    DListNode* H; // 더미 헤드 노드
    DListNode* T; // 더미 테일 노드
} DListType;

// 노드 생성 함수
DListNode* makeNode(Element e) {
    DListNode* node = (DListNode*)malloc(sizeof(DListNode));
    node->data = e;
    node->prev = node->next = NULL;
    return node;
}

// 리스트 초기화
void init(DListType* DL) {
    DL->H = makeNode(0); // 더미 헤드 노드
    DL->T = makeNode(0); // 더미 테일 노드
    DL->H->next = DL->T; // 헤드가 테일을 가리킴
    DL->T->prev = DL->H; // 테일이 헤드를 가리킴
}

// 리스트 크기 구하는 함수 (size 변수 사용하지 않음)
int getSize(DListType* DL) {
    int count = 0;
    DListNode* p = DL->H->next; // 헤드 다음 노드부터 시작
    while (p != DL->T) { // 테일 노드에 도달할 때까지
        count++;
        p = p->next; // 다음 노드로 이동
    }
    return count; // 총 노드 수 반환
}

// 삽입 함수
void insert(DListType* DL, int pos, Element e) {

    int size = getSize(DL);
    if (pos < 1 || pos > size + 1) {
        printf("Invalid position!\n");
        return;
    }

    DListNode* node = makeNode(e);
    DListNode* p = DL->H; // 더미 헤드부터 시작
    for (int i = 1; i < pos; i++) {
        p = p->next; // 원하는 위치에 도달
    }

    node->prev = p;          // p의 이전 노드로 설정
    node->next = p->next;   // p의 다음 노드로 설정
    p->next->prev = node;    // p의 다음 노드의 이전 노드를 새 노드로 설정
    p->next = node;          // p의 다음 노드를 새 노드로 설정

}

// 삭제 함수
Element delete(DListType* DL, int pos) {
    int size = getSize(DL);
    if (pos < 1 || pos > size) {
        printf("Invalid position!\n");
        return '\0'; // 잘못된 위치인 경우
    }

    DListNode* p = DL->H; // 더미 헤드부터 시작
    for (int i = 1; i <= pos; i++) {
        p = p->next; // 원하는 위치에 도달
    }

    Element e = p->data; // 삭제할 데이터 저장
    p->prev->next = p->next; // 이전 노드의 다음을 삭제할 노드의 다음으로 설정
    p->next->prev = p->prev; // 다음 노드의 이전을 삭제할 노드의 이전으로 설정
    free(p); // 메모리 해제
    return e; // 삭제한 데이터 반환
}

// 출력 함수
void print(DListType* DL) {
    for (DListNode* p = DL->H->next; p != DL->T; p = p->next) {
        printf("[%c] => ", p->data);
    }
    printf("NULL\n");
}

// 메인 함수
int main() {
    DListType DL; // DListType 구조체 선언
    init(&DL); // 리스트 초기화

    insert(&DL, 1, 'A'); print(&DL);
    insert(&DL, 2, 'B'); print(&DL);
    insert(&DL, 3, 'C'); print(&DL);
    insert(&DL, 4, 'D'); print(&DL);

    printf("Delete [%c] : ", delete(&DL, 1)); print(&DL);
    printf("Delete [%c] : ", delete(&DL, 2)); print(&DL);

    return 0;
}

// 슬라이드에 나와있는거 추가적으로 더 해보기