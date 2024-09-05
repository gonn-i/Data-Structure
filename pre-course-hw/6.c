// 6. 2g, 3g, 5g의 추가 각각 10개씩 있다. 각각의 추를 1개 이상 사용하여 무게 G를 측정하는 함수 sumOfWeghit(int g)를 만들고 테스트한다. 
// 함수는 입력받은 무게 G를 만족하는 모든 경우를 찾아서 각각의 추의 개수를 출력한다. 
// 만족하는 경우가 없으면 0이 출력된다. (반복문 & 함수)

#include <stdio.h>

void sumOfWeight(int G);

int main() {
    int G;

    printf("측정할 무게 G를 입력하세요: ");
    scanf("%d", &G);

    sumOfWeight(G);

    return 0;
}

void sumOfWeight(int G) {
    int count = 0;

    for (int i = 1; i <= 10; i++) {      
        for (int j = 1; j <= 10; j++) {   
            for (int k = 1; k <= 10; k++) {
                if (i * 2 + j * 3 + k * 5 == G) {
                    printf("%d %d %d\n", i, j, k);  
                    count++;  
                }
            }
        }
    }

    if (count == 0) {
        printf("0\n");  
    } else {
        printf("%d\n", count);  
    }
}
