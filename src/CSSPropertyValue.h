#ifndef _CSSOM_CSS_PROPERTY_VALUE_H
#define _CSSOM_CSS_PROPERTY_VALUE_H

#include "CSSPropertyType.h"
#include "LexicalUnitRange.h"

#include <cssom/CSSPropertyValue.h>

#include <sacc.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_CSSPropertyValue__initGlobals(void);

CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  const CSSOM *cssom, CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyType type, const SAC_LexicalUnit *value,
  SAC_Boolean important, int *error);

const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property);

void CSSOM_CSSPropertyValue__keepParser(CSSOM_CSSPropertyValue *property,
  SAC_Parser parser);

int CSSOM_CSSPropertyValue__omitGenericShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values);

int CSSOM_CSSPropertyValue__omitBoxShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
