#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10


void insertSort (int A[]) {
  for(int i = 1; i < N-1; i++){
    int key = A[i];
    int j = i - 1;
    while(j >= 0 && A[j] > key){
        A[j+1] = A[j]; // 🔥
        j--;
    }
    A[j+1] = key;
  }
}


void print(int A[]){
  for(int i=0; i <N; i++){
    printf("[%d] ", A[i]);
  }
  printf("\n");
}


int main(){

  int A[N];

  for( int i =0; i< N; i++){
    A[i] = rand() % 50;
  }

  printf("정렬전 : "); print(A);
  insertSort (A);
  printf("정렬후 : "); print(A);

  return 0;
}