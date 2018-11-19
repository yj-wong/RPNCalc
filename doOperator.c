#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_diff(struct tokenStack *stack);
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_if(struct tokenStack *stack);
static int op_modquot(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);
static int op_rot(struct tokenStack *stack);
static int op_rotminus(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);
static int op_s(struct tokenStack *stack);
static int op_size(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"MOD", op_mod},
  {"IF", op_if},
  {"MODQUOT", op_modquot},
  {"SWAP", op_swap},
  {"HELP", op_help},
  {"ROT", op_rot},
  {"ROTMINUS", op_rotminus},
  {"DROP", op_drop},
  {"S", op_s},
  {"size", op_size},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};

/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  int v;
  struct lexToken *t;

  t = popTokenStack(s);
  v = atoi(t->symbol);

  freeToken(t);
  return v;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
  struct lexToken *t;

  t = intToken(v);
  pushTokenStack(s, t);
}

int doOperator(struct tokenStack *stack, char *o)
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t;
  t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1+v2);

  return(0);
}

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1-v2);

  return(0);
}

static int op_product(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1*v2);

  return(0);
}

static int op_quotient(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1/v2);

  return(0);
}

static int op_gt(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);

  if(v1 > v2) {
    pushInt(stack, 1);
  } else {
    pushInt(stack, 0);
  }

  return(0);
}

static int op_lt(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);

  if(v1 < v2) {
    pushInt(stack, 1);
  } else {
    pushInt(stack, 0);
  }

  return(0);
}

static int op_ge(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);

  if(v1 >= v2) {
    pushInt(stack, 1);
  } else {
    pushInt(stack, 0);
  }

  return(0);
}

static int op_le(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);

  if(v1 <= v2) {
    pushInt(stack, 1);
  } else {
    pushInt(stack, 0);
  }

  return(0);
}

static int op_eq(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);

  if(v1 == v2) {
    pushInt(stack, 1);
  } else {
    pushInt(stack, 0);
  }

  return(0);
}

static int op_mod(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);

  return(0);
}

static int op_if(struct tokenStack *stack)
{
  return(0);
}

static int op_modquot(struct tokenStack *stack)
{
  int v1;
  int v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1%v2);
  pushInt(stack, v1/v2);

  return(0);
}

static int op_swap(struct tokenStack *stack)
{
  int v1;
  int v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v2);
  pushInt(stack, v1);

  return(0);
}

static int op_help(struct tokenStack *stack)
{
  printf("quit");
  printf("print");
  printf("dump");
  printf("\n+ (n1 n2 - add)");
  printf("\n- (n1 n2 — diff)");
  printf("\n* (n1 n2 — product) - push n1*n2");
  printf("\n/ (n1 n2 — quotient) - push n1/n2");
  printf("\nGT (n1 n2 — gt) -push 1 if n1 > n2 and 0 otherwise");
  printf("\nLT (n1 n2 — lt) -push 1 if n1 < n2 and 0 otherwise");
  printf("\nGE (n1 n2 — ge) -push 1 if n1 >= n2 and 0 otherwise");
  printf("\nLE (n1 n2 — le) -push 1 if n1 <= n2 and 0 otherwise");
  printf("\nEQ (n1 n2 — eq) -push 1 if n1 == n2 and 0 otherwise");
  printf("\nMOD (n1 - n1 n1) - push two copies of n1 onto the stack");
  printf("\nIF (n1 n2 v — x) - if v is not zero then push n1 otherwise n2");
  printf("\nMODQUOT (n1 n2 — rem quotient) - push remainder then quotient");
  printf("\nSWAP (n1 n2 — n2 n1) - swap the order of the top two elements on the stack");
  printf("\nHELP (—) - print out all commands plus a line of documentation");
  printf("\nROT (n1 n2 n3 — n2 n3 n1) - rotate top 3 elements on the stack");
  printf("\nROTMINUS (n1 n2 n3 — n3 n1 n2) - rotate top 3 elements on the stack");
  printf("\n\nDROP (n1 — ) - drop the top element off of the stack");
  printf("\nS (—) - print all elements on the stack non destructively");

  return(0);
}

static int op_rot(struct tokenStack *stack)
{
  int v1;
  int v2;
  int v3;

  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v2);
  pushInt(stack, v3);
  pushInt(stack, v1);

  return(0);
}

static int op_rotminus(struct tokenStack *stack)
{
  int v1;
  int v2;
  int v3;

  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v3);
  pushInt(stack, v1);
  pushInt(stack, v2);

  return(0);
}

static int op_drop(struct tokenStack *stack)
{
  popInt(stack);
  return(0);
}

static int op_s(struct tokenStack *stack)
{
  struct tokenStack *s = createTokenStack();
  struct lexToken *t;
  int size = stack->size;
  int i;

  for (i = 0; i < size; i++) {
    t = popTokenStack(stack);
    printToken(stdout, t);
    pushTokenStack(s, t);
  }
  for (i = 0; i < size; i++) {
    t = popTokenStack(s);
    pushTokenStack(stack, t);
  }

  free(s);
  return(0);
}

static int op_size(struct tokenStack *stack)
{
  printf("%d\n", stack->size);
  return(0);
}
