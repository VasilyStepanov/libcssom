#ifndef _CSSOM_CSSPROPERTY_H
#define _CSSOM_CSSPROPERTY_H

#include <cssom/CSSProperty.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSProperty* CSSOM_CSSProperty__alloc(
  const SAC_LexicalUnit *value, SAC_Boolean important);

void CSSOM_CSSProperty__free(CSSOM_CSSProperty * property);

void CSSOM_CSSProperty__setName(CSSOM_CSSProperty *property, const char *name);



#ifdef __cplusplus
}
#endif

#endif
