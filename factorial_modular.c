#include <stdio.h>

void factorial(int *factorials, int modulus)
{
  for(ssize_t i = 1;i < modulus;i++){
    factorials[i] = factorials[i - 1] * i % modulus;
  }

  for(ssize_t i = 0;i < modulus;i++){
    printf("%d ", factorials[i]);
  }
  printf("\n");
}

int main(void)
{
  int modulus, a, b;
  scanf("%d", &modulus);
  scanf("%d", &a);
  scanf("%d", &b);

  int factorials[modulus];
  factorials[0] = 1;
  
  factorial(factorials, modulus);

  int fact_a, fact_b;
  int counta, countb;
  fact_a = a % modulus;
  fact_b = b % modulus;

  printf("%d %d\n", factorials[fact_a], factorials[fact_b]);
  return 0;
}
