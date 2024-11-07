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

TreeNode* insertNode(TreeNode* root, element key) {
  TreeNode* z = makeNode(key);
  TreeNode* y = NULL;
  TreeNode* x = root;

  while (x != NULL) {
    y = x;
    if (key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == NULL) {
    // 트리가 비어있다면 새로운 노드가 루트가 된다.
    root = z;
  } else if (key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  return root;
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

  // 삽입
  for (int i = 0; i < 10; i++) {
    root = insertNode(root, keys[i]);
    printf("In-order after inserting %d: ", keys[i]);
    inOrder(root);
    printf("\n");
  }

  // 계승자 테스트
  TreeNode* node = searchNode(root, 26);
  if (node != NULL) {
    TreeNode* succ = successor(node);
    if (succ != NULL) {
      printf("Successor of %d: %d\n", node->key, succ->key);
    } else {
      printf("No successor for %d\n", node->key);
    }
  }

  // 삭제 테스트
  root = deleteNode(root, 18);
  printf("In-order after deleting 18: ");
  inOrder(root);
  printf("\n");

  root = deleteNode(root, 30);
  printf("In-order after deleting 30: ");
  inOrder(root);
  printf("\n");

  root = deleteNode(root, 26);
  printf("In-order after deleting 26: ");
  inOrder(root);
  printf("\n");

  return 0;
}
