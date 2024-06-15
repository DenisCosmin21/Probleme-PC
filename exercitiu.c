/*Cerinta :
  se citesc de la tastatura linii pana la intalnirea lui EOF(ctrl + d). Scrieti un program care citeste tot textul, iar apoi va afisa cuvintele din text care au un numar par de vocale, si va afisa dupa numarul de vocale al fiecarei linii. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int din_mem(int size)
{
  return size > 4 ? size / 2 * 3 : size + 1;
}

char *read_file(void)
{
  char *text = malloc(sizeof(char));
  assert(text != NULL);
  int max_size = 1;
  int size = 0;
  char c = 0;
  while((c = getchar()) != EOF){
    text[size++] = c;
    if(size == max_size){
      max_size = din_mem(max_size);
      assert(max_size > size);
      text = realloc(text, max_size * sizeof(char));
    }
  }
  text[size] = '\0';
  if(size == 0){
    free(text);
    return NULL;
  }
  else{
    return text;
  }
}

void show_voc_par(char *text)
{
  char *cuvant = malloc(sizeof(char));
  assert(cuvant != NULL);
  int size = 0;
  int max_size = 1;
  char voc[] = "aeiouAEIOU";
  int count_voc = 0;
  char *end_line = NULL, *end_word = NULL;
  do{
    //printf("%s\n", end_line);
    count_voc = 0;
    end_line = strchr(text, '\n');
    end_word = strchr(text, ' ');
    if(*text == '\0'){
      break;
    }
    if(end_word == NULL){
      end_word = text + strlen(text);
      printf("%c", *end_word);
    }
    if(end_line < end_word && (end_line != NULL)){
      end_word = end_line;
    }
    for(;(text < end_word);text++){
      cuvant[size++] = *text;
      if(size == max_size){
	max_size = din_mem(max_size);
	assert(max_size > size);
	cuvant = realloc(cuvant, max_size * sizeof(char));
	assert(text != NULL);
      }
      if(strchr(voc, *text)){
	count_voc++;
      }
    }
    cuvant[size] = '\0';
    if(count_voc % 2 == 0){
      printf("%s ", cuvant);
    }
    size = 0;
    text = end_word + 1;
  }while(end_word != NULL);
  
  free(cuvant);
  
}

void show_voc_line(char *text)
{
  char *end_line = NULL;
  int voc_count = 0;
  int line_count = 0;
  char voc[] = "aeiouAEIOU";
  do{
    voc_count = 0;
    line_count++;
    end_line = strchr(text, '\n');
    if(*text != '\0' && end_line == NULL){
      end_line = strchr(text, '\0');
    }
    else if(*text == '\0'){
      break;
    }
    for(;text < end_line;text++){
      if(strchr(voc, *text)){
	voc_count++;
      }
    }
    printf("Linia %d are : %d vocale\n", line_count, voc_count);
    text = end_line + 1;
  }while(end_line != NULL);
}

int main(void)
{
  char * text = read_file();
  if(text != NULL){
    show_voc_par(text);
    show_voc_line(text);
    free(text);
  }
  else{
    printf("Nu s-au citit caractere");
  }
  return 0;
}
