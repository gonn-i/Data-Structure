// 희소행렬 
#include <stdio.h>


typedef struct {
  int row; 
  int col;
  int value;
} Elem;

void transport_mat (Elem m[], int len){
  for(int i =0; i< len; i++){
    int temp =  m[i].row;
    m[i].row = m[i].col;
    m[i].col = temp;
  }
}

void print_mat (Elem m[], int len) {
  for(int i =0; i< len; i++){
    printf("row: %d  col: %d  value: %d\n", m[i].col, m[i].row, m[i].value);
  }
}

int main () {
  Elem mat[5] = {{0,3,11}, {2,5,42}, {3,1,33}, {4,4,87}, {5,4,55}};
  print_mat(mat,5);
  transport_mat(mat, 5);
  printf("============\n");
  print_mat(mat,5);
  return 0;
}