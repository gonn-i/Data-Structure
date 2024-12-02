#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define N 9
# define SWAP(x , y , t ) ((t) = (x), (x) = (y), (y) = (t))


int partition (int A[], int left, int right){
  int pivot = A[left];
  int low = left +1;
  int high = right;
  int temp; // t로 던져줄 애

  while(low <= high) {
    while(low <= high && A[low] <=pivot ) low++;

    while(low <= high && A[high] > pivot) high--;

    for(int i=0; i<N; i++){
      printf("[%d] ", A[i]);
    }
    printf("\n\nlow = %d, high = %d\n\n ", low, high);
    if(low < high) SWAP(A[low], A[high], temp);
  }
  SWAP(A[low], A[high], temp);
  return high;
} 

void quickSort (int A[], int left, int right) {
  if (left < right ){
    int q = partition(A, left, right);
    quickSort(A, left, q -1);
    quickSort(A, q+1, right);
  }
}

int main () {
  int A[N] = {5,3,8,4,9,1,6,2};
  // srand(time(NULL));
  // for(int i=0; i <N; i++){
  //   A[i] = rand( )% 100;
  // }

  quickSort (A, 0, 8);
  return 0;
}