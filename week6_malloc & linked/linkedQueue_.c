#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct QueueNode {
    element data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* rear;  // rear만 관리
} QueueType;

void init(QueueType* Q) {
    Q->rear = NULL; // 초기 상태에서 rear는 NULL
}

int isEmpty(QueueType* Q) {
    return Q->rear == NULL;
}

QueueNode* makeNode(element e) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = e;
    node->next = NULL;
    return node;
}

void enqueue(QueueType* Q, element e) {
    QueueNode* node = makeNode(e);
    if (isEmpty(Q)) {
        Q->rear = node; // 큐가 비어 있을 때 rear를 새 노드로 설정
        node->next = node; // 자기 자신을 가리키게 설정 (원형 구조)
    } else {
        node->next = Q->rear->next; // 새 노드의 next를 현재 front에 연결
        Q->rear->next = node; // 현재 rear의 next에 새 노드를 연결
    }
    Q->rear = node; // rear를 새 노드로 업데이트
}

element dequeue(QueueType* Q) {
    if (isEmpty(Q)) {
        printf("큐가 비어있습니다!\n");
        return -1; 
    }

    QueueNode* front = Q->rear->next; // front 노드 (rear의 다음 노드)
    element e = front->data;

    if (Q->rear == front) { // 큐에 노드가 하나만 있을 때
        Q->rear = NULL; // rear를 NULL로 설정
    } else {
        Q->rear->next = front->next; // rear의 next를 다음 노드로 업데이트
    }
    
    free(front); // 메모리 해제
    return e;
}

void print(QueueType* Q) {
    if (isEmpty(Q)) {
        printf("큐가 비어있습니다!\n");
        return;
    }
    
    QueueNode* p = Q->rear->next; // front 노드
    do {
        printf("[%d] => ", p->data);
        p = p->next;
    } while (p != Q->rear->next);
    printf("NULL\n");
}

int main() {
    QueueType Q;
    init(&Q);

    enqueue(&Q, 10); print(&Q);
    enqueue(&Q, 20); print(&Q);
    enqueue(&Q, 30); print(&Q);

    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);
    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);

    enqueue(&Q, 40); print(&Q);
    enqueue(&Q, 50); print(&Q);

    return 0;
}
