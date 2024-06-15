#ifndef __Stack_t
#define __Stack_t

#include <stdio.h>
#include <stdbool.h>

typedef enum
  {
    Char,
    Int
  }Type_t;

typedef struct
{
  union
  {
    char ch;
    int nr;
  }value;
  Type_t type;
  
}Value_t;

struct Stack
{
  size_t top, max;
  Value_t *values;
};

typedef struct Stack* Stack_t;

void show_elem(Value_t);

Value_t empty_val(void);

Stack_t init_stack(ssize_t);

void push(Stack_t, Value_t);

bool pop(Stack_t, Value_t *);

bool peek(Stack_t, Value_t *);

void destruct(Stack_t);

size_t size(Stack_t);

void show(Stack_t);

int return_value(Value_t);

Value_t *top_element(Stack_t);

bool rotate_stack(Stack_t);
#endif
