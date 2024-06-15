#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct p//lista definita
{
  struct p * start;//primul element din lista
  struct p * end;//ultimul element din lista
  struct p * urm;//elementul urmator
  struct p * ant;//elementul anterior
  int val;
}lista;

lista *initializare(int value, int *size)//initializeaza lista
{
  lista *list_start = malloc(sizeof(lista));
  list_start->start = list_start;
  list_start->end = list_start;
  list_start->urm = NULL;
  list_start->ant = NULL;
  list_start->val = value;
  *size += 1;
  return list_start;
}

void adaugare_element_coada(lista *list, int value, int *size)//adauga un element la capatul listei
{
  lista *list2 = malloc(sizeof(lista));
  list->end->urm = list2;
  list2->urm = NULL;
  list2->end = list2;
  list2->start = list;
  list2->ant = list->end;
  list->end = list2;
  list2->val = value;
  *size += 1;
}

lista * adaugare_element_inceput(lista *list, int value, int *size)//adauga un element la inceputul listei
{
  lista *list2 = malloc(sizeof(lista));
  list->ant = list2;
  list2->val = value;
  list->start = list2;
  list2->urm = list;
  list2->end = list->end;
  list2->ant = NULL;
  list2->start = list2;
  *size += 1;
  return list2;
}

void afisare(lista* list)//afiseaza elementele din lista
{
  lista *i = list;
  while(i != NULL){
    i = i->urm;
  }
}

void eliminare_element_coada(lista *list, int *size)//elimina elementul din capatul listei, scade dimensiunea listei, si elibereaza memoria alocata pentru ultimul element
{
  lista *aux = list->end;
  list->end = list->end->ant;
  list->end->urm = NULL;
  *size -=1;
  free(aux);
}

void eliberare(lista *list, int *size)//elibereaza memoria alocata dinamic la finalul programului
{
  lista *i = list->end;
  lista *j = i->ant;
  while(j != NULL){
    free(i);
    i = j;
    j = i->ant;
  }
  free(i);
  *size = 0;
}

int cautare_element(lista* list, int nr)//returneaza pozitia, iar daca nu exista returneaza -1
{
  int poz = 0;
  for(lista *i = list;i != NULL;i = i->urm){
    if(nr == i->val){
      return poz;
    }
    poz++;
  }
  return -1;
}

lista *cautare_element_pozitie(lista *list, int pozitie, int size) //returneaza numarul de pe pozitia pozitie daca exista, daca nu returneaza -1
{
  int cnt = 0;
  lista *list_iter = list;
  if((size - 1 < pozitie) || (pozitie < 0)){
    return NULL;
  }
  else if(pozitie < (size - 1) / 2){
    for(list_iter = list;cnt != pozitie;cnt++,list_iter = list_iter->urm){
      continue;
    }
  }
  else{
    cnt = size - 1;
    for(list_iter = list->end; cnt != pozitie;cnt--,list_iter = list_iter->ant){
      continue;
    }
  }
  return list_iter;
}

int valoare_pozitie(lista *list, int pozitie, int size)
{
  lista *val = cautare_element_pozitie(list, pozitie, size);
  if(val != NULL){
    return val->val;
  }
  else{
    return -1;
  }
}

void eliminare_element_pozitie(lista **list, int poz, int *size)
{
  if(poz < *size){
    lista *element = cautare_element_pozitie(*list, poz, *size);
    if(poz == 0){
      (*list) = element->urm;
      (*list)->start = *list;
      (*list)->ant = NULL;
    }
    else if(poz == *size - 1){
      (*list)->end = element->ant;
      (element->ant)->urm = NULL;
    }
    else{
      (element->ant)->urm = element->urm;
      (element->urm)->ant = element->ant;
      }
    free(element);
    *size -= 1;
  }
}

void adaugare_element_poz(lista *list, int poz, int*size, int value)
{
  if(poz <= *size)
    {
      if(poz == *size){
	adaugare_element_coada(list, value, size);
      }
      else if(poz == 0){
	adaugare_element_inceput(list, value, size);
      }
      else{
	lista *element = cautare_element_pozitie(list, poz, *size);
	lista *new_value = malloc(sizeof(lista));
	new_value->val = value;
	new_value->urm = element;
	new_value->ant = element->ant;
	new_value->start = list->start;
	new_value->end = list->end;
	(element->ant)->urm = new_value;
	(new_value->ant)->urm = new_value;
	*size += 1;
      }
    }
}
	
int main(void)
{
  int size = 0;
  lista *list_init = initializare(5, &size);
  adaugare_element_coada(list_init, 10, &size);
  list_init = adaugare_element_inceput(list_init, 15, &size);
  //eliminare_element_coada(list_init, &size);
  //afisare(list_init);
  //printf("%d\n", valoare_pozitie(list_init, 0, size));
  // int poz = cautare_element(list_init, 10);
  //printf("%d %d %d\n", valoare_pozitie(list_init, 1, size), valoare_pozitie(list_init, 3, size), valoare_pozitie(list_init, 0, size));
  //printf("%d %p %p\n", cautare_element_pozitie(list_init, 1, size)->val, cautare_element_pozitie(list_init, 1, size), cautare_element_pozitie(list_init, 3, size));
  //eliminare_element_pozitie(&list_init, 0, &size);
  adaugare_element_poz(list_init, 1, &size, 20);
  afisare(list_init);
  //eliberare(list_init, &size);
  return 0;
}

