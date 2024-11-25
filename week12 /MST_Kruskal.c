#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1 
#define FALSE 0
#define INF 100

int dist[N]; 
int vertices[N];

typedef struct Edge {
    char v1, v2;
    int weight;
    struct Edge* next;
} Edge;

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
    Edge* eHead;
    int vCount, eCount;
} GraphType;

void initGraph(GraphType* G) {
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;

    for(int i =0; i< N; i++){
        dist[i] = INF;
        vertices[i] = -1;
    }
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

Vertex* findMin (GraphType* G){
    Vertex* v = NULL;
    int min = INF;

    for(Vertex* p = G-> vHead; p != NULL; p = p -> next){
        if(dist[p -> vName - 65] < min && p -> isVisit == FALSE){
        min = dist[p -> vName- 65];
        v = p; 
    }
    }
    return v;
}

void selectionSort (GraphType* G, Edge* edges[]) {
  Edge* e = G->eHead;
  for (int i = 0; i < G->eCount; i++) {
    edges[i] = e;
    e = e->next;
  }

  for (int i = 0; i < G->eCount; i++) {
    int min = i;
    for (int j = i + 1; j < G->eCount; j++) {
        if (edges[j]->weight < edges[min]->weight) {
        min = j;
      }
    }
        e = edges[min];
        edges[min] = edges[i];
        edges[i] = e;
    }

    for (int i = 0; i < G->eCount; i++) {
        printf("[%c %c %d] ", edges[i]->v1, edges[i]->v2, edges[i]->weight);
    }
    printf("\n");
}

int Find (int vNum){
    while(vertices[vNum] != -1){
        vNum = vertices[vNum];
    }
    return vNum;
}

void Union (int vNum1, int vNum2){
    vertices[vNum2] = vNum1;
}

// 이거 사진보고 따라하기
void dijkstra(GraphType* G, char vName) {
    Vertex* v = NULL;
    AdjVertex* a = NULL;

    // dist 배열 초기화: 모든 값을 INF로 설정
    for (int i = 0; i < G->vCount; i++) {
        dist[i] = INF;
    }

    // 출발점의 거리는 0으로 설정
    dist[vName - 65] = 0;

    // Dijkstra 알고리즘 실행
    for (int i = 0; i < G->vCount; i++) {
        // 최소값을 가진 정점을 선택
        v = findMin(G);
        if (v == NULL) break;  // 더 이상 방문할 정점이 없으면 종료

        v->isVisit = TRUE;

        // 선택된 정점과 인접한 정점들에 대해 거리 갱신
        for (a = v->aHead; a != NULL; a = a->next) {
            Vertex* w = findVertex(G, a->aName);

            if (w != NULL && w->isVisit == FALSE && 
                dist[v->vName - 65] + a->weight < dist[a->aName - 65]) {
                dist[a->aName - 65] = dist[v->vName - 65] + a->weight;
            }
        }
    }

    // 최단 거리 출력
    for (int i = 0; i < G->vCount; i++) {
        printf("Vertex %c : %d\n", 65 + i, dist[i]);
    }
}



// Union find 기반 
void kruskal (GraphType* G, Edge* edges[]){
    int eCnt = 0, i=0;

    int vNum1, vNum2;
    Edge* e;

    while(eCnt < G -> vCount -1){
        e = edges[i];

        vNum1 = Find(e -> v1 - 65);
        vNum2 = Find(e -> v2 - 65);

        if(vNum1 != vNum2){
            printf(" %d. [%c %c %d]", eCnt +1, e -> v1, e-> v2, e -> weight);
            printf("\n");
            eCnt++;
            Union(vNum1, vNum2);
        }
        i++;
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

    Edge* edges [N];
    selectionSort(&G, edges);
    kruskal(&G, edges);

    // printGraph(&G);
    // prim(&G, 'A');

    return 0;
} 