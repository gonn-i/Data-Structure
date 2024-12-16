#include <stdio.h>
#include <stdlib.h>

# define M 13

typedef struct Buket {
  int key;
  int probeCount;
}Buket ;


typedef struct HashTable {
  Buket B [M];
}HashTable;

int hashFn (int key) {
  return key % M;
}

int hashFn2 (int key) {
  return 11 - (key - M);
}

void init (HashTable* HT) {
  for(int i =0; i < M; i++){
    HT -> B[i].key = 0;
    HT -> B[i].probeCount = 0;
  }
}

int isEmpty(HashTable* HT, int key){
  return HT->B[key].key == 0;
}

void insertItem (HashTable* HT, int key){
  int k = hashFn(key);
  int count = 0;

  for(int i =0; i < M; i++){
     k = (k  + i ) % M;
     count++;

     if(isEmpty(HT, k)){
        HT->B[k].key = key;
        HT->B[k].probeCount = count;
        return;
     }
  }
}


int searchItem (HashTable* HT, int key){
  int k = hashFn(key);

  for(int i =0; i < M; i++){
     k = (k  + i ) % M;

     if(isEmpty(HT, k)){
        return -1;
     } else if (HT->B[k].key == key){
        return 0;
     }
  }
  return -1;
}

int deleteItem (HashTable* HT, int key){
  int k = hashFn(key);

  for(int i =0; i < M; i++){
     k = (k  + i ) % M;

     if(isEmpty(HT, k)){
        return -1;
     } else if (HT->B[k].key == key){
        HT->B[k].key = -1;
        HT->B[k].probeCount = 0;
        return 0;
     }
  }
  return -1;
}

void print(HashTable * HT){
  for(int i =0; i < M; i++){
    printf(" %2d ", HT->B[i].key);
  }
  printf("\n");
}

void printHash(HashTable * HT){
  printf("Bucket   key    probe\n");
  for(int i =0; i < M; i++){
    printf("h[%2d] :  %2d   %2d\n", i , HT->B[i].key, HT->B[i].probeCount);
  }
}

int main () {
  HashTable HT;
  init (&HT);

  int data[] = {25,13,16,15,7,28, 31,20,1,28};

  printf(" h(key)       0   1   2   3   4  5  6  7  8  9  10 11 12\n" );
  printf(" ======      ===================================\n");

  for(int i =0; i < 10; i++){
    printf("h(%2d) : %2d|", data[i], hashFn(data[i]));
    insertItem(&HT, data[i]);
    print(&HT);
  }

  printf("\n");
  printHash(&HT);


  int key;
  printf("\n input SearchKey : ");
  scanf("%d", &key);
  if(searchItem(&HT, key) != -1){
    printf("%d 존재! \n", key);
  }else {
        printf("존재하지 않음!");
  }


  printf("\n input DeleteKey : ");
  scanf("%d", &key);
  if(deleteItem(&HT, key) != -1){
    printf("%d 삭제 \n", key);
  }else {
        printf("삭제할 아이템이 없음!\n");
  }

  printHash(&HT);

  return 0;
}