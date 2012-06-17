#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "CSSPropertyValue_azimuth.h"
#include "CSSPropertyValue_background.h"
#include "CSSPropertyValue_utility.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclarationValue.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



static SAC_LexicalUnit unit_transparent;
static SAC_LexicalUnit unit_none;
static SAC_LexicalUnit unit_repeat;
static SAC_LexicalUnit unit_scroll;
static SAC_LexicalUnit unit_0pct;

static const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderColorSubtypes[] = {
  CSSOM_BORDER_TOP_COLOR_PROPERTY,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY
};

static const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderStyleSubtypes[] = {
  CSSOM_BORDER_TOP_STYLE_PROPERTY,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY
};

static const CSSOM_CSSPropertyType
CSSOM_CSSPropertyValue_borderWidthSubtypes[] = {
  CSSOM_BORDER_TOP_WIDTH_PROPERTY,
  CSSOM_BORDER_RIGHT_WIDTH_PROPERTY,
  CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY,
  CSSOM_BORDER_LEFT_WIDTH_PROPERTY
};



void CSSOM_CSSPropertyValue__initGlobals(void) {
  unit_transparent.lexicalUnitType = SAC_IDENT;
  unit_transparent.desc.ident = "transparent";

  unit_none.lexicalUnitType = SAC_IDENT;
  unit_none.desc.ident = "none";

  unit_repeat.lexicalUnitType = SAC_IDENT;
  unit_repeat.desc.ident = "repeat";

  unit_scroll.lexicalUnitType = SAC_IDENT;
  unit_scroll.desc.ident = "scroll";

  unit_0pct.lexicalUnitType = SAC_PERCENTAGE;
  unit_0pct.desc.dimension.unit = "%";
  unit_0pct.desc.dimension.value.sreal = 0;
}



static int isBorderStyle(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", value->desc.ident) == 0) return 1;
    if (strcmp("hidden", value->desc.ident) == 0) return 1;
    if (strcmp("dotted", value->desc.ident) == 0) return 1;
    if (strcmp("dashed", value->desc.ident) == 0) return 1;
    if (strcmp("solid", value->desc.ident) == 0) return 1;
    if (strcmp("double", value->desc.ident) == 0) return 1;
    if (strcmp("groove", value->desc.ident) == 0) return 1;
    if (strcmp("ridge", value->desc.ident) == 0) return 1;
    if (strcmp("inset", value->desc.ident) == 0) return 1;
    if (strcmp("outset", value->desc.ident) == 0) return 1;
  }
  return 0;
}



static int isBorderWidth(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("thin", value->desc.ident) == 0) return 1;
    if (strcmp("medium", value->desc.ident) == 0) return 1;
    if (strcmp("thick", value->desc.ident) == 0) return 1;
  } else if (CSSOM_LexicalUnit_isNonNegativeLength(value)) {
    return 1;
  }
  return 0;
}



static const SAC_LexicalUnit** isBorderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isColor(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("transparent", begin[0]->desc.ident) == 0) return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** borderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isBorderStyle(begin[0])) return &begin[1];
  return &begin[0];
}



static const SAC_LexicalUnit** isBorderWidthToken(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isBorderWidth(begin[0])) return &begin[1];
  return &begin[0];
}



struct _CSSOM_CSSPropertyValue {
  size_t handles;
  CSSOM_CSSStyleDeclarationValue *parentValues;
  CSSOM_CSSPropertyValue *shorthand;
  SAC_Parser parser;
  CSSOM_CSSPropertyType type;
  const char *name;
  const SAC_LexicalUnit **holder;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  SAC_Boolean important;
  char *cssText;
};



static int LexicalUnit_eq(const SAC_LexicalUnit *lhs,
  const SAC_LexicalUnit *rhs)
{
  if (lhs->lexicalUnitType != rhs->lexicalUnitType) return 0;

  switch (lhs->lexicalUnitType) {
    case SAC_OPERATOR_PLUS:
    case SAC_OPERATOR_MINUS:
    case SAC_OPERATOR_COMMA:
    case SAC_OPERATOR_SLASH:
    case SAC_OPERATOR_MULTIPLY:
    case SAC_OPERATOR_MOD:
    case SAC_OPERATOR_EXP:
    case SAC_OPERATOR_LT:
    case SAC_OPERATOR_GT:
    case SAC_OPERATOR_LE:
    case SAC_OPERATOR_GE:
    case SAC_OPERATOR_TILDE:
    case SAC_INHERIT:
      break;
    case SAC_INTEGER:
      if (lhs->desc.integer != rhs->desc.integer) return 0;
      break;
    case SAC_REAL:
      if (lhs->desc.real != rhs->desc.real) return 0;
      break;
    case SAC_DIMENSION:
      if (strcmp(lhs->desc.dimension.unit, rhs->desc.dimension.unit) != 0)
        return 0;
      /* no breaks */
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_MILLIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
    case SAC_PERCENTAGE:
    case SAC_DEGREE:
    case SAC_GRADIAN:
    case SAC_RADIAN:
    case SAC_MILLISECOND:
    case SAC_SECOND:
    case SAC_HERTZ:
    case SAC_KILOHERTZ:
    case SAC_DOTS_PER_INCH:
    case SAC_DOTS_PER_CENTIMETER:
      if (lhs->desc.dimension.value.sreal != rhs->desc.dimension.value.sreal)
        return 0;
      break;
    case SAC_URI:
      if (strcmp(lhs->desc.uri, rhs->desc.uri) != 0) return 0;
      break;
    case SAC_FUNCTION:
      if (strcmp(lhs->desc.function.name, rhs->desc.function.name) < 0)
        return 0;
      /* no breaks */
    case SAC_RGBCOLOR:
    case SAC_ATTR_FUNCTION:
    case SAC_RECT_FUNCTION:
    case SAC_COUNTER_FUNCTION:
    case SAC_COUNTERS_FUNCTION:
    case SAC_NTH_CHILD_FUNCTION:
    case SAC_NTH_LAST_CHILD_FUNCTION:
    case SAC_NTH_OF_TYPE_FUNCTION:
    case SAC_NTH_LAST_OF_TYPE_FUNCTION:
      {
        SAC_LexicalUnit **lhsarg;
        SAC_LexicalUnit **rhsarg;

        for (
          lhsarg = lhs->desc.function.parameters,
          rhsarg = rhs->desc.function.parameters;
          *lhsarg != NULL || *rhsarg != NULL;
          ++lhsarg, ++rhsarg)
        {
          if (*lhsarg == NULL || *rhsarg == NULL) return 0;
          if (LexicalUnit_eq(*lhsarg, *rhsarg) == 0) return 0;
        }
      }
      break;
    case SAC_IDENT:
      if (strcmp(lhs->desc.ident, rhs->desc.ident) != 0) return 0;
      break;
    case SAC_STRING_VALUE:
      if (strcmp(lhs->desc.stringValue, rhs->desc.stringValue) != 0) return 0;
      break;
    case SAC_UNICODERANGE:
      if (strcmp(lhs->desc.unicodeRange, rhs->desc.unicodeRange) != 0) return 0;
      break;
    case SAC_SUB_EXPRESSION:
      {
        SAC_LexicalUnit **lhssub;
        SAC_LexicalUnit **rhssub;

        for (
          lhssub = lhs->desc.subValues,
          rhssub = rhs->desc.subValues;
          *lhssub != NULL || *rhssub != NULL;
          ++lhssub, ++rhssub)
        {
          if (LexicalUnit_eq(*lhssub, *rhssub) == 0) return 0;
        }
      }
      break;
  };
  return 1;
}



static int CSSPropertyValue_isInherit(const CSSOM_CSSPropertyValue *property) {
  if (property->end - property->begin != 1) return 0;
  return CSSOM_LexicalUnit_isInherit(property->begin[0]);
}



static int CSSPropertyValue_eq(const CSSOM_CSSPropertyValue *lhs,
  const CSSOM_CSSPropertyValue *rhs)
{
  const SAC_LexicalUnit **lit;
  const SAC_LexicalUnit **rit;

  if (lhs->end - lhs->begin != rhs->end - rhs->begin) return 0;

  for (lit = lhs->begin, rit = rhs->begin; lit != lhs->end; ++lit, ++rit) {
    if (LexicalUnit_eq(*lit, *rit) == 0) return 0;
  }

  return 1;
}



/**
 * Generic CSSProperty
 */

static int GenericCSSPropertyValue_emit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  const SAC_LexicalUnit **it;

  it = property->begin;
  if (it != property->end) {
    if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    while (++it != property->end) {
      if (fprintf(out, " ") < 0) return 1;
      if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    }
  }

  return 0;
}



/**
 * Shorthand CSSProperty
 */

static int BoxShorthandCSSPropertyValue_emit(
  const CSSOM_CSSPropertyValue *property, FILE *out);



static int GenericShorthandCSSPropertyValue_emit(
  const CSSOM_CSSPropertyValue *property, FILE *out);



static const SAC_LexicalUnit** CSSPropertyValue_walk(
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end);



static const SAC_LexicalUnit** CSSPropertyValue_genericShorthand(
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (&begin[1] == end && CSSOM_LexicalUnit_isInherit(begin[0])) {

    for (i = 0; i < size; ++i)
      _CSSOM_SET_RANGE(values[i], initial[i].type, begin, end);

  } else {

    tail = CSSPropertyValue_walk(initial, values, size, begin, end);
    if (tail != end) return begin;

    for (i = 0; i < size; ++i) {
      if (values[i].begin != NULL) continue;

      values[i] = initial[i];
    }

  }

  return end;
}



static const SAC_LexicalUnit** CSSPropertyValue_boxShorthand(
  const CSSOM_CSSPropertyType *types, _CSSOM_PropertyHandler handler,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  struct _CSSOM_LexicalUnitRange value;
  switch (end - begin) {
    case 1:
      if (!CSSOM_LexicalUnit_isInherit(begin[0]) && handler(begin, end,
        &value) != end)
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[1], types[1], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[2], types[2], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[3], types[3], &begin[0], &begin[1]);

      break;
    case 2:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values[2], types[2], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[3], types[3], &begin[1], &begin[2]);

      break;
    case 3:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values[2], types[2], &begin[2], &begin[3]);
      _CSSOM_SET_RANGE(values[3], types[3], &begin[1], &begin[2]);

      break;
    case 4:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3] ||
        handler(&begin[3], &begin[4], &value) != &begin[4])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values[2], types[2], &begin[2], &begin[3]);
      _CSSOM_SET_RANGE(values[3], types[3], &begin[3], &begin[4]);

      break;
  }

  return end;
}



/**
 * background
 */

static const SAC_LexicalUnit** CSSPropertyValue_background(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end, 
  struct _CSSOM_LexicalUnitRange *values)
{
  static const SAC_LexicalUnit *color[] = {
    &unit_transparent
  };

  static const SAC_LexicalUnit *image[] = {
    &unit_none
  };

  static const SAC_LexicalUnit *repeat[] = {
    &unit_repeat
  };

  static const SAC_LexicalUnit *attachment[] = {
    &unit_scroll
  };

  static const SAC_LexicalUnit *position[] = {
    &unit_0pct, &unit_0pct
  };

  static const struct _CSSOM_LexicalUnitRange
  initial[_CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes)] = {
    { CSSOM_BACKGROUND_COLOR_PROPERTY, _CSSOM_INITIAL(color) },
    { CSSOM_BACKGROUND_IMAGE_PROPERTY, _CSSOM_INITIAL(image) },
    { CSSOM_BACKGROUND_REPEAT_PROPERTY, _CSSOM_INITIAL(repeat) },
    { CSSOM_BACKGROUND_ATTACHMENT_PROPERTY, _CSSOM_INITIAL(attachment) },
    { CSSOM_BACKGROUND_POSITION_PROPERTY, _CSSOM_INITIAL(position) }
  };

  if (CSSPropertyValue_genericShorthand(initial, &values[1],
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes), begin, end) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_PROPERTY, begin, end);
  return end;
}



/**
 * border-collapse
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderCollapse(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("collapse", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("separate", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderCollapse(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderCollapse(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_COLLAPSE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderColorToken(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(CSSOM_CSSPropertyValue_borderColorSubtypes,
    CSSPropertyValue_borderColorToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_COLOR_PROPERTY, begin, end);
  return end;
}



/**
 * border-spacing
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderSpacing(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
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



static const SAC_LexicalUnit** CSSPropertyValue_borderSpacing(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderSpacing(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_SPACING_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderStyleToken(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = borderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(CSSOM_CSSPropertyValue_borderStyleSubtypes,
    CSSPropertyValue_borderStyleToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_STYLE_PROPERTY, begin, end);
  return end;
}



/**
 * border-top-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isBorderColor(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-right-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderRightColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_RIGHT_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-bottom-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderBottomColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_BOTTOM_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-left-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderLeftColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_LEFT_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-top-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (borderStyle(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-right-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderRightStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_RIGHT_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-bottom-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderBottomStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-left-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderLeftStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderStyle(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_LEFT_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-top-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isBorderWidthToken(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-right-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderRightWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-bottom-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderBottomWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-left-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderLeftWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderWidth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_LEFT_WIDTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_borderWidthToken(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = isBorderWidthToken(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(CSSOM_CSSPropertyValue_borderWidthSubtypes,
    CSSPropertyValue_borderWidthToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values[0], CSSOM_BORDER_WIDTH_PROPERTY, begin, end);
  return end;
}



static const SAC_LexicalUnit** CSSPropertyValue_whatever(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  _CSSOM_SET_RANGE(values[0], 0, begin, end);
  return end;
}



struct _CSSOM_CSSPropertyValue_settings {
  const char *name;
  int (*emit)(const CSSOM_CSSPropertyValue *property, FILE *out);
  const CSSOM_CSSPropertyType *subtypes;
  size_t nsubtypes;
  _CSSOM_PropertyHandler handler;
};



static const struct _CSSOM_CSSPropertyValue_settings settings[] = {
  /* CSSOM_AZIMUTH_PROPERTY */
  { "azimuth",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_azimuth },
  /* CSSOM_BACKGROUND_PROPERTY */
  { "background",
    &GenericShorthandCSSPropertyValue_emit,
    CSSOM_CSSPropertyValue_backgroundSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes),
    CSSPropertyValue_background },
  /* CSSOM_BACKGROUND_ATTACHMENT_PROPERTY */
  { "background-attachment",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundAttachment },
  /* CSSOM_BACKGROUND_COLOR_PROPERTY */
  { "background-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundColor },
  /* CSSOM_BACKGROUND_IMAGE_PROPERTY */
  { "background-image",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundImage },
  /* CSSOM_BACKGROUND_POSITION_PROPERTY */
  { "background-position",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundPosition },
  /* CSSOM_BACKGROUND_REPEAT_PROPERTY */
  { "background-repeat",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundRepeat },
  /* CSSOM_BORDER_PROPERTY */
  { "border",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_BORDER_COLLAPSE_PROPERTY */
  { "border-collapse",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderCollapse },
  /* CSSOM_BORDER_COLOR_PROPERTY */
  { "border-color",
    &BoxShorthandCSSPropertyValue_emit,
    CSSOM_CSSPropertyValue_borderColorSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderColorSubtypes),
    CSSPropertyValue_borderColor },
  /* CSSOM_BORDER_SPACING_PROPERTY */
  { "border-spacing",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderSpacing },
  /* CSSOM_BORDER_STYLE_PROPERTY */
  { "border-style",
    &BoxShorthandCSSPropertyValue_emit,
    CSSOM_CSSPropertyValue_borderStyleSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderStyleSubtypes),
    CSSPropertyValue_borderStyle },
  /* CSSOM_BORDER_TOP_PROPERTY */
  { "border-top",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_BORDER_RIGHT_PROPERTY */
  { "border-right",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_BORDER_BOTTOM_PROPERTY */
  { "border-bottom",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_BORDER_LEFT_PROPERTY */
  { "border-left",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_BORDER_TOP_COLOR_PROPERTY */
  { "border-top-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderTopColor },
  /* CSSOM_BORDER_RIGHT_COLOR_PROPERTY */
  { "border-right-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderRightColor },
  /* CSSOM_BORDER_BOTTOM_COLOR_PROPERTY */
  { "border-bottom-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderBottomColor },
  /* CSSOM_BORDER_LEFT_COLOR_PROPERTY */
  { "border-left-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderLeftColor },
  /* CSSOM_BORDER_TOP_STYLE_PROPERTY */
  { "border-top-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderTopStyle },
  /* CSSOM_BORDER_RIGHT_STYLE_PROPERTY */
  { "border-right-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderRightStyle },
  /* CSSOM_BORDER_BOTTOM_STYLE_PROPERTY */
  { "border-bottom-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderBottomStyle },
  /* CSSOM_BORDER_LEFT_STYLE_PROPERTY */
  { "border-left-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderLeftStyle },
  /* CSSOM_BORDER_TOP_WIDTH_PROPERTY */
  { "border-top-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderTopWidth },
  /* CSSOM_BORDER_RIGHT_WIDTH_PROPERTY */
  { "border-right-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderRightWidth },
  /* CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY */
  { "border-bottom-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderBottomWidth },
  /* CSSOM_BORDER_LEFT_WIDTH_PROPERTY */
  { "border-left-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_borderLeftWidth },
  /* CSSOM_BORDER_WIDTH_PROPERTY */
  { "border-width",
    &BoxShorthandCSSPropertyValue_emit,
    CSSOM_CSSPropertyValue_borderWidthSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderWidthSubtypes),
    CSSPropertyValue_borderWidth },
  /* CSSOM_BOTTOM_PROPERTY */
  { "bottom",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CAPTION_SIDE_PROPERTY */
  { "caption-side",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CLEAR_PROPERTY */
  { "clear",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CLIP_PROPERTY */
  { "clip",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_COLOR_PROPERTY */
  { "color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CONTENT_PROPERTY */
  { "content",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_COUNTER_INCREMENT_PROPERTY */
  { "counter",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_COUNTER_RESET_PROPERTY */
  { "counter-reset",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CUE_PROPERTY */
  { "cue",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CUE_AFTER_PROPERTY */
  { "cue-after",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CUE_BEFORE_PROPERTY */
  { "cue-before",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_CURSOR_PROPERTY */
  { "cursor",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_DIRECTION_PROPERTY */
  { "direction",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_DISPLAY_PROPERTY */
  { "display",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_ELEVATION_PROPERTY */
  { "elevation",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_EMPTY_CELLS_PROPERTY */
  { "empty-cells",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FLOAT_PROPERTY */
  { "float",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_PROPERTY */
  { "font",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_FAMILY_PROPERTY */
  { "font-family",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_SIZE_PROPERTY */
  { "font-size",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_SIZE_ADJUST_PROPERTY */
  { "font-size-adjust",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_STRETCH_PROPERTY */
  { "font-stretch",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_STYLE_PROPERTY */
  { "font-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_VARIANT_PROPERTY */
  { "font-variant",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_FONT_WEIGHT_PROPERTY */
  { "font-weight",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_HEIGHT_PROPERTY */
  { "height",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LEFT_PROPERTY */
  { "left",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LETTER_SPACING_PROPERTY */
  { "letter-spacing",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LINE_HEIGHT_PROPERTY */
  { "line-height",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LIST_STYLE_PROPERTY */
  { "list-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LIST_STYLE_IMAGE_PROPERTY */
  { "list-style-image",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LIST_STYLE_POSITION_PROPERTY */
  { "list-style-position",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_LIST_STYLE_TYPE_PROPERTY */
  { "list-style-type",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARGIN_PROPERTY */
  { "margin",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARGIN_TOP_PROPERTY */
  { "margin-top",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARGIN_RIGHT_PROPERTY */
  { "margin-right",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARGIN_BOTTOM_PROPERTY */
  { "margin-bottom",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARGIN_LEFT_PROPERTY */
  { "margin-left",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARKER_OFFSET_PROPERTY */
  { "marker-offset",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MARKS_PROPERTY */
  { "marks",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MAX_HEIGHT_PROPERTY */
  { "max-height",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MAX_WIDTH_PROPERTY */
  { "max-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MIN_HEIGHT_PROPERTY */
  { "min-height",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_MIN_WIDTH_PROPERTY */
  { "min-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_ORPHANS_PROPERTY */
  { "orphans",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_OUTLINE_PROPERTY */
  { "outline",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_OUTLINE_COLOR_PROPERTY */
  { "outline-color",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_OUTLINE_STYLE_PROPERTY */
  { "outline-style",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_OUTLINE_WIDTH_PROPERTY */
  { "outline-width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_OVERFLOW_PROPERTY */
  { "overflow",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PADDING_PROPERTY */
  { "padding",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PADDING_TOP_PROPERTY */
  { "padding-top",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PADDING_RIGHT_PROPERTY */
  { "padding-right",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PADDING_BOTTOM_PROPERTY */
  { "padding-bottom",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PADDING_LEFT_PROPERTY */
  { "padding-left",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAGE_PROPERTY */
  { "page",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAGE_BREAK_AFTER_PROPERTY */
  { "page-break-after",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAGE_BREAK_BEFORE_PROPERTY */
  { "page-break-before",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAGE_BREAK_INSIDE_PROPERTY */
  { "page-break-inside",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAUSE_PROPERTY */
  { "pause",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAUSE_AFTER_PROPERTY */
  { "pause-after",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PAUSE_BEFORE_PROPERTY */
  { "pause-before",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PITCH_PROPERTY */
  { "pitch",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PITCH_RANGE_PROPERTY */
  { "pitch-range",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_PLAY_DURING_PROPERTY */
  { "play-during",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_POSITION_PROPERTY */
  { "position",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_QUOTES_PROPERTY */
  { "quotes",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_RICHNESS_PROPERTY */
  { "richness",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_RIGHT_PROPERTY */
  { "right",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SIZE_PROPERTY */
  { "size",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SPEAK_PROPERTY */
  { "speak",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SPEAK_HEADER_PROPERTY */
  { "speak-header",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SPEAK_NUMERAL_PROPERTY */
  { "speak-numeral",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SPEAK_PUNCTUATION_PROPERTY */
  { "speak-punctuation",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SPEECH_RATE_PROPERTY */
  { "speech-rate",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_SRC_PROPERTY */
  { "src",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_STRESS_PROPERTY */
  { "stress",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TABLE_LAYOUT_PROPERTY */
  { "table-layout",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TEXT_ALIGN_PROPERTY */
  { "text-align",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TEXT_DECORATION_PROPERTY */
  { "text-decoration",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TEXT_INDENT_PROPERTY */
  { "text-indent",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TEXT_SHADOW_PROPERTY */
  { "text-shadow",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TEXT_TRANSFORM_PROPERTY */
  { "text-transform",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_TOP_PROPERTY */
  { "top",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_UNICODE_BIDI_PROPERTY */
  { "unicode-bidi",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_VERTICAL_ALIGN_PROPERTY */
  { "vertical-align",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_VISIBILITY_PROPERTY */
  { "visibility",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_VOICE_FAMILY_PROPERTY */
  { "voice-family",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_VOLUME_PROPERTY */
  { "volume",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_WHITE_SPACE_PROPERTY */
  { "white-space",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_WIDOWS_PROPERTY */
  { "widows",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_WIDTH_PROPERTY */
  { "width",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_WORD_SPACING_PROPERTY */
  { "word-spacing",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever },
  /* CSSOM_Z_INDEX_PROPERTY */
  { "z-index",
    &GenericCSSPropertyValue_emit,
    NULL,
    0,
    CSSPropertyValue_whatever }
};



static int isInheritShorthand(const CSSOM_CSSPropertyValue *shorthand) {
  size_t i;
  CSSOM_CSSPropertyValue *property;

  for (i = 0; i < settings[shorthand->type].nsubtypes; ++i) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, settings[shorthand->type].subtypes[i]);

    if (property == NULL) return 0;
    if (property->end - property->begin != 1) return 0;
    if (CSSOM_LexicalUnit_isInherit(property->begin[0]) == 0) return 0;
  }
  return 1;
}



static int GenericShorthandCSSPropertyValue_emit(
  const CSSOM_CSSPropertyValue *property, FILE *out)
{
  size_t i;
  int emited;
  const char *cssText;

  if (isInheritShorthand(property)) {
    cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
      property->parentValues, settings[property->type].subtypes[0]);
    if (fprintf(out, "%s", cssText) < 0) return 1;
    return 0;
  }

  emited = 0;
  for (i = 0; i < settings[property->type].nsubtypes; ++i) {
    cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
      property->parentValues, settings[property->type].subtypes[i]);
    if (cssText != NULL) {
      if (emited) {
        if (fprintf(out, " ") < 0) return 1;
      } else {
        emited = 1;
      }
      if (fprintf(out, "%s", cssText) < 0) return 1;
    }
  }

  return 0;
}



static int BoxShorthandCSSPropertyValue_emit(
  const CSSOM_CSSPropertyValue *property, FILE *out)
{
  CSSOM_CSSPropertyValue *top;
  CSSOM_CSSPropertyValue *right;
  CSSOM_CSSPropertyValue *bottom;
  CSSOM_CSSPropertyValue *left;
  CSSOM_CSSPropertyValue *print[4] = { NULL, NULL, NULL, NULL };
  size_t i;
  const char *cssText;
  int topbottom;
  int rightleft;
  int topright;

  top = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, settings[property->type].subtypes[0]);
  right = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, settings[property->type].subtypes[1]);
  bottom = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, settings[property->type].subtypes[2]);
  left = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, settings[property->type].subtypes[3]);



  /**
   * Imposible shorthand
   */

  if (top == NULL || right == NULL || bottom == NULL || left == NULL) return 0;

  topbottom = CSSPropertyValue_eq(top, bottom);
  rightleft = CSSPropertyValue_eq(right, left);
  topright = CSSPropertyValue_eq(top, right);



  /**
   * Imposible shorthand
   */

  if (!(rightleft && topbottom && topright)) {
    if (CSSPropertyValue_isInherit(top) ||
      CSSPropertyValue_isInherit(right) ||
      CSSPropertyValue_isInherit(bottom) ||
      CSSPropertyValue_isInherit(left))
    {
      return 0;
    }
  }

  if (rightleft) {
    if (topbottom) {
      if (topright) {
        print[0] = top;
      } else {
        print[0] = top;
        print[1] = right;
      }
    } else {
      print[0] = top;
      print[1] = right;
      print[2] = bottom;
    }
  } else {
    print[0] = top;
    print[1] = right;
    print[2] = bottom;
    print[3] = left;
  }

  for (i = 0; i < 4; ++i) {
    if (print[i] == NULL) break;

    cssText = CSSOM_CSSPropertyValue_cssText(print[i]);

    if (cssText == NULL) return 1;
    if (i != 0) {
      if (fprintf(out, " ") < 0) return 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  return 0;
}



static const SAC_LexicalUnit** CSSPropertyValue_walk(
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (begin == end) return end;

  for (i = 0; i < size; ++i) {
    if (values[i].begin != NULL) continue;

    tail = settings[initial[i].type].handler(begin, end, &values[i]);
    if (tail == begin) continue;

    if (CSSPropertyValue_walk(initial, values, size, tail, end) == end)
      return end;

    values[i].type = 0;
    values[i].begin = NULL;
    values[i].end = NULL;
  }

  return begin;
}



static CSSOM_CSSPropertyValue* CSSPropertyValue_alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **holder, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, SAC_Boolean important)
{
  CSSOM_CSSPropertyValue *property;

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) return NULL;

  property->handles = 1;
  property->parentValues = parentValues;
  property->shorthand = shorthand;
  property->parser = NULL;
  property->type = type;
  property->name = CSSOM__properties(cssom)[type];
  property->holder = holder;
  property->begin = begin;
  property->end = end;
  property->important = important;
  property->cssText = NULL;

  return property;
}



static CSSOM_CSSPropertyValue* assignProperties(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, const SAC_LexicalUnit **holder,
  struct _CSSOM_LexicalUnitRange *values, size_t size, SAC_Boolean important,
  int *error)
{
  CSSOM_CSSPropertyValue *shorthand;
  CSSOM_CSSPropertyValue *property;
  size_t i;
  int rval;

  if (values[0].begin == NULL) {
    if (error != NULL) *error = 1;
    return NULL;
  }

  shorthand = CSSPropertyValue_alloc(cssom, parentValues, NULL,
      values[0].type, holder, values[0].begin, values[0].end, important);
  if (shorthand == NULL) {
    if (error != NULL) *error = -1;
    return NULL;
  }

  for (i = 1; i < size; ++i) {
    if (values[i].begin == NULL) continue;

    property = CSSPropertyValue_alloc(cssom, parentValues, shorthand,
      values[i].type, NULL, values[i].begin, values[i].end, important);
    if (property == NULL) {
      if (error != NULL) *error = -1;
      return NULL;
    }

    if ((rval = CSSOM_CSSStyleDeclarationValue__assignProperty(parentValues,
      property)) != 0)
    {
      CSSOM_CSSPropertyValue_release(property);
      if (error != NULL) *error = rval;
      return NULL;
    }
  }

  return shorthand;
}



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyType type, const SAC_LexicalUnit *value,
  SAC_Boolean important, int *error)
{
  /**
   * The largest one.
   */
  struct _CSSOM_LexicalUnitRange values[] = {
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL }
  };

  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  const SAC_LexicalUnit **holder;
  CSSOM_CSSPropertyValue *property;

  if (value->lexicalUnitType != SAC_SUB_EXPRESSION) {
    holder = (const SAC_LexicalUnit**)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * 2);
    if (holder == NULL) return NULL;
    holder[0] = value;
    holder[1] = NULL;
    begin = &holder[0];
    end = &holder[1];
  } else {
    holder = NULL;
    begin = (const SAC_LexicalUnit**)value->desc.subValues;
    end = begin;
    while (*end != NULL) ++end;
  }

  if (settings[type].handler(begin, end, values) != end) {
    CSSOM_free(holder);
    if (error != NULL) *error = 1;
    return NULL;
  }

  /**
   * FIXME: Drop this line after CSSPropertyValue_whatever cleanup.
   */
  values[0].type = type;

  property = assignProperties(cssom, parentValues, holder, values,
    settings[type].nsubtypes + 1, important, error);
  if (property == NULL) {
    CSSOM_free(holder);
    if (error != NULL) *error = 1;
    return NULL;
  }
  
  if (error != NULL) *error = 0;
  return property;
}



void CSSOM_CSSPropertyValue_acquire(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  ++property->handles;
  CSSOM_CSSStyleDeclarationValue_acquire(property->parentValues);
  CSSOM_CSSPropertyValue_acquire(property->shorthand);
}



void CSSOM_CSSPropertyValue_release(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  assert(property->handles > 0);
  --property->handles;
  if (property->handles > 0) {
    CSSOM_CSSPropertyValue_release(property->shorthand);
    CSSOM_CSSStyleDeclarationValue_release(property->parentValues);
    return;
  }

  CSSOM_native_free(property->cssText);
  CSSOM_free(property->holder);
  SAC_DisposeParser(property->parser);
  CSSOM_free(property);
}



const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property)
{
  return property->name;
}



const char* CSSOM_CSSPropertyValue_cssText(
  const CSSOM_CSSPropertyValue *property)
{
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(property->cssText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (settings[property->type].emit(property, out) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_CSSPropertyValue*)property)->cssText = buf;

  return property->cssText;
}



static void CSSPropertyValue_swap(
  CSSOM_CSSPropertyValue *lhs, CSSOM_CSSPropertyValue *rhs)
{
  SWAP(lhs->parentValues, rhs->parentValues);
  SWAP(lhs->shorthand, rhs->shorthand);
  SWAP(lhs->parser, rhs->parser);
  SWAPS(lhs->type, rhs->type);
  SWAP(lhs->name, rhs->name);
  SWAP(lhs->holder, rhs->holder);
  SWAP(lhs->begin, rhs->begin);
  SWAP(lhs->end, rhs->end);
  SWAPS(lhs->important, rhs->important);
  SWAP(lhs->cssText, rhs->cssText);
}



void CSSOM_CSSPropertyValue_setCSSText(CSSOM_CSSPropertyValue *property,
  const char * cssText)
{
  const CSSOM *cssom;
  CSSOM_CSSPropertyValue *newProperty;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(
        CSSOM_CSSStyleDeclarationValue__parentStyle(property->parentValues))));
  newProperty = CSSOM__parsePropertyValue(cssom, property->parentValues,
    property->type, cssText, strlen(cssText), NULL, 0);
  if (newProperty == NULL) return;

  CSSPropertyValue_swap(property, newProperty);

  CSSOM_CSSPropertyValue_release(newProperty);
}



int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property) {
  return property->important == SAC_TRUE ? 1 : 0;
}




void CSSOM_CSSPropertyValue__keepParser(CSSOM_CSSPropertyValue *property,
  SAC_Parser parser)
{
  assert(property->parser == NULL);
  property->parser = parser;
}
