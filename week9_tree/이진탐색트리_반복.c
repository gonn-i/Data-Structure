#include <stdio.h>
#include <stdlib.h>

typedef int element;

// 오른쪽 왼쪽 자식 + 부모 
typedef struct TreeNode {
  element key;
  struct TreeNode *right, *left, *parent;
} TreeNode;

TreeNode* makeNode(element key) {
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
  node->key = key;
  node->left = node->right = node->parent = NULL;
  return node;
}

TreeNode* searchNode(TreeNode* root, element key) {
  while (root != NULL && key != root->key) { // 아직 노드가 남아있고 && 키를 못찾으면 
    if (key < root -> key) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return root;
}

// 이진 탐색 트리에 노드 삽입  (반봅)
TreeNode* insertNode(TreeNode* root, element key) {
  TreeNode* x = root; // 현재 탐색 중인 노드
  TreeNode* y = NULL; // 삽입될 부모 노드를 추적하기 위한 포인터
  TreeNode* z = makeNode(key); // 삽입할 새로운 노드를 생성 (고정)

  while (x != NULL) { // 루트가 끝까지 갈떄까지 
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

void inOrder(TreeNode* root) {
  if (root) {
    inOrder(root->left);
    printf("[%d] ", root->key);
    inOrder(root->right);
  }
}

// 왼쪽 서브 트리의 가장 왼쪽
TreeNode* minNode(TreeNode* root) {
  if (root == NULL) return NULL;  // 트리가 비어있는 경우 NULL 반환
  TreeNode* current = root;   // 현재 탐색 중인 노드
  while (current && current->left != NULL) {  // 왼쪽 자식이 존재하는 한 반복
    current = current->left;
  }
  return current;
}


// 계승자를 찾는 함수
TreeNode* successor(TreeNode* root) {
  // 오른쪽 자식이 있으면, 오른쪽 서브트리의 가장 왼쪽 노드를 찾는다.
  if (root->right != NULL) {
    return minNode(root->right);
  }
  // 오른쪽 자식이 없으면, 조상의 왼쪽 자식인 첫 번째 조상을 찾는다.
  TreeNode* p = root->parent;
  while (p != NULL && root == p->right) {
    root = p;
    p = p->parent;
  }
  return p;
}

TreeNode* deleteNode(TreeNode* root, element key) {
  if (root == NULL) return NULL;

  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  } else {  // 삭제할 노드 찾음
    if (root->left == NULL) {  // 왼쪽 자식 없
      TreeNode* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {  // 오른쪽 자식 없
      TreeNode* temp = root->left;
      free(root);
      return temp;
    } else {  // 왼쪽과 오른쪽 자식이 둘 다 있음
      TreeNode* temp = successor(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }
  return root;
}

int main() {
  TreeNode* root = NULL;
  element keys[] = {35, 18, 7, 26, 12, 3, 68, 22, 30, 99};

  for (int i = 0; i < 10; i++) {
    root = insertNode(root, keys[i]);
    printf("In-order after inserting %d: ", keys[i]);
    inOrder(root);
    printf("\n");
  }

  printf("Successor : %d\n", successor(searchNode(root, 26)) -> key);
  // (searchNode(root, 29) != NULL) ? printf("Found\n") : printf("Not Found\n");

  // root == deleteNode(root, 18); inOrder(root); printf("\n");
  // root = deleteNode(root, 30); inOrder(root); printf("\n");
  // root = deleteNode(root, 26); inOrder(root); printf("\n");


  return 0;
}
