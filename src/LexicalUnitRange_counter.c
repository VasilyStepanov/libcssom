#include "LexicalUnitRange_counter.h"

#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** counter_tail(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin == end) return end;
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[0];
    if (&begin[1] != end && begin[1]->lexicalUnitType == SAC_INTEGER) {
      return counter_tail(&begin[2], end);
    }
    return counter_tail(&begin[1], end);
  }
  return &begin[0];
}



static const SAC_LexicalUnit** counter(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
    if (&begin[1] != end && begin[1]->lexicalUnitType == SAC_INTEGER) {
      return counter_tail(&begin[2], end);
    }
    return counter_tail(&begin[1], end);
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_counterIncrement(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = counter(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_COUNTER_INCREMENT_PROPERTY, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_counterReset(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = counter(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_COUNTER_RESET_PROPERTY, begin, tail);
  return tail;
}
