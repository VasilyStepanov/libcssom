#ifndef _CSSOM_LEXICAL_UNIT_RANGE_H
#define _CSSOM_LEXICAL_UNIT_RANGE_H

#include "CSSPropertyType.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



struct _CSSOM_LexicalUnitRange {
  int hash;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  int owner;
};



#define _CSSOM_SET_RANGE(range, hash_val, begin_val, end_val) \
  do { \
    (range).hash = (hash_val); \
    (range).begin = (begin_val); \
    (range).end = (end_val); \
    (range).owner = -1; \
  } while (0)



#define _CSSOM_SET_RANGE_EX(range, hash_val, begin_val, end_val, owner_val) \
  do { \
    (range).hash = (hash_val); \
    (range).begin = (begin_val); \
    (range).end = (end_val); \
    (range).owner = (owner_val); \
  } while (0)



#ifdef __cplusplus
}
#endif

#endif
