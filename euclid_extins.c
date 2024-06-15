#include <stdio.h>

void euclid(long long a, long long b, long long *d, long long *x, long long *y)
{
  if(b == 0){
    *d = a;
    *x = 1;
    *y = 0;
  }
  else{
    long long x0, y0;
    euclid(b, a % b, d, &x0, &y0);
    *x = y0;
    *y = x0 - (a / b) * y0;
  }
}

int main(void)
{
  FILE *input = fopen("euclid3.in", "r");

  FILE *output = fopen("euclid3.out", "w");

  long long a, b, c, x, y, T, d;

  fscanf(input, "%lld", &T);

  while(T--){
    fscanf(input, "%lld", &a);
    fscanf(input, "%lld", &b);
    fscanf(input, "%lld", &c);

    euclid(a, b, &d, &x, &y);

    if(c % d){//Dacxa divizorul comun nu se divide cu  c citit, care ar trebui sa fie divizorul comun nu exista solutie, deoarece algoritmul ne ofera divizorul comun
      x = 0;
      y = 0;
    }
    else{
      x *= c/d;
      y *= c/d;
    }
    
    fprintf(output, "%lld %lld\n", x, y);
  }

  fclose(input);
  fclose(output);
  
  return 0;
}



