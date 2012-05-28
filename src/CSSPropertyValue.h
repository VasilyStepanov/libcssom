#ifndef _CSSOM_CSS_PROPERTY_VALUE_H
#define _CSSOM_CSS_PROPERTY_VALUE_H

#include <cssom/CSSPropertyValue.h>
#include <cssom/CSSProperties.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  const CSSOM *cssom, CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  SAC_Boolean important, int *error);

const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property);

void CSSOM_CSSPropertyValue__keepParser(CSSOM_CSSPropertyValue *property,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif
