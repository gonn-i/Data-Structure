#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define N 10


void insertSort (int A[]) {
  printf("Before Sort : \n");
  for(int i=0; i< N; i++){
    printf(" %d ", A[i]);
  }
  printf("\n");

  for(int i = 1; i <= N-1; i++){ // 오른손 더 작은가 비교할 
    int key = A[i];
    int j = i-1; // 왼손에 해당하는 idx
    while (j >=0 && A[j] > key) // 이미 정렬된 왼손 (카드가 있고, 젤 j값이 더 큰경우 -> 더 안쪽을 탐색할 경우)
    {
      A[j+1] = A[j]; // 왼쪽 큰 카드 뒤로 하나씩 밀기  // 🔥
      j--;
    }
    A[j+1] = key; // 기준이 안으로 옮겨짐 while 이 통하지 않는, j의 뒤에 넣기
  printf("\n");
  printf("%d step :  \n",i);
    for(int i=0; i< N; i++){
      printf(" %d ", A[i]);
    }
  printf("\n");
  }
}

int main () {
  int A[N];
  srand(time(NULL));

  for(int i=0; i <N; i++){
    A[i] = rand( )% 100;
  }

  insertSort (A);
  return 0;
}