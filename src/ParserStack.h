#ifndef _CSSOM_PARSER_STACK_H
#define _CSSOM_PARSER_STACK_H

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_ParserStack CSSOM_ParserStack;



CSSOM_ParserStack* CSSOM_ParserStack_alloc(const CSSOM *cssom);

void CSSOM_ParserStack_free(CSSOM_ParserStack *stack);

CSSOM_CSSProperty* CSSOM_ParserStack_setProperty(CSSOM_ParserStack *stack,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important);

void CSSOM_ParserStack_pop(CSSOM_ParserStack *stack);

CSSOM_CSSRule** CSSOM_ParserStack_pushCSSRuleCatcher(CSSOM_ParserStack *stack,
  CSSOM_CSSRule **cssRule);

CSSOM_CSSStyleSheet* CSSOM_ParserStack_pushCSSStyleSheetHolder(
  CSSOM_ParserStack *stack, CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSPageRule* CSSOM_ParserStack_pushCSSPageRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[]);

CSSOM_CSSMediaRule* CSSOM_ParserStack_pushCSSMediaRule(
  CSSOM_ParserStack *stack);

CSSOM_CSSStyleRule* CSSOM_ParserStack_pushCSSStyleRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[]);

int CSSOM_ParserStack_error(const CSSOM_ParserStack *stack,
  const SAC_Error *error);



#ifdef __cplusplus
}
#endif

#endif
