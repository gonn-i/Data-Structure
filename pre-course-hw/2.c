// 2. 성적을 입력받아 학점을 출력하는 프로그램을 만드세요. 
// 학점은 A, B, C, D or F 등급으로 나뉘며 점수의 입력은 0 ~ 100 점 사이이어야 합니다. (다중 IF & IF ~ ELSE IF문)

#include <stdio.h>

int main () {
  int grade =0;

  printf("학생의 점수를 입력하세요 : ");
  scanf("%d", &grade);

  if(grade > 100 || grade < 0){
    printf("Wrong Input");
  } else if(grade >=90){
    printf("A");
  } else if (grade >= 80){
      printf("B");
  } else if (grade >= 70){
      printf("C");
  } else {
      printf("D or F");
  }
  return 0;
}
