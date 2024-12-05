// 우선순위큐
#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int element;

typedef struct {
  element heap[N];
  int heapSize;
} HeapType;

void init(HeapType* H) {
  H->heapSize = 0;
}

// 추가한 노드 부모와 비교하여 위로 올리기 
void upHeap(HeapType* H) {
  int i = H->heapSize;
  element key = H->heap[i]; // 삽입한 노드

  // 부모와 비교하여 부모가 작으면 자식과 위치를 바꿈
  while (i > 1 && key > H->heap[i / 2]) {
    H->heap[i] = H->heap[i / 2]; // 부모 노드를 아래로 내리기 
    i /= 2;
  }
  H->heap[i] = key;  // 적당한 위치에 key 넣기
}

// 힙트리에 노드 추가 (제일 끝단에 추가)
void insertItem(HeapType* H, element key) {
  H->heapSize++;
  H->heap[H->heapSize] = key;

  upHeap(H);
}

void printHeap(HeapType* H) {
  for (int i = 1; i <= H->heapSize; i++) {
    printf("[%d] ", H->heap[i]);
  }
  printf("\n");
}

int main() {
  HeapType H;
  init(&H);
  element keys[] = {9, 7, 6, 5, 4, 3, 2, 2, 1, 3};

  for (int i = 0; i < 10; i++) {
    insertItem(&H, keys[i]);
  }
  
  printHeap(&H);  // 힙 출력

  return 0;
}
