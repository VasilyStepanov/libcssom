#ifndef _CSSOM_CSSPROPERTY_H
#define _CSSOM_CSSPROPERTY_H

#include <cssom/CSSProperty.h>

#include <sacc.h>



CSSOM_CSSProperty* CSSOM_CSSProperty__alloc(
  const SAC_LexicalUnit *value, SAC_Boolean important);

void CSSOM_CSSProperty__acquire(CSSOM_CSSProperty *property);

void CSSOM_CSSProperty__release(CSSOM_CSSProperty *property);

void CSSOM_CSSProperty__setName(CSSOM_CSSProperty *property, const char *name);



#endif
