#ifndef LIST_TP

#define LIST_TP

typedef struct lista_t * lista;

typedef struct
{
  int val;
  size_t prioritate;
}el;

lista initialize_list();

int append_inside(lista, lista, el);

lista append_front(lista, el);

lista eliberare(lista);

lista vecin(lista);

size_t get_priority(lista);

void show_elems(lista);

lista pop_list(lista, el*);

#endif
  
