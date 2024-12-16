#include <stdio.h>
#include <stdlib.h>

#define MAX(x,y) (((x>y)? (x): (y)))

typedef struct TreeNode {
  int key;
  struct  TreeNode * right;
  struct  TreeNode * left;
}TreeNode;

TreeNode * makeNode (int key){
  TreeNode * root = (TreeNode *)malloc(sizeof(TreeNode));
  root->key = key;
  root->left = NULL;
  root->right = NULL;

  return root;
}

int height (TreeNode * root){
  if(root == NULL) return 0;
  else return 1 + MAX( height(root -> left), height(root -> right));
}

int getBalance (TreeNode * root){
  if(root == NULL) return 0;
  return height(root -> left) - height(root -> right);
}

TreeNode * rotateRight (TreeNode * root){
  TreeNode * c = root -> left;
  root -> left = c -> right;
  c -> right= root;

  return c;
}

TreeNode * rotateLeft (TreeNode * root){
  TreeNode * c = root -> right;
  root -> right= c -> left;
  c -> left = root;

  return c;
}

TreeNode * insertNode (TreeNode * root, int key){
  if(root == NULL) return makeNode(key);

  if(key < root-> key ) root -> left = insertNode(root->left, key);
  else if(key > root-> key ) root -> right = insertNode(root-> right, key);

  int balance = getBalance(root);

  if( balance > 1 && key < root-> left ->key){ // LL
    return rotateRight(root);
  }

  if( balance < -1 && key > root-> right->key){ // RR
    return rotateLeft(root);
  }

  if( balance > 1 && key > root->left->key){ // LR
    root -> left  = rotateLeft(root -> left);
    return rotateRight(root);
  }

  if( balance < -1 && key < root-> right ->key){ // RL
    root -> right  = rotateRight(root -> right);
    return rotateLeft(root);
  }

  return root;  
}

void preOrder (TreeNode * root){
  if(root){
    printf("[");
    printf(" %d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
    printf("]");
  }
}

void display (TreeNode * root, int key) {
    printf("[Insert %d] : ", key);
    preOrder(root);
    printf("\n");

}

int main() {
    TreeNode *root = NULL;
    int data[] = {7, 8, 9, 2, 1, 5, 3, 6, 4};
    for(int i = 0; i  < 9; i++) {
        root = insertNode(root, data[i]);
        display(root, data[i]);
    }
    printf("\n");
    printf("Balance Factor : %d\n", getBalance(root));

    return 0;

}
