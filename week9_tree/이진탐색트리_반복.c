#include <stdio.h>
#include <stdlib.h>

typedef int element;

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
  while (root != NULL && key != root->key) {
    if (key < root->key) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return root;
}

TreeNode* insertNode(TreeNode* root, element key) {
  TreeNode* y = NULL;
  TreeNode* x = root;
  TreeNode* z = makeNode(key);

  while (x != NULL) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == NULL) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
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

TreeNode* minNode(TreeNode* root) {
  TreeNode* current = root;
  while (current && current->left != NULL) {
    current = current->left;
  }
  return current;
}

TreeNode* successor(TreeNode* root) {  // 계승자 찾기 (오른쪽 서브트리의 가장 왼쪽 노드)
  TreeNode* p = root;
  while (p->left != NULL) {
    return minNode(root);
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
    if (root->left == NULL) {  // 자식이 없거나 오른쪽 자식만 있음
      TreeNode* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {  // 왼쪽 자식만 있음
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
