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

CSSOM_CSSNamespaceRule* CSSOM_ParserStack_appendCSSNamespaceRule(
  CSSOM_ParserStack *stack,
  const SAC_STRING prefix, const SAC_STRING uri);

void CSSOM_ParserStack_pop(CSSOM_ParserStack *stack);

CSSOM_CSSRule** CSSOM_ParserStack_pushCSSRuleCatcher(CSSOM_ParserStack *stack,
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule **cssRule);

CSSOM_CSSStyleSheet* CSSOM_ParserStack_pushCSSStyleSheet(
  CSSOM_ParserStack *stack, CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSFontFaceRule* CSSOM_ParserStack_pushCSSFontFaceRule(
  CSSOM_ParserStack *stack);

CSSOM_CSSMediaRule* CSSOM_ParserStack_pushCSSMediaRule(
  CSSOM_ParserStack *stack, const SAC_MediaQuery *media[]);

CSSOM_CSSPageRule* CSSOM_ParserStack_pushCSSPageRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[]);

CSSOM_CSSStyleRule* CSSOM_ParserStack_pushCSSStyleRule(
  CSSOM_ParserStack *stack, const SAC_Selector *selectors[]);

int CSSOM_ParserStack_error(const CSSOM_ParserStack *stack,
  const SAC_Error *error);



#ifdef __cplusplus
}
#endif

#endif
