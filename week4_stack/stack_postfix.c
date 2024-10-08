#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef int element;  // element는 int 타입으로 정의

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
    s->top++;
    s->data[s->top] = item;
  }
}

element pop(stackType *s) {
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    exit(1);  // 에러 시 프로그램 종료
  }
  return s->data[s->top--];  // top을 감소시키며 값 반환
}

int eval(char expr[]) {
  stackType S;
  init(&S); // 숫자 혹은 연산값을 담을 스택

  int op1, op2;
  char c;

  int n = strlen(expr);
  for (int i = 0; i < n; i++) {
    c = expr[i];
    
    // 피연산자일 경우 -> 스택에 푸시 
    if (c >= '0' && c <= '9') {
      int num = c - '0';  // 문자 '0' ~ '9'를 숫자로 변환
      push(&S, num);
    } 
    // 연산자일 경우
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      op2 = pop(&S);  // 스택에서 두 피연산자를 꺼냄
      op1 = pop(&S);

      switch (c) {
        case '+':
          push(&S, op1 + op2);
          break;
        case '-':
          push(&S, op1 - op2);
          break;
        case '*':
          push(&S, op1 * op2);
          break;
        case '/':
          push(&S, op1 / op2);
          break;
        default:
          printf("잘못된 연산자\n");
          exit(1);
      }
    }
  }
  return pop(&S);  // 최종 결과 반환
}

int main() {
	char expr[N];
	scanf("%s", expr);

  int result = eval(expr);  // 후위 표기식 평가
  printf("결과: %d\n", result);

  return 0;
}
