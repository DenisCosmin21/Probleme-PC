#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_t
{
  struct lista_t *next;
  el element;
};

lista vecin(lista list)
{
  if(list->next == NULL){
    return NULL;
  }
  else{
    return list->next;
  }
}

lista initialize_list(el element)
{
  lista new = malloc(sizeof(struct lista_t));
  new->next = NULL;
  new->element = element;
  return new;
}

lista append_front(lista list, el element)
{
  lista new = initialize_list(element);
  new->next = list;
  return new;
}

int append_inside(lista list, lista next, el element)
{
  for(;vecin(list) != next;list = vecin(list)){
    if(list == NULL){
      return -1;
    }
  }

  lista copie = next;
  lista new = append_front(copie, element);
  list->next = new;
  return 1;
}

void show_elems(lista list)
{
  for(;; list = vecin(list)){
    printf("%d : prior %ld\n", list->element. val, list->element.prioritate);
    if(vecin(list) == NULL){
      break;
    }
  }
  printf("\n");
}

lista pop_list(lista list, el *element)
{
  *element = list->element;
  lista new = vecin(list);
  show_elems(new);
  //free(list);
  return new;
}

size_t get_priority(lista list)//responsabilitatea programatorului sa nu afiseze pe o lista inexistenta
{
  return list->element.prioritate;
}

lista eliberare(lista list)
{
  lista new = NULL;
  while(1){
    new = vecin(list);
    free(list);
    list = new;
    if(list == NULL){
      return NULL;//returnam doar NULL pentru a asigura programatorul ca nu poate avea un pointer eliberat salvat acolo
    }
  }
}

  
