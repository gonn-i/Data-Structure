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

int main (){
  StackType S;
  init(&S);

  push(&S, 10); print(&S);
  push(&S, 20); print(&S);

  printf("Pop [%d] : ", pop(&S)); print(&S);
  printf("Pop [%d] : ", pop(&S)); print(&S);
  return 0;
}