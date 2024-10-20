#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct stackNode{
  element data;
  struct stackNode* next;
} StackNode;

typedef struct {
  StackNode* top;
} StackType;

void init (StackType* S){
  S -> top = NULL;
}

int isEmpty(StackType *S){
  return S-> top == NULL;
}

StackNode* makeNode (element e){
  StackNode* node = (StackNode*)malloc(sizeof(StackNode));
  node -> data = e;
  node -> next = NULL;

  return node;
}

void push (StackType *S, element e) {
  StackNode* node = makeNode(e);
  node -> next = S->top;
  S -> top = node;
} 

void print(StackType* S){
  for(StackNode* p = S -> top; p != NULL; p = p -> next ){
    printf("[%d] => ", p -> data);
  }
  printf("NULL\n");
}

element pop (StackType* S){
  if(isEmpty(S)){
    return -1;
  } else {
    StackNode* p = S -> top;
    element e = p -> data;
    S -> top = p -> next;
    free(p);
    return e;
  }
}

// 스택의 모든 노드를 해제하는 함수
void freeStack(StackType* S) {
    StackNode* current = S->top;
    StackNode* temp;
    
    while (current != NULL) {
        temp = current;  // 현재 노드를 임시 저장
        current = current-> next;  // 다음 노드로 이동
        free(temp);  // 임시 저장한 노드의 메모리 해제
    }

    S->top = NULL;  // 스택이 완전히 해제되면 top을 NULL로 설정
}

int main (){
  StackType S;
  init(&S);

  push(&S, 10); print(&S);
  push(&S, 20); print(&S);

  printf("Pop [%d] : ", pop(&S)); print(&S);
  printf("Pop [%d] : ", pop(&S)); print(&S);


  return 0;
}