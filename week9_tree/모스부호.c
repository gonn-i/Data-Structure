#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef char Telement;

typedef struct {
    char alpha;
    char morseCode[6]; // 최대 5개 문자 + null terminator
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

TreeNode* makeMorseTree() {
    TreeNode* root = makeNode('\0', NULL, NULL); // 데이터 초기화
    for (int i = 0; i < 26; i++) {
        TreeNode* p = root;
        int n = strlen(table[i].morseCode);
        for (int j = 0; j < n; j++) {
            char c = table[i].morseCode[j];

            if (c == '.') {
                if (p->left == NULL) p->left = makeNode('\0', NULL, NULL);
                p = p->left;
            } else { // '-'일 경우
                if (p->right == NULL) p->right = makeNode('\0', NULL, NULL);
                p = p->right;
            }
        }
        p->data = table[i].alpha; // 노드에 문자 저장
    }
    return root;
}

void preOrder(TreeNode* root) {
    if (root) {
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
