#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
  char *cuvant;
  int word_count;
}Word;

typedef enum
  {
    true = 1,
    false = 0
  }bool;

int DetermineAllocSize(int old_size)
{
  if((old_size / 2) * 3 <= old_size){
    return old_size + 1;
  }
  else{
    return (old_size / 2) * 3;
  }
}

char *ReadText(void)
{
  char *text = malloc(sizeof(char));
  int size = 0;
  int max_size = 1;
  char read_character = 0;
  while((read_character = fgetc(stdin)) != EOF){
    text[size] = read_character;
    size++;
    if(size == max_size){
      max_size = DetermineAllocSize(max_size);
      text = realloc(text, max_size * sizeof(char));
    }
  }
  text[size] = '\0';
  return text;
}

Word *AddWordToList(Word *word_list, int *new_word_count, char *word)
{
  bool found_word = false;
    for(int i = 0;i < *new_word_count;i++){
      if(strcasecmp(word_list[i].cuvant, word) == 0){
	word_list[i].word_count++;
	found_word = true;
	free(word);
	break;
      }
    }
  
  if(found_word == false){
    *new_word_count += 1;
    word_list = realloc(word_list, *new_word_count * sizeof(Word));
    word_list[*new_word_count - 1].cuvant = word;
    word_list[*new_word_count - 1].word_count = 1;
  }
  return word_list;
}

int FindMaxCount(Word *word_list, int word_count)
{
  int max = 0;
  for(int i = 0;i < word_count;i++){
    if(word_list[i].word_count > max){
      max = word_list[i].word_count;
    }
  }
  return max;
}

int main(void)
{
  char *text = ReadText();
  Word *word_list = malloc(sizeof(Word));
  int new_word_count = 0;
  char *word_found = strtok(text, ";., \n");
  
  while(word_found != NULL){
    char *word_to_add = malloc((strlen(word_found) + 1) * sizeof(char));
    strcpy(word_to_add, word_found);
    word_list = AddWordToList(word_list, &new_word_count, word_to_add);
    word_found = strtok(NULL, ";., \n");
  }
  
  int max = FindMaxCount(word_list, new_word_count);
  
  for(int i = 0;i < new_word_count;i++){
    if(word_list[i].word_count == max){
      printf("%s\n", word_list[i].cuvant);
    }
  }

  for(int i = 0;i < new_word_count;i++){
    free(word_list[i].cuvant);
  }
  free(text);
  free(word_list);
}
