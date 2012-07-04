#include "LexicalUnitRange_display.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** display(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("inline", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("block", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("list-item", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("inline-block", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("inline-table", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table-row-group", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table-header-group", begin[0]->desc.ident) == 0)
      return &begin[1];
    if (strcmp("table-footer-group", begin[0]->desc.ident) == 0)
      return &begin[1];
    if (strcmp("table-row", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table-column-group", begin[0]->desc.ident) == 0)
      return &begin[1];
    if (strcmp("table-column", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table-cell", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("table-caption", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_display(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = display(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_DISPLAY_PROPERTY, begin, tail);
  return tail;
}
