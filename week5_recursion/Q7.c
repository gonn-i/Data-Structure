// 공백 없는 영어 문자열 하나를 입력받아, 특정 문자가 몇 번 나타나는 지 검사하는 프로그램을 작성하시오. 문자열의 길이는 최대 100이고, 문자 검사 시 대소문자를 구별한다. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rCountChar(char str[], char c, int i  ){
  int count = (str[i] == c)? 1: 0;
  if(i == 0 ) return count;
  else {
    return count + rCountChar(str, c, i-1);
  }
}

int main () {
  char str[100], c;
  fgets(str, 100, stdin);
  scanf("%c", &c);

  printf("%d\n", rCountChar(str, c, strlen(str)- 1));
}