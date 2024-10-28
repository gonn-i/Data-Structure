#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct DListNode {
    Element data;
    struct DListNode* prev;
    struct DListNode* next;
}DListNode;

DListNode* makeNode (Element e) {
    DListNode* node = (DListNode*) malloc(sizeof(DListNode));
    node -> data = e;
    node -> prev = node -> next = NULL;
    return node;
}

void init (DListNode* H, DListNode*T ){
    H -> next = T; // 헤드 -> 테일 
    T  -> prev = H; // 테일 -> 헤드
}


void insert (DListNode* H, int pos, Element e) {
    // 유효하지 않는 pos 값 넣기 !! 이거 무조건 시험에 나올듯
    DListNode* node = makeNode(e);
    DListNode* p = H; // 첫번째 노드 가져오기

    for(int i =1; i < pos; i++){
        p = p-> next; // 삽입할 위치의 앞 노드 
    }
    node -> prev = p; // 앞노드와 연결 
    node -> next = p -> next; // 뒷노드와 연결 
    p-> next -> prev = node; // 삽입 뒤에 있는 노드를 삽입 노드에 연결 
    p -> next = node; // 앞 노드를 뒤와 연결
}

Element delete (DListNode* H, int pos) {
    DListNode* p = H; // 젤 처음 노드 
    for(int i =1; i <= pos; i++){
        p = p -> next; // 삭제할 노드 
    }
    Element e = p -> data; 
    p-> prev -> next = p -> next; 
    p -> next -> prev = p -> prev; //오른쪽 친구의 왼쪽 손에, 내 왼쪽 친구를 연결
    free(p);
    return e;
}


void print(DListNode* H, DListNode* T){
    for( DListNode* p = H -> next; p !=T; p=p -> next){ // /NULL 이 아니라 T 만날떄까지!!!
    printf("[%c] => ", p -> data);
    }
    printf("\b\b\b    \n");
}



int main(){
    DListNode* H = makeNode(0); // 선행 포인터 그냥 0을 넣어줌 
    DListNode* T = makeNode(0); // 후행 포인터 그냥 0을 넣어줌 
    init(H,T);

    insert(H,1, 'A'); print(H,T);
    insert(H,2, 'B'); print(H,T);
    insert(H,3, 'C'); print(H,T);
    insert(H,1, 'D'); print(H,T); getchar();

    printf("Delete [%c] : ", delete(H,1)); print(H, T);
    printf("Delete [%c] : ", delete(H,2)); print(H, T);


    return 0;
}
