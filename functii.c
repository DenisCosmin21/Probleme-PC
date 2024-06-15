#include <stdio.h>

long long max(long long a, long long b)
{
  return (a > b) ? a : b;
}

void factorial(long long P, long long *factorials)//vom calcula factorialul pana la valoarea P care este clasa de resturi pe care aplicam calculele pentru eficienta O(n) de a calcula toti factorialii modulari. Poate avea probleme de ocupare prea mare de memorie, dar stim ca P nu poate lua valori prea mari deci va functiona. Acest algoritm se va realiza o singura data deoarece clasa de resturi este aceeais pentru fiecare test
{
  for(size_t i = 1;i <= P;i++){
    factorials[i] = factorials[i - 1] * i % P;
  }
}

int get_fact_value(long long value, long long P, long long *factorials)
{
  return (value != 0 && value % P == 0) ? 0 : factorials[value % P];
}

void euclid(long long A, long long B,long long *d, long long *x, long long *y)
{
  if(B == 0){
    *x = 1;
    *y = 0;
    *d = A;
  }
  else{
    long long x0, y0;
    euclid(B, A%B, d, &x0, &y0);
    *x = y0;
    *y = x0 - (A / B) * y0;
  }
}

long long invert_fact(long long value, long long P)//Din formula stim ca in calcule modulare A/B = A * B^-1
{
  long long x, y;
  long long d = 0;
  euclid(value, P,&d, &x, &y);
 
    if(x <= 0){
      x  = P + x % P;
    }
    return x;
  
}

long long calc(long long A, long long B, long long *factorials, long long P)
{
  if(A < B)
    return 0;
  else{
    return factorials[A] * invert_fact(factorials[B], P) % P * invert_fact(factorials[A - B], P) % P;
  }
}

long long combinari(long long A, long long B, long long P)
{
  long long comb = 1;
  //printf("%ld %ld\n", sizeof(long long), sizeof(long long int));
  //fscanf(input, "%lld", &P);
  //fscanf(input, "%lld", &Q);

  long long factorials[P];
  factorials[0] = 1;

  factorial(P, factorials);
  
    while(max(A, B) > 0){
      // printf("%d\n", combinari(A % P, B % P, factorials, P));
      comb = (comb * calc(A % P, B % P, factorials, P)) % P;
      A /= P;
      B /= P;
      //printf("1. %d %d %d\n", res[0], res[1], res[2]);
      // printf("res : %d\n", res[0] * res[1] * res[2] % P);
    }
    //
    //printf("%d\n", comb);
    //fprintf(output, "%lld\n", comb);
    
    //printf("%d %d %d\n", res[0], invert_fact(res[1], P), invert_fact(res[2], P));
    // printf("lld\n", (factorials[A % P] * invert_fact(factorials[B % P], P) * invert_fact(factorials[(A - B) % P], P)) % P);

  return comb;
}

int main(void)
{
  FILE *input = fopen("functii.in", "r");
  FILE *output = fopen("functii.out", "w");

  long long P = 30103;
  long long n, s;
  long long zero_vals;
  long long sum = 0;
  
  fscanf(input, "%lld", &n);
  fscanf(input, "%lld", &s);

  if(s > n){
    fprintf(output, "0");
  }
  else{
    zero_vals = combinari(n, (n - s), P) % P;
    for(int i = 1;i <= s - 1;i++){
      sum += combinari(s, i, P) % P;
    }
    // printf("%d\n", zero_vals);
    sum = sum % P;
    fprintf(output, "%lld\n", (zero_vals * sum) % P);
  }

  fclose(input);
  fclose(output);

  return 0;
}
	   
