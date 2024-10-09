// [ 문제 1 ] 양의 정수 N을 입력 받아, 1부터 N까지의 합을 구하는 프로그램을 작성하시오. 

#include <stdio.h> 



int recursion_sum (int n){
  int s =0;
  if(n == 1) return 1;
  else {
    s = n + recursion_sum(n-1);
  }
  return s;
}

int main (){
  int num;
  int sum = 0;
  scanf("%d", &num);

  printf("%d" , recursion_sum(num));

  return 0;
}