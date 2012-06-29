#include "LexicalUnitRange_border.h"

#include "CSSOM.h"
#include "CSSEmitter.h"
#include "gcc.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>



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



static const SAC_LexicalUnit** borderTopColorToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderColor(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderTopStyleToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderRightStyleToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_RIGHT_STYLE_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderBottomStyleToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL) {
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, begin,
      tail);
  }
  return tail;
}



static const SAC_LexicalUnit** borderLeftStyleToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_LEFT_STYLE_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderTopWidthToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidth(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderRightWidthToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidth(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** borderBottomWidthToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidth(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL) {
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, begin,
      tail);
  }
  return tail;
}



static const SAC_LexicalUnit** borderLeftWidthToken(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidth(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_LEFT_WIDTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * border
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_border(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  static const _CSSOM_PropertyHandler handlers[3] = {
    borderTopWidthToken,
    borderTopStyleToken,
    CSSOM_LexicalUnitRange_borderTopColor,
  };

  int marker[3] = { 0, 0, 0 };

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_PROPERTY);

  assert(setting->nsubtypes == _CSSOM_ARSIZE(marker));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, setting->subtypes,
    handlers, setting->initial, ranges != NULL ? &ranges[1] : NULL, marker,
    setting->nsubtypes, begin, end) != end)
  {
    return begin;
  }

  if (ranges != NULL) {
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_PROPERTY, begin, end);
    _CSSOM_SET_RANGE(ranges[1], CSSOM_BORDER_TOP_WIDTH_PROPERTY,
      ranges[1].begin, ranges[1].end);
    _CSSOM_SET_RANGE(ranges[2], CSSOM_BORDER_TOP_STYLE_PROPERTY,
      ranges[2].begin, ranges[2].end);
    _CSSOM_SET_RANGE(ranges[3], CSSOM_BORDER_TOP_COLOR_PROPERTY,
      ranges[3].begin, ranges[3].end);
    _CSSOM_SET_RANGE(ranges[4], CSSOM_BORDER_RIGHT_WIDTH_PROPERTY,
      ranges[1].begin, ranges[1].end);
    _CSSOM_SET_RANGE(ranges[5], CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
      ranges[2].begin, ranges[2].end);
    _CSSOM_SET_RANGE(ranges[6], CSSOM_BORDER_RIGHT_COLOR_PROPERTY,
      ranges[3].begin, ranges[3].end);
    _CSSOM_SET_RANGE(ranges[7], CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY,
      ranges[1].begin, ranges[1].end);
    _CSSOM_SET_RANGE(ranges[8], CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
      ranges[2].begin, ranges[2].end);
    _CSSOM_SET_RANGE(ranges[9], CSSOM_BORDER_BOTTOM_COLOR_PROPERTY,
      ranges[3].begin, ranges[3].end);
    _CSSOM_SET_RANGE(ranges[10], CSSOM_BORDER_LEFT_WIDTH_PROPERTY,
      ranges[1].begin, ranges[1].end);
    _CSSOM_SET_RANGE(ranges[11], CSSOM_BORDER_LEFT_STYLE_PROPERTY,
      ranges[2].begin, ranges[2].end);
    _CSSOM_SET_RANGE(ranges[12], CSSOM_BORDER_LEFT_COLOR_PROPERTY,
      ranges[3].begin, ranges[3].end);
  }

  return end;
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
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = borderCollapse(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_COLLAPSE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_COLOR_PROPERTY);

  if (CSSOM_LexicalUnitRange_boxShorthand(cssom, setting->subtypes,
    borderTopColorToken, begin, end,
    ranges != NULL ? &ranges[1] : NULL) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_COLOR_PROPERTY, begin, end);
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
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = borderSpacing(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_SPACING_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_STYLE_PROPERTY);

  if (CSSOM_LexicalUnitRange_boxShorthand(cssom, setting->subtypes,
    borderTopStyleToken, begin, end, ranges != NULL ? &ranges[1] : NULL) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_STYLE_PROPERTY, begin, end);
  return end;
}



/**
 * border-top
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTop(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  static const _CSSOM_PropertyHandler handlers[3] = {
    borderTopWidthToken,
    borderTopStyleToken,
    CSSOM_LexicalUnitRange_borderTopColor,
  };

  int marker[3] = { 0, 0, 0 };

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_TOP_PROPERTY);

  assert(setting->nsubtypes == _CSSOM_ARSIZE(marker));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, setting->subtypes,
    handlers, setting->initial, ranges != NULL ? &ranges[1] : NULL, marker,
    setting->nsubtypes, begin, end) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_TOP_PROPERTY, begin, end);
  return end;
}



/**
 * border-right
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRight(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  static const _CSSOM_PropertyHandler handlers[3] = {
    borderRightWidthToken,
    borderRightStyleToken,
    CSSOM_LexicalUnitRange_borderRightColor,
  };

  int marker[3] = { 0, 0, 0 };

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_RIGHT_PROPERTY);

  assert(setting->nsubtypes == _CSSOM_ARSIZE(marker));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, setting->subtypes,
    handlers, setting->initial, ranges != NULL ? &ranges[1] : NULL, marker,
    setting->nsubtypes, begin, end) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_RIGHT_PROPERTY, begin, end);
  return end;
}



/**
 * border-bottom
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottom(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  static const _CSSOM_PropertyHandler handlers[3] = {
    borderBottomWidthToken,
    borderBottomStyleToken,
    CSSOM_LexicalUnitRange_borderBottomColor,
  };

  int marker[3] = { 0, 0, 0 };

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_BOTTOM_PROPERTY);

  assert(setting->nsubtypes == _CSSOM_ARSIZE(marker));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, setting->subtypes,
    handlers, setting->initial, ranges != NULL ? &ranges[1] : NULL, marker,
    setting->nsubtypes, begin, end) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_BOTTOM_PROPERTY, begin, end);
  return end;
}



/**
 * border-left
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeft(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  static const _CSSOM_PropertyHandler handlers[3] = {
    borderLeftWidthToken,
    borderLeftStyleToken,
    CSSOM_LexicalUnitRange_borderLeftColor,
  };

  int marker[3] = { 0, 0, 0 };

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_LEFT_PROPERTY);

  assert(setting->nsubtypes == _CSSOM_ARSIZE(marker));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, setting->subtypes,
    handlers, setting->initial, ranges != NULL ? &ranges[1] : NULL, marker,
    setting->nsubtypes, begin, end) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_LEFT_PROPERTY, begin, end);
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
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = borderColor(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopColor(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionColor(CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, end,
    ranges);
}



/**
 * border-right-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightColor(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionColor(CSSOM_BORDER_RIGHT_COLOR_PROPERTY, begin, end,
    ranges);
}



/**
 * border-bottom-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomColor(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionColor(CSSOM_BORDER_BOTTOM_COLOR_PROPERTY, begin, end,
    ranges);
}



/**
 * border-left-color
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftColor(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionColor(CSSOM_BORDER_LEFT_COLOR_PROPERTY, begin, end,
    ranges);
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
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = borderStyle(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopStyle(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionStyle(CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, end,
    ranges);
}



/**
 * border-right-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightStyle(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionStyle(CSSOM_BORDER_RIGHT_STYLE_PROPERTY, begin, end,
    ranges);
}



/**
 * border-bottom-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomStyle(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionStyle(CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, begin, end,
    ranges);
}



/**
 * border-left-style
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftStyle(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionStyle(CSSOM_BORDER_LEFT_STYLE_PROPERTY, begin, end,
    ranges);
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
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const SAC_LexicalUnit **tail;

  tail = borderWidth(begin, end);
  if (tail == begin) return begin;

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], type, begin, tail);
  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopWidth(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionWidth(CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, end,
    ranges);
}



/**
 * border-right-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightWidth(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionWidth(CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, begin, end,
    ranges);
}



/**
 * border-bottom-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomWidth(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionWidth(CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, begin, end,
    ranges);
}



/**
 * border-left-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftWidth(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  return borderDirectionWidth(CSSOM_BORDER_LEFT_WIDTH_PROPERTY, begin, end,
    ranges);
}



/**
 * border-width
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;

  setting = CSSOM__propertySetting(cssom, CSSOM_BORDER_WIDTH_PROPERTY);

  if (CSSOM_LexicalUnitRange_boxShorthand(cssom, setting->subtypes,
    borderTopWidthToken, begin, end, ranges != NULL ? &ranges[1] : NULL) != end)
  {
    return begin;
  }

  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], CSSOM_BORDER_WIDTH_PROPERTY, begin, end);
  return end;
}
