#include <stdio.h>
#include "Queue.h"

int main(void)
{
  Queue_t que = init_que();
  que = enque(que, 5);
  printf("%d ", deque(que));
  destruct(que);
  return 0;
}
