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

int getSize(ListType* L) {
    int size = 0;  // 리스트 크기 초기화
    ListNode* p = L->head;  // 리스트의 헤드부터 시작

    // 리스트를 순회하며 크기 계산
    while (p != NULL) {
        size++;
        p = p->next;  // 다음 노드로 이동
    }

    return size;  // 최종 크기 반환
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
  
  int size = getSize(L);

  // 유효하지 않은 pos 값을 체크 (각자 알아서 if문 짜셈)

  if (pos < 1 || pos > size + 1) {  // pos 값이 유효한지 확인
        printf("유효하지 않은 위치입니다. (1 ~ %d)\n", size + 1);
        free(node);  // 동적으로 할당한 메모리 해제
        return;
  }  

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

  // 리스트의 크기를 가져옴
  int size = getSize(L);

  // pos 유효성 검사
  if (pos < 1 || pos > size) {
      printf("유효하지 않은 위치입니다. (1 ~ %d)\n", size);
      return -1;
  }

  if(pos == 1) return deleteFirst(L);
  else {
    for (int i = 2; i <= pos; i++ ){
      q = p; //삭제노드 앞 노드
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
  printf("\b\b\b   \n");
}


int main(){
  ListType L;
  init(&L);
    insertFirst(&L, 'A'); print(&L);
    insertFirst(&L, 'B'); print(&L); getchar();

    insert(&L, 1,'C'); print(&L);
    insert(&L, 4,'C'); print(&L);
    insert(&L, 10,'C'); print(&L); getchar();

    printf("delete [%c] : ", deleteFirst(&L)); print(&L);
    printf("delete [%c] : ", deletePosition(&L, 2)); print(&L);

  return 0;
}