#include "ParserStack.h"

#include "CSSMediaRule.h"
#include "CSSOM.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"
#include "Stack.h"
#include "Stack.c"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "memory.h"

#include <cssom/CSSStyleRule.h>

#include <sacc.h>

#include <assert.h>



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
    struct _CSSOM_ParserState *);

  CSSOM_CSSStyleRule* (*appendCSSStyleRule)(
    struct _CSSOM_ParserState *, const SAC_Selector *[]);

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
  CSSOM_free(state);
}



static CSSOM_CSSProperty* ParserState_setProperty(
  struct _CSSOM_ParserState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return state->vtable->setProperty(state, property, value, important);
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
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule **cssRule;
};



static CSSOM_CSSPageRule* ParserCSSRuleCatcherState_appendCSSPageRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSPageRule__alloc(state->styleSheet, selectors);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSMediaRule* ParserCSSRuleCatcherState_appendCSSMediaRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state)
{
  CSSOM_CSSMediaRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSMediaRule__alloc(state->styleSheet);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSStyleRule* ParserCSSRuleCatcherState_appendCSSStyleRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSStyleRule__alloc(state->styleSheet, selectors);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static struct _CSSOM_ParserState_vtable ParserCSSRuleCatcherState_vtable = {
  NULL,
  (CSSOM_CSSPageRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSRuleCatcherState_appendCSSPageRule,
  (CSSOM_CSSMediaRule* (*)(struct _CSSOM_ParserState *))
  ParserCSSRuleCatcherState_appendCSSMediaRule,
  (CSSOM_CSSStyleRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSRuleCatcherState_appendCSSStyleRule
};



static struct _CSSOM_ParserCSSRuleCatcherState* ParserCSSRuleCatcherState_alloc(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = (struct _CSSOM_ParserCSSRuleCatcherState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSRuleCatcherState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSRuleCatcherState_vtable);
  state->styleSheet = styleSheet;
  state->cssRule = cssRule;

  return state;
}



/**
 * CSSStyleSheet
 */

struct _CSSOM_ParserCSSStyleSheetState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSStyleSheet *styleSheet;
};



static CSSOM_CSSPageRule* ParserCSSStyleSheetState_appendCSSPageRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_Selector *selectors[])
{
  return CSSOM_CSSStyleSheet__appendCSSPageRule(state->styleSheet, selectors);
}



static CSSOM_CSSMediaRule* ParserCSSStyleSheetState_appendCSSMediaRule(
  struct _CSSOM_ParserCSSStyleSheetState *state)
{
  return CSSOM_CSSStyleSheet__appendCSSMediaRule(state->styleSheet);
}



static CSSOM_CSSStyleRule* ParserCSSStyleSheetState_appendCSSStyleRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_Selector *selectors[])
{
  return CSSOM_CSSStyleSheet__appendCSSStyleRule(state->styleSheet, selectors);
}



static struct _CSSOM_ParserState_vtable
ParserCSSStyleSheetState_vtable = {
  NULL,
  (CSSOM_CSSPageRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSStyleSheetState_appendCSSPageRule,
  (CSSOM_CSSMediaRule* (*)(struct _CSSOM_ParserState *))
  ParserCSSStyleSheetState_appendCSSMediaRule,
  (CSSOM_CSSStyleRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSStyleSheetState_appendCSSStyleRule
};



static struct _CSSOM_ParserCSSStyleSheetState*
ParserCSSStyleSheetState_alloc(CSSOM_CSSStyleSheet *styleSheet)
{
  struct _CSSOM_ParserCSSStyleSheetState *state;

  state = (struct _CSSOM_ParserCSSStyleSheetState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSStyleSheetState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSStyleSheetState_vtable);
  state->styleSheet = styleSheet;

  return state;
}



/**
 * CSSPageRule
 */

struct _CSSOM_ParserCSSPageRuleState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSPageRule *cssRule;
};



static struct _CSSOM_ParserState_vtable ParserCSSPageRuleState_vtable = {
  NULL,
  NULL,
  NULL,
  NULL
};



static struct _CSSOM_ParserCSSPageRuleState* ParserCSSPageRuleState_alloc(
  CSSOM_CSSPageRule *cssRule)
{
  struct _CSSOM_ParserCSSPageRuleState *state;

  state = (struct _CSSOM_ParserCSSPageRuleState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSPageRuleState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSPageRuleState_vtable);
  state->cssRule = cssRule;

  return state;
}



/**
 * CSSMediaRule
 */

struct _CSSOM_ParserCSSMediaRuleState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSMediaRule *cssRule;
};



static struct _CSSOM_ParserState_vtable ParserCSSMediaRuleState_vtable = {
  NULL,
  NULL,
  NULL,
  NULL
};



static struct _CSSOM_ParserCSSMediaRuleState* ParserCSSMediaRuleState_alloc(
  CSSOM_CSSMediaRule *cssRule)
{
  struct _CSSOM_ParserCSSMediaRuleState *state;

  state = (struct _CSSOM_ParserCSSMediaRuleState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSMediaRuleState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSMediaRuleState_vtable);
  state->cssRule = cssRule;

  return state;
}



/**
 * CSSStyleRule
 */

struct _CSSOM_ParserCSSStyleRuleState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSStyleRule *cssRule;
};



static CSSOM_CSSProperty* ParserCSSStyleRuleState_setProperty(
  struct _CSSOM_ParserCSSStyleRuleState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return CSSOM_CSSStyleDeclaration__setProperty(
    CSSOM_CSSStyleRule_style(state->cssRule),
    property, value, important);
}



static struct _CSSOM_ParserState_vtable ParserCSSStyleRuleState_vtable = {
  (CSSOM_CSSProperty* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_LexicalUnit *, SAC_Boolean))
  ParserCSSStyleRuleState_setProperty,
  NULL,
  NULL,
  NULL
};



static struct _CSSOM_ParserCSSStyleRuleState* ParserCSSStyleRuleState_alloc(
  CSSOM_CSSStyleRule *cssRule)
{
  struct _CSSOM_ParserCSSStyleRuleState *state;

  state = (struct _CSSOM_ParserCSSStyleRuleState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSStyleRuleState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSStyleRuleState_vtable);
  state->cssRule = cssRule;

  return state;
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



CSSOM_CSSProperty* CSSOM_ParserStack_setProperty(CSSOM_ParserStack *stack,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return ParserState_setProperty(*CSSOM_Stack_ParserState_top(stack->state),
    property, value, important);
}



CSSOM_CSSRule** CSSOM_ParserStack_pushCSSRuleCatcher(CSSOM_ParserStack *stack,
  CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = ParserCSSRuleCatcherState_alloc(NULL, cssRule);
  if (state == NULL) return NULL;

  if (CSSOM_Stack_ParserState_push(stack->state,
    (struct _CSSOM_ParserState*)state) == NULL)
  {
    ParserState_free((struct _CSSOM_ParserState*)state);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleSheet* CSSOM_ParserStack_pushCSSStyleSheet(
  CSSOM_ParserStack *stack, CSSOM_CSSStyleSheet *styleSheet)
{
  struct _CSSOM_ParserCSSStyleSheetState *state;

  state = ParserCSSStyleSheetState_alloc(styleSheet);
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
