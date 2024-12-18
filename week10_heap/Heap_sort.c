// 1) n/2 개의 노드가 내부노드 
// 2) 외부노드 -> 완전 이진트리 ok 
// 3) 외부노드 -> 비교조건 ok
// 3) heapify() 를 통해서, 작게 트리를 만들어서 최대/최소를 올리고 -> 상위 트리에서 또 비교하면서 올림
// 정적으로 배열을 넣고, 이제 그걸 힙 정렬 
#include <stdio.h>
#include <stdlib.h>

void heapify(int A[], int i, int n) {
    int max;
    int left = 2 * i;       // 왼쪽 자식의 인덱스
    int right = 2 * i + 1;  // 오른쪽 자식의 인덱스

    // 왼쪽 자식이 있고, 부모보다 큰 경우
    if (left < n && A[left] > A[i]) {
        max = left; // 젤 큰 값의 인덱스 hㅌ    
    } else {
        max = i; // 걍 부모가 젤 큼
    }

    // 오른쪽 자식이 있고, 현재 max보다 큰 경우
    if (right < n && A[right] > A[max]) {
        max = right;
    }

    // max가 i가 아닌 경우, 교환하고 재귀적으로 호출
    if (max != i) {
        int tmp = A[i];
        A[i] = A[max];
        A[max] = tmp;

        heapify(A, max, n);
    }
}

// 내부 노드 힙속성 만족 
void buildHeap(int A[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        heapify(A, i, n);
    }
}

void printHeap(int A[], int n) {
    for (int i = 1; i < n; i++) {
        printf("[%d] ", A[i]);
    }
    printf("\n");
}


void heapSort(int A[], int n) {
    buildHeap(A, n);
    printHeap(A,n);
    printf("----------------------------------------\n");

    for (int i = n - 1; i > 1; i--) {
        //: 최댓값(A[1])을 배열 끝(A[i])으로 이동
        int tmp = A[i];
        A[i] = A[1];
        A[1] = tmp;

        heapify(A, 1, i); // 여기에서는 젤 큰 값을 앞으로 뺴기 위한 
        printHeap(A,n);
    }
}


int main() {
    int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7} ;  // 첫 번째 요소는 0 (사용하지 않음)
    int n = sizeof(A) / sizeof(A[0]);

    heapSort(A, n);
    printHeap(A, n);
    return 0;
}
