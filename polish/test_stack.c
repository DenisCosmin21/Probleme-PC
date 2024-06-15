#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
int main(void)
{
  Stack_t st = init_stack(0);
  Value_t val;
  val.type = Int;
  val.value.nr = 10;
  push(st, val);
  val.value.nr = 5;
  push(st, val);
  Stack_t sti = init_stack(0);
  pop(st, top_element(sti));
  show(sti);
}
