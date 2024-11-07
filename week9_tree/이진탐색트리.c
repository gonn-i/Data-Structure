
// 순환문을 통한 이진탐색 트리
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
  element key;
  struct  TreeNode *right, * left;
} TreeNode;

TreeNode* makeNode (element key) {
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); 
  node -> key = key;
  node -> left = node -> right = NULL;
  return node;
}

TreeNode* insertNode (TreeNode* root, element key){
  if(root ==NULL){
    return makeNode(key);
  } 
  if(key < root -> key) {
    root -> left = insertNode(root -> left, key);
  } else if (key > root -> key){
    root -> right = insertNode(root -> right, key);
  } 
  return root;
} 

void inOrder (TreeNode* root) {
  if(root) {
    inOrder(root -> left);
    printf("[%d] ", root -> key);
    inOrder(root -> right);
  }
}

TreeNode*  successor(TreeNode* root){ // 계층자 찾기 (오른쪽 트리의 왼쪽 끝)
  TreeNode* p = root;
  while(p -> left != NULL){
    p = p -> left;
  }
  return p;
}

TreeNode* deleteNode (TreeNode* root, element key){
  if(root == NULL) return NULL;
    if(key < root -> key) {
    root -> left = deleteNode(root -> left, key);
  } else if (key > root -> key){
    root -> right = deleteNode(root -> right, key);
  }  else { // 삭제할 노드 찾음
    if(root -> left == NULL){ // case 1 자식이 암것도 없거나 left에 하나만 있는 경우
      TreeNode* temp = root -> right;
      free(root);
      return temp;
    } else if (root -> right == NULL){ // case 2 
      TreeNode* temp = root -> left;
      free(root); 
      return temp;
    } else {
      TreeNode* temp = successor(root -> right);
      root -> key = temp -> key;
      root -> right = deleteNode(root -> right, temp -> key);
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
  root == deleteNode(root, 18); inOrder(root); printf("\n");
  // root = deleteNode(root, 30); inOrder(root); printf("\n");
  // root = deleteNode(root, 26); inOrder(root); printf("\n");
  return 0;
}