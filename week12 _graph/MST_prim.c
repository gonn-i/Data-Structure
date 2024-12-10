#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1 
#define FALSE 0
#define INF 100

int dist[N];  // 최소 가중치를 기록하는 배열
char selectedVertices[N];  // 선택된 정점 순서를 기록
int totalWeight = 0;       // MST의 총 가중치

typedef struct Edge {
    char v1, v2;       // 간선이 연결하는 두 정점
    int weight;        // 간선의 가중치
    struct Edge* next; // 다음 간선을 가리키는 포인터
} Edge;

typedef struct AdjVertex {
    char aName;        // 인접 정점의 이름
    struct AdjVertex* next; // 다음 인접 정점을 가리키는 포인터
} AdjVertex;

typedef struct Vertex {
    char vName;        // 정점의 이름
    int isVisit;       // 정점의 방문 여부
    AdjVertex* aHead;  // 인접 정점들을 가리키는 포인터
    struct Vertex* next; // 다음 정점을 가리키는 포인터
} Vertex;

typedef struct {
    Vertex* vHead;     // 정점들을 가리키는 포인터
    Edge* eHead;       // 간선들을 가리키는 포인터
    int vCount, eCount; // 정점과 간선의 개수
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

    G->vCount++;

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
    AdjVertex* a = (AdjVertex*)malloc(sizeof(AdjVertex));
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

void insertEdge(GraphType* G, char v1, char v2, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = weight;
    e->next = NULL;

    G->eCount++;

    if (G->eHead == NULL) {
        G->eHead = e;
    } else {
        Edge* p = G->eHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = e;
    }

    Vertex* v = findVertex(G, v1);
    if (v != NULL) {
        makeAdjVertex(v, v2);
    } else {
        printf("Vertex %c not found!\n", v1);
    }
}

void printGraph(GraphType* G) {
    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        printf("[%c]", p->vName);
        for (AdjVertex* q = p->aHead; q != NULL; q = q->next) {
            printf(" -> [%c]", q->aName);
        }
        printf("\n");
    }
    printf("\nEdges:\n");
    for (Edge* e = G->eHead; e != NULL; e = e->next) {
        printf("[%c, %c] : [%d]\n", e->v1, e->v2, e->weight);
    }
}

Vertex* findMin(GraphType* G) {
    Vertex* v = NULL;
    int min = INF;

    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        if (dist[p->vName - 'A'] < min && p->isVisit == FALSE) {
            min = dist[p->vName - 'A'];
            v = p;
        }
    }
    return v;
}

void prim(GraphType* G, char vName) {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }

    Vertex* V = findVertex(G, vName);
    dist[vName - 'A'] = 0;
    int selectedCount = 0;

    for (int i = 0; i < G->vCount; i++) {
        V = findMin(G);
        if (V == NULL) break;

        V->isVisit = TRUE;
        selectedVertices[selectedCount++] = V->vName;

        for (AdjVertex* A = V->aHead; A != NULL; A = A->next) {
            Vertex* w = findVertex(G, A->aName);
            if (w == NULL || w->isVisit == TRUE) continue;

            Edge* E = G->eHead;
            while (E != NULL) {
                if ((E->v1 == V->vName && E->v2 == A->aName) || (E->v1 == A->aName && E->v2 == V->vName)) {
                    if (dist[A->aName - 'A'] > E->weight) {
                        dist[A->aName - 'A'] = E->weight;
                    }
                }
                E = E->next;
            }
        }

        for (Edge* E = G->eHead; E != NULL; E = E->next) {
            if (E->v1 == V->vName || E->v2 == V->vName) {
                totalWeight += dist[V->vName - 'A'];
                break;
            }
        }
    for (int i = 0; i < G -> vCount; i++) {
            printf("%5d", dist[i]);
        }
        printf("\n");
    }


    printf("\nMST 순서: ");
    for (int i = 0; i < selectedCount; i++) {
        printf("%c ", selectedVertices[i]);
    }
    printf("\n총 가중치 합: %d\n", totalWeight);
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
    insertEdge(&G, 'C', 'E', 16);
    insertEdge(&G, 'D', 'E', 17);
    insertEdge(&G, 'D', 'F', 37);
    insertEdge(&G, 'E', 'F', 19);

    printGraph(&G);
    prim(&G, 'A');

    return 0;
}