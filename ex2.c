#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void PrintBit(uint32_t numar)
{
  uint32_t mask = 1;
  mask <<= 31;
  for(int i = 0;i < 32;i++){
    if((numar & mask) != 0){
      printf("1");
    }
    else{
      printf("0");
    }
    mask >>= 1;
  }
  printf("\n");
}

uint32_t RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
  uint32_t rezultat = 0;
  rezultat |= red;
  rezultat <<= 8;
  rezultat |= green;
  rezultat <<= 8;
  rezultat |= blue;
  rezultat <<= 8;
  rezultat |= alpha;
  return rezultat;
}

float DetermineAlphaLevel(uint32_t EncodedValue)
{
  uint32_t alpha = 0;
  alpha |= (EncodedValue << 24) >> 24;
  return ((float)alpha / 255) * 100;
}

int main(void)
{
  uint32_t rezultat = RGBA(255, 255, 255, 127);
  printf("%f\n", DetermineAlphaLevel(rezultat));
  return 0;
}
