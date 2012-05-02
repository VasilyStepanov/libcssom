#ifndef _CSSOM_CSS_PROPERTY_VALUE_H
#define _CSSOM_CSS_PROPERTY_VALUE_H

#include <cssom/CSSPropertyValue.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  const SAC_LexicalUnit *value, SAC_Boolean important);

void CSSOM_CSSPropertyValue__setName(CSSOM_CSSPropertyValue *property,
  const char *name);

const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property);



#ifdef __cplusplus
}
#endif

#endif
