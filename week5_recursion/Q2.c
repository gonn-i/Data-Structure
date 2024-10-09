// [ 문제 2 ] 양의 정수를 입력 받아, 각 자리의 수를 높은 자릿수부터 차례로 출력하는 프로그램을 작성하시오. 

#include <stdio.h>


void rPrintDigit(int num) {
  if(num < 10){
    printf("%5d - %d\n", num, num % 10);
  } else {
    rPrintDigit(num / 10);
    printf("%5d - %d\n", num, num % 10);
  }
}

int main () {
  int num;
  scanf("%d", &num);
  rPrintDigit(num);

  return 0;
}