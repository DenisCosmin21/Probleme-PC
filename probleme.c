#include <stdio.h>
#include <stdint.h>

void print_bit_16 (uint64_t nr)
{
  uint64_t mask = 1; // 0b1000000000000000
  mask = mask << 63;
  uint16_t i = 0;
  for (i = 0; i < 64; i++)
    {
      if ((nr & mask) == 0)
        {
          printf ("0");
        }
      else
        {
          printf ("1");
        }
      mask = mask >> 1; // mask >>= 1;
    }
  printf ("\n");
}

void printbit(uint8_t nr)
{
  uint8_t mask = 1 << 7;
  for(int i = 0;i < 8;i++){
    if(nr & mask){
      printf("1");
    }
    else{
      printf("0");
    }
    mask >>= 1;
  }
  printf("\n");
}
uint8_t pb8(uint8_t nr)
{
  nr = nr | 1;
  nr = nr | (1 << 2);
  nr = nr | (1 << 3);
  nr = nr & (~(1 << 1));
  nr = nr & (~(1 << 5));
  nr = nr & (~(1 << 6));
  if(nr & (1 << 4)){
    nr = nr & (~(1 << 4));
  }
  else{
    nr = nr | (1 << 4);
  }
  if(nr & (1 << 7)){
    nr = nr & (~(1 << 7));
  }
  else{
    nr = nr | (1 << 7);
  }
  return nr;
}

void despachetare(char c)
{
  uint8_t mask = 1;
  uint8_t nible = 0;
  for(int i = 0;i < 2;i++){
    for(int j = 0;j < 4;j++){
      if(mask & c){
	nible = nible | mask;
      }
      mask <<= 1;
    }
    printbit(nible);
    printf("%hhd \n", nible);
    nible = 0;
    mask >>= 4;
    c >>= 4;
  }
}
uint8_t impachetare(uint8_t nr1, uint8_t nr2)
{
  printbit(nr1);
  printbit(nr2);
  char c;
  uint8_t mask = 1;
  for(int i = 0;i < 2;i++){
    for(int j = 0;j < 4;j++){
      if(nr1 & mask){
	c = c | mask;
      }
      else{
	c = c & (~mask);
      }
      mask = mask << 1;
    }
    nr1 = nr2;
    nr1 <<= 4;
  }
  printbit(c);
  return c;
}

int pb13(unsigned int nr)
{
  int contor = 0;
  unsigned int mask = 1;
  for(int i = 0;i < sizeof(nr) * 4;i++){
    if(nr & mask){
      contor++;
    }
    mask<<=1;
  }
  return contor;
}
int main(void)
{
  uint8_t nr = 0, nr2 = 0;
  scanf("%hhd", &nr);
  scanf("%hhd", &nr2);
  //printbit(nr);
  //printbit(pb8(nr));
  //printf("%hhd\n", impachetare(nr, nr2));
  //despachetare(impachetare(nr, nr2));
  printbit(50);
  print_bit_16(2);
  printf("%d\n", pb13(50));
  printf("%ld", sizeof(1));
  return 0;
}
