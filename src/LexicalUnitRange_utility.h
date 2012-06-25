#ifndef _CSSOM_LEXICAL_UNIT_RANGE_UTILITY_H
#define _CSSOM_LEXICAL_UNIT_RANGE_UTILITY_H

#include "CSSPropertySetting.h"
#include "LexicalUnitRange.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



#define _CSSOM_ASIZE(array) \
  (sizeof(array) / sizeof(array[0]))

#define _CSSOM_INITIAL(initial) \
  (initial), &(initial)[_CSSOM_ASIZE(initial)]



int CSSOM_LexicalUnit_isInherit(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isAngle(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isLength(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isNonNegativeLength(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isColor(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isUrl(const SAC_LexicalUnit *value);

int CSSOM_LexicalUnit_isPercentage(const SAC_LexicalUnit *value);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_genericShorthand(
  const CSSOM *cssom, CSSOM_CSSPropertyType type,
  const _CSSOM_PropertyHandler *handlers,
  struct _CSSOM_LexicalUnitRange *values, int *marker,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_boxShorthand(
  const CSSOM_CSSPropertyType *subtypes,
  const SAC_LexicalUnit** (*handler)(const SAC_LexicalUnit **,
    const SAC_LexicalUnit **),
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_whatever(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
