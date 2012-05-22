#ifndef _CSSOM_CSS_PROPERTY_VALUE_H
#define _CSSOM_CSS_PROPERTY_VALUE_H

#include <cssom/CSSPropertyValue.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, const char *name,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  SAC_Boolean important);

const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property);

void CSSOM_CSSPropertyValue__keepParser(CSSOM_CSSPropertyValue *property,
  SAC_Parser parser);

const SAC_LexicalUnit** CSSOM_CSSPropertyValue__begin(
  const CSSOM_CSSPropertyValue *property);

const SAC_LexicalUnit** CSSOM_CSSPropertyValue__end(
  const CSSOM_CSSPropertyValue *property);


#ifdef __cplusplus
}
#endif

#endif
