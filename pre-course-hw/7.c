// 7. 크기가 N(N ≤ 50)인 1차원 배열에 1 ~ 100 사이의 난수를 저장한 후, 최댓값을 구하는 프로그램을 작성하라. (일차원 배열)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (void) {
  int N =0;
  srand((unsigned int)time(NULL));

  printf("1 ~ 50 사이의 수 N을 입력하십시오 : ");
  while(1) {
    if(N > 50 || N <= 0){
      scanf("%d", &N);
    } else {
      break;
    }
  }

  int arr[N];

  int max =0;

  for(int i=0; i <N; i++){
    arr[i] = rand() % 100;
    printf("%d ", arr[i]);
    if(max <= arr[i]) max = arr[i];
  }

  printf("\n%d", max);

  return 0;
}