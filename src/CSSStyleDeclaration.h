#ifndef _CSSOM_CSSSTYLEDECLARATION_H
#define _CSSOM_CSSSTYLEDECLARATION_H

#include <cssom/CSSStyleDeclaration.h>

#include "FSM_CSSProperty.h"

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef CSSOM_FSMIter_CSSProperty CSSOM_CSSStyleDeclarationIter;

typedef CSSOM_FSMConstIter_CSSProperty CSSOM_CSSStyleDeclarationConstIter;



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  const CSSOM_FSMTable_CSSProperty *table);

void CSSOM_CSSStyleDeclaration__free(CSSOM_CSSStyleDeclaration * style);

CSSOM_CSSProperty* CSSOM_CSSStyleDeclaration__setProperty(
  CSSOM_CSSStyleDeclaration *style,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important);



CSSOM_CSSStyleDeclarationIter CSSOM_CSSStyleDeclaration__begin(
  CSSOM_CSSStyleDeclaration *style);

CSSOM_CSSStyleDeclarationIter CSSOM_CSSStyleDeclaration__end(
  CSSOM_CSSStyleDeclaration *style);

CSSOM_CSSStyleDeclarationIter
CSSOM_CSSStyleDeclarationIter_next(
  CSSOM_CSSStyleDeclarationIter iter);



CSSOM_CSSStyleDeclarationConstIter CSSOM_CSSStyleDeclaration__cbegin(
  const CSSOM_CSSStyleDeclaration *style);

CSSOM_CSSStyleDeclarationConstIter CSSOM_CSSStyleDeclaration__cend(
  const CSSOM_CSSStyleDeclaration *style);

CSSOM_CSSStyleDeclarationConstIter
CSSOM_CSSStyleDeclarationConstIter_next(
  CSSOM_CSSStyleDeclarationConstIter iter);



#ifdef __cplusplus
}
#endif

#endif
