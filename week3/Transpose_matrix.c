// 전치행렬 
#include <stdio.h> 
# define ROWS 3 
# define COLS 3 

void transport_mat (int m[ROWS][COLS]){
  for(int i =0; i <ROWS; i++){
    for(int j =i+1; j <COLS; j++){ // [0,1] [0,2] [1,2] 만 돌면됨
      int temp = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = temp;
    } 
  }
}

void print_mat (int mat[ROWS][COLS]){
  for(int i =0; i <ROWS; i++){
    for(int j =0; j <COLS; j++){
      printf("%d ", mat[i][j]);
    } 
    printf("\n");
  }
}

int main(){
  int mat[ROWS][COLS] = {4,0,1,1,6,5,7,3,6};
  print_mat(mat);
  transport_mat(mat);
  printf("=============\n");
  print_mat(mat);
  return 0;
}