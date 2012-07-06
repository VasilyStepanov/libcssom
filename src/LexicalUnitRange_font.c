#include "LexicalUnitRange_font.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>



/**
 * font-family
 */

static const SAC_LexicalUnit** genericFamily(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("serif", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("sans-serif", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("cursive", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("fantasy", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("monospace", begin[0]->desc.ident) == 0) return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** familyName(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (begin[0]->lexicalUnitType == SAC_STRING_VALUE) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    while (++begin != end) {
      if ((**begin).lexicalUnitType != SAC_IDENT) break;
    }
    return &begin[0];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** familyNameOrGenericFamily(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  const SAC_LexicalUnit **tail;

  tail = genericFamily(begin, end);
  if (tail != begin) return tail;

  return familyName(begin, end);
}



static const SAC_LexicalUnit** fontFamily(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  const SAC_LexicalUnit **tail;

  if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }

  tail = familyNameOrGenericFamily(begin, end);

  while (1) {
    if (tail == begin) break;
    begin = tail;

    if (begin == end) break;
    if (begin[0]->lexicalUnitType != SAC_OPERATOR_COMMA) break;

    if (&begin[1] == end) break;
    tail = familyNameOrGenericFamily(&begin[1], end);
  }

  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_fontFamily(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = fontFamily(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_FONT_FAMILY_PROPERTY, begin, tail);
  return tail;
}



/**
 * font-size
 */

static const SAC_LexicalUnit** fontSize(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("xx-small", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("x-small", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("small", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("medium", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("large", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("x-large", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("xx-large", begin[0]->desc.ident) == 0) return &begin[1];

    if (strcmp("larger", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("smaller", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isNonNegativeLength(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isNonNegativePercentage(begin[0])) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_fontSize(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = fontSize(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_FONT_SIZE_PROPERTY, begin, tail);
  return tail;
}



/**
 * font-style
 */

static const SAC_LexicalUnit** fontStyle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("normal", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("italic", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("oblique", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_fontStyle(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = fontStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_FONT_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * font-variant
 */

static const SAC_LexicalUnit** fontVariant(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("normal", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("small-caps", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_fontVariant(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = fontVariant(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_FONT_VARIANT_PROPERTY, begin, tail);
  return tail;
}
