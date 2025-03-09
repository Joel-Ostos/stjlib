#include "queue.h"
#include "stack.h"

int main() {
  int* q = {0};
  int* s = {0};
  stack_push(s, 21);
  stack_push(s, 22);
  stack_push(s, 23);
  stack_push(s, 24);
  printf("%d ,", stack_pop(s));
  printf("%d ,", stack_pop(s));
  printf("%d ,", stack_pop(s));
  printf("%d ,", stack_pop(s));
  printf("%d ,", stack_pop(s));
  printf("%d ,", stack_pop(s));
  printf("%d ",  stack_pop(s));

  queue_push(q, 1);
  queue_push(q, 2);
  queue_push(q, 4);
  queue_push(q, 4);
  queue_push(q, 4);
  queue_push(q, 4);
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
  printf("%d ", queue_pop(q));
}
