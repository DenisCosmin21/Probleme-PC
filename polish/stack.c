#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

Value_t empty_val(void)
{
  return (Value_t){.value.ch = '\0', .type = Char};
}

Stack_t init_stack(ssize_t stack_size)
{
  assert(stack_size >= 0);
  Stack_t new_stack = malloc(sizeof(struct Stack));
  assert(new_stack != NULL); 
  new_stack->top = 0;
  new_stack->max = stack_size;
  
  if(stack_size == 0){
    new_stack->values = NULL;
  }
  else{
    new_stack->values = malloc(stack_size * sizeof(Value_t));
    assert(new_stack->values != NULL);
  }
  return new_stack;
}

void alloc(Stack_t stack)
{
  stack->max = (stack->max < 4) ? (stack->max + 1) : (stack->max / 2 * 3);
  stack->values = realloc(stack->values, stack->max * sizeof(Value_t));
  assert(stack->values != NULL);
}

void push(Stack_t stack, Value_t value)
{
  if(size(stack) == stack->max){
    alloc(stack);
  }
  assert(size(stack) < stack->max);
  
  stack->values[size(stack)] = value;
  stack->top++;
}

bool peek(Stack_t stack, Value_t *value)
{
  if(stack->values == NULL){
    if(value != NULL){
      *value = empty_val();
    }
    return false;
  }
  else if(size(stack) <= 0){
    return false;
  }
  if(value != NULL){
    *value = stack->values[size(stack) - 1];
  }
  return true;
}

bool pop(Stack_t stack, Value_t *value)
{
  if(peek(stack, value) == false){
    return false;
  }
  else{
    stack->top--;
    return true;
  }
}

void destruct(Stack_t stack)
{
  free(stack->values);
  free(stack);
}

size_t size(Stack_t stack)
{
  return stack->top;
}

void show_elem(Value_t val)
{
  switch(val.type){
  case Char:
    printf("%c", val.value.ch);
    break;
  case Int:
    printf("%d", val.value.nr);
    break;
  }
}

void show(Stack_t stack)
{
  for(int i = 0;i < size(stack);i++){
    show_elem(stack->values[i]);
  }
  printf("\n");
}

int return_value(Value_t val)
{
  switch(val.type){
  case Char:
    return val.value.ch;
    break;
  case Int:
    return val.value.nr;
    break;
  default:
    return 0;
  }
}

Value_t *top_element(Stack_t stack)
{
  if(size(stack) == stack->max){
    alloc(stack);
  }
  stack->top++;
  return &(stack->values[size(stack) - 1]);
}

bool rotate_stack(Stack_t stack)
{
  if(size(stack) == 0){
    return false;
  }
  size_t left = 0;
  size_t right = size(stack) - 1;
  Value_t aux;
  while(left < right){
    aux = stack->values[left];
    stack->values[left] = stack->values[right];
    stack->values[right] = aux;
    left++;
    right--;
  }
  return true;
}
