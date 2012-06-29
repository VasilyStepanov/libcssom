#include "LexicalUnitRange_color.h"

#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** color(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isColor(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_color(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = color(begin, end);
  if (tail == begin) return begin;

  if (values != NULL)
    _CSSOM_SET_RANGE(values[0], CSSOM_COLOR_PROPERTY, begin, tail);
  return tail;
}
