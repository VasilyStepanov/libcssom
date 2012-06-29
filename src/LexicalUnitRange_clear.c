#include "LexicalUnitRange_clear.h"

#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** clear(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("left", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("right", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("both", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_clear(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = clear(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CLEAR_PROPERTY, begin, tail);
  return tail;
}
