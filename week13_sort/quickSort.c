#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define N 8
# define SWAP(x , y , t ) ((t) = (x), (x) = (y), (y) = (t))


int partition (int A[], int left, int right){
  int pivot = A[left]; // 젤 왼쪽을 피벗으로 
  int low = left +1;
  int high = right;
  int temp; // t로 던져줄 애

  while(low <= high) { // 겹쳐진걸 넘어서 엇갈리면 SWAP
    while(low <= high && A[low] <= pivot ) low++; // 피벗보다 작으면 일단 쓰루 다음 인덱스로 
    while(low <= high && A[high] > pivot) high--; //  피벗보다 크면 일단 쓰루 안으로 들어가는 인덱스로 

    for(int i=0; i<N; i++){
      printf("[%d] ", A[i]);
    }
    printf("\n\nlow = %d, high = %d\n\n ", low, high); 
    if(low < high) SWAP(A[low], A[high], temp); // 둘이 교환
  }
  SWAP(A[left], A[high], temp); // A[left]는 피벗, A[high] 랑 자리 바꾸기
  return high;
} 

void quickSort (int A[], int left, int right) {
  if (left < right ){
    int q = partition(A, left, right); // 피벗을 중간에 넣기 위한 partition
    quickSort(A, left, q -1); // 피벗 왼쪽 부분 정렬
    quickSort(A, q+1, right); // 피벗 오른쪽 부분 정렬
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