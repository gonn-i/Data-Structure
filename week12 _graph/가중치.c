#include <stdio.h>
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0

// 간선을 나타내는 구조체 (두 정점과 / 가중치/ 다른 간선과 연결된 포인터를 가지고 있음)
typedef struct Edge {
    char v1, v2;
    int weight;
    struct Edge* next;
} Edge;

// 각 정점의 인접 정점
typedef struct AdjVertex {
    char aName;
    struct AdjVertex* next;
} AdjVertex;

typedef struct Vertex { // 정점 (돌멩이))
    char vName;
    int isVisit;
    AdjVertex* aHead;
    struct Vertex* next;
} Vertex;

typedef struct GraphType{
    Vertex* vHead; // 정점리스트
    Edge* eHead;  // 간선리스트 (가중치 + 어디에 연결)
    int vCount, eCount;
} GraphType;

void initGraph(GraphType* G) {
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;
}

void makeVertex(GraphType* G, char vName) {
    Vertex* V = (Vertex*)malloc(sizeof(Vertex));
    V->vName = vName;
    V->aHead = NULL;
    V->next = NULL;
    V->isVisit = FALSE;

    G->vCount++; // 정점수 추가 + 1

    if (G -> vHead == NULL) {
        G -> vHead = V; // 그래프가 텅 비었으면 그냥 정점리스트에 넣기
    } else {
        Vertex* p = G->vHead;
        while (p -> next != NULL) {
            p = p->next;
        }
        p->next = V; // 젤 끝에 연결시켜주기
    }
}

// 인접 정점을 추가해주기
void makeAdjVertex(Vertex* v, char aName) {
    AdjVertex* a = (AdjVertex*)malloc(sizeof(AdjVertex));
    a-> aName = aName;
    a-> next = NULL;

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
// 연결시킬 정점 찾기 
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

void insertEdge(GraphType* G, char v1, char v2, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = weight;
    e->next = NULL;

    G->eCount++;

    if (G->eHead == NULL) {
        G->eHead = e; // 그래프 비었으면 바로 edge 연결
    } else {
        Edge* p = G-> eHead; 
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = e;
    }

    Vertex* V = findVertex(G, v1); 
    if (V != NULL) {
        makeAdjVertex(V, v2);
    } else {
        printf("Vertex %c not found!\n", v1);
    }
}

void printGraph(GraphType* G) {
    // 인접리스트 출력 
    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        printf("[%c]", p->vName);
        for (AdjVertex* q = p->aHead; q != NULL; q = q->next) {
            printf(" -> [%c]", q->aName);
        }
        printf("\n");
    }
    printf("\nEdges:\n"); 
    // EDGE 반영된거 출력
    for (Edge* e = G->eHead; e != NULL; e = e->next) {
        printf("[%c, %c] : [%d]\n", e->v1, e->v2, e->weight);
    }
}

void rDFS(GraphType* G, char vName) {
    Vertex* V = findVertex(G, vName);
    if (V == NULL || V->isVisit == TRUE) {
        return;
    }

    V->isVisit = TRUE;
    printf("[%c]", V->vName);

    for (AdjVertex* a = V->aHead; a != NULL; a = a->next) {
        rDFS(G, a->aName);
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

    insertEdge(&G, 'A', 'B', 25);
    insertEdge(&G, 'A', 'D', 12);
    insertEdge(&G, 'B', 'C', 10);
    insertEdge(&G, 'B', 'D', 15);
    insertEdge(&G, 'C', 'G', 16);
    insertEdge(&G, 'D', 'E', 17);
    insertEdge(&G, 'D', 'F', 37);
    insertEdge(&G, 'E', 'G', 14);
    insertEdge(&G, 'E', 'F', 19);
    insertEdge(&G, 'F', 'G', 42);

    printGraph(&G);
    // printf("\nDepth-First Search starting from 'B':\n");
    // rDFS(&G, 'B');

    return 0;
}
