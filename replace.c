#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *concatenare_string(char *text, char *start,const char *end, const char *with, int inc)
{
  static int contor = 0;
  static char *begin = NULL;
  if(begin == NULL){
    begin = start;
  }
  for(;begin != end; begin++){
    text[contor] = begin[0];
    contor++;
  }
  text[contor] = '\0';
  strcat(text, with);
  contor += strlen(with);
  begin = begin + inc;
  return text;
}

char *string_replace(char *where,const char *what,const char*with)
{
  int cnt = 0;
  char *aux = strstr(where, what);
  if(aux == NULL){
    return NULL;
  }
  else{
    cnt = 1;
    char *rezultat = NULL;
    char *ant = NULL;
    if((rezultat = malloc((strlen(where) - strlen(aux) + strlen(with) + 1) * sizeof(rezultat))) == NULL){
      return NULL;
    }
    else{
      memset(rezultat, '\0', 1);
      rezultat = concatenare_string(rezultat, where, aux, with, strlen(what));
      while((aux = strstr(aux + strlen(what), what)) != NULL){
	cnt++;
	rezultat = realloc(rezultat, (strlen(where) - strlen(aux) + cnt * strlen(with) + 1) * sizeof(rezultat));
	rezultat = concatenare_string(rezultat, where, aux, with, strlen(what));
	ant = aux;
      }
      rezultat = realloc(rezultat, (strlen(rezultat) + strlen(ant + strlen(what)) + 1));
      strcat(rezultat, ant + strlen(what));
      return rezultat;
    }
  }
}

int main(void)
{
  char s1[] = "Acesta este un string si un string este terminat cu 0x00";
  char s2[] = "string";
  char s3[] = "sir de caractere";
  char *rez = string_replace(s1, s2, s3);
  printf("%s\n", rez);
  free(rez);
  return 0;
}
