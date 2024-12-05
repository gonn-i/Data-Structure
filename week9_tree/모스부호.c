#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef char Telement;

typedef struct {
    char alpha;
    char morseCode[6]; // 모스 부호 최대 길이는 5, +1은 널 종료 문자
} Code;

Code table[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};

typedef struct TreeNode {
    Telement data;
    struct TreeNode* left;
    struct TreeNode* right;  
} TreeNode;

TreeNode* makeNode(Telement data, TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = left;
    node->right = right; 
    return node;
}

// 모스 부호 트리를 만드는 함수
TreeNode* makeMorseTree() {
    TreeNode* root = makeNode('\0', NULL, NULL); // 루트는 빈 노드로 시작
    for (int i = 0; i < 26; i++) {
        TreeNode* p = root;
        int n = strlen(table[i].morseCode);
        for (int j = 0; j < n; j++) {
            char c = table[i].morseCode[j];

            if (c == '.') { // '.'은 왼쪽으로 가는 경로
                if (p->left == NULL) p->left = makeNode('\0', NULL, NULL);
                p = p->left;
            } else if (c == '-') { // '-'는 오른쪽으로 가는 경로
                if (p->right == NULL) p->right = makeNode('\0', NULL, NULL);
                p = p->right;
            }
        }
        p->data = table[i].alpha; // 노드에 문자 저장
    }
    return root;
}

// 전위 순회 함수
void preOrder(TreeNode* root) {
    if (root) {
        // root->data가 유효한 값일 경우에만 출력
        if (root->data != '\0') { 
            printf("[%c] => ", root->data);
        }
        preOrder(root->left);
        preOrder(root->right);        
    }
}

int main() {
    TreeNode* morseTree = makeMorseTree();
    printf("Pre-order traversal of Morse code tree:\n");
    preOrder(morseTree);
    return 0;
}
