#ifndef _CSSOM_CSSPROPERTY_H
#define _CSSOM_CSSPROPERTY_H

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSProperty CSSOM_CSSProperty;



CSSOM_CSSProperty* CSSOM_CSSProperty__alloc(
  const SAC_LexicalUnit *value, SAC_Boolean important);

void CSSOM_CSSProperty__setName(CSSOM_CSSProperty *property, const char *name);

void CSSOM_CSSProperty_acquire(CSSOM_CSSProperty *property);

void CSSOM_CSSProperty_release(CSSOM_CSSProperty *property);

const char* CSSOM_CSSProperty_cssText(const CSSOM_CSSProperty *property);

const char* CSSOM_CSSProperty_name(const CSSOM_CSSProperty *property);

int CSSOM_CSSProperty_important(const CSSOM_CSSProperty *property);





#ifdef __cplusplus
}
#endif

#endif
