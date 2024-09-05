// 8. 주사위를 10000번 던져서 각 면이 나오는 횟수를 시뮬레이션 하는 프로그램을 작성하라. (일차원 배열)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  srand((unsigned int)time(NULL));

  int arr[6] = {0,0,0,0,0,0};

  for(int i=0; i <1000; i++){
    arr[rand() % 6] += 1;
  }

  
  for(int i=0; i<6; i++){
    printf("%d 이/가 나온 횟수: %d\n", i+1, arr[i]);
  }

  return 0;
}