#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*char *linie( FILE *f)
{
  char *text=NULL;
  if((text=malloc(sizeof(text)))==NULL)
    {
      printf("err");
      return NULL;
    }
  int size=0;
  while((fscanf(f,"%c",&text[size])==1) && text[size]!='\n')
    {
      size++;
      if((text=realloc(text,(size+1)*sizeof(text) ))==NULL)
	{
	  printf("err");
	  free(text);
	  return NULL;
	}
    }
  
  text[size]='\0';
  if(text[0] == '\0')
  {
    if(!feof(f))
    {
      text = realloc(text, 2 * sizeof(char));
      text[0] = '\n';
      text[1] = '\0';
    }
    else
    {
      free(text);
      return NULL;
    }
  }
  
  return text;
}
*/
void *eroare(void)
{
    printf("err");
    return NULL;
}

/*char **tablou( int *size, FILE *f)
{
  char **tab=NULL;
  char *text =NULL;
  if((tab=malloc(sizeof(char*)))==NULL)
    {
      eroare();
    }
   while((text=linie(f))!=NULL)
    {
      tab[*size]=text;
      (*size)++;
      if((tab=realloc(tab, ((*size)+1)*sizeof(char*)))==NULL)
	eroare();
    }
   return tab;
}
*/
void afisare(char **tab, int size, FILE *f)
{
  for(int i=0;i<size;i++)
    {
      fprintf(f,"%s\n",tab[i]);
    }
}

int *generare_numere(int size)
{
  int *nr_generate = malloc((size+1) * sizeof(int));
  int lungime_tablou = 0;
  int numar = 0;
  int exista = 0;
  srand(time(0));
  for(int i = 0;i < size;i++){
    
    do{
      exista = 0;
      numar = rand()%size;
      for(int j = 0;j < lungime_tablou;j++){
	if(nr_generate[j] == numar){
	  exista = 1;
	  break;
	}
      }
    }while(exista == 1);
    nr_generate[i] = numar;
    lungime_tablou++;
  }
  return nr_generate;
}

void write_random(char **tab, char *filepath, int size)
{
  FILE *f=fopen(filepath,"w");
  int *nr_gen=generare_numere(size);
  for(int i=0;i<size;i++)
    {
      fprintf(f,"%s\n",tab[nr_gen[i]]);
    }
  fclose(f);
  free(nr_gen);
}

void sort(char **tab, int size, char *filepath)
{
  FILE *f=fopen(filepath,"w");
  char *aux=NULL;
  for(int i=0;i<size-1;i++)
    {
      for(int j=i+1;j<size;j++)
	{
	  if(strcmp(tab[i],tab[j])>0)
	    {
	      aux=tab[i];
	      tab[i]=tab[j];
	      tab[j]=aux;
	    }
	}
    }
  afisare(tab,size,f);
  fclose(f);
}

void eliberare(char **tab, int size)
{
  for(int i=0;i<size;i++)
    {
      free(tab[i]);
    }
  free(tab);
}

char *citire_text(FILE *f)
{
  char *text = malloc(sizeof(char));
  int size = 0;
  while((text[size++] = fgetc(f)) != EOF){
    text = realloc(text, (size + 1) * sizeof(char));
  }
  text = realloc(text, (size + 1) * sizeof(char));
  text[size] = '\0';
  return text;
}

char *separare_linie(char *text)
{
  static int contor = 0;
  if(contor == 0){
    contor = 1;
    return strtok(text, "\n");
  }
  else{
    return strtok(NULL, "\n");
  }
}

char **adaugare_tablou(char *linie, char **tablou, int size)
{
  tablou = realloc(tablou, (size + 1) * sizeof(char*));
  tablou[size - 1] = malloc((strlen(linie) + 1) * sizeof(char));
  strcpy(tablou[size - 1], linie);
  return tablou;
}

int find_word(char *text, char *word)
{
  int contor = 0;
  char *cuvant = NULL;
  cuvant = strstr(text, word);
  if(cuvant != NULL){
    contor++;
  }
  else{
    return 0;
  }
  while((cuvant = strstr(cuvant + strlen(word), word)) != NULL){
    contor++;
  }
  return contor;
}

/*int find_word(char **tab, char*word)
{
  int contor = 0;
  char *p = NULL;
  int i = 0;
  while(tab[i][0] != '\0'){
    p = strstr(tab[i], word);
    if(p != NULL){
      contor++;
      while((p = strstr(p + strlen(word), word)) != NULL){
      contor++;
    }
    }
    
    i++;
  }
  return contor;
  }*/

int main(void)
{
  FILE *f=fopen("scrisoare.txt","r");
  int size=0;
  char *text = citire_text(f);
  char *linie = NULL;
  char **tablou = NULL;

  while((linie = separare_linie(text)) != NULL){
    size++;
    tablou = adaugare_tablou(linie, tablou, size);
  }
  free(text);
  afisare(tablou,size,stdout);
  //sort(tab,size,"out5.txt");
  //write_random(tab,"out6.txt",size);
  eliberare(tablou,size);
  fclose(f);
  return 0;
}
