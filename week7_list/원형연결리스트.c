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
    node->next = L->tail->next; // 새로운 친구를 젤 앞에 노드(원래 맨뒤에 친구가 link하던 노드)와 연결 
    L->tail->next = node; // 원래 맨 뒤던 친구를 새로운 애와 연결
    L->tail = node;  // 마지막 노드를 업데이트 (마지막을 넘겨줌)
  }
  L->size++;
}

Element deleteFirst(ListType* L) {
  if(isEmpty(L))return -1;
  ListNode* p = L -> tail; // 젤 뒤 노드 
  ListNode* q = p -> next; // 젤 앞 노드
  Element e = q-> data; // 젤 앞 노드 값 

  if(p== q) {
    L -> tail = NULL; // 노드가 하나밖에 없는 경우
  } else {
    p -> next = q-> next; // 젤 뒤에서 link 하는 노드 초기화
  }

  L->size--;
  free(q);
  return e;
}

// 노드 수 카운트
int nodeCount(ListType* L) {
  return L->size;
}

Element deleteLast(ListType* L) {
  if(isEmpty(L))return -1;
  ListNode* p = L -> tail; // 젤 뒤 
  ListNode* q = p -> next; // 젤 앞 
  Element e = p -> data; // 젤 뒤 값 

  if(nodeCount(L) == 1) {
    L -> tail = NULL; // 노드 하나인 경우
  } else { 
    while ( q -> next != p){// 젤 뒤의 바로 앞 노드 찾기 
      q = q -> next;
    }
    q -> next = p -> next; // 이제는 젤 뒤가 되어버린 size -1 번째 노드를 젤 앞과 연결 
    L -> tail = q; 
  }

  L->size--;
  free(p);
  return e;
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
  insertFirst(&L, 'B'); print(&L); getchar();

  insertLast(&L, 'C'); print(&L);
  insertLast(&L, 'D'); print(&L); 

  printf("deleteFirst [%c] : ", deleteFirst(&L)); print(&L);
  printf("deleteLast [%c] : ", deleteLast(&L)); print(&L);


  return 0;
}
