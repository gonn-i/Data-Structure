// 9. 다음과 같은 이차원배열을 초기화하고 화면에 출력하는 프로그램을 작성하라. (이차원 배열)

#include <stdio.h>

int main (){

  int arr[3][4];

  for(int i=0; i <3; i++){
    int row = i * 10;
    printf("--------------------------------\n");
    for(int j =0; j<4; j++){
      arr[i][j] = row + j;
      printf("| %d\t ", arr[i][j]);
    }
    printf("\n");
  }
  printf("--------------------------------");
  return 0;
}