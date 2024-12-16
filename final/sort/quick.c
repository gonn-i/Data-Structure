#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define SWAP(x, y, temp) ((temp = x), (x = y), (y = temp))


int partition (int A[], int l, int r){
  int pivot = l; 
  int low = l +1;
  int high = r;
  int temp;

  while(low <= high){
    while(A[pivot] >= A[low] && low  <= r) low++;
    while(A[pivot] <= A[high] && high >= l+1) high--;

    if (low < high) {
          SWAP(A[low], A[high], temp);
      }
  }
  SWAP(A[pivot], A[high], temp);
  return high;
}

void quickSort (int A[], int left, int right ){
  if(left < right){ // 여긴
    int p = partition(A, left, right);
    quickSort(A, left, p-1);
    quickSort(A, p+1, right);
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
  quickSort (A, 0, N-1);
  printf("정렬후 : "); print(A);
  return 0;
}