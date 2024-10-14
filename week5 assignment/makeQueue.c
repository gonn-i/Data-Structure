// 스택 2개로 큐 만들기 (응용문제)
#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef char element;  

typedef struct stackType {
  int top; // 인덱스로 (empty / full 구분)
  element data[N];
} stackType;

void init(stackType *s) {
  s->top = -1;  // 초기화
}

int isEmpty(stackType *s) {
  return s->top == -1;  // 스택이 비었는지 확인
}

int isFull(stackType *s) {
  return s->top == N - 1;  // 스택이 가득 찼는지 확인
}

void push(stackType *s, element item) {
  if (isFull(s)) {  // 스택이 가득 찼다면 
  // (⭐️인자로 포인터를 주면(&S) 이중포인터로 받아야 함 -> 주소를 담은 병의 구조를 전달하는 꼴이라) 걍 s 주기 
  // main 함수에서 만든 s 와, 매개변수로 넘겨준 s는 차이가 있음 
    printf("오버플로우 발생!\n");
  } else {
    s->top++;  // 스택의 top을 증가시키고 
    s->data[s->top] = item;  // 입력받은 item을 저장
  }
}

// 마지막 값 꺼내기
element pop(stackType *s) { // char pop (stackType *s) 이랑 똑같지만 요렇게 쓰면 통일성 굿
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    return -1;  // 스택이 비었을 때 반환할 값 (char에서 -1은 유효하지 않은 값)
  }
  char e = s->data[s->top];  // top에 있는 값을 가져옴
  s->top--;  // top을 감소시킴
  return e;  // 꺼낸 값 반환
}

element peek (stackType *s) { // 마지막 값 참조 
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    return -1;  // 스택이 비었을 때 
  }
  return s->data[s->top];  // top에 있는 값을 가져옴
}

void print (stackType *s){
  for (int i = s-> top; i >= 0 ; i--){
    printf("%c ", s -> data[i]);
    printf("\n");
  }
}

void enqueue(stackType* S, element e ){
  push(S,e);
}

element dequeue (stackType* S1, stackType* S2){
  if (isEmpty(S2)) {
    if(isEmpty(S1)){
      printf("스택 비었음\n");
      return -1;  // 스택이 비었을 때 반환할 값 (char에서 -1은 유효하지 않은 값)
    }
  } 
    while(!isEmpty(S1)){
      push(S2, pop(S1));
    }
  
  return pop(S2);
}

int main() {
  stackType S1, S2;
  init(&S1); init(&S2);

  enqueue(&S1, 'A');
  enqueue(&S1, 'B');
  enqueue(&S1, 'C');

  printf("[%c]", dequeue(&S1, &S2));

  enqueue(&S1, 'D');
  enqueue(&S1, 'E');
    printf("[%c]", dequeue(&S1, &S2));
    printf("[%c]", dequeue(&S1, &S2));
    printf("[%c]", dequeue(&S1, &S2));
  return 0;
}
