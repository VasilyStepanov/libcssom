#ifndef _CSSOM_CSS_PROPERTY_VALUE_UTILITY_H
#define _CSSOM_CSS_PROPERTY_VALUE_UTILITY_H

#include "CSSProperties.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



struct _CSSOM_LexicalUnitRange {
  CSSOM_CSSPropertyType type;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
};



typedef const SAC_LexicalUnit**(*_CSSOM_PropertyHandler)(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



#define _CSSOM_SET_RANGE(range, type_val, begin_val, end_val) \
  do { \
    (range).type = (type_val); \
    (range).begin = (begin_val); \
    (range).end = (end_val); \
  } while (0)



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



#ifdef __cplusplus
}
#endif

#endif
