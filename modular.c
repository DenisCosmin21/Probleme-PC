#include <stdio.h>

void euclid(long long A, long long N, int *d, long long *x, long long *y)
{
  if(N == 0){
    *d = A;
    *x = 1;
    *y = 0;
  }
  else{
    long long x0, y0;
    euclid(N, A % N, d, &x0, &y0);
    *x = y0;
    *y = x0 - (A / N) * y0;
  }
}

int main(void)
{
  FILE *input = fopen("inversmodular.in", "r");

  FILE *output = fopen("inversmodular.out", "w");
  
  long long A, N, x, y;
  
  int d = 1;
  
  fscanf(input, "%lld", &A);
  fscanf(input, "%lld", &N);
  euclid(A, N, &d, &x, &y);
  while(x < 0){
    x += N;
  }
  
  fprintf(output, "%lld", x);

  fclose(input);
  fclose(output);
  
  return 0;
}
