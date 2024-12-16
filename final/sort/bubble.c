#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10


void bubbleSort (int A[]) {
  for(int i =1; i < N; i++){
    for(int j =1; j <N; j++){
      if(A[j] < A[j-1]){
        int temp = A[j];
        A[j] = A[j-1];
        A[j-1] = temp;
      }
    }
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

  srand(time(NULL));
  for( int i =0; i< N; i++){
    A[i] = rand() % 50;
  }

  printf("정렬전 : "); print(A);
  bubbleSort (A);
  printf("정렬후 : "); print(A);

  return 0;
}