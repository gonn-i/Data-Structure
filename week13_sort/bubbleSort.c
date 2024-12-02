#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define N 10


void bubbleSort (int A[]) {
  printf("Before Sort : \n");
  for(int i=0; i< N; i++){
    printf(" %d ", A[i]);
  }
  printf("\n");

  printf("\n");
  printf("<<<<<<<<<< 버블 정렬 >>>>>>>>>>>");

  for(int i = 1; i <= N-1; i++){ // 오른손 더 작은가 비교할 

  for(int j =1 ; j <= N-i; j++){
    if(A[j-1] > A[j]){
      int tmp = A[j-1];
      A[j-1] = A[j];
      A[j] = tmp;
    }
  }

  printf("\n");
  printf("%d step >> ",i);
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

  bubbleSort (A);
  return 0;
}