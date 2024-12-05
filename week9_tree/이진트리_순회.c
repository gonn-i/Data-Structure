// 일반 이진트리 
#include <stdio.h>
#include <stdlib.h>

typedef char Telement;

typedef struct TreeNode {
  Telement data;
  struct  TreeNode* left;
  struct  TreeNode* right;  
} TreeNode;

TreeNode* makeNode (Telement data, TreeNode* left, TreeNode* right) {
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
  node -> data = data;
  node -> left = left;
  node -> right = right; 

  return node;
}
// 전위순회 VLR
void preOrder (TreeNode* root) {
  if(root) {
    printf("[%c] => ", root -> data);
    preOrder(root -> left);
    preOrder(root -> right);
  }
}

// 중위순회 LVR
void inOrder (TreeNode* root) {
  if(root) {
    inOrder(root -> left);
    printf("[%c] => ", root -> data);
    inOrder(root -> right);
  }
}

// 후위순회 LRV
void postOrder (TreeNode* root) {
  if(root) {
    postOrder(root -> left);
    postOrder(root -> right);
    printf("[%c] => ", root -> data); 
  }
}

int nodeCount (TreeNode* root) { // 루트가 전달되는건 트리 자체가 오는거라는거랑 같음
  if (!root) { //root == NULL  // 노드가 없는 경우, 0 반환
      return 0;
  } else {
    return 1 + nodeCount(root -> left) + nodeCount(root -> right);  // 현재 노드 + 왼쪽 + 오른쪽
  }
}

int isExternal (TreeNode* root) {  // 단말노드 여부 판별 (자식 노드 있는지 확인)
  return (root -> left == NULL && root -> right == NULL);
}

int leafCount (TreeNode* root) { // 자손 갯수

  if(!root) return 0; // 트리가 아무것도 없으면 0
  if(isExternal(root)) return 1; // 단말 노드이면 1 
  return leafCount(root -> left) + leafCount(root -> right); // 왼쪽 + 오른쪽 

}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int height(TreeNode* root) { // 트리 높이
  if (!root) return 0;
  else return 1 + MAX(height(root->left), height(root->right));  // 현재 노드 + 더 높은 서브트리
  
}

void treeReverse (TreeNode* root) { // 좌우 대칭 
  if(root){
    TreeNode* temp = root -> left;  // 왼쪽과 오른쪽 서브트리를 교환 (temp 를 두고)
    root -> left = root -> right;
    root -> right = temp;

    treeReverse(root -> left); // 왼쪽 작은 트리들도 똑같이 바꿔줌 
    treeReverse(root -> right); // 오른쪽도 마찬가지 
  }
}

// 특정 노드의 레벨을 구하는 함수
int getLevel(TreeNode* root, Telement target, int level) {
  if (!root) return 0; // 노드가 암것도 없을때

  if (root->data == target) return level; // 현재 노드가 타겟 노드면 현재 레벨 반환

  int leftLevel = getLevel(root->left, target, level + 1);   // 왼쪽 서브트리에서 타겟 노드 검색
  if (leftLevel != 0) return leftLevel; // 왼쪽에서 찾았다면 레벨 반환

  return getLevel(root->right, target, level + 1);  // 오른쪽 서브트리에서 타겟 노드 검색
}

int main () {
  // 노드는 아래에서부터 만들기 
  TreeNode* N4 = makeNode('D', NULL, NULL );
  TreeNode* N5 = makeNode('E', NULL , NULL);
  TreeNode* N6 = makeNode('F', NULL , NULL);
  TreeNode* N2 = makeNode('B', N4 , N5 );
  TreeNode* N3 = makeNode('C', N6 , NULL );
  TreeNode* N1 = makeNode('A', N2 , N3);

  preOrder(N1);  printf("\b\b\b   "); printf("\n"); // 전위순회 VLR
  inOrder(N1);   printf("\b\b\b   "); printf("\n"); // 중위순회 LVR
  postOrder(N1);   printf("\b\b\b   "); printf("\n"); // 후위순회 LRV

  printf("\n");
  printf("Node count : %d\n", nodeCount(N1)); 
  printf("Leaf count : %d\n", leafCount(N1)); //자식 노드가 없는 노드
  printf("isExternal : %d\n",  isExternal(N6)); //특정 노드가 리프 노드인지 여부를 판별
  printf("Height: %d\n", height(N1));

  treeReverse(N1); inOrder(N1);   printf("\b\b\b   "); printf("\n"); // 트리 좌우대칭 시키기
  return 0;
}