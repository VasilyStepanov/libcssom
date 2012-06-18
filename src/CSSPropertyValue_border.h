#ifndef _CSSOM_CSS_PROPERTY_VALUE_BORDER_H
#define _CSSOM_CSS_PROPERTY_VALUE_BORDER_H

#include "CSSPropertyValue_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



extern const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderColorSubtypes[4];

extern const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderStyleSubtypes[4];

extern const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderWidthSubtypes[4];



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderCollapse(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderSpacing(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
