#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX_SIZE  = 10;
typedef char Element;

typedef struct {
  Element* data; 
  int top;
} Stack;

void init (Stack* S) {
  S -> data = (Element*)malloc(sizeof(Element)* MAX_SIZE);
  S -> top = -1;
}

int isEmpty (Stack* S) {
  return S -> top == -1;
}

int isFull (Stack *S) {
  return S -> top == MAX_SIZE;
}

void push (Stack* S, Element e) {
  S -> top++;
  S -> data[S -> top] = e;
}

void print (Stack* S) {
  if(isFull(S)){
    MAX_SIZE *=2;
    S -> data = (Element*)realloc(S -> data, sizeof(Element)*MAX_SIZE);
  }
  for(int i =0; i <= S -> top; i++){
    printf("[%c] => ", S -> data[i]);
  }
  printf("\b\b\b    \n");
}

Element pop (Stack* S) {
  if(isEmpty(S)){
    printf("텅빈 스택!");
    return 0;
  }
  int prev = S -> top;
  S -> top--;
  return S -> data[prev];
}

int main () {
  srand(time(NULL));
  Stack S;
  init(&S);
  for(int i =0; i < 10; i++){
    push(&S,  rand() % 26 + 'a');
    print(&S);
  }
    printf("Delete: [%c] : ", pop(&S)); print(&S);
    printf("Delete: [%c] : ", pop(&S)); print(&S);
    printf("Delete: [%c] : ", pop(&S)); print(&S);

  return 0;
}