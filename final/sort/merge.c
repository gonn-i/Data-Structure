#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sorted[N];

void merge (int A[], int left, int mid, int right){
  int l = left; // 왼쪽꺼 
  int r = mid +1; // 오른쪽꺼 
  int s = left; // 새 배열꺼

  while( l<= mid && r <= right){
    if(A[l] > A[r]) sorted[s++] = A[r++];
    else sorted[s++] = A[l++];
  }

  while ( l<= mid){
      sorted[s++] = A[l++];
  
  }
  while (r <= right) { 
      sorted[s++] = A[r++];
  }

  for(int i =left; i<= right; i++){
    A[i] = sorted[i];
  }
}

void mergeSort (int A[], int left, int right){
  if(left < right){
    int mid = left + (right - left) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid+1, right);
    merge(A, left, mid, right);
  }
}


void print(int A[]){
  for(int i=0; i <N; i++){
    printf("[%d] ", A[i]);
  }
  printf("\n");
}

int main () {
  int A[N];

  srand(time(NULL));
  for(int i =0; i < N; i ++){
    A[i] = rand() % 50;
  }


  printf("정렬전 : "); print(A);
  mergeSort (A, 0, N-1);
  printf("정렬후 : "); print(A);
  return 0;
}