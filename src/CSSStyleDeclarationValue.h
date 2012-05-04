#ifndef _CSSOM_CSS_STYLE_DECLARATION_VALUE_H
#define _CSSOM_CSS_STYLE_DECLARATION_VALUE_H

#include <cssom/CSSStyleDeclarationValue.h>

#include "FSM_CSSPropertyValue.h"

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef CSSOM_FSMIter_CSSPropertyValue CSSOM_CSSStyleDeclarationValueIter;

typedef CSSOM_FSMConstIter_CSSPropertyValue
  CSSOM_CSSStyleDeclarationValueConstIter;



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclarationValue__alloc(
  CSSOM_CSSStyleDeclaration *parentStyle);

CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclarationValue_parentStyle(
  const CSSOM_CSSStyleDeclarationValue *values);

CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue__setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean priority);

const char* CSSOM_CSSStyleDeclarationValue__getPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property);

const char* CSSOM_CSSStyleDeclarationValue__getPropertyPriority(
  const CSSOM_CSSStyleDeclarationValue *values, const char * property);

void CSSOM_CSSStyleDeclarationValue_setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value);

void CSSOM_CSSStyleDeclarationValue_setPropertyEx(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value, const char *priority);



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__begin(
  CSSOM_CSSStyleDeclarationValue *values);

CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__end(
  CSSOM_CSSStyleDeclarationValue *values);

CSSOM_CSSStyleDeclarationValueIter
CSSOM_CSSStyleDeclarationValueIter_next(
  CSSOM_CSSStyleDeclarationValueIter iter);



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cbegin(
  const CSSOM_CSSStyleDeclarationValue *values);

CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cend(
  const CSSOM_CSSStyleDeclarationValue *values);

CSSOM_CSSStyleDeclarationValueConstIter
CSSOM_CSSStyleDeclarationValueConstIter_next(
  CSSOM_CSSStyleDeclarationValueConstIter iter);



#ifdef __cplusplus
}
#endif

#endif