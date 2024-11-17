#include <stdio.h>
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0

typedef struct AdjVertex {
    char aName;
    struct AdjVertex* next;
} AdjVertex;

typedef struct Vertex {
    char vName;
    int isVisit;
    AdjVertex* aHead;
    struct Vertex* next;
} Vertex;

typedef struct {
    Vertex* vHead;
} GraphType;

void initGraph(GraphType* G) {
    G->vHead = NULL;
}

void makeVertex(GraphType* G, char vName) {
    Vertex* V = (Vertex*) malloc(sizeof(Vertex));
    V->vName = vName;
    V->aHead = NULL;
    V->next = NULL;
    V->isVisit = FALSE;

    if (G->vHead == NULL) {
        G->vHead = V;
    } else {
        Vertex* p = G->vHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = V;
    }
}

void makeAdjVertex(Vertex* v, char aName) {
    AdjVertex* a = (AdjVertex*) malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->next = NULL;

    if (v->aHead == NULL) {
        v->aHead = a;
    } else {
        AdjVertex* p = v->aHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = a;
    }
}

Vertex* findVertex(GraphType* G, char vName) {
    Vertex* p = G->vHead;
    while (p != NULL) {
        if (p->vName == vName) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void insertEdge(GraphType* G, char v1, char v2) {
    Vertex* V = findVertex(G, v1);
    if (V != NULL) {
        makeAdjVertex(V, v2);
    }
}

// 반복적 깊이 우선 탐색 (iDFS) - 스택을 이용한 구현
void iDFS(GraphType* G, char start) {
    // 초기화
    for (Vertex* v = G->vHead; v != NULL; v = v->next) {
        v->isVisit = FALSE;
    }

    Vertex* V = findVertex(G, start);
    if (V == NULL) {
        printf("Vertex %c not found!\n", start);
        return;
    }

    char stack[50]; 
    int top = -1;
    stack[++top] = start;
    
    while (top >= 0) {
        char vName = stack[top--];
        V = findVertex(G, vName);
        if (V->isVisit == FALSE) {
            V->isVisit = TRUE;
            printf("[%c]", V->vName);
        }
        
        for (AdjVertex* a = V->aHead; a != NULL; a = a->next) {
            if (findVertex(G, a->aName)->isVisit == FALSE) {
                stack[++top] = a->aName;
            }
        }
    }
}

// 너비 우선 탐색 (BFS) - 큐를 이용한 구현
void iBFS(GraphType* G, char start) {
    for (Vertex* v = G->vHead; v != NULL; v = v->next) {
        v->isVisit = FALSE;
    }

    Vertex* V = findVertex(G, start);
    if (V == NULL) {
        printf("Vertex %c not found!\n", start);
        return;
    }

    char queue[100]; 
    int front = 0, rear = 0;
    queue[rear++] = start;
    V->isVisit = TRUE;

    while (front < rear) {
        char vName = queue[front++];
        V = findVertex(G, vName);
        printf("[%c]", V->vName);
        
        for (AdjVertex* a = V->aHead; a != NULL; a = a->next) {
            if (findVertex(G, a->aName)->isVisit == FALSE) {
                queue[rear++] = a->aName;
                findVertex(G, a->aName)->isVisit = TRUE;
            }
        }
    }
}

int main() {
    GraphType G;
    initGraph(&G);

    makeVertex(&G, 'A');
    makeVertex(&G, 'B');
    makeVertex(&G, 'C');
    makeVertex(&G, 'D');
    makeVertex(&G, 'E');
    makeVertex(&G, 'F');
    makeVertex(&G, 'G');
    makeVertex(&G, 'H');

    insertEdge(&G, 'A', 'B');
    insertEdge(&G, 'A', 'C');
    insertEdge(&G, 'B', 'D');
    insertEdge(&G, 'C', 'D');
    insertEdge(&G, 'C', 'E');
    insertEdge(&G, 'D', 'F');
    insertEdge(&G, 'E', 'G');
    insertEdge(&G, 'E', 'H');
    insertEdge(&G, 'G', 'H');

    printf("iDFS: ");
    iDFS(&G, 'C');
    printf("\n");

    printf("BFS: ");
    iBFS(&G, 'C');
    printf("\n");

    return 0;
}
