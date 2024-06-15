#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
  int value;
  void *next_item;
}List;

typedef struct
{
  List *inceput;
  List *final;
}Capete;

typedef struct
{
  List *vector_a;
  List *vector_b;
}ValoriEliminate;

void ListInit(Capete *margini)
{
  margini->inceput = NULL;
  margini->final = NULL;
}

void AddListData(Capete *margini, int value_to_add)
{
  List *vector = malloc(sizeof(List));
  if(margini->inceput == NULL){
    margini->inceput = vector;
    margini->final = vector;
    vector->value = value_to_add;
    vector->next_item = NULL;
  }
  else{
    margini->final->next_item = vector;
    margini->final = vector;
    vector->value = value_to_add;
    vector->next_item = NULL;
  }
}

void FreeList(Capete margini)
{
  List *vector = margini.inceput;
  List *next_vector = vector->next_item;
  for(;vector != NULL;vector = next_vector){
    next_vector = vector->next_item;
    free(vector);
  }
}

ValoriEliminate FindSameValues(Capete list_a, Capete list_b)
{
  
  List *vector_a = list_a.inceput, *vector_b = list_b.inceput;
  ValoriEliminate values;
  for(;vector_a != NULL;vector_a = vector_a->next_item){
    for(List *iterator_b = vector_b;iterator_b != NULL;iterator_b = iterator_b->next_item){
      if(vector_a->value == iterator_b->value){
	values.vector_a = vector_a;
	values.vector_b = iterator_b;
	return values;
      }
    }
  }
  values.vector_a = NULL;
  values.vector_b = NULL;
  return values;
}

void DeleteValue(Capete *margini, List *list_to_delete)
{
  List *elem_ant = NULL;
  for(List *iterator = margini->inceput;iterator != list_to_delete;iterator = iterator->next_item)
    {
      elem_ant = iterator;
    }
  
  if(elem_ant == NULL){
    margini->inceput = list_to_delete->next_item;
    free(list_to_delete);
  }
  else if(list_to_delete == margini->final){
    free(list_to_delete);
    margini->final = elem_ant;
  }
  else{
    elem_ant->next_item = list_to_delete->next_item;
    free(list_to_delete);
  }
}

void RemoveSameValues(ValoriEliminate values, Capete *list_a, Capete *list_b)
{
  DeleteValue(list_a, values.vector_a);
  DeleteValue(list_b, values.vector_b);
}
  
void RemoveAndAddToC(Capete *list_c, Capete *list_a, Capete *list_b)
{
  ListInit(list_c);
  ValoriEliminate values = FindSameValues(*list_a, *list_b);
  while(values.vector_a != NULL){
    AddListData(list_c, values.vector_a->value);
    RemoveSameValues(values, list_a, list_b);
    values = FindSameValues(*list_a, *list_b);
  }
}

void ShowListValues(Capete list_to_show)
{
  for(List *iterator = list_to_show.inceput;iterator != NULL;iterator = iterator->next_item){
    printf("%d ", iterator->value);
  }
  printf("\n");
}

int main(void)
{
  Capete list_a, list_b, list_c;
  ListInit(&list_a);
  ListInit(&list_b);
  ListInit(&list_c);
  int nr = 0;
  while(scanf("%d", &nr) == 1 && nr != 0){
    AddListData(&list_a, nr);
  }
  
  while(scanf("%d", &nr) == 1 && nr != 0){
    AddListData(&list_b, nr);
  }

  RemoveAndAddToC(&list_c, &list_a, &list_b);
  ShowListValues(list_c);
  ShowListValues(list_b);
  ShowListValues(list_a);
  FreeList(list_a);
  FreeList(list_b);
  FreeList(list_c);
  return 0;
}
