#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct ListNode {
  Element data;
  struct ListNode* next;
} ListNode;

typedef struct ListType {
  ListNode* tail;
  int size;
} ListType;

void init(ListType* L) {
  L->tail = NULL;
  L->size = 0;
}

int isEmpty(ListType* L) {
  return L->size == 0;
}

ListNode* makeNode(Element e) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->data = e;
  node->next = NULL;
  return node;
}

void insertFirst(ListType* L, Element e) {
  ListNode* node = makeNode(e);

  if (isEmpty(L)) {
    L->tail = node;
    L->tail->next = node;
  } else {
    node->next = L->tail->next;
    L->tail->next = node;
  }
  L->size++;
}

void insertLast(ListType* L, Element e) {
  ListNode* node = makeNode(e);

  if (isEmpty(L)) {
    L->tail = node;
    L->tail->next = node;
  } else {
    node->next = L->tail->next;
    L->tail->next = node;
    L->tail = node;  // 마지막 노드를 업데이트
  }
  L->size++;
}

void print(ListType* L) {
  if (!isEmpty(L)) {
    ListNode* p = L->tail->next;  // 첫 번째 노드부터 시작
    do {
      printf("[%c] => ", p->data);
      p = p->next;
    } while (p != L->tail->next);  // 다시 처음으로 돌아오면 종료
    printf("\b\b\b   \n");
  }
}

int main() {
  ListType L;
  init(&L);

  insertFirst(&L, 'A'); print(&L);
  insertFirst(&L, 'B'); print(&L);

  insertLast(&L, 'C'); print(&L);
  insertLast(&L, 'D'); print(&L);

  return 0;
}
