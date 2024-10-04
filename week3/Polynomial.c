// 미지수가 하나인 다항식 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define N 100 

typedef struct {
  int degree;
  int coef[N]; // 다항식 계수 (역순으로 저장)
} Poly;

void print (Poly p, char *str) {
  printf("%s", str);

  for(int i = p.degree; i >=0; i--){
    printf("%d x^%d + " , p.coef[i], i);
  };
  printf("%d\n", p.coef[0]);
}

Poly add (Poly a, Poly b){
  Poly c;
  c.degree = (a.degree > b.degree)? a.degree: b.degree; // 최고 차수 비교

  for(int i =0; i <=c.degree; i++){
    c.coef[i] = ((i <=a.degree)? a.coef[i] : 0) 
                + ((i <=  b.degree) ? b.coef[i] : 0);
  }
  return c;
}

int eval (Poly p, int x) {
  int result = p.coef[0];

  for(int i=1; i <= p.degree; i++){
    result += p.coef[i] * pow(x,i);
  }
  return result;
}

int main () {
  Poly a, b, c; // a+b = c

  scanf("%d %d", &a.degree, &b.degree);
  
  for(int i=0; i <=a.degree; i++){
    scanf("%d" , &a.coef[i]);
  }
  for(int i=0; i <=b.degree; i++){
    scanf("%d" , &b.coef[i]);

  }
  // 초기 다항식 출력 
  print(a, "A = ");
  print(b, "B = ");

  c = add(a,b); // 다항식 간의 합 수행
  print(c, " C = ");

  // 각 다항식의 결과값 연산
  printf("A(1) = %d\n", eval(a, 1));
  printf("B(2) = %d\n", eval(b, 2));
  return 0;
}
