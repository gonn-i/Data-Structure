#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct TreeNode {
  element key;
  struct TreeNode * left;
  struct TreeNode * right;
};

TreeNode * makeNode (element data, TreeNode* left, TreeNode * right) {
  TreeNode * node = (TreeNode *)malloc(sizeof(TreeNode));
  node->key = data;
  node->left = left;
  node->right = right;
  return node;
}

void preOrder (TreeNode * node ) {
  if(node){
    printf("  [%c] =>", node->key);
    preOrder(node->left);
    preOrder(node->right);
  }
}
void inOrder (TreeNode * node ) {
  if(node){
    inOrder(node->left);
    printf("  [%c] =>", node->key);
    inOrder(node->right);
  }
}
void postOrder (TreeNode * node ) {
  if(node){
    postOrder(node->left);
    postOrder(node->right);
    printf("  [%c] =>", node->key);
  }
}


int nodeCount (TreeNode * node) {
  if(node == NULL) return 0;
  else return 1+ nodeCount(node-> left) + nodeCount(node -> right);
}

int leafCount (TreeNode * node){
  if(node == NULL) return 0;
  else return nodeCount(node-> left) + nodeCount(node -> right);
}

int isExternal (TreeNode * node){
  return !(node-> left) && !(node->right )? -1: 0;
}

void treeReverse (TreeNode * node){
   if(node){
    TreeNode * t = node -> left;
    node -> left = node -> right;
    node -> right = t;


  treeReverse( node -> left);
  treeReverse( node -> right);
   }

}


int main () {
  TreeNode* N4 = makeNode('D', NULL, NULL );
  TreeNode* N5 = makeNode('E', NULL , NULL);
  TreeNode* N6 = makeNode('F', NULL , NULL);
  TreeNode* N2 = makeNode('B', N4 , N5 );
  TreeNode* N3 = makeNode('C', N6 , NULL );
  TreeNode* N1 = makeNode('A', N2 , N3);

  preOrder(N1);  printf("\b\b\b   "); printf("\n"); // 전위순회 VLR
  inOrder(N1);   printf("\b\b\b   "); printf("\n"); // 중위순회 LVR
  postOrder(N1);   printf("\b\b\b   "); printf("\n"); // 후위순회 LRV

  printf("Node count : %d\n", nodeCount(N1)); 
  printf("leaf count : %d\n", leafCount(N1));
  printf("isExternal : %d\n",  isExternal(N1));

  treeReverse(N1); inOrder(N1);   printf("\b\b\b   "); printf("\n"); // 트리 좌우대칭 시키기
  return 0;
}