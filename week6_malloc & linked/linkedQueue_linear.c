#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct QueueNode {
    element data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} QueueType;

void init(QueueType* Q) {
    Q->front = NULL;
    Q->rear = NULL;
}

int isEmpty(QueueType* Q) {
    return Q->front == NULL;
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
        Q->front = node;
        Q->rear = node;
    } else {
        Q->rear->next = node;
        Q->rear = node; // rear가 유령값을 참조하고 있음
    }
}

void print(QueueType* Q) {
    for (QueueNode* p = Q->front; p != NULL; p = p->next) {
        printf("[%d] => ", p->data);
    }
    printf("NULL\n");
}

element dequeue(QueueType* Q) {
    if (isEmpty(Q)) {
        return -1; 
    } else {
        QueueNode* p = Q->front;
        element e = p->data;
        Q->front = p->next; 
        if (Q->front == NULL) { // 화살표가 2개라 꼭 있어야 함 
            Q->rear = NULL;  
        }
        free(p);
        return e;
    }
}

int main() {
    QueueType Q;
    init(&Q);

    enqueue(&Q, 10); print(&Q);
    enqueue(&Q, 20); print(&Q);

    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);
    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);

    enqueue(&Q, 30); print(&Q);
    return 0;
}
