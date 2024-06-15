#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void PrintBit(uint32_t numar)
{
  uint32_t mask = 1 << 31;
  for(int i = 0;i < 32;i++){
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

uint32_t DataEncryption(uint8_t zi, uint8_t luna, uint16_t an)
{
  uint32_t data_criptata = 0;
  data_criptata |= zi;
  data_criptata <<= 8;
  data_criptata |= luna;
  data_criptata <<= 16;
  data_criptata |= an;
  return data_criptata;
}

uint8_t RetrieveMonth(uint32_t data_criptata)
{
  uint8_t luna_decriptata= 0;
  data_criptata >>= 16;
  luna_decriptata |= data_criptata;
  return luna_decriptata;
}


int main(void)
{
  uint8_t zi = 2, luna = 4;
  uint16_t an = 2023;
  PrintBit(DataEncryption(zi, luna, an));
  printf("%d\n", RetrieveMonth(DataEncryption(zi, luna, an)));
}
