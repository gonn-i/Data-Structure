#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 

typedef char element;

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
  return Q-> front == (Q -> rear +1) % N;
}

void enqueue (QueueType* Q, element e){
  if(isFull(Q)){
    printf("오버플로우입니다");
  } else {
    Q -> rear = (Q -> rear +1 ) % N; 
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

int main () {
  QueueType Q;
  init(&Q);
  srand(time(NULL));

  for(int i=0; i <  7; i++){
    enqueue(&Q, rand() % 26 + 65);
    print(&Q);
  }

  for(int i=0; i <3; i++){
    printf("[%c]", dequeue(&Q));
  }
  printf("\n\n");
  print(&Q);
  getchar();

  printf("\n\n");

  for(int i=0; i <  6; i++){
    enqueue(&Q, rand() % 26 + 65);
    print(&Q);
  }

  for(int i=0; i <3; i++){
    printf("[%c]", dequeue(&Q));
  }
  printf("\n\n");
  print(&Q);
  getchar();

  return 0;
}
