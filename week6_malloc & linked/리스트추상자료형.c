#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct ListNode {
  Element data;
  struct ListNode* next;
}ListNode;

typedef struct ListType {
  ListNode * head;
  int size;
}ListType;

void init (ListType* L){
  L -> head = NULL;
  L -> size = 0;
}

int isEmpty (ListType* L) {
  return L -> size == 0;
}

ListNode* makeNode (Element e) {
  ListNode* node = (ListNode*) malloc(sizeof(ListNode));
  node -> data = e;
  node -> next = NULL;
  return node;
}

void insertFirst (ListType* L, Element e) {
  ListNode* node = makeNode(e);
  node -> next =  L -> head;// 내가 누굴 향함?
  L -> head =  node; // 누가 나를 향함?
  L -> size++;
}

// 연결 어떻게 하는지가 가장 중요 
void insert (ListType* L, int pos, Element e) {
  ListNode* node = makeNode(e);
  ListNode* p = L -> head;

  // 유효하지 않은 pos 값을 체크 (각자 알아서 if문 짜셈)
  if(pos == 1){
    insertFirst(L,e);
  } else { // 반복문 돌리는거 주목해서 보셈 
    for (int i = 2; i < pos; i++ ){
      p = p -> next;
    }
    node -> next = p -> next;
    p -> next = node ;
    L -> size++;
  }
}


Element deleteFirst (ListType* L) {
  if(isEmpty(L)) return -1;

  ListNode* p = L -> head;
  Element e = p -> data;

  L -> head = p -> next; // 연결 해주는 방법

  L -> size--;
  free(p);
  return e;
}

Element deletePosition (ListType* L, int pos) {
  if(isEmpty(L)) return -1;

  ListNode* p = L -> head;
  ListNode* q;

  if(pos == 1) return deleteFirst(L);
  else {
for (int i = 2; i <= pos; i++ ){
      q = p;
      p = q-> next;
    }
  Element e = p -> data;
  q-> next = p -> next;

  L -> size--;
  free(p);
  return e;
  }

}


void print(ListType* L){
  for( ListNode* p = L ->head; p !=NULL; p=p -> next){
    printf("[%c] => ", p -> data);
  }
  printf("\b\b\b \n");
}


int main(){
  ListType L;
  init(&L);
    insertFirst(&L, 'A'); print(&L);
    insertFirst(&L, 'B'); print(&L); getchar();

    insert(&L, 1,'C'); print(&L);
    insert(&L, 4,'C'); print(&L);
    insert(&L, 3,'C'); print(&L); getchar();

    printf("delete [%c] : ", deleteFirst(&L)); print(&L);
    printf("delete [%c] : ", deletePosition(&L, 2)); print(&L);

  return 0;
}