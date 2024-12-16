#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10


void selectSort (int A []){
  for(int i =0; i < N-1; i++){
    int min = i;
    for(int j =i+1; j < N; j++){
      if(A[min] > A[j]){
        min = j;
      }
    }
      int temp = A[i];
      A[i] = A[min];
      A[min] = temp;
  }
}

void print(int A[]){
  for(int i=0; i <N; i++){
    printf("[%d] ", A[i]);
  }
  printf("\n");
}

int main() {
  int A[N] = {};

  srand(time(NULL));

  for(int i=0; i < N; i++){
    A[i] = rand() % 100;
  }

  printf("정렬전 : "); print(A);
  selectSort (A);
  printf("정렬후 : "); print(A);

  

  return 0;
}