#include "CSSPropertyValue_border.h"

#include "gcc.h"

#include <string.h>



const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderColorSubtypes[] = {
  CSSOM_BORDER_TOP_COLOR_PROPERTY,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY
};

const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderStyleSubtypes[] = {
  CSSOM_BORDER_TOP_STYLE_PROPERTY,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY
};

const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderWidthSubtypes[] = {
  CSSOM_BORDER_TOP_WIDTH_PROPERTY,
  CSSOM_BORDER_RIGHT_WIDTH_PROPERTY,
  CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY,
  CSSOM_BORDER_LEFT_WIDTH_PROPERTY
};



static const SAC_LexicalUnit** isBorderColor(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isColor(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("transparent", begin[0]->desc.ident) == 0) return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** isBorderStyle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("hidden", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("dotted", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("dashed", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("solid", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("double", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("groove", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("ridge", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("inset", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("outset", begin[0]->desc.ident) == 0) return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** isBorderWidth(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("thin", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("medium", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("thick", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isNonNegativeLength(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * border-collapse
 */

static const SAC_LexicalUnit** borderCollapse(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("collapse", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("separate", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderCollapse(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderCollapse(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_COLLAPSE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-color
 */

static const SAC_LexicalUnit** borderColorToken(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSOM_LexicalUnitRange_boxShorthand(
    CSSOM_CSSPropertyValue_borderColorSubtypes, borderColorToken, begin, end,
    &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_COLOR_PROPERTY, begin, end);
  return end;
}



/**
 * border-spacing
 */

static const SAC_LexicalUnit** borderSpacing(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isLength(begin[0])) {
    if (&begin[1] != end &&
      CSSOM_LexicalUnit_isLength(begin[1]))
    {
      return &begin[2];
    }
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderSpacing(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderSpacing(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_SPACING_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-style
 */

static const SAC_LexicalUnit** borderStyleToken(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSOM_LexicalUnitRange_boxShorthand(
    CSSOM_CSSPropertyValue_borderStyleSubtypes, borderStyleToken, begin, end,
    &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_STYLE_PROPERTY, begin, end);
  return end;
}



/**
 * border-top-color
 */

static const SAC_LexicalUnit** borderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isBorderColor(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** borderDirectionColor(CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionColor(CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, end,
    values);
}



/**
 * border-right-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionColor(CSSOM_BORDER_RIGHT_COLOR_PROPERTY, begin, end,
    values);
}



/**
 * border-bottom-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionColor(CSSOM_BORDER_BOTTOM_COLOR_PROPERTY, begin, end,
    values);
}



/**
 * border-left-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionColor(CSSOM_BORDER_LEFT_COLOR_PROPERTY, begin, end,
    values);
}



/**
 * border-top-style
 */

static const SAC_LexicalUnit** borderStyle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (isBorderStyle(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** borderDirectionStyle(CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionStyle(CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, end,
    values);
}



/**
 * border-right-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionStyle(CSSOM_BORDER_RIGHT_STYLE_PROPERTY, begin, end,
    values);
}



/**
 * border-bottom-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionStyle(CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, begin, end,
    values);
}



/**
 * border-left-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionStyle(CSSOM_BORDER_LEFT_STYLE_PROPERTY, begin, end,
    values);
}



/**
 * border-top-width
 */

static const SAC_LexicalUnit** borderWidth(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (isBorderWidth(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** borderDirectionWidth(CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionWidth(CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, end,
    values);
}



/**
 * border-right-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionWidth(CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, begin, end,
    values);
}



/**
 * border-bottom-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionWidth(CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, begin, end,
    values);
}



/**
 * border-left-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  return borderDirectionWidth(CSSOM_BORDER_LEFT_WIDTH_PROPERTY, begin, end,
    values);
}



/**
 * border-width
 */

static const SAC_LexicalUnit** borderWidthToken(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSOM_LexicalUnitRange_boxShorthand(
    CSSOM_CSSPropertyValue_borderWidthSubtypes, borderWidthToken, begin, end,
    &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values, 0, CSSOM_BORDER_WIDTH_PROPERTY, begin, end);
  return end;
}
