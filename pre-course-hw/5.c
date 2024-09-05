// 5. 정수 N을 입력받아 1부터 N까지 홀수의 합과 짝수의 합을 구하여 출력하는 프로그램을 작성하세요. 

#include <stdio.h>

int main (){
  int N = 0;

  printf("정수 N을 입력하시오 : ");
  scanf("%d", &N);

  int odd = 0;
  int even =0;

  for(int i = 1; i <= N/2; i++){
    even += 2 * i;
    odd += ((2 * i) - 1);
  }

  printf("%d\n", even);
  printf("%d", odd);
}