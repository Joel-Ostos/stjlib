#ifndef REGEX_H
#define REGEX_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "dynamic_array.h"
#include "stack.h"


enum  op {UNION, KLEENE, CONCAT,  OP_PAR, CL_PAR, NONE};

typedef char* regex;

enum op getop(char x) 
{
  switch(x) {
    case '(': return OP_PAR;
    case '*': return KLEENE;
    case '?': return CONCAT;
    case '+': return UNION;
    case ')': return CL_PAR;
  }
  return NONE;
}

void reordenate_stack(char x, char** s, char** q) 
{
  if (*(s) == NULL || stack_size(*s) == 0) {
    stack_push(*s, x);
    return;
  }

  enum op top = getop(stack_top(*s));
  enum op oper = getop(x);

  if (oper == OP_PAR) {
    stack_push(*s, x);
    return;
  }

  if (oper == CL_PAR) {
    while (top != OP_PAR && stack_size(*s) != 0) {
      queue_push(*q, stack_pop(*s));
      char operand = stack_top(*s);
      top = getop(operand);
    }
    if (top == OP_PAR) {
      stack_pop(*s);
      return;
    }
    printf("Invalid regex sequence");
    exit(1);
  }

  while (oper >= top && stack_size(*s) != 0) {
    if (top == OP_PAR) {
      stack_push(*s, x);
      return;
    };
    queue_push(*q, stack_pop(*s));
    top = getop(stack_top(*s));
  }
  stack_push(*s, x);
}

regex shunting_postfix(regex src) 
{
  regex output = {0};
  char* opts = {0};
  char* characters = {0};
  size_t sz = strlen(src);

  for (size_t i = 0; i < sz; i++) {
    if (isalnum(src[i])) queue_push(characters, src[i]);
    else if (getop(src[i]) != NONE) reordenate_stack(src[i], &opts, &characters);
  }

  while (!(queue_empty(characters))) {
    da_append(output, queue_pop(characters));
  }

  while (!(stack_empty(opts))) {
    da_append(output, stack_pop(opts));
  }

  return output;
}


regex shunting_prefix(regex* src) 
{
  regex output = (regex) "";
  char* opts = {0};
  char* characters = {0};
  return output;
}

#endif
