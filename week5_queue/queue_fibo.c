#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 

typedef int element;

typedef struct QueueType
{
  int front, rear;
  element data[N];
}QueueType;


void init (QueueType* Q) {
  Q -> front = Q -> rear = 0; // front 값 rear 값 0 초기화
}

int isEmpty (QueueType* Q){
  return Q -> front == Q -> rear;
}

int isFull (QueueType* Q){
  return Q-> front == (Q -> rear +1  % N);
}

void enqueue (QueueType* Q, element e){
  if(isFull(Q)){
    printf("오버플로우입니다");
  } else {
    Q -> rear = (Q ->rear +1% N )  ;
    Q -> data[Q -> rear] = e;
  }
}

element dequeue (QueueType* Q){
  if(isEmpty(Q)){
    printf("빈 큐!");
    return -1;
  }

  Q -> front = (Q -> front +1) %N;
  return Q -> data[Q -> front];
}

element peek (QueueType* Q){
  if(isEmpty(Q)){
    printf("빈 큐!");
    return -1;
  }

  return Q -> data[(Q -> front +1) % N];
}

void print (QueueType* Q){
  printf("Front %d Rear %d", Q-> front, Q-> rear);
  int i = Q -> front;
  while (i != Q -> rear) {
    i = (i+1) % N;
    printf("[%c]", Q -> data[i]);
  }
  printf("\n");
}

void fibo ( int n){
  QueueType Q;
  init(&Q);

  enqueue(&Q,1);
  enqueue(&Q,1);

  for( int i =1; i <= n; i++){
    element e1 = dequeue(&Q);
    element e2 = peek(&Q);

    printf("%d ", e1);
    enqueue(&Q, e1+e2);
  }

  while(isEmpty(&Q)){
    printf(" %d", dequeue(&Q));
  }

  printf("\n");
}

int main () {
  int n;
  scanf("%d", &n);

  fibo(n);

  return 0;
}
