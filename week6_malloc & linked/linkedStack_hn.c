#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef char Element;

typedef struct StackNode {
  Element data;
  struct StackNode* link;
}  StackNode;

typedef struct StackType{
  StackNode* top;  // 얘가 헤드 포이터가 되는거임 
} StackType;

void init (StackType* S){
  S -> top = (StackNode*)malloc(sizeof(StackNode));  // 헤드 노드 할당
  S -> top -> link  = NULL;
}

int isEmpty (StackType* S) {
  return S -> top -> link == NULL;
}

StackNode* makeNode (Element e){
  StackNode* N = (StackNode*)malloc(sizeof(StackNode)); // 딱 하나 들어갈 정도만 (그떄그떄 필요할때마다 뽑아쓰는 느낌)
  N -> data = e; // 데이터 넣어주고, 임시로 다음 가리킬 친구 (link)는 NULL 처리
  N -> link = NULL;
  return N;
}

void push (StackType* S ,Element e) {
  StackNode* node =  makeNode(e);
  node -> link = S -> top -> link;   // 원래 top 자리에 있던 친구를, 새로운 노드 뒤로 주기
  S -> top -> link  = node;   // top 자리에 새로운 친구 앉히기
}

Element pop (StackType* S) {
  if(isEmpty(S)){
    printf("스택이 비었습니다!");
    return '\0';
  }
  StackNode* p = S -> top -> link; // top 을 기준으로 현재 젤 앞 노드 뽑아내기 
  Element e = p -> data; // 그 노드의 데이터값 잠깐 저장 
  S -> top -> link = p -> link; // top에 그 뒤에 노드를 연결 
  free(p); // 꼭 할당 풀어주기
  return e;
}

void print(StackType* S) {
    for (StackNode* p = S->top->link; p != NULL; p = p->link) {  // 선언도 StackNode* p = S->top; 할 수 있단거 꼭!!
        printf("[%c] => ", p->data);
    }
    printf("NULL\n");
}

void reverse_print(StackNode* N) {
    if (N != NULL) {  // N이 NULL이 아닐 때 계속 재귀 호출
        printf("[%c] => ", N->data);
        reverse_print(N->link);
    }
    printf("\b\b\b    \n");
}

// 스택의 모든 노드를 해제하는 함수
void freeStack(StackType* S) {
    StackNode* current = S->top;
    StackNode* temp;
    
    while (current != NULL) {
        temp = current;  // 현재 노드를 임시 저장
        current = current-> link;  // 다음 노드로 이동
        free(temp);  // 임시 저장한 노드의 메모리 해제
    }

    S->top = NULL;  // 스택이 완전히 해제되면 top을 NULL로 설정
    free(S->top);  // top 포인터 자체도 해제
}


int main () {
  StackType* S;
  init(&S);

  // push(&S, 'A'); print(&S);
  // push(&S, 'B'); print(&S);
  // push(&S, 'C'); print(&S);

  // printf("Delete [%c] : ", pop(&S)); print(&S);
  // printf("Delete [%c] : ", pop(&S)); print(&S);

  push(&S, 'A'); reverse_print(S);
  push(&S, 'B'); reverse_print(S);
  push(&S, 'C'); reverse_print(S);

  printf("Delete [%c] : ", pop(&S)); reverse_print(S);
  printf("Delete [%c] : ", pop(&S)); reverse_print(S);

  freeStack(S );
  return 0;
}