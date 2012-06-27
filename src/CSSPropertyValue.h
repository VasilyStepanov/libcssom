#ifndef _CSSOM_CSS_PROPERTY_VALUE_H
#define _CSSOM_CSS_PROPERTY_VALUE_H

#include "CSSPropertyData.h"
#include "CSSPropertyType.h"
#include "LexicalUnitRange.h"

#include <cssom/CSSPropertyValue.h>

#include <sacc.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, CSSOM_CSSPropertyType type,
  CSSOM_CSSPropertyData *data, SAC_Boolean important, int *error);

CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__allocShorthand(
  const CSSOM *cssom, CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyType type);

const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSPropertyValue__omitGenericShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values);

int CSSOM_CSSPropertyValue__omitBoxShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values);

int CSSOM_CSSPropertyValue__omitRecursiveShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
