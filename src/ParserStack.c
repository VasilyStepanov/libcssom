#include "ParserStack.h"

#include "CSSOM.h"
#include "Stack.h"
#include "Stack.c"
#include "memory.h"



struct _CSSOM_ParserState;



struct _CSSOM_ParserState_vtable {

  CSSOM_CSSProperty* (*setProperty)(
    struct _CSSOM_ParserState *,
    const SAC_STRING,
    const SAC_LexicalUnit *,
    SAC_Boolean);

  CSSOM_CSSPageRule* (*appendCSSPageRule)(
    struct _CSSOM_ParserState *, const SAC_Selector *[]);

  CSSOM_CSSMediaRule* (*appendCSSMediaRule)(
    struct _CSSOM_ParserState *state);

  CSSOM_CSSStyleRule* (*appendCSSStyleRule)(
    struct _CSSOM_ParserState *, const SAC_Selector *[]);

  void (*free)(struct _CSSOM_ParserState *);

};



struct _CSSOM_ParserState {
  struct _CSSOM_ParserState_vtable *vtable;
};



static void ParserState_ctor(struct _CSSOM_ParserState *state,
  struct _CSSOM_ParserState_vtable *vtable)
{
  state->vtable = vtable;
}



static void ParserState_free(struct _CSSOM_ParserState *state) {
  state->vtable->free(state);
}



static CSSOM_CSSProperty* ParserState_setProperty(
  struct _CSSOM_ParserState *state,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return state->vtable->setProperty(state, propertyName, value, important);
}



static CSSOM_CSSPageRule* ParserState_appendCSSPageRule(
  struct _CSSOM_ParserState *state, const SAC_Selector *selectors[])
{
  return state->vtable->appendCSSPageRule(state, selectors);
}



static CSSOM_CSSMediaRule* ParserState_appendCSSMediaRule(
  struct _CSSOM_ParserState *state)
{
  return state->vtable->appendCSSMediaRule(state);
}



static CSSOM_CSSStyleRule* ParserState_appendCSSStyleRule(
  struct _CSSOM_ParserState *state, const SAC_Selector *selectors[])
{
  return state->vtable->appendCSSStyleRule(state, selectors);
}



/**
 * CSSRuleCatcher
 */

struct _CSSOM_ParserCSSRuleCatcherState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSRule **cssRule;
};



static struct _CSSOM_ParserState_vtable ParserCSSRuleCatcherState_vtable = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};



static struct _CSSOM_ParserCSSRuleCatcherState* ParserCSSRuleCatcherState_alloc(
  CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = (struct _CSSOM_ParserCSSRuleCatcherState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSRuleCatcherState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSRuleCatcherState_vtable);
  state->cssRule = cssRule;

  return state;
}



/**
 * CSSStyleSheetHolder
 */

struct _CSSOM_ParserCSSStyleSheetHolderState {
  struct _CSSOM_ParserState super;
};



struct _CSSOM_ParserCSSStyleSheetHolderState*
ParserCSSStyleSheetHolderState_alloc(CSSOM_CSSStyleSheet *styleSheet);



/**
 * CSSPageRule
 */

struct _CSSOM_ParserCSSPageRuleState {
  struct _CSSOM_ParserState super;
};



struct _CSSOM_ParserCSSPageRuleState* ParserCSSPageRuleState_alloc(
  CSSOM_CSSPageRule *cssRule);



/**
 * CSSMediaRule
 */

struct _CSSOM_ParserCSSMediaRuleState {
  struct _CSSOM_ParserState super;
};



struct _CSSOM_ParserCSSMediaRuleState* ParserCSSMediaRuleState_alloc(
  CSSOM_CSSMediaRule *cssRule);



/**
 * CSSStyleRule
 */

struct _CSSOM_ParserCSSStyleRuleState {
  struct _CSSOM_ParserState super;
};



struct _CSSOM_ParserCSSStyleRuleState* ParserCSSStyleRuleState_alloc(
  CSSOM_CSSStyleRule *cssRule);



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



CSSOM_CSSProperty* CSSOM_ParserStack_setProperty(CSSOM_ParserStack *stack,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return ParserState_setProperty(*CSSOM_Stack_ParserState_top(stack->state),
    propertyName, value, important);
}



CSSOM_CSSRule** CSSOM_ParserStack_pushCSSRuleCatcher(CSSOM_ParserStack *stack,
  CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = ParserCSSRuleCatcherState_alloc(cssRule);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleSheet* CSSOM_ParserStack_pushCSSStyleSheetHolder(
  CSSOM_ParserStack *stack, CSSOM_CSSStyleSheet *styleSheet)
{
  struct _CSSOM_ParserCSSStyleSheetHolderState *state;

  state = ParserCSSStyleSheetHolderState_alloc(styleSheet);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return styleSheet;
}



CSSOM_CSSPageRule* CSSOM_ParserStack_pushCSSPageRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;
  struct _CSSOM_ParserCSSPageRuleState *state;

  cssRule = ParserState_appendCSSPageRule(
    *CSSOM_Stack_ParserState_top(stack->state), selectors);
  if (cssRule == NULL) return NULL;

  state = ParserCSSPageRuleState_alloc(cssRule);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSMediaRule* CSSOM_ParserStack_pushCSSMediaRule(
  CSSOM_ParserStack *stack)
{
  CSSOM_CSSMediaRule *cssRule;
  struct _CSSOM_ParserCSSMediaRuleState *state;

  cssRule = ParserState_appendCSSMediaRule(
    *CSSOM_Stack_ParserState_top(stack->state));
  if (cssRule == NULL) return NULL;

  state = ParserCSSMediaRuleState_alloc(cssRule);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleRule* CSSOM_ParserStack_pushCSSStyleRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;
  struct _CSSOM_ParserCSSStyleRuleState *state;

  cssRule = ParserState_appendCSSStyleRule(
    *CSSOM_Stack_ParserState_top(stack->state), selectors);
  if (cssRule == NULL) return NULL;

  state = ParserCSSStyleRuleState_alloc(cssRule);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return cssRule;
}
