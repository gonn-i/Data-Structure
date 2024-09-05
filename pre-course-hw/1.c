// 1. 오늘 수업이 끝나고 당신은 점심으로 햄버거를 먹으려고 합니다. 햄버거 한 개의 가격이 K, 사려고 하는 햄버거의 개수가 N개, 현재 당신의 지갑에 있는 돈이 M원이라 할 때, 햄버거를 사기 위해 모자란
// 돈의 액수를 알려주는 프로그램을 작성하세요. (IF 조건문)


#include <stdio.h>

int main(void)
{

    int K = 0;
    int N = 0;
    int M = 0;

    int result = 0;
    printf("햄버거 가격 K를 입력하세요: ");
    scanf("%d", &K);
    printf("햄버거의 개수 N를 입력하세요: ");
    scanf("%d", &N);
    printf("현재 당신의 지갑에 있는 돈을 입력하세요 : ");
    scanf("%d", &M);

    result = M - (K *N);

    if(result > 0){
      printf("%d", 0);
    } else {
      result *= -1;
      printf("%d", result);
      }
}
