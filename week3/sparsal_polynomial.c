#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
  int expo; // 항 지수 (n차)
  float coeff; // 항 계수
} Term;

typedef struct {
  int nTerms;
  Term term[MAX_TERMS]; // 지수 + 계수 저장 배열 
} SparsePoly;

// 두 SparsePoly의 덧셈 함수
SparsePoly add (SparsePoly a, SparsePoly b) {
  SparsePoly c;
  c.nTerms = 0;

  for(int i = 0, j = 0; i < a.nTerms || j < b.nTerms;) {
    if(i == a.nTerms || a.term[i].expo < b.term[j].expo) // a 항 모두 처리 || b항의 차수가 더 큰 경우
      c.term[c.nTerms++] = b.term[j++]; // b의 특정 항(차수 + 지수) c에 넣기 
    else if (j == b.nTerms || a.term[i].expo > b.term[j].expo) // vice versa
      c.term[c.nTerms++] = a.term[i++];
    else {  // 같은 차수인 경우 계수를 더해줌
      c.term[c.nTerms] = a.term[i++]; // 1) 차수 전달 + 계수도 
      c.term[c.nTerms++].coeff += b.term[j++].coeff;  //  b의 계수 더해줌 (차수는 이미 전달했기 떄문)
    }
  }
  return c;
}

// 다항식을 출력하는 함수
void printPoly(SparsePoly p) {
  for(int i = 0; i < p.nTerms; i++) {
    printf("(%.1f)x^%d", p.term[i].coeff, p.term[i].expo);
    if (i < p.nTerms - 1) printf(" + ");
  }
  printf("\n");
}

void main () {
  SparsePoly a = {2, {{100, 10.0}, {0, 6.0}}};  // 다항식 a: 10.0x^100 + 6.0
  SparsePoly b = {2, {{50, 1.1}, {3, 2.0}}};    // 다항식 b: 1.1x^50 + 2.0x^3
  SparsePoly c = add(a, b);                     // 다항식 덧셈 결과 c
  
  printf("a: ");
  printPoly(a);
  
  printf("b: ");
  printPoly(b);
  
  printf("a+b: ");
  printPoly(c);
}
