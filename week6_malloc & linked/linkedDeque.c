// 덱으로 이름 바꾸기 

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

void insertFront (QueueType* Q, element e){
      QueueNode* node = makeNode(e);
    if (isEmpty(Q)) {
        Q->front = node; 
        Q->rear = node;
    } else {
        Q->rear->next = node;
        Q->rear = node; 
    }
}

void enqueue(QueueType* Q, element e) {
    QueueNode* node = makeNode(e);
    if (isEmpty(Q)) {
        Q->front = node;
        Q->rear = node;
    } else {
        node ->next = Q -> front; //  나는 누굴 가르키지?
        Q-> front = node; // 누가 나를 가르키지?
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

element deleteRear (QueueType* Q){
      if (isEmpty(Q)) {
        return -1; 
    } 

    QueueNode* p = Q -> front;
    QueueNode* q;
    element e;

    if(p -> next == NULL){
      e = p -> data;
      init(Q);
    } else { // 노드가 최소 2개 이상
      while(p -> next != NULL){
        q = p;  // q는 p로 (오른쪽 칸으로)
        p = p -> next; // p는 다음으로 
      }
      Q -> rear = q;
      q -> next = NULL; // 안하면 다음에 삽입이 안 될수도 있음
      e = p -> data;
    }
    free(p);
    return e;
}



int main() {
    QueueType Q;
    init(&Q);

    enqueue(&Q, 10); print(&Q);
    enqueue(&Q, 20); print(&Q);

    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);
    printf("dequeue [%d] : ", dequeue(&Q)); print(&Q);

    enqueue(&Q, 30); print(&Q);
    insertFront(&Q, 40); print(&Q);

    printf("DeleteRear [%d] : ", deleteRear(&Q)); print(&Q);
    return 0;
}
