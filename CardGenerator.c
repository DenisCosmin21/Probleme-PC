#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

typedef struct
{
  int *values;
  int size;
  int max_size;
}vector;

void show_vector(vector arr)
{
  for(int i = 0;i < arr.size;i++){
    printf("%d ", arr.values[i]);
  }
  printf("\n");
}

vector vec_new(void)
{
  return (vector){.values = NULL, .size = 0, .max_size = 0};
}

void vec_free(vector v){
  free(v.values);
}

int det_size(int old_size)
{
  if(old_size < 4){
    return old_size + 1;
  }
  else{
    return old_size / 2 * 3;
  }
}

void alloc_vector(vector *v, int new_capacity)
{
  assert(v->max_size <= new_capacity);
  v->values = realloc(v->values, new_capacity * sizeof(int));
  assert(v->values != NULL);
  v->max_size = new_capacity;
}

void reserve(vector *arr, int dimensiune)
{
  printf("%d ", arr->max_size);
  arr->values = realloc(arr->values, (arr->max_size + dimensiune) * sizeof(int));
  assert(arr->values != NULL);
  
  for(int i = 0;i < dimensiune;i++){
    arr->values[arr->max_size + i] = 0;
  }
  arr->max_size += dimensiune;
}

vector *back_inserter(vector *arr)
{
  return arr;
}

void push_back(vector *arr, int value)
{
  if(arr->size == arr->max_size){
    alloc_vector(arr, det_size(arr->max_size));
  }
  arr->values[arr->size] = value;
  arr->size++;
}

int *begin(vector arr)
{
  assert(arr.values != NULL && "uninitialized array");
  return &arr.values[0];
}

int *end(vector arr)
{
  assert(arr.values != NULL && "uninitialized array");
  return &arr.values[arr.size - 1];
}
	  
void copy(int *start, int *end, vector *where)
{
  assert(start <= end && "start location is bigger then end location");
  for(;start <= end;start++){
    if(where->size == where->max_size){
      alloc_vector(where, det_size(where->max_size));
    }
    push_back(where, *start);
  }
}

vector initialize_card_stack(int card_stack_count)
{
  vector card_stack = vec_new();
  int poz = 0;
  reserve(&card_stack, card_stack_count);
  srand(time(NULL));
  for(int i = 2;i <= 14;i++){
    for(int j = 0;j < 4;j++){
      do{
	poz = rand() % 52 + 1;
      }while(card_stack.values[poz - 1] != 0);
      card_stack.values[poz - 1] = i;
    }
  }
  card_stack.size = 52;
  return card_stack;
}

int main(int argc, char **argv)
{
  int card_stack_count = 52;//Intr-un pachet de blackJack sunt 52 de carti defapt. lista_carti = {2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A}, model_carti = {inima rosie, inima neagra, trefla, romb}. stacks_cout = |pachet| * |model_carti| = 13 * 4 = 52
  //Exemplu c++ folosind std vector :
  /*constexpr auto stacks_count = 5;

card_stack_.reserve(card_stack_.size() * stacks_count);
// clone the cards for better distribution
for (auto i{0}; i < stacks_count; i++) {
    std::copy(std::begin(card_stack_), std::begin(card_stack_ + 32), std::back_inserter(card_stack_));
}
  */
  
  int stacks = 5;
  vector card_stack = initialize_card_stack(card_stack_count);
  reserve(&card_stack, stacks * card_stack_count);
  
  for(int i = 0;i < stacks;i++){
    copy(begin(card_stack), begin(card_stack) + card_stack_count - 1, back_inserter(&card_stack));
    }
  
  show_vector(card_stack);
  vec_free(card_stack);
  return 0;
}
    

  
