#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef int element;


typedef struct TreeNode {
    element key;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;


TreeNode* makeNode(element key){
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;

}

int height(TreeNode* root) {

    if(!root) return 0;

    else return 1 + MAX(height(root->left), height(root->right));    
} 

int getBalance(TreeNode *root)
{
    if(root == NULL)
        return 0;
    return height(root->left) - height(root->right);     // 왼쪽과 오른쪽의 높이차

}

TreeNode* rotateLeft (TreeNode* p){
    TreeNode* c = p-> right; // p는 현재 노드, c는 p의 오른쪽 자식 
    p -> right = c -> left; // c가 젤 위로 가야하니, p의 오른쪽에 c의 왼쪽 자식 주기 
    c -> left = p; // c가 최고니까, p가 자식이 됨

    return c;
}

TreeNode* rotateRight (TreeNode* p){
    TreeNode* c = p-> left; // 마찬가지로 p는 현재노드, c는 p의 왼쪽 자식
    p -> left = c -> right; // p가 내려로 내려갈거라, 원래 왼쪽에 c가 있었지만 이제는 c의 오른쪽 자식 줌
    c -> right = p;

    return c;
}

TreeNode* insertNode(TreeNode* root, element key)

{
    if(root == NULL)
        return makeNode(key);

    if(key < root->key) 
        root->left = insertNode(root->left, key); // 여기에서 바로 삽입하는게 아니라 재귀로 root == NULL 이 될때까지 내려가서 젤 끝에

    else if(key > root->key)
        root->right = insertNode(root->right, key); 

    int balance = getBalance(root); // 넣고 나서 밸런스가 맞는지 확인 

    if(balance < -1 && key > root -> right -> key){ // RR type : 오른쪽 서브트리에서 균형 깨짐 -> root 를 바꿀 수 있게 회전시캬주기 
        return rotateLeft(root);
    } 
    if(balance > 1 && key < root -> left -> key){ // LL type 왼쪽 서브트리에서 균형 깨짐 -> root 를 바꿀 수 있게 회전시캬주기 
        return rotateRight (root);
    }

    if( balance >1 && key > root -> left -> key) { // LR 타입
        root -> left = rotateLeft(root-> left); // 더 아래 서브 트리 먼저 반전시키고
        return rotateRight(root); // 오른쪽 반전 
    }

    if( balance < -1 && key < root -> right -> key) { // RL 타입
        root -> right = rotateRight(root-> right); // 더 아래 서브트리 먼저 오른쪽 반전
        return rotateLeft(root);  // 그 다음 왼쪽 반전
    }

    return root;    
}


void preOrder(TreeNode *root) {
    if(root){
        printf("[");
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
        printf("]");

    }
}


void display(TreeNode *root, int key){
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

