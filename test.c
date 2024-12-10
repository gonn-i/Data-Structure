#include <stdio.h>
#include <stdlib.h>

typedef int element;

// 오른쪽 왼쪽 자식 + 부모 
typedef struct TreeNode {
  element key;
  struct TreeNode *right, *left, *parent;
} TreeNode;

TreeNode* makeNode ( element data){
  TreeNode* node = (TreeNode* )malloc(sizeof(TreeNode));
  node -> key = data;
  node -> left = NULL;
  node -> parent = NULL;
  node -> right = NULL;
  return node;
}

// 이진 탐색 트리에 노드 삽입  (반봅)
TreeNode* insertNode(TreeNode* root, element key) {
  TreeNode* x = root; // 현재 탐색 중인 노드
  TreeNode* y = NULL; // 삽입될 부모 노드를 추적하기 위한 포인터
  TreeNode* z = makeNode(key); // 삽입할 새로운 노드를 생성 (고정)

  while (x != NULL) { // 루트가 끝까지 갈때까지 
    y = x; // y는 x의 부모
    if (z -> key < x -> key) { 
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z -> parent = y; // 부모를 연결시켜주기
  if (y == NULL) { // 부모라고할 노드 없는 경우 (트리 빈 경우) z가 루트
    root = z;
  } else if (z -> key < y -> key) {
    y->left = z; // 부모보다 작으면 왼쪽에 z 연결 
  } else {
    y->right = z; // 부모보다 크면 오른쪽에 연결
  }

  return root;
}

void Inorder (TreeNode* root){
  if(root){
    Inorder(root -> left);
    printf("[%d] =>", root -> key);
    Inorder(root -> right);
  }
}


int main() {
  TreeNode* root = NULL;
  element keys[] = {35, 18, 7, 26, 12, 3, 68, 22, 30, 99};

  for (int i = 0; i < 10; i++) {
    root = insertNode(root, keys[i]);
    printf("In-order after inserting %d: ", keys[i]);
    Inorder(root);
    printf("\b\b\b    ");
    printf("\n");
  }

  // printf("Successor : %d\n", successor(searchNode(root, 26)) -> key);
  // (searchNode(root, 29) != NULL) ? printf("Found\n") : printf("Not Found\n");

  // root == deleteNode(root, 18); inOrder(root); printf("\n");
  // root = deleteNode(root, 30); inOrder(root); printf("\n");
  // root = deleteNode(root, 26); inOrder(root); printf("\n");


  return 0;
}
