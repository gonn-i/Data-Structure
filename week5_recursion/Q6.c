// [ 문제 6 ] 두 개의 양의 정수를 입력받아, 이 두 정수의 최대공약수(gcd)를 유클리드 호제법으로 계산하여 출력하는 프로그램을 작성하시오.

#include <stdio.h>

void gcd (int n1, int n2) {
  int max = n1; int min = n2;
  if(n2 > n1) {
    max = n2;
    min = n1;
  }
  if(min == 0 ){
    printf("최대공약수는 %d", max);
  } else {
    gcd(max%min, min);
  }
  return;
}

int main(){
  int num1, num2;
  scanf("%d %d", &num1, &num2);

  gcd(num1, num2);
}