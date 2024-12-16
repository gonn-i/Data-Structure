#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1 
#define FALSE 0
#define INF 100

int dist[N]; // 최단 거리 배열
int vertices[N]; // Union-Find 배열

typedef struct Edge {
    char v1, v2; // 간선이 연결하는 두 정점
    int weight;  // 간선 가중치
    struct Edge* next; // 다음 간선 포인터
} Edge;

typedef struct AdjVertex {
    char aName; // 인접 정점 이름
    struct AdjVertex* next; // 다음 인접 정점 포인터
} AdjVertex;

typedef struct Vertex {
    char vName; // 정점 이름
    int isVisit; // 방문 여부
    AdjVertex* aHead; // 인접 정점 리스트 헤드
    struct Vertex* next; // 다음 정점 포인터
} Vertex;

typedef struct {
    Vertex* vHead;
    Edge* eHead;
    int vCount, eCount;
} GraphType;

// 그래프 초기화 함수
void initGraph(GraphType* G) {
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;

    // dist 및 vertices 배열 초기화
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        vertices[i] = -1; // Union-Find 부모 노드 초기화
    }
}

void makeVertex(GraphType* G, char vName) {
    Vertex* V = (Vertex*)malloc(sizeof(Vertex));
    V->vName = vName;
    V->aHead = NULL;
    V->next = NULL;
    V->isVisit = FALSE;

    G->vCount++;

    // 정점 리스트 추가 
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

// 인접 정점 추가 
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

// 정점 탐색
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

    // 간선 리스트 추가 
    if (G->eHead == NULL) {
        G->eHead = e;
    } else {
        Edge* p = G->eHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = e;
    }

    // 인접 정점 추가 
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


// 먼저 정렬해서 가중치순으로 정렬
void selectionSort (GraphType* G, Edge* edges[]) {
    Edge* e = G -> eHead;

    for (int i = 0; i < G -> eCount; i++) { // 원래 있던 edge 그대로 담음 
        edges[i] = e;
        e = e->next;
    }

    // edge 정렬 
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


void dijkstra(GraphType* G, char vName) {
    Vertex* v = NULL; // 현재 처리 중인 정점
    AdjVertex* a = NULL; // 인접 정점 리스트를 순회하기 위한 포인터

    // 1. dist 배열 초기화: 모든 정점의 거리를 무한대로 설정
    for (int i = 0; i < G->vCount; i++) {
        dist[i] = INF;
    }

    // 2. 출발점의 거리를 0으로 설정
    dist[vName - 'A'] = 0; // 정점 이름을 인덱스로 변환 ('A' -> 0, 'B' -> 1, ...)

    // 3. 다익스트라 알고리즘 실행
    for (int i = 0; i < G->vCount; i++) {
        // (1) 방문하지 않은 정점 중에서 가장 작은 거리 값을 가진 정점을 찾음
        v = findMin(G);
        if (v == NULL) break; // 모든 정점이 방문되었으면 종료

        v->isVisit = TRUE; // 선택된 정점을 방문 처리

        // (2) 선택된 정점의 인접 정점들에 대해 거리 갱신
        for (a = v->aHead; a != NULL; a = a->next) {
            Vertex* w = findVertex(G, a->aName); // 인접 정점 탐색

            // 방문하지 않은 정점이고, 기존 거리보다 새로운 경로가 더 짧은 경우
            if (w != NULL && w->isVisit == FALSE) {
                Edge* edge = G->eHead; // 그래프의 엣지 리스트에서 가중치를 찾아야 함
                while (edge != NULL) {
                    if ((edge->v1 == v->vName && edge->v2 == a->aName) || 
                        (edge->v1 == a->aName && edge->v2 == v->vName)) {
                        // 가중치를 찾아 거리 계산
                        int newDist = dist[v->vName - 'A'] + edge->weight;
                        if (newDist < dist[a->aName - 'A']) {
                            dist[a->aName - 'A'] = newDist; // 거리 갱신
                        }
                        break;
                    }
                    edge = edge->next;
                }
            }
        }
    }

    // 4. 최단 거리 출력
    for (int i = 0; i < G->vCount; i++) {
        printf("Vertex %c : %d\n", 'A' + i, dist[i]);
    }
}

// Union-Find: Union 함수
void Union (int vNum1, int vNum2){
    vertices[vNum2] = vNum1;
}

// Union-Find: Find 함수
int Find (int vNum){
    while(vertices[vNum] != -1){
        vNum = vertices[vNum];
    }
    return vNum;
}

// Union find 기반 
void kruskal (GraphType* G, Edge* edges[]){
    int eCnt = 0, i=0;

    int vNum1, vNum2;
    Edge* e;

    while(eCnt < G -> vCount -1){ // eCount == 전체 노드개수 -1
        e = edges[i]; // edge 작은거부터 

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


    return 0;
} 