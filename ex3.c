#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void PrintBit(short int numar)
{
  short int mask = 1 << ((sizeof(short int) * 4) - 1);
  for(int i = 0;i < sizeof(short int) * 4;i++){
    if(!(numar & mask)){
      printf("0");
    }
    else{
      printf("1");
    }
    mask >>= 1;
  }
  printf("\n");
}

int PrelucrareBiti(short int numar)
{
  short int mask = 7;
  PrintBit(mask);
  if((numar & mask) == 7){
    mask <<= 3;
  }
  return numar | mask;
}

int main(void)
{
  short int read_number = 0;
  while((scanf("%hd", &read_number) == 1) && (read_number != 0)){
    PrintBit(read_number);
    PrintBit(PrelucrareBiti(read_number));
  }
  return 0;
}
