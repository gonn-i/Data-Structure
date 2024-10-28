// [ 문제 4 ] N 개의 정수를 입력 받아 (N ≤ 20), 최댓값을 구하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rMax(int* arr, int i ){
  if(i == 0){
    return arr[0];
  } else {
    int max = rMax(arr, i-1);
    printf("현재 최대값 %d vs arr %d\n", max, arr[i]);
    if(max < arr[i-1]){
      max = arr[i-1];
    }
    return max;
  }
}

int main () {
  int size;
  scanf("%d", &size);
  int* arr = (int*) malloc(sizeof(int) * size);
  srand(time(NULL)); 

  for(int i=0; i< size; i++){
    arr[i] = rand() % 100;
    printf("%d ", arr[i]);
  }
  printf("\n");
  printf("\nMax = %d", rMax(arr, size -1));

  return 0;
}