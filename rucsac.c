#include <stdio.h>

long long max(long long a, long long b)
{
  return a > b ? a : b;
}

int main(void)
{
  FILE *input = fopen("rucsac.in", "r");

  FILE *output = fopen("rucsac.out", "w");

  size_t n, G;

  fscanf(input, "%ld", &n);
  fscanf(input, "%ld", &G);
  
  long long int price[10000], weight[10000];

  long long int optim[10000];
  int sol = 0;

  optim[0] = 0;

  for(size_t i = 0;i < n;i++){
    fscanf(input, "%lld", &weight[i]);
    fscanf(input, "%lld", &price[i]);
  }

  for(size_t i = 0;i < n;i++){
    for(int j = G - weight[i];j >= 0; --j){
      optim[j + weight[i]] = max(optim[j + weight[i]], optim[j] + price[i]);
      sol = max(sol, optim[j + weight[i]]);
    }
  }

  fprintf(output, "%d", sol);

  fclose(input);

  fclose(output);

  return 0;
}
