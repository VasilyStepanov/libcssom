#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclarationValue.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



#define ASIZE(array) \
  (sizeof(array) / sizeof(array[0]))

#define INITIAL(initial) \
  (initial), &(initial)[ASIZE(initial)]



struct _CSSOM_LexicalUnitRange {
  CSSOM_CSSPropertyType type;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
};

#define SET_RANGE(range, type_val, begin_val, end_val) \
  do { \
    (range).type = (type_val); \
    (range).begin = (begin_val); \
    (range).end = (end_val); \
  } while (0)

typedef const SAC_LexicalUnit**(*PropertyHandler)(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);



static SAC_LexicalUnit unit_transparent;
static SAC_LexicalUnit unit_none;
static SAC_LexicalUnit unit_repeat;
static SAC_LexicalUnit unit_scroll;
static SAC_LexicalUnit unit_0pct;

static const CSSOM_CSSPropertyType shorthand_background[] = {
  CSSOM_BACKGROUND_COLOR_PROPERTY,
  CSSOM_BACKGROUND_IMAGE_PROPERTY,
  CSSOM_BACKGROUND_REPEAT_PROPERTY,
  CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
  CSSOM_BACKGROUND_POSITION_PROPERTY
};

static const CSSOM_CSSPropertyType shorthand_borderColor[] = {
  CSSOM_BORDER_TOP_COLOR_PROPERTY,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY
};

static const CSSOM_CSSPropertyType shorthand_borderStyle[] = {
  CSSOM_BORDER_TOP_STYLE_PROPERTY,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY
};

static const CSSOM_CSSPropertyType shorthand_borderWidth[] = {
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



static int isInherit(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_INHERIT) return 1; 
  return 0;
}



static int isAngle(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_DEGREE) {
    return 1;
  } else if (value->lexicalUnitType == SAC_GRADIAN) {
    return 1;
  } else if (value->lexicalUnitType == SAC_RADIAN) {
    return 1;
  }
  return 0;
}



static int isLength(const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
      return 1;
    case SAC_REAL:
      if (value->desc.real == 0) return 1;
      break;
    case SAC_INTEGER:
      if (value->desc.integer == 0) return 1;
      break;
    default:
      break;
  }
  return 0;
}



static int isNonNegativeLength(const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
      if (value->desc.dimension.value.sreal >= 0) return 1;
      break;
    case SAC_REAL:
      if (value->desc.real == 0) return 1;
      break;
    case SAC_INTEGER:
      if (value->desc.integer == 0) return 1;
      break;
    default:
      break;
  }
  return 0;
}



static int isColor(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_RGBCOLOR) {
    const SAC_LexicalUnit *red;
    const SAC_LexicalUnit *green;
    const SAC_LexicalUnit *blue;

    if (value->desc.function.parameters[0] == NULL) return 0;
    red = value->desc.function.parameters[0];


    if (red->lexicalUnitType != SAC_INTEGER) return 0;
    if (red->desc.integer < 0 || red->desc.integer > 255) return 0;

    if (value->desc.function.parameters[1] == NULL) return 0;
    if (value->desc.function.parameters[1]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[2] == NULL) return 0;
    green = value->desc.function.parameters[2];

    if (green->lexicalUnitType != SAC_INTEGER) return 0;
    if (green->desc.integer < 0 || green->desc.integer > 255) return 0;

    if (value->desc.function.parameters[3] == NULL) return 0;
    if (value->desc.function.parameters[3]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[4] == NULL) return 0;
    blue = value->desc.function.parameters[4];

    if (blue->lexicalUnitType != SAC_INTEGER) return 0;
    if (blue->desc.integer < 0 || blue->desc.integer > 255) return 0;

    if (value->desc.function.parameters[5] != NULL) return 0;

    return 1;
  } else if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("aqua", value->desc.ident) == 0) return 1;
    if (strcmp("black", value->desc.ident) == 0) return 1;
    if (strcmp("blue", value->desc.ident) == 0) return 1;
    if (strcmp("fuchsia", value->desc.ident) == 0) return 1;
    if (strcmp("gray", value->desc.ident) == 0) return 1;
    if (strcmp("green", value->desc.ident) == 0) return 1;
    if (strcmp("lime", value->desc.ident) == 0) return 1;
    if (strcmp("maroon", value->desc.ident) == 0) return 1;
    if (strcmp("navy", value->desc.ident) == 0) return 1;
    if (strcmp("olive", value->desc.ident) == 0) return 1;
    if (strcmp("orange", value->desc.ident) == 0) return 1;
    if (strcmp("purple", value->desc.ident) == 0) return 1;
    if (strcmp("red", value->desc.ident) == 0) return 1;
    if (strcmp("silver", value->desc.ident) == 0) return 1;
    if (strcmp("teal", value->desc.ident) == 0) return 1;
    if (strcmp("white", value->desc.ident) == 0) return 1;
    if (strcmp("yellow", value->desc.ident) == 0) return 1;
  }
  return 0;
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
  } else if (isNonNegativeLength(value)) {
    return 1;
  }
  return 0;
}



static int isUrl(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_URI) return 1;
  return 0;
}



static int isPercentage(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_PERCENTAGE) return 1;
  return 0;
}



static const SAC_LexicalUnit** isBorderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isColor(begin[0])) {
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



struct _CSSOM_CSSPropertyValue_vtable {
  const CSSOM_CSSPropertyType *types;
  const size_t ntypes;
  int (*emit)(const CSSOM_CSSPropertyValue *property, FILE *out);
};



struct _CSSOM_CSSPropertyValue {
  const struct _CSSOM_CSSPropertyValue_vtable *vtable;
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
  return isInherit(property->begin[0]);
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



static int CSSPropertyValue_emit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  return property->vtable->emit(property, out);
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



static const struct _CSSOM_CSSPropertyValue_vtable
GenericCSSPropertyValue_vtable = {
  NULL,
  0,
  &GenericCSSPropertyValue_emit
};



/**
 * Shorthand CSSProperty
 */

static int isInheritShorthand(const CSSOM_CSSPropertyValue *shorthand) {
  size_t i;
  CSSOM_CSSPropertyValue *property;

  for (i = 0; i < shorthand->vtable->ntypes; ++i) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, shorthand->vtable->types[i]);

    if (property == NULL) return 0;
    if (property->end - property->begin != 1) return 0;
    if (isInherit(property->begin[0]) == 0) return 0;
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
      property->parentValues, property->vtable->types[0]);
    if (fprintf(out, "%s", cssText) < 0) return 1;
    return 0;
  }

  emited = 0;
  for (i = 0; i < property->vtable->ntypes; ++i) {
    cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
      property->parentValues, property->vtable->types[i]);
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
    property->parentValues, property->vtable->types[0]);
  right = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, property->vtable->types[1]);
  bottom = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, property->vtable->types[2]);
  left = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, property->vtable->types[3]);



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



static const struct _CSSOM_CSSPropertyValue_vtable
BackgroundCSSPropertyValue_vtable = {
  shorthand_background,
  ASIZE(shorthand_background),
  &GenericShorthandCSSPropertyValue_emit
};



static const struct _CSSOM_CSSPropertyValue_vtable
BorderColorCSSPropertyValue_vtable = {
  shorthand_borderColor,
  ASIZE(shorthand_borderColor),
  &BoxShorthandCSSPropertyValue_emit
};



static const struct _CSSOM_CSSPropertyValue_vtable
BorderStyleCSSPropertyValue_vtable = {
  shorthand_borderStyle,
  ASIZE(shorthand_borderStyle),
  &BoxShorthandCSSPropertyValue_emit
};



static const struct _CSSOM_CSSPropertyValue_vtable
BorderWidthCSSPropertyValue_vtable = {
  shorthand_borderWidth,
  ASIZE(shorthand_borderWidth),
  &BoxShorthandCSSPropertyValue_emit
};



static const struct _CSSOM_CSSPropertyValue_vtable *vtables[] = {
  &GenericCSSPropertyValue_vtable, /* CSSOM_AZIMUTH_PROPERTY */
  &BackgroundCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_ATTACHMENT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_IMAGE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_POSITION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BACKGROUND_REPEAT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_COLLAPSE_PROPERTY */
  &BorderColorCSSPropertyValue_vtable, /* CSSOM_BORDER_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_SPACING_PROPERTY */
  &BorderStyleCSSPropertyValue_vtable, /* CSSOM_BORDER_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_TOP_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_RIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_BOTTOM_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_LEFT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_TOP_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_RIGHT_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_BOTTOM_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_LEFT_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_TOP_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_RIGHT_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_BOTTOM_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_LEFT_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_TOP_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_RIGHT_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BORDER_LEFT_WIDTH_PROPERTY */
  &BorderWidthCSSPropertyValue_vtable, /* CSSOM_BORDER_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_BOTTOM_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CAPTION_SIDE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CLEAR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CLIP_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CONTENT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_COUNTER_INCREMENT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_COUNTER_RESET_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CUE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CUE_AFTER_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CUE_BEFORE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_CURSOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_DIRECTION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_DISPLAY_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_ELEVATION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_EMPTY_CELLS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FLOAT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_FAMILY_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_SIZE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_SIZE_ADJUST_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_STRETCH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_VARIANT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_FONT_WEIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_HEIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LEFT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LETTER_SPACING_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LINE_HEIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LIST_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LIST_STYLE_IMAGE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LIST_STYLE_POSITION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_LIST_STYLE_TYPE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARGIN_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARGIN_TOP_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARGIN_RIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARGIN_BOTTOM_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARGIN_LEFT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARKER_OFFSET_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MARKS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MAX_HEIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MAX_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MIN_HEIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_MIN_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_ORPHANS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_OUTLINE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_OUTLINE_COLOR_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_OUTLINE_STYLE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_OUTLINE_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_OVERFLOW_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PADDING_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PADDING_TOP_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PADDING_RIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PADDING_BOTTOM_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PADDING_LEFT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAGE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAGE_BREAK_AFTER_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAGE_BREAK_BEFORE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAGE_BREAK_INSIDE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAUSE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAUSE_AFTER_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PAUSE_BEFORE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PITCH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PITCH_RANGE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_PLAY_DURING_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_POSITION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_QUOTES_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_RICHNESS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_RIGHT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SIZE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SPEAK_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SPEAK_HEADER_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SPEAK_NUMERAL_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SPEAK_PUNCTUATION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SPEECH_RATE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_SRC_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_STRESS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TABLE_LAYOUT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TEXT_ALIGN_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TEXT_DECORATION_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TEXT_INDENT_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TEXT_SHADOW_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TEXT_TRANSFORM_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_TOP_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_UNICODE_BIDI_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_VERTICAL_ALIGN_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_VISIBILITY_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_VOICE_FAMILY_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_VOLUME_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_WHITE_SPACE_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_WIDOWS_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_WIDTH_PROPERTY */
  &GenericCSSPropertyValue_vtable, /* CSSOM_WORD_SPACING_PROPERTY */
  &GenericCSSPropertyValue_vtable /* CSSOM_Z_INDEX_PROPERTY */
};



static const SAC_LexicalUnit** CSSPropertyValue_walk(
  const PropertyHandler *handlers, struct _CSSOM_LexicalUnitRange *values,
  size_t size, const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (begin == end) return end;

  for (i = 0; i < size; ++i) {
    if (values[i].begin != NULL) continue;

    tail = handlers[i](begin, end, &values[i]);
    if (tail == begin) continue;

    if (CSSPropertyValue_walk(handlers, values, size, tail, end) == end)
      return end;

    values[i].type = 0;
    values[i].begin = NULL;
    values[i].end = NULL;
  }

  return begin;
}



static const SAC_LexicalUnit** CSSPropertyValue_genericShorthand(
  const PropertyHandler *handlers,
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (&begin[1] == end && isInherit(begin[0])) {

    for (i = 0; i < size; ++i)
      SET_RANGE(values[i], initial[i].type, begin, end);

  } else {

    tail = CSSPropertyValue_walk(handlers, values, size, begin, end);
    if (tail != end) return begin;

    for (i = 0; i < size; ++i) {
      if (values[i].begin != NULL) continue;

      values[i] = initial[i];
    }

  }

  return end;
}



static const SAC_LexicalUnit** CSSPropertyValue_boxShorthand(
  const CSSOM_CSSPropertyType *types, PropertyHandler handler,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  struct _CSSOM_LexicalUnitRange value;
  switch (end - begin) {
    case 1:
      if (!isInherit(begin[0]) && handler(begin, end, &value) != end) {
        return begin;
      }

      SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      SET_RANGE(values[1], types[1], &begin[0], &begin[1]);
      SET_RANGE(values[2], types[2], &begin[0], &begin[1]);
      SET_RANGE(values[3], types[3], &begin[0], &begin[1]);

      break;
    case 2:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2])
      {
        return begin;
      }

      SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      SET_RANGE(values[2], types[2], &begin[0], &begin[1]);
      SET_RANGE(values[3], types[3], &begin[1], &begin[2]);

      break;
    case 3:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3])
      {
        return begin;
      }

      SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      SET_RANGE(values[2], types[2], &begin[2], &begin[3]);
      SET_RANGE(values[3], types[3], &begin[1], &begin[2]);

      break;
    case 4:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3] ||
        handler(&begin[3], &begin[4], &value) != &begin[4])
      {
        return begin;
      }

      SET_RANGE(values[0], types[0], &begin[0], &begin[1]);
      SET_RANGE(values[1], types[1], &begin[1], &begin[2]);
      SET_RANGE(values[2], types[2], &begin[2], &begin[3]);
      SET_RANGE(values[3], types[3], &begin[3], &begin[4]);

      break;
  }

  return end;
}



/**
 * azimuth
 */

static int azimuth_isAngleIdent(const char *ident) {
  if (strcmp("left-side", ident) == 0) return 1;
  if (strcmp("far-left", ident) == 0) return 1;
  if (strcmp("left", ident) == 0) return 1;
  if (strcmp("center-left", ident) == 0) return 1;
  if (strcmp("center", ident) == 0) return 1;
  if (strcmp("center-right", ident) == 0) return 1;
  if (strcmp("right", ident) == 0) return 1;
  if (strcmp("far-right", ident) == 0) return 1;
  if (strcmp("right-side", ident) == 0) return 1;
  return 0;
}



static const SAC_LexicalUnit** azimuth_angle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (strcmp("behind", begin[0]->desc.ident) == 0) {
        return &begin[1];
      }
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** azimuth_behind(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (azimuth_isAngleIdent(begin[0]->desc.ident)) {
        return &begin[1];
      }
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_readAzimuth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isAngle(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("leftwards", begin[0]->desc.ident) == 0) {
      return &begin[1];
    }
    if (strcmp("rightwards", begin[0]->desc.ident) == 0) {
      return &begin[1];
    }

    if (azimuth_isAngleIdent(begin[0]->desc.ident))
      return azimuth_angle(&begin[1], end);

    if (strcmp("behind", begin[0]->desc.ident) == 0)
      return azimuth_behind(&begin[1], end);

  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_azimuth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readAzimuth(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_AZIMUTH_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-attachment
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBackgroundAttachment(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("scroll", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("fixed", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundAttachment(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBackgroundAttachment(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BACKGROUND_ATTACHMENT_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBackgroundColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isColor(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("transparent", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBackgroundColor(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BACKGROUND_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-image
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBackgroundImage(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isUrl(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundImage(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBackgroundImage(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BACKGROUND_IMAGE_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-position
 */

static const SAC_LexicalUnit** backgroundPosition_horizontal(
  const SAC_LexicalUnit **expr)
{
  if (expr[0] == NULL) {
    return &expr[0];
  } else if (isPercentage(expr[0])) {
    return &expr[1];
  } else if (isLength(expr[0])) {
    return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("top", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("bottom", expr[0]->desc.ident) == 0) return &expr[1];
  }

  return &expr[0];
}



static const SAC_LexicalUnit** backgroundPosition_vertical(
  const SAC_LexicalUnit **expr)
{
  if (expr[0] == NULL) {
    return &expr[0];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("left", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("right", expr[0]->desc.ident) == 0) return &expr[1];
  }
  return &expr[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_readBackgroundPosition(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isPercentage(begin[0]) || isLength(begin[0])) {
    return backgroundPosition_horizontal(&begin[1]);
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {

    if (strcmp("left", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcmp("right", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcmp("top", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcmp("bottom", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcmp("center", begin[0]->desc.ident) == 0) {
      const SAC_LexicalUnit **tail;

      if (begin[1] == NULL) return &begin[1];

      tail = backgroundPosition_horizontal(&begin[1]);
      if (tail != &begin[1]) return tail;

      return backgroundPosition_vertical(&begin[1]);
    }

  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundPosition(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBackgroundPosition(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BACKGROUND_POSITION_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-repeat
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBackgroundRepeat(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("repeat", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("repeat-x", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("repeat-y", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("no-repeat", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundRepeat(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBackgroundRepeat(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BACKGROUND_REPEAT_PROPERTY, begin, tail);
  return tail;
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

  static const PropertyHandler handlers[ASIZE(shorthand_background)] = {
    CSSPropertyValue_backgroundColor,
    CSSPropertyValue_backgroundImage,
    CSSPropertyValue_backgroundRepeat,
    CSSPropertyValue_backgroundAttachment,
    CSSPropertyValue_backgroundPosition
  };

  static const struct _CSSOM_LexicalUnitRange
  initial[ASIZE(shorthand_background)] = {
    { CSSOM_BACKGROUND_COLOR_PROPERTY, INITIAL(color) },
    { CSSOM_BACKGROUND_IMAGE_PROPERTY, INITIAL(image) },
    { CSSOM_BACKGROUND_REPEAT_PROPERTY, INITIAL(repeat) },
    { CSSOM_BACKGROUND_ATTACHMENT_PROPERTY, INITIAL(attachment) },
    { CSSOM_BACKGROUND_POSITION_PROPERTY, INITIAL(position) }
  };

  if (CSSPropertyValue_genericShorthand(handlers, initial, &values[1],
    ASIZE(shorthand_background), begin, end) != end)
  {
    return begin;
  }

  SET_RANGE(values[0], CSSOM_BACKGROUND_PROPERTY, begin, end);
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
  } else if (isInherit(begin[0])) {
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

  SET_RANGE(values[0], CSSOM_BORDER_COLLAPSE_PROPERTY, begin, tail);
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

  SET_RANGE(values[0], CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(shorthand_borderColor,
    CSSPropertyValue_borderColorToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  SET_RANGE(values[0], CSSOM_BORDER_COLOR_PROPERTY, begin, end);
  return end;
}



/**
 * border-spacing
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderSpacing(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isLength(begin[0])) {
    if (&begin[1] != end && isLength(begin[1])) return &begin[2];
    return &begin[1];
  } else if (isInherit(begin[0])) {
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

  SET_RANGE(values[0], CSSOM_BORDER_SPACING_PROPERTY, begin, tail);
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

  SET_RANGE(values[0], CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(shorthand_borderStyle,
    CSSPropertyValue_borderStyleToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  SET_RANGE(values[0], CSSOM_BORDER_STYLE_PROPERTY, begin, end);
  return end;
}



/**
 * border-top-color
 * border-right-color
 * border-bottom-color
 * border-left-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderTopColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isBorderColor(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderTopColor(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BORDER_TOP_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-top-style
 * border-right-style
 * border-bottom-style
 * border-left-style
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderTopStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (borderStyle(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopStyle(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderTopStyle(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BORDER_TOP_STYLE_PROPERTY, begin, tail);
  return tail;
}



/**
 * border-top-width
 * border-right-width
 * border-bottom-width
 * border-left-width
 */

static const SAC_LexicalUnit** CSSPropertyValue_readBorderTopWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isBorderWidthToken(begin, end) == &begin[1]) {
    return &begin[1];
  } else if (isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_borderTopWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = CSSPropertyValue_readBorderTopWidth(begin, end);
  if (tail == begin) return begin;

  SET_RANGE(values[0], CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
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

  SET_RANGE(values[0], CSSOM_BORDER_TOP_WIDTH_PROPERTY, begin, tail);
  return tail;
}



static const SAC_LexicalUnit** CSSPropertyValue_borderWidth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  if (CSSPropertyValue_boxShorthand(shorthand_borderWidth,
    CSSPropertyValue_borderWidthToken, begin, end, &values[1]) != end)
  {
    return begin;
  }

  SET_RANGE(values[0], CSSOM_BORDER_WIDTH_PROPERTY, begin, end);
  return end;
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

  property->vtable = vtables[type];
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
  int *error,
  int (*assign)(CSSOM_CSSStyleDeclarationValue *, CSSOM_CSSPropertyValue *))
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

/*
  if ((rval = assign(parentValues, shorthand)) != 0) {
    CSSOM_CSSPropertyValue_release(shorthand);
    if (error != NULL) *error = rval;
    return NULL;
  }
*/

  for (i = 1; i < size; ++i) {
    if (values[i].begin == NULL) continue;

    property = CSSPropertyValue_alloc(cssom, parentValues, shorthand,
      values[i].type, NULL, values[i].begin, values[i].end, important);
    if (property == NULL) {
      if (error != NULL) *error = -1;
      return NULL;
    }

    if ((rval = assign(parentValues, property)) != 0) {
      CSSOM_CSSPropertyValue_release(property);
      if (error != NULL) *error = rval;
      return NULL;
    }
  }

  return shorthand;
}



static CSSOM_CSSPropertyValue* CSSPropertyValue_validate(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **holder, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, SAC_Boolean important, int *error,
  int (*assign)(CSSOM_CSSStyleDeclarationValue *, CSSOM_CSSPropertyValue *))
{
  switch (type) {
    case CSSOM_AZIMUTH_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_azimuth(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange
        values[ASIZE(shorthand_background) + 1] = {
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_background(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_ATTACHMENT_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_backgroundAttachment(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_COLOR_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_backgroundColor(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_IMAGE_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_backgroundImage(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_POSITION_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_backgroundPosition(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BACKGROUND_REPEAT_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_backgroundRepeat(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_PROPERTY:
      break;
    case CSSOM_BORDER_COLLAPSE_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_borderCollapse(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_COLOR_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange
        values[ASIZE(shorthand_borderColor) + 1] = {
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
        };

        if (CSSPropertyValue_borderColor(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_SPACING_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_borderSpacing(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_STYLE_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange
        values[ASIZE(shorthand_borderStyle) + 1] = {
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
        };

        if (CSSPropertyValue_borderStyle(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_TOP_PROPERTY:
    case CSSOM_BORDER_RIGHT_PROPERTY:
    case CSSOM_BORDER_BOTTOM_PROPERTY:
    case CSSOM_BORDER_LEFT_PROPERTY:
      break;
    case CSSOM_BORDER_TOP_COLOR_PROPERTY:
    case CSSOM_BORDER_RIGHT_COLOR_PROPERTY:
    case CSSOM_BORDER_BOTTOM_COLOR_PROPERTY:
    case CSSOM_BORDER_LEFT_COLOR_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_borderTopColor(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        values[0].type = type;

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_TOP_STYLE_PROPERTY:
    case CSSOM_BORDER_RIGHT_STYLE_PROPERTY:
    case CSSOM_BORDER_BOTTOM_STYLE_PROPERTY:
    case CSSOM_BORDER_LEFT_STYLE_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_borderTopStyle(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        values[0].type = type;

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_TOP_WIDTH_PROPERTY:
    case CSSOM_BORDER_RIGHT_WIDTH_PROPERTY:
    case CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY:
    case CSSOM_BORDER_LEFT_WIDTH_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange values[1] = {
          { 0, NULL, NULL }
        };

        if (CSSPropertyValue_borderTopWidth(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        values[0].type = type;

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BORDER_WIDTH_PROPERTY:
      {
        struct _CSSOM_LexicalUnitRange
        values[ASIZE(shorthand_borderWidth) + 1] = {
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
          { 0, NULL, NULL },
        };

        if (CSSPropertyValue_borderWidth(begin, end, values) != end) {
          if (error != NULL) *error = 1;
          return NULL;
        }

        return assignProperties(cssom, parentValues, holder, values,
          ASIZE(values), important, error, assign);
      }
    case CSSOM_BOTTOM_PROPERTY:
    case CSSOM_CAPTION_SIDE_PROPERTY:
    case CSSOM_CLEAR_PROPERTY:
    case CSSOM_CLIP_PROPERTY:
    case CSSOM_COLOR_PROPERTY:
    case CSSOM_CONTENT_PROPERTY:
    case CSSOM_COUNTER_INCREMENT_PROPERTY:
    case CSSOM_COUNTER_RESET_PROPERTY:
    case CSSOM_CUE_PROPERTY:
    case CSSOM_CUE_AFTER_PROPERTY:
    case CSSOM_CUE_BEFORE_PROPERTY:
    case CSSOM_CURSOR_PROPERTY:
    case CSSOM_DIRECTION_PROPERTY:
    case CSSOM_DISPLAY_PROPERTY:
    case CSSOM_ELEVATION_PROPERTY:
    case CSSOM_EMPTY_CELLS_PROPERTY:
    case CSSOM_FLOAT_PROPERTY:
    case CSSOM_FONT_PROPERTY:
    case CSSOM_FONT_FAMILY_PROPERTY:
    case CSSOM_FONT_SIZE_PROPERTY:
    case CSSOM_FONT_SIZE_ADJUST_PROPERTY:
    case CSSOM_FONT_STRETCH_PROPERTY:
    case CSSOM_FONT_STYLE_PROPERTY:
    case CSSOM_FONT_VARIANT_PROPERTY:
    case CSSOM_FONT_WEIGHT_PROPERTY:
    case CSSOM_HEIGHT_PROPERTY:
    case CSSOM_LEFT_PROPERTY:
    case CSSOM_LETTER_SPACING_PROPERTY:
    case CSSOM_LINE_HEIGHT_PROPERTY:
    case CSSOM_LIST_STYLE_PROPERTY:
    case CSSOM_LIST_STYLE_IMAGE_PROPERTY:
    case CSSOM_LIST_STYLE_POSITION_PROPERTY:
    case CSSOM_LIST_STYLE_TYPE_PROPERTY:
    case CSSOM_MARGIN_PROPERTY:
    case CSSOM_MARGIN_TOP_PROPERTY:
    case CSSOM_MARGIN_RIGHT_PROPERTY:
    case CSSOM_MARGIN_BOTTOM_PROPERTY:
    case CSSOM_MARGIN_LEFT_PROPERTY:
    case CSSOM_MARKER_OFFSET_PROPERTY:
    case CSSOM_MARKS_PROPERTY:
    case CSSOM_MAX_HEIGHT_PROPERTY:
    case CSSOM_MAX_WIDTH_PROPERTY:
    case CSSOM_MIN_HEIGHT_PROPERTY:
    case CSSOM_MIN_WIDTH_PROPERTY:
    case CSSOM_ORPHANS_PROPERTY:
    case CSSOM_OUTLINE_PROPERTY:
    case CSSOM_OUTLINE_COLOR_PROPERTY:
    case CSSOM_OUTLINE_STYLE_PROPERTY:
    case CSSOM_OUTLINE_WIDTH_PROPERTY:
    case CSSOM_OVERFLOW_PROPERTY:
    case CSSOM_PADDING_PROPERTY:
    case CSSOM_PADDING_TOP_PROPERTY:
    case CSSOM_PADDING_RIGHT_PROPERTY:
    case CSSOM_PADDING_BOTTOM_PROPERTY:
    case CSSOM_PADDING_LEFT_PROPERTY:
    case CSSOM_PAGE_PROPERTY:
    case CSSOM_PAGE_BREAK_AFTER_PROPERTY:
    case CSSOM_PAGE_BREAK_BEFORE_PROPERTY:
    case CSSOM_PAGE_BREAK_INSIDE_PROPERTY:
    case CSSOM_PAUSE_PROPERTY:
    case CSSOM_PAUSE_AFTER_PROPERTY:
    case CSSOM_PAUSE_BEFORE_PROPERTY:
    case CSSOM_PITCH_PROPERTY:
    case CSSOM_PITCH_RANGE_PROPERTY:
    case CSSOM_PLAY_DURING_PROPERTY:
    case CSSOM_POSITION_PROPERTY:
    case CSSOM_QUOTES_PROPERTY:
    case CSSOM_RICHNESS_PROPERTY:
    case CSSOM_RIGHT_PROPERTY:
    case CSSOM_SIZE_PROPERTY:
    case CSSOM_SPEAK_PROPERTY:
    case CSSOM_SPEAK_HEADER_PROPERTY:
    case CSSOM_SPEAK_NUMERAL_PROPERTY:
    case CSSOM_SPEAK_PUNCTUATION_PROPERTY:
    case CSSOM_SPEECH_RATE_PROPERTY:
    case CSSOM_SRC_PROPERTY:
    case CSSOM_STRESS_PROPERTY:
    case CSSOM_TABLE_LAYOUT_PROPERTY:
    case CSSOM_TEXT_ALIGN_PROPERTY:
    case CSSOM_TEXT_DECORATION_PROPERTY:
    case CSSOM_TEXT_INDENT_PROPERTY:
    case CSSOM_TEXT_SHADOW_PROPERTY:
    case CSSOM_TEXT_TRANSFORM_PROPERTY:
    case CSSOM_TOP_PROPERTY:
    case CSSOM_UNICODE_BIDI_PROPERTY:
    case CSSOM_VERTICAL_ALIGN_PROPERTY:
    case CSSOM_VISIBILITY_PROPERTY:
    case CSSOM_VOICE_FAMILY_PROPERTY:
    case CSSOM_VOLUME_PROPERTY:
    case CSSOM_WHITE_SPACE_PROPERTY:
    case CSSOM_WIDOWS_PROPERTY:
    case CSSOM_WIDTH_PROPERTY:
    case CSSOM_WORD_SPACING_PROPERTY:
    case CSSOM_Z_INDEX_PROPERTY:
      break;
  }

  {
    struct _CSSOM_LexicalUnitRange values[] = {
      { 0, NULL, NULL },
    };

    SET_RANGE(values[0], type, begin, end);

    return assignProperties(cssom, parentValues, holder, values,
      ASIZE(values), important, error, assign);
  }
}



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyType type, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, SAC_Boolean important, int *error)
{
  const SAC_LexicalUnit **holder;
  CSSOM_CSSPropertyValue *property;

  if (end == NULL) {
    holder = (const SAC_LexicalUnit**)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * 2);
    if (holder == NULL) return NULL;
    holder[0] = *begin;
    holder[1] = NULL;
    begin = &holder[0];
    end = &holder[1];
  } else {
    holder = NULL;
  }

  property = CSSPropertyValue_validate(cssom, parentValues, type, holder, begin,
    end, important, error, CSSOM_CSSStyleDeclarationValue__assignProperty);
  if (property == NULL) {
    CSSOM_free(holder);
    return NULL;
  }
  
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

  if (CSSPropertyValue_emit(property, out) != 0) {
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
