#include <stdio.h>>
#include <stdlib.h>

#define N 10
#define TRUE 1
#define FALSE 0

char vName[N] = {'A', 'B', 'C', 'D', 'E', 'F','G','H', 'I', 'J'};
int visited [N];

typedef struct {
  int vSize; // 정점의 개수
  int adjMat[N][N]; // 2차원 배열로 정점의 연결상태 저장 
  // adjMat[u][v] = 1 이면, u와 v가 서로 연결 // adjMat[u][v] = 0 이면 연결되지 않음
}GraphType;

// 초기화 
void initGraphType (GraphType* G) {
  G -> vSize = 0; 
  for(int i =0; i < N; i++){
    for (int j = 0; j < N; j++) { 
      G->adjMat[i][j] = 0; // 연결 -> 0 (연결되지 않음으로 설정)
    }
  }
}

// 특정 정점과 연결된 간선의 개수를 계산
int degree(GraphType* G, int v) {
  int count = 0;
  for (int i = 0; i < G->vSize; i++) {
    if (G->adjMat[v][i] == 1) count++; // 정점 v와 연결된 간선 수를 구함 
  }
  return count; 
}

// 간선추가 (정점과 정점 연결 시켜주기)
void insertEdge(GraphType* G, int u ,int v) {
  if (u < G -> vSize && v < G -> vSize){ // u가 존재하고, v가 존재할 경우
    G -> adjMat[u][v] = G -> adjMat[v][u] =1;
  }
}

void print(GraphType* G) {
  for(int i=0; i < G->vSize; i++){
    printf("%c(%d) |",vName[i], degree(G,i));
  
    for(int j =0 ;j < G->vSize; j++){
    printf(" %d", G -> adjMat[i][j]);
    }
    printf("| \n");
  }
}

// 총 정점의 수 설정 
void setVertexCount(GraphType* G, int n) {
  G -> vSize = n;
}

void rDFS (GraphType* G, int s) {
  visited[s] = TRUE; // 방문처리
  printf("[%c]", vName[s]);
  for(int t = 0; t  < G -> vSize; t++){
    if(G -> adjMat[s][t] == 1 && visited[t] == FALSE){
      rDFS(G, t); // s와 연결된거 싹다 출력 
    }
  }

}

int main () {
  GraphType G;
  initGraphType(&G);

  int n;
  printf(" 정점의 수: ");
  scanf("%d", &n);
  printf("\n");

  setVertexCount(&G, n);
  insertEdge(&G, 0, 1); insertEdge(&G, 0, 2);
  insertEdge(&G, 1, 3); insertEdge(&G, 2, 3);
  insertEdge(&G, 2, 4); insertEdge(&G, 3, 5);
  insertEdge(&G, 4, 6); insertEdge(&G, 4, 7);
  insertEdge(&G, 6, 7); print(&G); printf("\n");

  printf("DFS : ");
  rDFS(&G, 1);
  return 0;
}