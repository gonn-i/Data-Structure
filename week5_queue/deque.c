#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 

typedef char element;

typedef struct DequeType
{
  int front, rear;
  element data[N];
}DequeType;


void init (DequeType* D) {
  D -> front = D -> rear = 0; // front 값 rear 값 0 초기화
}

int isEmpty (DequeType* D){
  return D -> front == D -> rear;
}

int isFull (DequeType* D){
  return D-> front == (D -> rear +1) % N;
}

void addFront(DequeType* D, element e){
  if(isFull(D)){
    printf("오버플로우입니다");
  } else {
    D->front = (D->front - 1 + N) % N;
    D -> data[D -> front] = e;

  }
}

void addRear (DequeType* D, element e){
  if(isFull(D)){
    printf("오버플로우입니다");
  } else {
    D -> rear = (D -> rear +1 ) % N; 
    D -> data[D -> rear] = e;
  }
}

element deleteFront (DequeType* D){  // dequeue
  if(isEmpty(D)){
    printf("빈 큐!");
    return -1;
  }

  D-> front = (D -> front +1) %N;
  return D -> data[D -> front];
}

element deleteRear (DequeType* D){   // pop
  if(isEmpty(D)){
    printf("빈 큐!");
    return -1;
  }
  int pos = D -> rear;
  D-> rear = (D -> rear -1 + N) %N;
  return D -> data[pos];
}

element getFront (DequeType* D){
  if(isEmpty(D)){
    printf("빈 큐!");
    return -1;
  }

return D->data[(D->front +1 ) % N];
}

element getRear (DequeType* D){   // peek of stack
  if(isEmpty(D)){
    printf("빈 큐!");
    return -1;
  }

return D->data[D->rear]; 
}

void print (DequeType* D){
  printf("Front %d Rear %d", D-> front, D-> rear);
  int i = D -> front;
  while (i != D -> rear) {
    i = (i+1) % N;
    printf("[%c]", D -> data[i]);
  }
  printf("\n");
}


int main () {
  DequeType D;
  init(&D);
  srand(time(NULL));

  for(int i =0; i <7; i++){
    addRear(&D, rand() % 26 + 'A');
  }
  print(&D);

  for(int i=0; i <3; i++){
    printf("delete_Front: [%c]\n\n", deleteFront(&D));
  }
  printf("\n\n");
  print(&D);

  printf("peek_Front: [%c]\n\n", getFront(&D));
  print(&D);


  for(int i =0; i <2; i++){
    addFront(&D, rand() % 26 + 65);
  }
  print(&D);

  for(int i=0; i <3; i++){
    printf("delete_rear: [%c]\n\n", deleteRear(&D));
  }
  printf("\n\n");
  print(&D);

  printf("peek_rear: [%c]\n\n", getRear(&D));
  print(&D);

}
