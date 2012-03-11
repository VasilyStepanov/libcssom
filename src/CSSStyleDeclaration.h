#ifndef _CSSOM_CSSSTYLEDECLARATION_H
#define _CSSOM_CSSSTYLEDECLARATION_H

#include <cssom/CSSStyleDeclaration.h>

#include "FSM_CSSProperty.h"

#include <cssom/CSSProperty.h>

#include <sacc.h>



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  const CSSOM_FSMTable_CSSProperty *table);

void CSSOM_CSSStyleDeclaration__free(CSSOM_CSSStyleDeclaration *style);

CSSOM_CSSProperty* CSSOM_CSSStyleDeclaration__setProperty(
  CSSOM_CSSStyleDeclaration *style,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important);



#endif
