#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode
{
  element data;
  struct TreeNode* left;
  struct TreeNode* right;
}TreeNode;


TreeNode* makeNode (element key){
  TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));
  node -> data = key;
  node -> right = NULL;
  node -> left = NULL;
  return node;
}

TreeNode* insertNode (TreeNode* root, element key){
  if(root == NULL) return  makeNode(key);
  if(key < root -> data ) root-> left =  insertNode(root->left, key);
  if(key > root -> data ) root -> right =  insertNode(root->right, key);

  return root;
}

void inOrder(TreeNode* root) {
  if(root){
    inOrder(root -> left);
    printf(" [%d] =>", root -> data);
    inOrder(root -> right);
  }
}
// 현재 노드보다 작은 값 중 가장 작은 값을 가지는 노드
TreeNode* successor (TreeNode* root){
  while( root -> left != NULL ){
      root = root -> left;
  }
  return root;
}

TreeNode* deleteNode (TreeNode* root , element target){
  if(!root) return NULL;
  if(target < root -> data) root -> left  = deleteNode(root -> left, target); // 반환값 주워다가 연결 
  else if(target > root -> data) root -> right = deleteNode(root -> right, target);  // 반환값 주워다가 연결 
  else {
    if(root -> left == NULL) {
      TreeNode* temp = root -> right;
      free(root);
      return temp;
    }
    else if (root -> right == NULL){
      TreeNode* temp = root -> left;
      free(root);
      return temp;
    } 
    else {
      TreeNode* temp = successor(root -> right);
      root -> data = temp -> data; // 대신 연결
      root -> right = deleteNode(root -> right , temp -> data); // 그 계승자 데이터 삭제한걸로 오른쪽을 바꿔주기
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
    printf("\b\b\b   ");
    printf("\n");
  }
  printf("==============================\n");
  root = deleteNode(root, 18); 
  inOrder(root); 
  printf("\b\b\b   ");
  printf("\n");

  root = deleteNode(root, 30); inOrder(root);   printf("\b\b\b   "); printf("\n");
  root = deleteNode(root, 26); inOrder(root);    printf("\b\b\b   ");printf("\n");
  return 0;
}