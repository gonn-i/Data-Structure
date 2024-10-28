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

void preOrder (TreeNode* root) {
  if(root) {
    printf("[%c] => ", root -> data);
    preOrder(root -> left);
    preOrder(root -> right);
  }
}

void inOrder (TreeNode* root) {
  if(root) {
    inOrder(root -> left);
    printf("[%c] => ", root -> data);
    inOrder(root -> right);
  }
}

void postOrder (TreeNode* root) {
  if(root) {
    postOrder(root -> left);
    postOrder(root -> right);
    printf("[%c] => ", root -> data); 
  }
}

int nodeCount (TreeNode* root) { // 루트가 전달되는건 트리 자체가 오는거라는거랑 같음
  if (!root) { //root == NULL
      return 0;
  } else {
    return 1 + nodeCount(root -> left) + nodeCount(root -> right);
  }
}

int isExternal (TreeNode* root) {  // 단말노드 (마지막 레벨에 오는 친구)
  return (root -> left == NULL && root -> right == NULL);
}

int leafCount (TreeNode* root) {
  if(!root) {
    return 0;
  } else {
    if(isExternal(root)){
      return 1;
    } else {
      return leafCount(root -> left) + leafCount(root -> right);
    }
  }
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int height(TreeNode* root) {
  if (!root) {
    return 0;
  } else {
    return 1 + MAX(height(root->left), height(root->right));
  }
}

void treeReverse (TreeNode* root) { // 좌우 대칭 
  if(root){
    TreeNode* temp = root -> left;
    root -> left = root -> right;
    root -> right = temp;

    treeReverse(root -> left);
    treeReverse(root -> right);
  }
}

int main () {
  // 노드는 아래에서부터 만들기 
  TreeNode* N4 = makeNode('D', NULL,NULL );
  TreeNode* N5 = makeNode('E',NULL , NULL);
  TreeNode* N6 = makeNode('F',NULL , NULL);
  TreeNode* N2 = makeNode('B',N4 , N5 );
  TreeNode* N3 = makeNode('C',N6 , NULL );
  TreeNode* N1 = makeNode('A',N2 , N3);

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