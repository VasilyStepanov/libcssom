#include "LexicalUnitRange_captionSide.h"

#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** captionSide(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("top", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("bottom", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_captionSide(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = captionSide(begin, end);
  if (tail == begin) return begin;

  if (values != NULL)
    _CSSOM_SET_RANGE(values[0], CSSOM_CAPTION_SIDE_PROPERTY, begin, tail);
  return tail;
}
