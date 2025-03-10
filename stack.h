#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define INIT_SIZE 	10
#define GROW_FACTOR 	2

typedef struct Stack Stack;

struct Stack {
  size_t cap;
  size_t used;
};

#define stack_cast(x) ((Stack*) x - 1)
#define stack_push(x, v) !(x) ?  x = stack_init(x, sizeof(*x)), stack_put(x, v) : stack_put(x,v) 
#define stack_put(x, v) stack_check(stack_cast(x)) ? (x)[stack_cast(x)->used] = v, stack_cast(x)->used++ : (stack_grow(x, sizeof(x[0])), (x)[stack_cast(x)->used] = v, stack_cast(x)->used++)
#define stack_pop(x)     !(x)  ? printf("Unitialized stack\n"): stack_delete(x) 
#define stack_top(x)     stack_cast(x)->used == 0 ? :  (x)[stack_cast(x)->used-1]
#define stack_delete(x)  stack_cast(x)->used == 0 ? : (stack_cast(x)->used--, (x)[stack_cast(x)->used])
#define stack_size(x)  	 stack_cast(x)->used
#define stack_empty(x)   !(x) ? true: stack_cast(x)->used == 0

bool stack_check(Stack* x) 
{
  return !(x->used == (x->cap-1));
}

void* stack_init(void* x, size_t elem_size) 
{
  void* b = malloc(INIT_SIZE * elem_size + sizeof(Stack));
  ((Stack*)b)->cap = INIT_SIZE;
  ((Stack*)b)->used = 0;
  b = (Stack*) b + sizeof(Stack);
  assert(b);
  return b;
}

void* stack_grow(void* x, size_t elem_size) 
{
  void* b = realloc(stack_cast(x), ((Stack*)b)->cap * GROW_FACTOR * elem_size + sizeof(Stack));
  ((Stack*)b)->cap = INIT_SIZE * GROW_FACTOR;
  b = (Stack*) b + sizeof(Stack);
  assert(b);
  return b;
}

#endif
