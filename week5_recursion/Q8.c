// 알파벳 순서로 정렬해서 출력하기 (중간 문제 이런 식으로 나온다 )

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

typedef char element;  // element는 char 타입으로 정의

typedef struct stackType {
  int top;
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
  if (isFull(s)) { 
    printf("오버플로우 발생!\n");
  } else {
    s->top++;  // 스택의 top을 증가시키고
    s->data[s->top] = item;  // 입력받은 item을 저장
  }
}

void print (stackType *s){
  for (int i = s-> top; i >= 0 ; i--){
    printf("%c ", s -> data[i]);
  }
}

element pop(stackType *s) {
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    return -1;  // 스택이 비었을 때 반환할 값 (char에서 -1은 유효하지 않은 값)
  }
  char e = s->data[s->top];  // top에 있는 값을 가져옴
  s->top--;  // top을 감소시킴
  return e;  // 꺼낸 값 반환
}

element peek (stackType *s) {
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    return -1;  // 스택이 비었을 때 반환할 값 (char에서 -1은 유효하지 않은 값)
  }
  return s->data[s->top];  // top에 있는 값을 가져옴
}

void sortedPush (stackType *s, element a) {
  element temp;
  if(isEmpty(s) || a > peek(s)) push(s,a);
  else {
    temp = pop(s);
    sortedPush(s,a);
    push(s,temp);
  }

}

int main() {
  stackType S;
  init(&S);
  srand(time(NULL));

  for(int i=0; i <10; i++){
    sortedPush(&S, rand() % 26 + 65);
    print(&S);
    printf("\n");
  }

  return 0;
}

char s2[16] = {'H','\0'};
char s2[16] = {'H'};

