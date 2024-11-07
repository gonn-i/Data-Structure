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

void upHeap(HeapType* H) {
  int i = H->heapSize;
  element key = H->heap[i];

  // 부모와 비교하여 부모가 작으면 자식과 위치를 바꿈
  while (i > 1 && key > H->heap[i / 2]) {
    H->heap[i] = H->heap[i / 2];
    i /= 2;
  }
  H->heap[i] = key;  // key를 적절한 위치에 넣음
}

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
