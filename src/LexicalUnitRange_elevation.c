#include "LexicalUnitRange_elevation.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** elevation(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isAngle(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("below", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("level", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("above", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("higher", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("lower", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_elevation(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = elevation(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_ELEVATION_PROPERTY, begin, tail);
  return tail;
}
