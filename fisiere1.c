#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct x
{
  char *judet;
  int sumaTotal;
  int beneficiari_platiti;
}Persoane;

void inlocuire_string(char **string, int *size)
{
  free(*string);
  *string = malloc(sizeof(char));
  *size = 0;
}

void alocare_structura(Persoane **list, int *size)
{
  *size += 1;
  *list = realloc(*list, (*size + 1) * sizeof(Persoane));
}

void alocare_string(char **string, int *size)
{
  *size += 1;
  *string = realloc(*string, (*size + 1) * sizeof(char));
}

void add_data(Persoane **list, int *size, char *string, int *pop, int *plati)
{
  int camp = 2;
  char *judet = malloc(sizeof(char));
  int *beneficiari = &((*list)[*size]).beneficiari_platiti;
  int *suma = &((*list)[*size]).sumaTotal;
  char *p = strtok(string, ";");
  judet = realloc(judet, (strlen(p) + 1) * sizeof(char));
  strcpy(judet, p);
  p = strtok(NULL, ";");
  *pop = max(*pop, strtol(p, NULL, 10));
  p = strtok(NULL, ";");
  *beneficiari = strtol(p, NULL, 10);
  while(camp < 4){
    p = strtok(NULL, ";");
    camp++;
  }
  *suma = strtol(p, NULL, 10);
  p = strtok(NULL, ";");
  *plati = max(*plati, strtol(p, NULL, 10));
  ((*list) + (*size))->judet = judet;
  
  alocare_structura(list, size);
}

void citire(Persoane **list, int *size)
{
  int pop = 0;
  int plati = 0;
  FILE *f = fopen("indemnizatie.csv", "r");
  char *string = malloc(sizeof(char));
  int sizeS = 0;
  char c = '0';
  
  while((c = fgetc(f)) != EOF){
    if(c == '\n'){
      add_data(list, size, string, &pop, &plati);
      inlocuire_string(&string, &sizeS);
    }
    else{
      string[sizeS] = c;
      alocare_string(&string, &sizeS);
    }
  }
  printf("%d %d\n", pop, plati);
  free(string);
  fclose(f);
}

void afisare(Persoane *list, int size)
{
  for(int i = 0;i < size;i++){
    printf("%s %d %d\n", list[i].judet, list[i].beneficiari_platiti, list[i].sumaTotal);
  }
}

void eliberare(Persoane **list, int *size)
{
  for(int i = 0;i < *size;i++){
    free((*list)[i].judet);
  }
  free(*list);
  *size = 0;
}

int main(void)
{
  int size = 0;
  Persoane *list = malloc(sizeof(Persoane));
  citire(&list, &size);
  afisare(list, size);
  eliberare(&list, &size);
  return 0;
}
