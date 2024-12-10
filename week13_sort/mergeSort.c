#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int sorted[N]; // 전역 배열으로 sorted 선언

void merge(int A[], int left, int mid, int right) {
    int i = left; // 시작인덱스 
    int j = mid + 1; // 시작인덱스 
    int k = left; // 정렬된 결과를 임시로 저장할 새로운 배열의 왼쪽임 

    while (i <= mid && j <= right) { // 왼쪽 부분배열과 오른쪽 부분배열에 처리할것이 있는 경우
        if (A[i] <= A[j])  // 첫 번째 부분 배열(A[i])과 두 번째 부분 배열(A[j])을 비교
            sorted[k++] = A[i++];
        else 
            sorted[k++] = A[j++]; 
    }
    
    // 왼쪽 배열이 먼저 끝난 경우, 오른쪽 배열의 남은 값들을 sorted에 복사
    if (i > mid) {
        for (int l = j; l <= right; l++) 
            sorted[k++] = A[l];
    }
    // 오른쪽 배열이 먼저 끝난 경우, 왼쪽 배열의 남은 값들을 sorted에 복사
    else {
        for (int l = i; l <= mid; l++) 
            sorted[k++] = A[l];
    }

    // 정렬된 배열을 원래 배열에 덮어씌워주기
    for (int l = left; l <= right; l++) 
        A[l] = sorted[l];
}

void mergeSort(int A[], int left, int right) {
    if (left < right) { // 분할할 수 있으면 
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

int main() {
    int A[N];
    srand(time(NULL));

    // 배열에 랜덤 값 할당
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
    }

    // 정렬 전 출력
    printf("Before Sort : \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    // Merge Sort 실행
    mergeSort(A, 0, N - 1);

    // 정렬 후 출력
    printf("<<<<<<<<<< merge sort >>>>>>>>>>>>\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
