#include "LexicalUnitRange_cursor.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** cursor_prefix(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin == end) {
    return begin;
  } else if (CSSOM_LexicalUnit_isUri(begin[0])) {
    if (&begin[1] == end) return &begin[0];
    if (begin[1]->lexicalUnitType != SAC_OPERATOR_COMMA) return &begin[0];

    return cursor_prefix(&begin[2], end);
  }

  return &begin[0];
}


static const SAC_LexicalUnit** cursor(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }

  begin = cursor_prefix(begin, end);
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("auto", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("crosshair", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("default", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("pointer", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("move", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("e-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("ne-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("nw-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("n-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("se-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("sw-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("s-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("w-resize", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("text", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("wait", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("help", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("progress", begin[0]->desc.ident) == 0) return &begin[1];
  }

  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cursor(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = cursor(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CURSOR_PROPERTY, begin, tail);
  return tail;
}
