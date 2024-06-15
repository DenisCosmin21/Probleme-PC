#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define chunck_cuvant 5
#define chunck_string 10

char * alocare_string(char *string, int *max_size)
{
  string = realloc(string, (*max_size + chunck_string) * sizeof(char));
  *max_size = *max_size + chunck_string;
  return string;
}

char * adaugare_cuvant(char *s, char *cuvant, int *size, int *max_size, int lungime_cuvant)
{
  static int iteratie = 0;
  if(iteratie == 0){
    iteratie++;
    while(*max_size < lungime_cuvant){
      s = alocare_string(s, max_size);
    }
    strcpy(s, cuvant);
    *size += lungime_cuvant;
  }
  else{
    if(tolower(s[*size - 2]) == tolower(cuvant[0]) && tolower(s[*size - 1]) == tolower(cuvant[1])){
      while(lungime_cuvant > *max_size - *size){
	s = alocare_string(s, max_size);
      }
      strcat(s, "-");
      strcat(s, cuvant);
      *size += lungime_cuvant + 1;
    }
    
}
  return s;
}
char * alocare_cuvant(char *cuvant, int *max_size)
{
  cuvant = realloc(cuvant, (*max_size + chunck_cuvant) * sizeof(char));
  *max_size = *max_size + chunck_cuvant;
  return cuvant;
}

void citire(char *s, int *size, int *max_size)
{
  int size_cuv = 0;
  int max_size_cuv = chunck_cuvant;
  char x;
  char *cuvant = malloc(chunck_cuvant * sizeof(char));
  while((x = getchar()) != EOF){
    if(!isalnum(x)){
      if(size_cuv == 0){
	break;
      }
      cuvant[size_cuv] = '\0';
      s = adaugare_cuvant(s, cuvant, size, max_size, size_cuv);
      size_cuv = 0;
      strcpy(cuvant, "");
    }
    else{
      size_cuv++;
      if(size_cuv == max_size_cuv){
	cuvant = alocare_cuvant(cuvant, &max_size_cuv);
      }
      cuvant[size_cuv - 1] = x;
    }
  }
  free(cuvant);
}
      
    
int main(void)
{
  int max_size = chunck_string;
  int size = 0;
  char *s = malloc(chunck_string * sizeof(char));
  citire(s, &size, &max_size);
  printf("%s", s);
  free(s);
  return 0;
}
