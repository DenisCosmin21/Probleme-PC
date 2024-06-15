#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
  char *cuvant;
  int count;
}cuv;
  
int din_memory_calc(int size)
{
  if(size < 4){
    return size + 1;
  }
  else{
    return size / 2 * 3;
  }
}

char *read_text(char *file_path)
{
  FILE *buffer = fopen(file_path, "r");
  assert(buffer != NULL);
  char *text = malloc(1 * sizeof(char));
  assert(text != NULL);
  size_t size = 0;
  size_t max_size = 1;
  char c = 0;
  char ant = 0;
  while((c = fgetc(buffer)) != EOF){
    if((ant == '\n' && c == '\n') == 0){
      text[size] = c;
      size++;
      if(size == max_size){
	max_size = din_memory_calc(max_size);
	assert(size <= max_size);
	text = realloc(text, max_size * sizeof(char));
	assert(text != NULL);
      }
    }
    else{
      size--;
      text[size] = '\0';
      break;
    }
    ant = c;
  }
  fclose(buffer);
  text[size] = '\0';
  if(strlen(text) == 0){
    free(text);
    return NULL;
  }
  text = realloc(text, (size+1) * sizeof(char));
  return text;
}

char *get_line(char *text)
{
  if(strlen(text) == 0){
    return NULL;
  }
  char *end_line = strchr(text, '\n');
  char *line = malloc((end_line - text + 1) * sizeof(char));
  assert(line != NULL);
  size_t size = 0;
  for(;text < end_line;text++){
    line[size] = *text;
    size++;
  }
  line[size] = '\0';
  return line;
}

cuv *parcurgere_structura(cuv *list, size_t word_count, char *cuvant)
{
  if(word_count == 0){
    return 0;
  }
  for(cuv *start = list;start != list + word_count;start++){
    if(strcmp(start->cuvant, cuvant) == 0){
      return start;
    }
    }
  return NULL;
}

cuv *add_words_from_line(char *line, cuv *list, size_t *word_count)
{
  char *space = NULL;
  char *cuvant = NULL;
  size_t dimensiune_cuvant = 0;
  size_t dimensiune_alocata_cuvant = 0;
  do{
    space = strchr(line, ' ');
    cuvant = malloc(sizeof(char));
    dimensiune_cuvant = 0;
    dimensiune_alocata_cuvant = 1;
    for(char *i = line;i < space;i++){
      if(*i != '\n'){
	cuvant[dimensiune_cuvant] = *i;
	dimensiune_cuvant++;
	if(dimensiune_cuvant == dimensiune_alocata_cuvant){
	  dimensiune_alocata_cuvant = din_memory_calc(dimensiune_alocata_cuvant);
	  cuvant = realloc(cuvant, dimensiune_alocata_cuvant);
	  assert(cuvant != NULL);
	}
      }
    }
    cuvant[dimensiune_cuvant] = '\0';
    if(cuvant[0] == '\n' || cuvant[0] == '\0'){
      free(cuvant);
      break;
    }
    cuv *pozition = parcurgere_structura(list, *word_count, cuvant);
    if(pozition == NULL){
      list = realloc(list, (*word_count + 1) * sizeof(cuv));
      assert(list != NULL);
      *word_count += 1;
      list[*word_count - 1].cuvant = cuvant;
      list[*word_count - 1].count = 1;
    }
    else{
      free(cuvant);
      pozition->count ++;
    }
    line = space + 1;
  }while(space != NULL);
  return list;
}

cuv *max_word(cuv *list, size_t word_count)
{
  int max = 0;
  cuv *return_value = NULL;
  for(cuv * start = list;start < list + word_count;start++){
    if(start->count > max){
      max = start->count;
      return_value = start;
    }
  }
  return return_value;
}

void show_element(cuv list)
{
  printf("%s -> %d\n", list.cuvant, list.count);
}

int main(void)
{
  char path[] = "scrisoare.txt";
  char *text = NULL;
  char *pointer_text = NULL;
  char *line = NULL;
  cuv *list = malloc(sizeof(cuv));
  size_t  word_count = 0;
  if((text = read_text(path)) != NULL){
    pointer_text = text;
    while((line = get_line(pointer_text)) != NULL){
      pointer_text = strchr(pointer_text, '\n') + 1;
      list = add_words_from_line(line, list, &word_count);
      free(line);
    }
    for(int i = 0;i < word_count;i++){
      show_element(list[i]);
      }
    cuv *word = max_word(list, word_count);
    show_element(*word);
    free(text);
    for(int i = 0;i < word_count;i++){
      free(list[i].cuvant);
    }
    free(list);
  }
  return 0;
}
