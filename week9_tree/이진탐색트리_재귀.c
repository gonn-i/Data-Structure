
// 순환문을 통한 이진탐색 트리
#include <stdio.h>
#include <stdlib.h>

typedef int element;

// 트리 노드 구조체
typedef struct TreeNode {
  element key; // 노드 자체 값
  struct  TreeNode *right, * left; // 오른쪽, 왼쪽 자식 노드 포인터
} TreeNode;

// 새로운 노드 동적 생성 
TreeNode* makeNode (element key) {
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); 
  node -> key = key;
  node -> left = node -> right = NULL; // 자식 노드 일단 NULL
  return node;
}

// 이진 탐색 트리에 노드 삽입  (재귀 호출)
TreeNode* insertNode (TreeNode* root, element key){
  if(root == NULL) return makeNode(key); //트리 텅빈 경우  그냥 새 노드 반환 

  // 삽입할 값이 작으면 (현재 노드보다) -> 자식의 왼쪽에 
  if(key < root -> key) {
    root -> left = insertNode(root -> left, key);
  } 
    // 삽입할 값이 크면 (현재 노드보다) -> 자식의 오른쪽에 
  else if (key > root -> key){
    root -> right = insertNode(root -> right, key);
  } 
  return root;
} 


// 중위 순회: 왼쪽 - 현재 - 오른쪽 순서로 출력
void inOrder (TreeNode* root) {
  if(root) {
    inOrder(root -> left); // 왼쪽 먼저 방문 
    printf("[%d] ", root -> key);
    inOrder(root -> right); // 다음 오른쪽 방문 
  }
}

// 계층자 찾기 (오른쪽 트리의 왼쪽 끝) -> 가장 작은 값을 가진 노드 
TreeNode*  successor(TreeNode* root){ 
  TreeNode* p = root;
  while(p -> left != NULL){
    p = p -> left;
  }
  return p;
}

TreeNode* deleteNode (TreeNode* root, element key){
  if(root == NULL) return NULL; // 배열이 텅 빈 경우

  if(key < root -> key) { // 삭제할 값이, root key 보다 작으면
    root -> left = deleteNode(root -> left, key);
  } 
  else if (key > root -> key){ // 삭제할 값이, root key 보다 크면
    root -> right = deleteNode(root -> right, key);
  }  
   // 삭제할 노드 찾음
  else {
    if(root -> left == NULL){ // case 1 왼쪽 자식이 없는 경우
      TreeNode* temp = root -> right;
      free(root);
      return temp;
    } else if (root -> right == NULL){ // case 2 오른쪽 자식만 없는 경우
      TreeNode* temp = root -> left;
      free(root); 
      return temp;
    } else { // 두 자식다 있는 경우
      TreeNode* temp = successor(root -> right); 
      root -> key = temp -> key; // 대신 연결해주기
      root -> right = deleteNode(root -> right, temp -> key); // 원래 오른쪽에 연결되어있던걸 삭제
    }
  } 
  return root;
}

int main () {

  TreeNode*  root = NULL;
  element keys[] = {35,18,7,26,12,3,68,22,30, 99};

  for(int i =0; i < 10; i++){
    root = insertNode(root, keys[i]);
    inOrder(root);
    printf("\n");
  }
  root = deleteNode(root, 18); 
  inOrder(root); 
  printf("\n");
  root = deleteNode(root, 30); inOrder(root); printf("\n");
  root = deleteNode(root, 26); inOrder(root); printf("\n");
  return 0;
}