#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1
#define FALSE 0

char vName[N] = {'A', 'B', 'C', 'D', 'E', 'F','G','H', 'I', 'J'};
int visited [N];

typedef struct {
  int vSize;
  int adjMat[N][N];
} GraphType;


void initGraphType(GraphType* G) {
  G->vSize = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      G->adjMat[i][j] = 0;
    }
  }
}

void insertEdge(GraphType* G, int u ,int v) {
  if (u < G->vSize && v < G->vSize) {
    G->adjMat[u][v] = G->adjMat[v][u] = 1;
  }
}

void print(GraphType* G) {
  for (int i = 0; i < G->vSize; i++) {
    printf("%c |", vName[i]);
    for (int j = 0; j < G->vSize; j++) {
      printf(" %d", G->adjMat[i][j]);
    }
    printf("| \n");
  }
}

void setVertexCount(GraphType* G, int n) {
  G->vSize = n;
}

// 반복적 깊이 우선 탐색 (iDFS) - 스택으로
void iDFS(GraphType* G, int start) {
  int stack[N]; 
  int top = -1; 
  stack[++top] = start;  

  while (top >= 0) {  
    int s = stack[top--]; 
    if (!visited[s]) { 
      visited[s] = TRUE;  
      printf("[%c]", vName[s]);  
    }

    for (int t = 0; t < G->vSize; t++) {
      if (G->adjMat[s][t] == 1 && !visited[t]) {
        stack[++top] = t;  
      }
    }
  }
}

// 너비 우선 탐색(BFS) - 큐로
void iBFS(GraphType* G, int start) {
  int queue[N];  
  int front = 0, rear = 0;  
  queue[rear++] = start;  
  visited[start] = TRUE;  

  while (front < rear) { 
    int s = queue[front++]; 
    printf("[%c]", vName[s]); 

    for (int t = 0; t < G->vSize; t++) {
      if (G->adjMat[s][t] == 1 && !visited[t]) {
        queue[rear++] = t;  
        visited[t] = TRUE; 
      }
    }
  }
}

int main () {
  GraphType G;  
  initGraphType(&G);  

  int n;
  printf("정점의 수: ");
  scanf("%d", &n);
  printf("\n");

  setVertexCount(&G, n);
  insertEdge(&G, 0, 1); insertEdge(&G, 0, 2);
  insertEdge(&G, 1, 3); insertEdge(&G, 2, 3);
  insertEdge(&G, 2, 4); insertEdge(&G, 3, 5);
  insertEdge(&G, 4, 6); insertEdge(&G, 4, 7);
  insertEdge(&G, 6, 7); 
  print(&G); 
  printf("\n");

  printf("iDFS: ");
  for (int i = 0; i < n; i++) visited[i] = FALSE;  
  iDFS(&G, 1);  
  printf("\n");

  printf("BFS : ");
  for (int i = 0; i < n; i++) visited[i] = FALSE;  
  iBFS(&G, 1);  

  return 0;
}
