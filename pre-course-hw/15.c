//15. 14번 문제를 해결하기 위해 void deposit(Bank* a, amount)함수를 정의해보자.

#include <stdio.h>
#include <string.h>

struct Bank {
    int accountNum;  
    char name[50];     
    int balance;       
};

void deposit(struct Bank *a, int amount) {
    a->balance += amount; 
}

int main() {
    struct Bank user;  
    char input[100]; 

    printf("계좌번호 이름 잔액을 입력하시오 : ");
    fgets(input, sizeof(input), stdin);

    sscanf(input, "%d %s %d", &user.accountNum, user.name, &user.balance);


    deposit(&user, 1000);


    printf("입금 후 %s의 %d계좌의 잔액은 %d원\n", user.name, user.accountNum, user.balance);

    return 0;
}
