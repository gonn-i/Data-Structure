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
    V -> isVisit = FALSE;

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
}

void rDFS(GraphType* G, char vName){
  // 재귀추적
  Vertex* V = findVertex(G, vName);
  AdjVertex*a = NULL;

  if(V -> isVisit == FALSE){
    V -> isVisit = TRUE;
    printf("[%c]", V -> vName);
  }

  for(a = V -> aHead; a!= NULL; a = a -> next){
    V = findVertex(G,a -> aName);
    if(V -> isVisit == FALSE){
      rDFS(G, V -> vName);
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

    printGraph(&G); printf("\n");

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
