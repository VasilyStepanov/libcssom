#ifndef _CSSOM_LEXICAL_UNIT_RANGE_H
#define _CSSOM_LEXICAL_UNIT_RANGE_H

#include "CSSPropertyType.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



struct _CSSOM_LexicalUnitRange {
  CSSOM_CSSPropertyType type;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
};



#define _CSSOM_SET_RANGE(range, index, type_val, begin_val, end_val) \
  do { \
    if (range != NULL) { \
      (range)[(index)].type = (type_val); \
      (range)[(index)].begin = (begin_val); \
      (range)[(index)].end = (end_val); \
    } \
  } while (0)



#ifdef __cplusplus
}
#endif

#endif