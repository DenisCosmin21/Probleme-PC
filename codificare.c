#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define modulo_value 16777216

int check_overflow(unsigned int value)//aceasta functie va determina daca numarul este scris pe mai mult de 24 de biti
{
  if((value >> 24) != 0){//shiftam numarul cu 24 deoarece daca are mai mult de 24 de biti valoarea va fi diferita de 0
    return 1;
  }
  return 0;
}

unsigned int encrypt_data(char *data, int N)
{
  unsigned int data_value;
  data_value = data[0];
  data_value <<= 8;
  data_value |= data[1];
  data_value <<= 8;
  data_value |= data[2];
  data_value += N;
  if(check_overflow(data_value) == 1){
    data_value %= modulo_value;//acea valoare este 2^24, si o utilizam pentru a nu face operatia de putere, mai ales cum stim ca utilizam doar 2 ^ 24
  }
  return data_value;
}

char *read_data(char *data)
{
  ssize_t count = 0;
  char ch;
  while(count < 3 && (ch = getchar()) && ch != EOF && ch != '\n'){//vom citi caractere pana la intalnirea endline sau pana la terminarea citirii din fisier sau consola, in maximul a 3 caractere citite pentru a avea secventele de 24 de biti cerute
    data[count++] = ch;
  }
  if(count < 3){
    memset(data + count, 0x00, 3 - count); //Vom adauga biti de 0 in continuare pana la 24 de biti pentru criptare, daca secventa are mai putin de 24 de biti adica 3 caractere
    return NULL;
  }
  else{
    return data;
  }
  
}

void show_bytes(unsigned int encrypted_data)
{
  printf("%02x ", encrypted_data >> 16);
  encrypted_data <<= 16;
  printf("%02x ", encrypted_data >> 24);
  encrypted_data <<= 8;
  printf("%02x ", encrypted_data >> 24);
}

int main(void)
{
  int N;
  scanf("%d", &N);
  getchar();//citim caracterul de endline dupa introducerea numarului N
  char data[3];
  unsigned int encrypted_data;
  while(read_data(data) != NULL){//citim cate 3 bytes de informatie, adica 3 caractere
    encrypted_data = encrypt_data(data, N);
    show_bytes(encrypted_data);
  }
  encrypted_data = encrypt_data(data, N);
  show_bytes(encrypted_data);
  return 0;
}
