// 4. 숫자를 입력받아 일의 자리, 십의 자리, 백의 자리, ... 수로 잘라 출력하는 프로그램을 작성하세요. 
// 단 입력받는 숫자의 자릿수는 제약이 없습니다. (반복문)

#include <stdio.h>

int main() {
    int num, digit;
    
    printf("숫자를 입력하세요: ");
    scanf("%d", &num);

    // 0이 입력된 경우
    if (num == 0) {
        printf("일의 자리: 0\n");
        return 0;
    }


    while (num > 0) {
        digit = num % 10;
        printf("%d\n", digit); 
        num /= 10; 
    }

    return 0;
}
