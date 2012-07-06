#ifndef _CSSOM_LEXICAL_UNIT_RANGE_UTILITY_H
#define _CSSOM_LEXICAL_UNIT_RANGE_UTILITY_H

#include "CSSPropertySetting.h"
#include "LexicalUnitRange.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



#define _CSSOM_ARSIZE(array) \
  (sizeof(array) / sizeof(array[0]))



int CSSOM_LexicalUnit_isInherit(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isAngle(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isLength(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isNonNegativeLength(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isColor(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isUri(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isPercentage(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isNonNegativePercentage(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isShape(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isString(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isCounter(const SAC_LexicalUnit *value);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_genericShorthand(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const int *subhashes, const _CSSOM_PropertyHandler *handlers,
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *ranges, int *marker, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_boxShorthand(const CSSOM *cssom, 
  const CSSOM_CSSStyleDeclarationValue *values, const int *subhashes,
  _CSSOM_PropertyHandler handler, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_linearShorthand(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const int *subhashes, _CSSOM_PropertyHandler handler,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_whatever(const CSSOM *cssom,
  const CSSOM_CSSStyleDeclarationValue *values, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);



#ifdef __cplusplus
}
#endif

#endif
