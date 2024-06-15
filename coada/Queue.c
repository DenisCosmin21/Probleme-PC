#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct node
{
  Element_t value;
  struct node *next;
};
  
struct Queue
{
  struct node *first;
  struct node *last;
};

Queue_t init_que(void)
{
  Queue_t que = malloc(sizeof(struct Queue));
  if(que == NULL){
    return NULL;
  }
  que->first = NULL;
  que->last = NULL;
  return que;
}

Queue_t enque(Queue_t que, Element_t value)
{
  struct node *new = malloc(sizeof(struct node));
  new->value = value;
  new->next = NULL;
  if(que->first == NULL){
    que->first = new;
    que->last = new;
  }
  else{
    que->last->next = new;
    que->last = new;
  }
  return que;
}

Element_t deque(Queue_t que)
{
  if(que->first == NULL){
    return 0;
  }
  else{
    struct node *nod = que->first;
    que->first = que->first->next;
    if(que->first == NULL){
      que->last = NULL;
    }
    Element_t value = nod->value;
    free(nod);
    return value;
  }
}

int destruct(Queue_t que)
{
  if(que->first == NULL && que->last == NULL){
    free(que);
    return 1;
  }
  else{
    return 0;
  }
}
      
