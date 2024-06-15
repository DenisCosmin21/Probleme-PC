#ifndef __Queue
#define __Queue

typedef unsigned Element_t;

typedef struct Queue * Queue_t;

Queue_t init_que();

Queue_t enque(Queue_t, Element_t);

Element_t deque(Queue_t);

int destruct(Queue_t);
#endif
