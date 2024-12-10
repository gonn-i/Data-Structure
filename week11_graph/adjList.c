#include <stdio.h>
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0

// A → B, A → C, B → C로 연결되어 있다면 
// A (Vertex) -> AdjVertex(B) -> AdjVertex(C) -> NULL 이런식으로 연결시킴 
// A의 aHead 가 B를 가리킴
// Vertex A -> Vertex B -> Vertex C -> NULL 이렇게 정점 리스트 연결 
// next로 A는 B를 , B는 C를, C는 NULL을 가리킴

typedef struct AdjVertex { // 연결 고리
    char aName; // 정점 (노드)
    struct AdjVertex* next; // 연결 간선 (다음 인접 정점)
} AdjVertex;

typedef struct Vertex { // 각 노드를 의미 
    char vName;
    int isVisit; // 방문 여부 체크
    AdjVertex* aHead; // 정점 내부의 인접 정점들(간선)
    struct Vertex* next; // 그래프의 정점 리스트 전체를 연결
} Vertex;

typedef struct { // 그래프 전체 
    Vertex* vHead; // 첫번째 정점의 포인터
} GraphType;



void initGraph(GraphType* G) {
    G->vHead = NULL;
}

void makeVertex(GraphType* G, char vName) {
    Vertex* V = (Vertex*) malloc(sizeof(Vertex));
    V-> vName = vName;
    V-> aHead = NULL;
    V-> next = NULL;
    V -> isVisit = FALSE;

    if (G->vHead == NULL) {
        G->vHead = V; // 그래프에 아무것도 없으면, 그래프 첫 노드는 V (새 노드)
    } else {
        Vertex* p = G->vHead; // 아니라면 젤 앞에 있는애 불러와서 
        while (p->next != NULL) { // 그 뒤에 연결 
            p = p->next;
        }
        p -> next = V;
    }
}

void makeAdjVertex(Vertex* v, char aName) {
    AdjVertex* a = (AdjVertex*) malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->next = NULL;

    if (v->aHead == NULL) { // 원래 돌멩이에 연결된거 없었다면 그냥 aHead에 연결 
        v->aHead = a;
    } else {
        AdjVertex* p = v->aHead; // 제일 앞 노드의 다음에 연결 
        while (p->next != NULL) { // 근데 그 앞에 있는 돌멩이의 젤 뒤에 연결 
            p = p->next;
        }
        p->next = a; // 연결!!
    }
}

Vertex* findVertex(GraphType* G, char vName) {
    Vertex* p = G->vHead;
    while (p != NULL) {
        if (p-> vName == vName) {
            return p; // v1 에 해당하는 돌멩이를 찾아서 반환
        }
        p = p->next;
    }
    return NULL;
}

void insertEdge(GraphType* G, char v1, char v2) {
    Vertex* V = findVertex(G, v1);
    if (V != NULL) { // 노드가 있을떄만 서로 연결 
        makeAdjVertex(V, v2);
    } else {
        printf("Vertex %c not found!\n", v1);
    }
}

void printGraph(GraphType* G) {
    for (Vertex* p = G -> vHead; p != NULL; p = p->next) {
        printf("[%c]", p->vName); // 모든 정점에 대해 이름 출력 
        for (AdjVertex* q = p -> aHead; q != NULL; q = q->next) {
            printf(" -> [%c]", q->aName); // 연결로 타고 들어가기
        }
        printf("\n");
    }
}

void rDFS(GraphType* G, char vName){
  // 재귀추적
    Vertex* V = findVertex(G, vName);
    AdjVertex*a = NULL;

    if(V -> isVisit == FALSE){
        V -> isVisit = TRUE;
        printf("[%c]", V -> vName);
    }

    for(a = V -> aHead; a!= NULL; a = a -> next){ // 다음 인접연결고리가 있으면 재귀호출!! 
        V = findVertex(G, a -> aName);// 인접한 돌멩이 vertex 갱신
        if(V -> isVisit == FALSE){
            rDFS(G, V -> vName); 
        }
    }
}

int main() {
    GraphType G;
    initGraph(&G);

    // 얘는 단순 노드 (돌멩이 만들어주기)
    makeVertex(&G, 'A');
    makeVertex(&G, 'B');
    makeVertex(&G, 'C');
    makeVertex(&G, 'D');
    makeVertex(&G, 'E');
    makeVertex(&G, 'F');
    makeVertex(&G, 'G');
    makeVertex(&G, 'H');

    printGraph(&G); printf("\n");

    // 여기에서 돌멩이 서로 엮어주기 
    insertEdge(&G, 'A', 'B');
    insertEdge(&G, 'A', 'C');
    insertEdge(&G, 'B', 'D');
    insertEdge(&G, 'C', 'D');
    insertEdge(&G, 'C', 'E');
    insertEdge(&G, 'D', 'F');
    insertEdge(&G, 'E', 'G');
    insertEdge(&G, 'E', 'H');
    insertEdge(&G, 'G', 'H');

    printGraph(&G); printf("\n");


    rDFS(&G, 'B');
    return 0;
}
