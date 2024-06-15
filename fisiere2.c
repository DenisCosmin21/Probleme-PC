#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

void alocare_string(char **string, int *sizeS)
{
  *sizeS += 1;
  *string = realloc(*string, (*sizeS + 1) * sizeof(char));
}

void alocare_tablou(char ***tablou, int *size)
{
  *size += 1;
  *tablou = realloc(*tablou, (*size + 1) * sizeof(char*));
}

void citire(char ***tablou, int *size)
{
  FILE *f = fopen("scrisoare.txt", "r");
  char c = ' ';
  //char **adresa = *tablou;
  (*tablou)[*size] = malloc(sizeof(char));
  int sizeS = 0;
  while((c = fgetc(f)) != EOF){
    if(c == '\n'){
      ((*tablou)[*size])[sizeS] = '\0';
      // printf("%s\n", (*tablou)[*size]);
      alocare_tablou(tablou, size);
      (*tablou)[*size] = malloc(sizeof(char));
      sizeS = 0;
      // printf("%s\n", (*tablou)[*size - 1]);
    }
    else{
      // printf("%d %d\n", *size, sizeS);
      ((*tablou)[*size])[sizeS] = c;
      // printf("%d %d\n", *size, sizeS);
      alocare_string(&((*tablou)[*size]), &sizeS);
    }
  }
  free((*tablou)[*size]);
  fclose(f);
}

void afisare(char **tablou, int size, char *fisier)
{
  FILE *f = fopen(fisier, "w");
  //printf("%s", fisier);
  for(int i = 0;i < size;i++){
    //printf("%s\n", tablou[i]);
    fprintf(f, "%s\n", tablou[i]);
  }
  fclose(f);
}

void eliberare(char ***tablou, int *size)
{
  for(int i = 0;i < *size;i++){
    free((*tablou)[i]);
  }
  free(*tablou);
  *size = 0;
}

char **copiere(char **string, int size)
{
  char **copie = NULL;
  copie = malloc(sizeof(string) * (size));
  memcpy(copie, string, (size) * sizeof(string));
  return copie;
}

void schimbare(char **element1, char**element2)
{
  char *copie = *element1;
  *element1 = *element2;
  *element2 = copie;
}

int alphabetical(char *element1, char *element2)
{
  return strcmp(element1, element2);
}

void write_sort(char **lines, char *filepath, int size)
{
  char **copie = copiere(lines, size);
  for(int i = 0;i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(alphabetical(copie[i], copie[j]) > 0){
	schimbare(&copie[i], &copie[j]);
      }
    }
  }
  afisare(copie, size, filepath);
  free(copie);
}

	  
int main(void)
{
  int size = 0;
  char **tablou = malloc(sizeof(tablou));
  citire(&tablou, &size);
  write_sort(tablou, "date.txt", size);
  
  eliberare(&tablou, &size);
}
