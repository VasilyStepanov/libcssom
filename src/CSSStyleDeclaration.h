#ifndef _CSSOM_CSSSTYLEDECLARATION_H
#define _CSSOM_CSSSTYLEDECLARATION_H

#include <cssom/CSSStyleDeclaration.h>

#include "FSM_CSSProperty.h"

#include <sacc.h>



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration_alloc(
  const CSSOM_FSM_CSSProperty *fsm);

void CSSOM_CSSStyleDeclaration_free(CSSOM_CSSStyleDeclaration *style);

void CSSOM_CSSStyleDeclaration_append(CSSOM_CSSStyleDeclaration *style,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important);



#endif
