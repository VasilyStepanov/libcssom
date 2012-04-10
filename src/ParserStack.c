#include "ParserStack.h"

#include "CSSOM.h"
#include "Stack.h"
#include "Stack.c"
#include "memory.h"



struct _CSSOM_ParserState {
  int dummy;
};



static void ParserState_free(struct _CSSOM_ParserState *state) {
  CSSOM_free(state);
}



CSSOM_STACK_DECLARE(struct _CSSOM_ParserState *, ParserState)

CSSOM_STACK_DEFINE(struct _CSSOM_ParserState *, ParserState)



struct _CSSOM_ParserStack {
  const CSSOM *cssom;
  CSSOM_Stack_ParserState *state;
};



CSSOM_ParserStack* CSSOM_ParserStack_alloc(const CSSOM *cssom) {
  CSSOM_Stack_ParserState *state;
  CSSOM_ParserStack *stack;

  state = CSSOM_Stack_ParserState_alloc();
  if (state == NULL) return NULL;

  stack = (CSSOM_ParserStack*)CSSOM_malloc(sizeof(CSSOM_ParserStack));
  if (stack == NULL) {
    CSSOM_Stack_ParserState_free(state);
    return NULL;
  }

  stack->cssom = cssom;
  stack->state = state;

  return stack;
}



void CSSOM_ParserStack_free(CSSOM_ParserStack *stack) {
  struct _CSSOM_ParserState **it;

  for (
    it = CSSOM_Stack_ParserState_top(stack->state);
    it != NULL;
    CSSOM_Stack_ParserState_pop(stack->state),
    it = CSSOM_Stack_ParserState_top(stack->state))
  {
    ParserState_free(*it);
  }

  CSSOM_Stack_ParserState_free(stack->state);
  CSSOM_free(stack);
}



void CSSOM_ParserStack_pop(CSSOM_ParserStack *stack) {
  CSSOM_Stack_ParserState_pop(stack->state);
}



int CSSOM_ParserStack_error(const CSSOM_ParserStack *stack,
  const SAC_Error *error)
{
  return CSSOM__error(stack->cssom, error);
}
