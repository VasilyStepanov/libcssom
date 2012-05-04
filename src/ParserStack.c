#include "ParserStack.h"

#include "CSSFontFaceRule.h"
#include "CSSImportRule.h"
#include "CSSMediaRule.h"
#include "CSSNamespaceRule.h"
#include "CSSOM.h"
#include "CSSPageRule.h"
#include "CSSRuleList.h"
#include "CSSStyleRule.h"
#include "Stack.h"
#include "Stack.c"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "ParserStats.h"
#include "memory.h"

#include <cssom/CSSStyleRule.h>

#include <sacc.h>

#include <assert.h>



struct _CSSOM_ParserState;



struct _CSSOM_ParserState_vtable {

  CSSOM_CSSPropertyValue* (*setProperty)(
    struct _CSSOM_ParserState *,
    const SAC_STRING,
    const SAC_LexicalUnit *,
    SAC_Boolean);

  CSSOM_CSSPageRule* (*appendCSSPageRule)(
    struct _CSSOM_ParserState *, const SAC_Selector *[]);

  CSSOM_CSSMediaRule* (*appendCSSMediaRule)(
    struct _CSSOM_ParserState *, const SAC_MediaQuery *media[]);

  CSSOM_CSSStyleRule* (*appendCSSStyleRule)(
    struct _CSSOM_ParserState *, const SAC_Selector *[]);

  CSSOM_CSSNamespaceRule* (*appendCSSNamespaceRule)(
    struct _CSSOM_ParserState *, const SAC_STRING prefix, const SAC_STRING uri);

  CSSOM_CSSFontFaceRule* (*appendCSSFontFaceRule)(
    struct _CSSOM_ParserState *);

  CSSOM_CSSImportRule* (*appendCSSImportRule)(
    struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_STRING,
    const SAC_MediaQuery *[], const SAC_STRING);

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



static CSSOM_CSSPropertyValue* ParserState_setProperty(
  struct _CSSOM_ParserState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return state->vtable->setProperty(state, property, value, important);
}



static CSSOM_CSSImportRule* ParserState_appendCSSImportRule(
  struct _CSSOM_ParserState *state,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *media[], const SAC_STRING defaultNamepaceURI)
{
  return state->vtable->appendCSSImportRule(state,
    base, uri, media, defaultNamepaceURI);
}



static CSSOM_CSSNamespaceRule* ParserState_appendCSSNamespaceRule(
  struct _CSSOM_ParserState *state,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  return state->vtable->appendCSSNamespaceRule(state, prefix, uri);
}



static CSSOM_CSSPageRule* ParserState_appendCSSPageRule(
  struct _CSSOM_ParserState *state, const SAC_Selector *selectors[])
{
  return state->vtable->appendCSSPageRule(state, selectors);
}



static CSSOM_CSSMediaRule* ParserState_appendCSSMediaRule(
  struct _CSSOM_ParserState *state, const SAC_MediaQuery *media[])
{
  return state->vtable->appendCSSMediaRule(state, media);
}



static CSSOM_CSSStyleRule* ParserState_appendCSSStyleRule(
  struct _CSSOM_ParserState *state, const SAC_Selector *selectors[])
{
  return state->vtable->appendCSSStyleRule(state, selectors);
}



static CSSOM_CSSFontFaceRule* ParserState_appendCSSFontFaceRule(
  struct _CSSOM_ParserState *state)
{
  return state->vtable->appendCSSFontFaceRule(state);
}



/**
 * CSSRuleCatcher
 */

struct _CSSOM_ParserCSSRuleCatcherState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSRule *parentRule;
  CSSOM_CSSStyleSheet *parentStyleSheet;
  CSSOM_CSSRule **cssRule;
};



static CSSOM_CSSPageRule* ParserCSSRuleCatcherState_appendCSSPageRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSPageRule__alloc(state->parentRule,
    state->parentStyleSheet, selectors);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSMediaRule* ParserCSSRuleCatcherState_appendCSSMediaRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state, const SAC_MediaQuery *media[])
{
  CSSOM_CSSMediaRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSMediaRule__alloc(state->parentRule,
    state->parentStyleSheet, media);
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

  cssRule = CSSOM_CSSStyleRule__alloc(state->parentRule,
    state->parentStyleSheet, selectors);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSNamespaceRule* ParserCSSRuleCatcherState_appendCSSNamespaceRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  CSSOM_CSSNamespaceRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSNamespaceRule__alloc(state->parentRule,
    state->parentStyleSheet, prefix, uri);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSFontFaceRule* ParserCSSRuleCatcherState_appendCSSFontFaceRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state)
{
  CSSOM_CSSFontFaceRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSFontFaceRule__alloc(state->parentRule,
    state->parentStyleSheet);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static CSSOM_CSSImportRule* ParserCSSRuleCatcherState_appendCSSImportRule(
  struct _CSSOM_ParserCSSRuleCatcherState *state,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *media[], const SAC_STRING defaultNamepaceURI)
{
  CSSOM_CSSImportRule *cssRule;

  assert(*state->cssRule == NULL);

  cssRule = CSSOM_CSSImportRule__alloc(state->parentRule,
    state->parentStyleSheet, base, uri, media, defaultNamepaceURI);
  if (cssRule == NULL) return NULL;

  *state->cssRule = (CSSOM_CSSRule*)cssRule;

  return cssRule;
}



static struct _CSSOM_ParserState_vtable ParserCSSRuleCatcherState_vtable = {
  NULL,
  (CSSOM_CSSPageRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSRuleCatcherState_appendCSSPageRule,
  (CSSOM_CSSMediaRule* (*)(struct _CSSOM_ParserState *,
    const SAC_MediaQuery *[]))
  ParserCSSRuleCatcherState_appendCSSMediaRule,
  (CSSOM_CSSStyleRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSRuleCatcherState_appendCSSStyleRule,
  (CSSOM_CSSNamespaceRule* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_STRING))
  ParserCSSRuleCatcherState_appendCSSNamespaceRule,
  (CSSOM_CSSFontFaceRule* (*)(struct _CSSOM_ParserState *))
  ParserCSSRuleCatcherState_appendCSSFontFaceRule,
  (CSSOM_CSSImportRule* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_STRING,
    const SAC_MediaQuery *[], const SAC_STRING))
  ParserCSSRuleCatcherState_appendCSSImportRule
};



static struct _CSSOM_ParserCSSRuleCatcherState* ParserCSSRuleCatcherState_alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = (struct _CSSOM_ParserCSSRuleCatcherState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSRuleCatcherState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSRuleCatcherState_vtable);
  state->parentRule = parentRule;
  state->parentStyleSheet = parentStyleSheet;
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



static CSSOM_CSSFontFaceRule* ParserCSSStyleSheetState_appendCSSFontFaceRule(
  struct _CSSOM_ParserCSSStyleSheetState *state)
{
  return CSSOM_CSSRuleList__appendCSSFontFaceRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet);
}



static CSSOM_CSSImportRule* ParserCSSStyleSheetState_appendCSSImportRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *media[], const SAC_STRING defaultNamepaceURI)
{
  return CSSOM_CSSRuleList__appendCSSImportRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet, base, uri, media, defaultNamepaceURI);
}



static CSSOM_CSSPageRule* ParserCSSStyleSheetState_appendCSSPageRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_Selector *selectors[])
{
  return CSSOM_CSSRuleList__appendCSSPageRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet, selectors);
}



static CSSOM_CSSMediaRule* ParserCSSStyleSheetState_appendCSSMediaRule(
  struct _CSSOM_ParserCSSStyleSheetState *state, const SAC_MediaQuery *media[])
{
  return CSSOM_CSSRuleList__appendCSSMediaRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet, media);
}



static CSSOM_CSSNamespaceRule* ParserCSSStyleSheetState_appendCSSNamspaceRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  return CSSOM_CSSRuleList__appendCSSNamespaceRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet, prefix, uri);
}



static CSSOM_CSSStyleRule* ParserCSSStyleSheetState_appendCSSStyleRule(
  struct _CSSOM_ParserCSSStyleSheetState *state,
  const SAC_Selector *selectors[])
{
  return CSSOM_CSSRuleList__appendCSSStyleRule(
    CSSOM_CSSStyleSheet_cssRules(state->styleSheet),
    CSSOM_CSSStyleSheet_ownerRule(state->styleSheet),
    state->styleSheet, selectors);
}



static struct _CSSOM_ParserState_vtable
ParserCSSStyleSheetState_vtable = {
  NULL,
  (CSSOM_CSSPageRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSStyleSheetState_appendCSSPageRule,
  (CSSOM_CSSMediaRule* (*)(struct _CSSOM_ParserState *,
    const SAC_MediaQuery *[]))
  ParserCSSStyleSheetState_appendCSSMediaRule,
  (CSSOM_CSSStyleRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSStyleSheetState_appendCSSStyleRule,
  (CSSOM_CSSNamespaceRule* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_STRING))
  ParserCSSStyleSheetState_appendCSSNamspaceRule,
  (CSSOM_CSSFontFaceRule* (*)(struct _CSSOM_ParserState *))
  ParserCSSStyleSheetState_appendCSSFontFaceRule,
  (CSSOM_CSSImportRule* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_STRING,
    const SAC_MediaQuery *[], const SAC_STRING))
  ParserCSSStyleSheetState_appendCSSImportRule
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
 * CSSFontFaceRule
 */

struct _CSSOM_ParserCSSFontFaceRuleState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSFontFaceRule *cssRule;
};



static CSSOM_CSSPropertyValue* ParserCSSFontFaceRuleState_setProperty(
  struct _CSSOM_ParserCSSFontFaceRuleState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return CSSOM_CSSStyleDeclarationValue__setProperty(
    CSSOM_CSSStyleDeclaration_values(
      CSSOM_CSSFontFaceRule_style(state->cssRule)),
    property, value, important);
}



static struct _CSSOM_ParserState_vtable ParserCSSFontFaceRuleState_vtable = {
  (CSSOM_CSSPropertyValue* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_LexicalUnit *, SAC_Boolean))
  ParserCSSFontFaceRuleState_setProperty,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};



static struct _CSSOM_ParserCSSFontFaceRuleState*
ParserCSSFontFaceRuleState_alloc(
  CSSOM_CSSFontFaceRule *cssRule)
{
  struct _CSSOM_ParserCSSFontFaceRuleState *state;

  state = (struct _CSSOM_ParserCSSFontFaceRuleState*)CSSOM_malloc(
    sizeof(struct _CSSOM_ParserCSSFontFaceRuleState));
  if (state == NULL) return NULL;

  ParserState_ctor((struct _CSSOM_ParserState*)state,
    &ParserCSSFontFaceRuleState_vtable);
  state->cssRule = cssRule;

  return state;
}



/**
 * CSSPageRule
 */

struct _CSSOM_ParserCSSPageRuleState {
  struct _CSSOM_ParserState super;
  CSSOM_CSSPageRule *cssRule;
};



static CSSOM_CSSPropertyValue* ParserCSSPageRuleState_setProperty(
  struct _CSSOM_ParserCSSPageRuleState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return CSSOM_CSSStyleDeclarationValue__setProperty(
    CSSOM_CSSStyleDeclaration_values(CSSOM_CSSPageRule_style(state->cssRule)),
    property, value, important);
}



static struct _CSSOM_ParserState_vtable ParserCSSPageRuleState_vtable = {
  (CSSOM_CSSPropertyValue* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_LexicalUnit *, SAC_Boolean))
  ParserCSSPageRuleState_setProperty,
  NULL,
  NULL,
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



static CSSOM_CSSStyleRule* ParserCSSMediaRuleState_appendCSSStyleRule(
  struct _CSSOM_ParserCSSMediaRuleState *state,
  const SAC_Selector *selectors[])
{
  return CSSOM_CSSRuleList__appendCSSStyleRule(
    CSSOM_CSSMediaRule_cssRules(state->cssRule), (CSSOM_CSSRule*)state->cssRule,
    CSSOM_CSSRule_parentStyleSheet((CSSOM_CSSRule*)state->cssRule),
    selectors);
}



static struct _CSSOM_ParserState_vtable ParserCSSMediaRuleState_vtable = {
  NULL,
  NULL,
  NULL,
  (CSSOM_CSSStyleRule* (*)(struct _CSSOM_ParserState *,
    const SAC_Selector *[]))
  ParserCSSMediaRuleState_appendCSSStyleRule,
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



static CSSOM_CSSPropertyValue* ParserCSSStyleRuleState_setProperty(
  struct _CSSOM_ParserCSSStyleRuleState *state,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return CSSOM_CSSStyleDeclarationValue__setProperty(
    CSSOM_CSSStyleDeclaration_values(CSSOM_CSSStyleRule_style(state->cssRule)),
    property, value, important);
}



static struct _CSSOM_ParserState_vtable ParserCSSStyleRuleState_vtable = {
  (CSSOM_CSSPropertyValue* (*)(struct _CSSOM_ParserState *,
    const SAC_STRING, const SAC_LexicalUnit *, SAC_Boolean))
  ParserCSSStyleRuleState_setProperty,
  NULL,
  NULL,
  NULL,
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
  CSSOM_ParserStats *stats;
  CSSOM_Stack_ParserState *state;
};



CSSOM_ParserStack* CSSOM_ParserStack_alloc(const CSSOM *cssom) {
  CSSOM_ParserStats *stats;
  CSSOM_Stack_ParserState *state;
  CSSOM_ParserStack *stack;

  stats = CSSOM_ParserStats_alloc();
  if (stats == NULL) return NULL;

  state = CSSOM_Stack_ParserState_alloc();
  if (state == NULL) {
    CSSOM_ParserStats_free(stats);
    return NULL;
  }

  stack = (CSSOM_ParserStack*)CSSOM_malloc(sizeof(CSSOM_ParserStack));
  if (stack == NULL) {
    CSSOM_Stack_ParserState_free(state);
    CSSOM_ParserStats_free(stats);
    return NULL;
  }

  stack->cssom = cssom;
  stack->stats = stats;
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
  CSSOM_ParserStats_free(stack->stats);
  CSSOM_free(stack);
}



const CSSOM_ParserStats* CSSOM_ParserStack_stats(
  const CSSOM_ParserStack *stack)
{
  return stack->stats;
}



void CSSOM_ParserStack_pop(CSSOM_ParserStack *stack) {
  ParserState_free(*CSSOM_Stack_ParserState_top(stack->state));
  CSSOM_Stack_ParserState_pop(stack->state);
}



int CSSOM_ParserStack_error(const CSSOM_ParserStack *stack,
  const SAC_Error *error)
{
  CSSOM_ParserStats_errorHandler(stack->stats, error);
  return CSSOM__error(stack->cssom, error);
}



CSSOM_CSSPropertyValue* CSSOM_ParserStack_setProperty(CSSOM_ParserStack *stack,
  const SAC_STRING property,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  return ParserState_setProperty(*CSSOM_Stack_ParserState_top(stack->state),
    property, value, important);
}



CSSOM_CSSImportRule* CSSOM_ParserStack_appendCSSImportRule(
  CSSOM_ParserStack *stack,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *media[], const SAC_STRING defaultNamepaceURI)
{
  return ParserState_appendCSSImportRule(
    *CSSOM_Stack_ParserState_top(stack->state),
    base, uri, media, defaultNamepaceURI);
}



CSSOM_CSSNamespaceRule* CSSOM_ParserStack_appendCSSNamespaceRule(
  CSSOM_ParserStack *stack,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  return ParserState_appendCSSNamespaceRule(
    *CSSOM_Stack_ParserState_top(stack->state), prefix, uri);
}



CSSOM_CSSRule** CSSOM_ParserStack_pushCSSRuleCatcher(CSSOM_ParserStack *stack,
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *styleSheet,
  CSSOM_CSSRule **cssRule)
{
  struct _CSSOM_ParserCSSRuleCatcherState *state;

  state = ParserCSSRuleCatcherState_alloc(parentRule, styleSheet, cssRule);
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



CSSOM_CSSFontFaceRule* CSSOM_ParserStack_pushCSSFontFaceRule(
  CSSOM_ParserStack *stack)
{
  CSSOM_CSSFontFaceRule *cssRule;
  struct _CSSOM_ParserCSSFontFaceRuleState *state;

  cssRule = ParserState_appendCSSFontFaceRule(
    *CSSOM_Stack_ParserState_top(stack->state));
  if (cssRule == NULL) return NULL;

  state = ParserCSSFontFaceRuleState_alloc(cssRule);
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
  CSSOM_ParserStack *stack, const SAC_MediaQuery *media[])
{
  CSSOM_CSSMediaRule *cssRule;
  struct _CSSOM_ParserCSSMediaRuleState *state;

  cssRule = ParserState_appendCSSMediaRule(
    *CSSOM_Stack_ParserState_top(stack->state), media);
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
