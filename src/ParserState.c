#include "ParserState.h"

#include "Stack.h"
#include "Stack.c"
#include "memory.h"



struct _CSSOM_ParserStateItem {
  int dummy;
};



static void ParserStateItem_free(struct _CSSOM_ParserStateItem *item) {
  CSSOM_free(item);
}



CSSOM_STACK_DECLARE(struct _CSSOM_ParserStateItem *, ParserStateItem)

CSSOM_STACK_DEFINE(struct _CSSOM_ParserStateItem *, ParserStateItem)



struct _CSSOM_ParserState {
  const CSSOM *cssom;
  CSSOM_Stack_ParserStateItem *stack;
};



CSSOM_ParserState* CSSOM_ParserState_alloc(const CSSOM *cssom) {
  CSSOM_Stack_ParserStateItem *stack;
  CSSOM_ParserState *state;

  stack = CSSOM_Stack_ParserStateItem_alloc();
  if (stack == NULL) return NULL;

  state = (CSSOM_ParserState*)CSSOM_malloc(sizeof(CSSOM_ParserState));
  if (state == NULL) {
    CSSOM_Stack_ParserStateItem_free(stack);
    return NULL;
  }

  state->cssom = cssom;
  state->stack = stack;

  return state;
}



void CSSOM_ParserState_free(CSSOM_ParserState *state) {
  struct _CSSOM_ParserStateItem **it;

  for (
    it = CSSOM_Stack_ParserStateItem_top(state->stack);
    it != NULL;
    CSSOM_Stack_ParserStateItem_pop(state->stack),
    it = CSSOM_Stack_ParserStateItem_top(state->stack))
  {
    ParserStateItem_free(*it);
  }

  CSSOM_Stack_ParserStateItem_free(state->stack);
  CSSOM_free(state);
}
