// 13. (계좌번호, 이름, 잔액)의 정보를 갖는 구조체 Bank를 선언한 후, 각 필드를 입력 받고 이를 출력하는 프로그램을 작성하라. 

#include <stdio.h>

struct Bank {
    int accountNum;  
    char name[50];     
    int balance;       
};

int main() {
    struct Bank user;  

    printf("계좌번호 이름 잔액 입력하시오 : ");
    scanf("%d %s %d", &user.accountNum, user.name, &user.balance);

    printf("%s의 %d계좌의 잔액은 %d원\n", user.name, user.accountNum, user.balance);

    return 0;
}
