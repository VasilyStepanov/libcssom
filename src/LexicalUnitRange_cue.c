#include "LexicalUnitRange_cue.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>



static const SAC_LexicalUnit** cue(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isUri(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cueAfter(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = cue(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CUE_AFTER_PROPERTY, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cueBefore(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = cue(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CUE_BEFORE_PROPERTY, begin, tail);
  return tail;
}


const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cue(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  setting = CSSOM__propertySetting(cssom, CSSOM_CUE_PROPERTY);

  if (CSSOM_LexicalUnitRange_linearShorthand(cssom, values, setting->subhashes,
    CSSOM_LexicalUnitRange_cueBefore, begin, end,
    ranges != NULL ? &ranges[1] : NULL) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_CUE_PROPERTY, begin, end);
  return end;
}
