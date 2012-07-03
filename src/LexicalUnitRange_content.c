#include "LexicalUnitRange_content.h"

#include "gcc.h"

#include <string.h>



static int isAttr(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_ATTR_FUNCTION) {
    if (value->desc.function.parameters[0] == NULL) return 0;
    if (value->desc.function.parameters[0]->lexicalUnitType != SAC_IDENT)
      return 0;
    if (value->desc.function.parameters[1] != NULL) return 0;
    return 1;
  }
  return 0;
}



static const SAC_LexicalUnit** content_tail(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin == end) return end;
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("open-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("close-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("no-open-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("no-close-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isString(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isUri(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isCounter(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (isAttr(begin[0])) {
    return content_tail(&begin[1], end);
  }
  return &begin[0];
}



static const SAC_LexicalUnit** content(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("normal", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("open-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("close-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("no-open-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
    if (strcmp("no-close-quote", begin[0]->desc.ident) == 0)
      return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isString(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isUri(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isCounter(begin[0])) {
    return content_tail(&begin[1], end);
  } else if (isAttr(begin[0])) {
    return content_tail(&begin[1], end);
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_content(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = content(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CONTENT_PROPERTY, begin, tail);
  return tail;
}
