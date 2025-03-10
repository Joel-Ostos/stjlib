#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define INIT_SIZE 	10
#define GROW_FACTOR 	2

typedef struct Queue Queue;

struct Queue {
  size_t cap;
  size_t used;
  int idx;
};

#define queue_cast(x) ((Queue*) x - 1)
#define queue_push(x, v) !(x) ?  x = queue_init(x, sizeof(*x)), queue_put(x, v) : queue_put(x,v) 
#define queue_put(x, v) check(queue_cast(x)) ? (x)[queue_cast(x)->used] = v, queue_cast(x)->used++ : (queue_grow(x, sizeof(x[0])), (x)[queue_cast(x)->used] = v, queue_cast(x)->used++)
#define queue_pop(x)   !(x)  ? printf("Unitialized queue\n"): queue_delete(x) 
#define queue_delete(x)  queue_cast(x)->idx == queue_cast(x)->used ? (printf("Empty queue\n"), -1) :  (queue_cast(x)->idx++, (x)[queue_cast(x)->idx-1])
#define queue_empty(x)  queue_cast(x)->idx == queue_cast(x)->used

bool check(Queue* x) 
{
  return !(x->used == (x->cap-1));
}

void* queue_init(void* x, size_t elem_size) 
{
  void* b = malloc(INIT_SIZE * elem_size + sizeof(Queue));
  ((Queue*)b)->cap = INIT_SIZE;
  ((Queue*)b)->used = 0;
  ((Queue*)b)->idx = 0;
  b = (Queue*) b + sizeof(Queue);
  assert(b);
  return b;
}

void* queue_grow(void* x, size_t elem_size) 
{
  void* b = realloc(queue_cast(x), ((Queue*)b)->cap * GROW_FACTOR * elem_size + sizeof(Queue));
  ((Queue*)b)->cap = INIT_SIZE * GROW_FACTOR;
  b = (Queue*) b + sizeof(Queue);
  assert(b);
  return b;
}

#endif
