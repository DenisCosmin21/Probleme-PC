#include <stdio.h>
#include "lista.h"

//Stiva cu lista
typedef lista stiva;
typedef lista coada;

stiva init_st(el element)
{
  stiva new = initialize_list(element);
  return new;
}

stiva find_prior_position(stiva st, size_t prioritate)
{
  for(;st != NULL; st = vecin(st)){
    if(get_priority(st) >= prioritate){
      return st;
    }
  }
  return NULL;
}

stiva push_to_stiv(stiva st, el element)
{
  //Intai vom cauta pozitia pe car eil introducem in functie de prioritate
  //show_elems(find_prior_position(st, element.prioritate));
  append_inside(st, find_prior_position(st, element.prioritate), element);
  return st;
}

el pop(stiva *st)
{
  el element;
  *st = pop_list(*st, &element);
  return element;
}

//Coada cu lista
coada init_coada(el element)
{
  coada new = initialize_list(element);
  return new;
}

coada find_prior_pos(coada cd, size_t prioritate)
{
  for(;cd != NULL; cd = vecin(cd)){
    if(get_priority(cd) > prioritate){
      return cd;
    }
  }
  return NULL;
}

coada push_to_cd(coada cd, el element)
{
  //Intai vom cauta pozitia pe car eil introducem in functie de prioritate
  //show_elems(find_prior_position(st, element.prioritate));
  append_inside(cd, find_prior_pos(cd, element.prioritate), element);
  return cd;
}

el pop_cd(coada *cd)
{
  el element;
  *cd = pop_list(*cd, &element);
  return element;
}

int main(void)
{
  el elem1 = {1, 1};
  el elem2 = {2, 2};
  el elem3 = {3, 3};
  el elem4 = {4, 2};
  
  coada new = init_coada(elem1);
  show_elems(new);
  new = push_to_cd(new, elem2);
  show_elems(new);
  new = push_to_cd(new, elem3);
  show_elems(new);
  new = push_to_cd(new, elem4);
  show_elems(new);

  elem1 = pop_cd(&new);
  printf("%d -> %ld\n", elem1.val, elem1.prioritate);

  show_elems(new);
  return 0;
}
