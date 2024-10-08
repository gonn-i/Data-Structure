// 중위 표기법을 후위 표기법으로 변환하는 함수 (변환된 후위 표기법을 문자열로 반환)
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

element peek(stackType *s) {
  if (isEmpty(s)) {
    printf("스택 비었음\n");
    exit(1);  // 에러 시 프로그램 종료
  }
  return s->data[s->top];  // top 값 반환 (스택에서 제거하지 않음)
}

// 연산자의 우선순위를 반환하는 함수
int prec(char op) {
  switch (op) {
    case '(': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: return -1;  // 잘못된 연산자
  }
}

// 후위 표기법 계산 함수
int eval(char expr[]) {
  stackType S;
  init(&S);

  int op1, op2;
  char c;

  int n = strlen(expr);
  for (int i = 0; i < n; i++) {
    c = expr[i];
    
    // 피연산자일 경우 -> 스택에 push
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
          if (op2 == 0) {
            printf("0으로 나눌 수 없습니다.\n");
            exit(1);
          }
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

// 중위 표기법 ---> 후위 표기법으로 변환하는 함수 (변환된 후위 표기법을 문자열로 반환)
void infixToPostfix(char expr[], char result[]) {
  stackType S;
  init(&S);

  char c, op;
  int n = strlen(expr);
  int idx = 0;

  for (int i = 0; i < n; i++) {
    c = expr[i];

    // 피연산자일 경우 -> 숫자는 배열에 저장
    if (c >= '0' && c <= '9') {
      result[idx++] = c;  // 피연산자는 그대로 저장
    } 
    // 왼쪽 괄호일 경우 -> 여는 괄호를 스택에 push
    else if (c == '(') {
      push(&S, c);
    } 
    // 오른쪽 괄호일 경우  -> 여는 괄호 제거 ( 5 + 7)
    else if (c == ')') {
      op = pop(&S);
      while (op != '(') {
        result[idx++] = op;  // 괄호 안의 연산자를 모두 저장
        op = pop(&S);
      }
    } 
    // 연산자일 경우
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!isEmpty(&S)) {
        op = peek(&S);
        if (prec(c) <= prec(op)) {
          result[idx++] = pop(&S);
        } else {
          break;
        }
      }
      push(&S, c);
    }
  }

  // 스택에 남아 있는 연산자들을 모두 저장
  while (!isEmpty(&S)) {
    result[idx++] = pop(&S);
  }
  result[idx] = '\0';  // 후위 표기법 문자열 종료
}

int main() {
  char expr[N];
  char postfix[N];

  printf("중위 표기법 입력: ");
  scanf("%s", expr);

  infixToPostfix(expr, postfix);
  printf("후위 표기법: %s\n", postfix);
  printf("후위 표기법 계산 결과: %d\n", eval(postfix));

  return 0;
}
