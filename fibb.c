#include <stdio.h>

#define modulus 666013

void matrix_exponent(long long power, long long *rez)
{
  long long matrix[4] = {0, 1, 1, 1};
  long long matrix_cpy[4];
  long long mask = 1;
  if(power > 1){
    for(;mask <= power; mask <<= 1){
      if((mask & power) != 0){
	matrix_cpy[0] = rez[0];
	matrix_cpy[1] = rez[1];
	matrix_cpy[2] = rez[2];
	matrix_cpy[3] = rez[3];
      
	rez[0] = (matrix[0] * matrix_cpy[0] + matrix[1] * matrix_cpy[2]) % modulus;
	rez[1] = (matrix[0] * matrix_cpy[1] + matrix[1] * matrix_cpy[3]) % modulus;
	rez[2] = (matrix[2] * matrix_cpy[0] + matrix[3] * matrix_cpy[2]) % modulus;
	rez[3] = (matrix[2] * matrix_cpy[1] + matrix[3] * matrix_cpy[3]) % modulus;
      }

      matrix_cpy[0] = matrix[0];
      matrix_cpy[1] = matrix[1];
      matrix_cpy[2] = matrix[2];
      matrix_cpy[3] = matrix[3];

      matrix[0] = (matrix_cpy[0] * matrix_cpy[0] + matrix_cpy[1] * matrix_cpy[2]) % modulus;
      matrix[1] = (matrix_cpy[0] * matrix_cpy[1] + matrix_cpy[1] * matrix_cpy[3]) % modulus;
      matrix[2] = (matrix_cpy[2] * matrix_cpy[0] + matrix_cpy[3] * matrix_cpy[2]) % modulus;
      matrix[3] = (matrix_cpy[2] * matrix_cpy[1] + matrix_cpy[3] * matrix_cpy[3]) % modulus;
    }
  }
  else if(power == 0){
    rez[0] = 1;
    rez[1] = 0;
    rez[2] = 0;
    rez[3] = 1;
  }
}
  
int main(void)
{
  FILE *input = fopen("kfib.in", "r");
  FILE *output = fopen("kfib.out", "w");

  long long termen, rez[4] = {0, 1, 1, 1};
  
  fscanf(input, "%lld", &termen);

  matrix_exponent(termen - 3, rez);
  //printf("%lld %lld %lld %lld\n", rez[0], rez[1], rez[2], rez[3]);
  fprintf(output, "%lld", (rez[1] + rez[3]) % modulus);
  fclose(input);
  fclose(output);

  return 0;
}
  
