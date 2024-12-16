#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define M 13

typedef struct hashType {
  int key;
  struct hashType * next;
}hashType;

void init (hashType* HT){
  for(int i =0; i < M; i++){
    HT[i].key = 0;
    HT[i].next = NULL;
  }
}

int hashFn (int key){
  return key % M;
}

void insertHash (hashType * HT, int key){
  int hashVal = hashFn(key);
  hashType* node = (hashType*)malloc(sizeof(hashType));

  node->key = key;
  node->next = HT[hashVal].next;
  HT[hashVal].next = node;
}

void printHash (hashType* HT){
  hashType * node;
  for(int i =0; i < M;i ++){
      printf("HT[%2d] : ",i);
      for(node = HT[i].next; node != NULL; node = node->next){
        printf(" [%d] ", node -> key);
      }
      printf("\n");
  }
}

int deletehash (hashType* HT, int key){
  int hashVal = hashFn(key);

  hashType* p = &HT[hashVal];
  hashType* q;

  while( p -> next != NULL){
    q = p ->next; 
    if(q->key == key){
      p->next = q->next;
      free(q);
      return 0;
    } 
      p = p -> next;
  
  }
  return -1; // 없는 경우
}

int main (){
  hashType HT[M];
  init(HT);
  srand(time(NULL));
  int key;

  for(int i =0; i < 20; i++){
    int num = rand() % 100 + 1; 
    insertHash(HT, num);
  }
  printHash(HT);

  printf("삭제할  key : ");
  scanf("%d", &key);

  if(deletehash (HT,key) == -1){
    printf("존재하지 않는 키");
  } else {
    printf("삭제한 키 : %d", key);
  }

  printHash(HT);

  return 0;
}