#include <stdlib.h>
#include <stdio.h>

#define N 100
#define M 6

char map[M][M] = {
    {'1', '1', '1', '1', '1', '1'},
    {'0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '1', '1', '0', '0', 'x'},
    {'1', '1', '1', '0', '1', '1'},
    {'1', '1', '1', '1', '1', '1'},
};

typedef struct {
    int r, c;
} Coor;

typedef Coor element;

typedef struct stackType {
    int top;
    element data[N];
} stackType;

typedef struct queueType {
    int front, rear;
    element data[N];
} queueType;

void initStack(stackType *s) {
    s->top = -1;
}

int isEmptyStack(stackType *s) {
    return s->top == -1;
}

int isFullStack(stackType *s) {
    return s->top == N - 1;
}

void push(stackType *s, element item) {
    if (isFullStack(s)) {
        printf("스택 오버플로우 발생!\n");
    } else {
        s->top++;
        s->data[s->top] = item;
    }
}

element pop(stackType *s) {
    if (isEmptyStack(s)) {
        printf("스택 비었음\n");
        return (element){-1, -1}; 
    }
    return s->data[s->top--];
}

void initQueue(queueType *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmptyQueue(queueType *q) {
    return q->front == q->rear;
}

int isFullQueue(queueType *q) {
    return (q->rear + 1) % N == q->front;
}

void enqueue(queueType *q, element item) {
    if (isFullQueue(q)) {
        printf("큐 오버플로우 발생!\n");
    } else {
        q->data[q->rear] = item;
        q->rear = (q->rear + 1) % N;
    }
}

element dequeue(queueType *q) {
    if (isEmptyQueue(q)) {
        printf("큐 비었음\n");
        return (element){-1, -1}; 
    }
    return q->data[q->front++];
}

void printMap() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int dfs(Coor start) {
    stackType stack;
    initStack(&stack);
    push(&stack, start);
    // 상, 하, 좌, 우
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 

    while (!isEmptyStack(&stack)) {
        Coor current = pop(&stack);
        
        if (map[current.r][current.c] == 'x') {
            printf("탈출 성공!\n");
            return 1;
        }
        if (map[current.r][current.c] == '0') {
            map[current.r][current.c] = '*'; // 방문 표시를 별표로 함
            printf("\n");
            printMap(); 

            // 상하좌우 이동
            for (int i = 0; i < 4; i++) {
                int newR = current.r + directions[i][0];
                int newC = current.c + directions[i][1];
                // 유효한 범위 체크와 이동 가능여부 체크
                if (newR >= 0 && newR < M && newC >= 0 && newC < M && (map[newR][newC] == '0' || map[newR][newC] == 'x')) {
                    push(&stack, (element){newR, newC});
                }
            }
        }
    }
    printf("탈출 실패!\n");
    return 0;
}

int bfs(Coor start) {
    queueType queue;
    initQueue(&queue);
    enqueue(&queue, start);
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상, 하, 좌, 우

    while (!isEmptyQueue(&queue)) {
        Coor current = dequeue(&queue);

        if (map[current.r][current.c] == 'x') {
            printf("탈출 성공!\n");
            return 1;
        }

        if (map[current.r][current.c] == '0') {
            map[current.r][current.c] = '*'; // 방문 표시
            printf("\n");
            printMap(); 

            // 상하좌우 이동
            for (int i = 0; i < 4; i++) {
                int newR = current.r + directions[i][0];
                int newC = current.c + directions[i][1];
                // 유효한 범위 체크 및 이동할 수 있는지 확인
                if (newR >= 0 && newR < M && newC >= 0 && newC < M && (map[newR][newC] == '0' || map[newR][newC] == 'x')) {
                    enqueue(&queue, (element){newR, newC});
                }
            }
        }
    }
    printf("탈출에 실패!\n");
    return 0;
}

int main() {
    Coor start = {1, 0}; 
    printf("\n!DFS를 통한 탐색을 시작!\n");
    dfs(start);
    printf("=========================");
    char Map[M][M] = {
        {'1', '1', '1', '1', '1', '1'},
        {'0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '1', '1'},
        {'1', '1', '1', '0', '0', 'x'},
        {'1', '1', '1', '0', '1', '1'},
        {'1', '1', '1', '1', '1', '1'},
    };
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            map[i][j] = Map[i][j];
        }
    }

    printf("\n!BFS를 통한 탐색을 시작!\n");
    bfs(start);
    
    return 0;
}
