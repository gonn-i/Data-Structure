#include <stdio.h>
#include <stdlib.h>

#define M 13 // 버킷개수

typedef struct {
  int key; // 슬롯을 하나만 둬서 충돌 잘나게 임의 설정
  int probeCount; // 탐색 횟수 기록용 
}Bucket;

typedef struct  
{
  Bucket B[M];
}HashTable;

void init (HashTable *HT){
  for(int i = 0; i < M; i++){
    HT -> B[i].key = 0;
    HT -> B[i].probeCount = 0; // 구조체 형태 기억할것 HT -> B[i].어쩌구 🔥
  }
}

int isEmpty (HashTable *HT, int b) { // 특정 버킷이 비었는지 판별 0이면 빈거!!
  return HT -> B[b].key == 0; 
}

int hashFn (int key) { // M 의 나머지 값으로 key 모듈레이션 
  return key % M;
}

int hashFn2 (int key){
  return 11 - (key %  11);  // M보다 작은 소수중 가장 큰 소수로 key 모듈레이션
}

void insertItem(HashTable *HT, int key){
  int hashVal = hashFn(key); // 해시 함수를 통해, 삽입해 넣을 인덱스 뽑아내기 
  int count = 0;

  for(int i =0; i < M; i++){
    count++;
   int b = (hashVal + i )%  M; // 선형 조사법 (다음 슬롯을 순차적으로 탐색 + i )
    // int b = (hashVal + i * i )% M ; // 이차조사법 ( 다음 슬롯을 i * i 로 탐색)
    // int b = (hashVal + i * hashFn2(key)) % M;  // 이중 해싱법 

    if(isEmpty(HT,b)){ // 만약 빈자리라면 넣고 , or not 반복문 계속 타기 
      HT -> B[b].key = key;
      HT -> B[b].probeCount = count;
      return;
    }
  }
}

int findItem(HashTable *HT, int key){
  int hashVal = hashFn(key);

  for(int i =0; i < M; i++){
    int b = (hashVal + i )%  M ; // 선형 조사법
    //int b = (hashVal + i * i )% 13 ; // 이차조사법
    // int b = (hashVal + i * hashFn2(key)) % M;  // 이중 해싱법


    if(isEmpty(HT,b)){ // 탐색했는데 비었다? 그러면 없는거임 
      return -1;
    }
    else if (HT -> B[b].key == key) {
      return b;
    }
  }
  return -1 ; // 끝까지 돌았는데 찾는게 없는거 
}

int deleteItem(HashTable *HT, int key){
  int hashVal = hashFn(key);

  for(int i =0; i < M; i++){
   int b = (hashVal + i )%  M; // 선형 조사법
    //int b = (hashVal + i * i )% 13 ; // 이차조사법
    // int b = (hashVal + i * hashFn2(key)) % M;  // 이중 해싱법


    if(isEmpty(HT,b)){
      return -1;
    }
    else if (HT -> B[b].key == key) { // 삭제 == 초기화 시켜준다고 생각하셈
      HT -> B[b].key = -1;
      HT -> B[b].probeCount = 0;
      return key;
    }
  }
  return -1 ; // 꽉찼는데 찾는게 없는거 
}

void print (HashTable *HT) {
  for(int i =0; i < M; i++){
    printf(" %2d", HT -> B[i].key);
  }
  printf("\n");
}

void printHash (HashTable *HT) {
  printf("Bucket   Key   Probe\n ");
  printf("===================\n");
  for(int i=0; i < M; i++){
    printf("HT[%02d] : %2d   %d\n", i, HT-> B[i].key, HT -> B[i].probeCount);
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
  if(findItem(&HT, key) != -1){
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