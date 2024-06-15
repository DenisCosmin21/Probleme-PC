#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
  int an;
  char *titlu;
  int buget;
}lista_filme;

FILE *deschidere_fisier(char *nume, char *operatie)
{
  if(strcmp(nume, "stdin") == 0){
    return stdin;
  }
  else if(strcmp(nume, "stdout") == 0){
    return stdout;
  }
  else{
    return fopen(nume, operatie);
  }
}

char *citire_text(FILE *f)
{
  char *text = NULL;
  int size = 0;
  int c = 0;
  text = malloc(sizeof(char));
  while((c = fgetc(f)) != EOF){
    text[size] = c;
    size++;
    text = realloc(text, (size + 1) * sizeof(char));
  }
  text[size] = '\0';
  if(text[0] == '\0'){
    free(text);
    return NULL;
  }
  else{
    printf("%s\n", text);
    free(text);
    return NULL;
  }
}

lista_filme *get_data_from_line(char *linie, int nr_inregistrari, lista_filme *filme)
{
  filme = realloc(filme, (nr_inregistrari + 1) * sizeof(lista_filme));
  char *virgula = strchr(linie, ',');
  virgula[0] = '\0';
  filme[nr_inregistrari].an = strtol(linie, NULL, 10);
  virgula = strchr(virgula + 1, ',');
  virgula[0] = '\0';
  linie = virgula + 1;
  virgula = strchr(virgula + 1, ',');
  virgula[0] = '\0';
  filme[nr_inregistrari].titlu = malloc((strlen(linie) + 1) * sizeof(char));
  strcpy(filme[nr_inregistrari].titlu, linie);
  virgula = strchr(virgula + 1, ',');
  virgula = strchr(virgula + 1, ',');
  virgula = strchr(virgula + 1, ',');
  linie = virgula + 1;
  virgula = strchr(virgula + 1, ',');
  virgula[0] = '\0';
  filme[nr_inregistrari].buget = strtol(linie, NULL, 10);
  return filme;
}

void afisare(lista_filme *filme, int size, char *nume_fisier)
{
  FILE *f = deschidere_fisier(nume_fisier, "w");
  for(int i = 0;i < size;i++){
    fprintf(f, "%d %s %d\n", filme[i].an, filme[i].titlu, filme[i].buget);
  }
  if(strcmp(nume_fisier, "stdout") != 0){
    fclose(f);
  }
}

void eliberare(lista_filme *filme, int size)
{
  for(int i = 0;i < size;i++){
    free(filme[i].titlu);
  }
  free(filme);
}

lista_filme *sortare_an_aparitie(lista_filme *filme, int size)
{
  lista_filme aux;
  for(int i = 0;i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(filme[i].an > filme[j].an){
	aux = filme[i];
	filme[i] = filme[j];
	filme[j] = aux;
      }
    }
  }
  afisare(filme, size, "out1.txt");
  return filme;
}

int main(void)
{
  lista_filme *filme = NULL;
  int nr_inregistrari = 0;
  FILE *f = deschidere_fisier("movies.csv", "r");
  char *text = citire_text(f);
  if(text != NULL){
    char *linie = strtok(text, "\n");
    while(linie != NULL){
      filme = get_data_from_line(linie, nr_inregistrari, filme);
      nr_inregistrari++;
      linie = strtok(NULL, "\n");
    }
    afisare(filme, nr_inregistrari, "stdout");
    filme = sortare_an_aparitie(filme, nr_inregistrari);
    eliberare(filme, nr_inregistrari);
  }
  fclose(f);
  return 0;
}
