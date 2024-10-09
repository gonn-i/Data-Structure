// [ 문제 5 ] 원반의 개수 N을 입력받아, 하노이 탑 문제의 수행과정을 예시와 같이 출력하는 프로그램을 작성하시오.
#include <stdio.h>

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("원반 1을 %c에서 %c로 이동\n", from, to);
        return;
    }
    // n-1개의 원반을 A에서 B로 이동 (보조 기둥 사용)
    hanoi(n - 1, from, aux, to);
    // n번째 원반을 A에서 C로 이동
    printf("원반 %d을 %c에서 %c로 이동\n", n, from, to);
    // n-1개의 원반을 B에서 C로 이동 (보조 기둥 사용)
    hanoi(n - 1, aux, to, from);
}

int main () {
    int N;

    printf("원반의 개수를 입력하세요: ");
    scanf("%d", &N);

    // A 기둥에서 C 기둥으로 원반을 이동 (B 기둥을 보조로 사용)
    hanoi(N, 'A', 'C', 'B');

    return 0;
}
