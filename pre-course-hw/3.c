// 3. 2번 문제를 Switch Case 문으로 작성하세요

#include <stdio.h>

int main () {
  int grade = 0;

  printf("학생의 점수를 입력하세요 : ");
  scanf("%d", &grade);

  if(grade > 100 || grade < 0){
    printf("Wrong Input");
  } else {
    switch(grade / 10){
      case 10: 
      case 9:  
        printf("A");
        break;
      case 8:  
        printf("B");
        break;
      case 7: 
        printf("C");
        break;
      default: 
        printf("D or F");
        break;
    }
  }
  
  return 0;
}
