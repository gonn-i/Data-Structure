#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 13

typedef struct HashType {
	int key;
	struct HashType* next ;
} HashType;

void init(HashType* HT) {
	for (int i = 0; i < M; i++){
		HT[i].key = 0;
		HT[i].next = NULL; // 헤더의 역할
	}
}

int hashFn(int key) {
    return key % M;
} 

void insertItem(HashType* HT, int key) {
	int b = hashFn(key);
	HashType* node = (HashType*)malloc(sizeof(HashType));
	node->key = key;
	node->next = HT[b].next;  // 원래 기준 HT[key]가 손잡고 있던 친구 넘겨주기
	HT[b].next = node; // if key 충돌이 생겨도 앞에 끼워주기
}

int findItem(HashType* HT, int key) {
	int b = hashFn(key);
	int count = 0;
	HashType* p;
	for (p = HT[b].next; p != NULL; p = p->next)
		if (p->key == key)
			count++;
	return count; // 몇번쨰에서 탐색되었는지
}

int deleteItem(HashType* HT, int key) {
	int b = hashFn(key);
	int count = 0;
	HashType* p = &HT[b]; // 기준이 되는 버킷 
	HashType* q; 

	while (p->next) {
		if (p->next->key == key){
			count++;
			q = p->next; // q 는 삭제할 친구
			p->next = q->next; // 앞에 있는 친구(P) 에게, 삭제할 노드의 뒷 친구 연결 
			free(q);
		}
		else
			p = p->next;
	}
	return count;
}

void printHash(HashType* HT) {
	HashType* p;
	for (int i = 0; i < M; i++){ // 버킷 전체를 돌면서 
		printf("HT[%02d] : ", i);
		for (p = HT[i].next; p != NULL; p = p->next)
			printf("[%d] ", p->key);
		printf("\n");
	}
}

int main() {
	HashType HT[M];
	int key;
	init(HT);
	
	srand(time(NULL));
	
	for (int i = 0; i < 20; i++)
		insertItem(HT, rand() % 90 + 10);
	printHash(HT);
	
	printf("\nInput search key : ");
	scanf("%d", &key);
	printf("There are %d %d.\n", findItem(HT, key), key);
	
	printf("\nInput delete key : ");
	scanf("%d", &key);
	printf("%d %d deleted.\n\n", deleteItem(HT, key), key);
	printHash(HT);
}




