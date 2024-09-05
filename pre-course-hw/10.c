// 10. 3행 4열의 배열의 임의의 수를 입력받아 저장하고 각 행의 합과 각 열의 합을 출력하는 프로그램을 작성하라. (이차원 배열 요소 접근)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
  int arr[3][4];

  srand((unsigned int)time(NULL));
  int num;

  // 입력을 통한 이차원 배열 저장
  for(int i=0; i<3; i++){
    for(int j=0; j <4; j++){
      printf("%d행 %d열에 넣을 임의의 숫자를 입력하세오 : ", i+1, j+1);
      scanf("%d", &num);
      arr[i][j] = num;
    }
  }

  int col[4] = {0,0,0,0};

  for(int i=0; i<3; i++){
      int row =0;
    for(int j=0; j <4; j++){
      row += arr[i][j] ;
    }
    printf("%d 행의 합 : %d\n", i+1, row);
  }
  printf("=======================\n");
  for(int i=0; i<4; i++){
    int col =0;
    for(int j=0; j <3; j++){
      col += arr[j][i] ;
    }
    printf("%d 열의 합 : %d\n", i+1, col);
  }


  return 0;
}