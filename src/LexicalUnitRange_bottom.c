#include "LexicalUnitRange_azimuth.h"

#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** bottom(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isLength(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isPercentage(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("auto", begin[0]->desc.ident) == 0) {
      return &begin[1];
    }
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_bottom(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = bottom(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BOTTOM_PROPERTY, begin, tail);
  return tail;
}
