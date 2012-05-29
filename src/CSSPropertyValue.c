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
#include <strings.h>



#define ASIZE(array) \
  (sizeof(array) / sizeof(array[0]))

#define INITIAL(initial) \
  { (initial), &(initial)[ASIZE(initial)] }



typedef const SAC_LexicalUnit**(*PropertyHandler)(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end);



static SAC_LexicalUnit unit_transparent;
static SAC_LexicalUnit unit_none;
static SAC_LexicalUnit unit_repeat;
static SAC_LexicalUnit unit_scroll;
static SAC_LexicalUnit unit_50pct;



void CSSOM_CSSPropertyValue__initGlobals(void) {
  unit_transparent.lexicalUnitType = SAC_IDENT;
  unit_transparent.desc.ident = "transparent";

  unit_none.lexicalUnitType = SAC_IDENT;
  unit_none.desc.ident = "none";

  unit_repeat.lexicalUnitType = SAC_IDENT;
  unit_repeat.desc.ident = "repeat";

  unit_scroll.lexicalUnitType = SAC_IDENT;
  unit_scroll.desc.ident = "scroll";

  unit_50pct.lexicalUnitType = SAC_PERCENTAGE;
  unit_50pct.desc.dimension.unit = "%";
  unit_50pct.desc.dimension.value.sreal = 50;
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
    if (strcasecmp("aqua", value->desc.ident) == 0) return 1;
    if (strcasecmp("black", value->desc.ident) == 0) return 1;
    if (strcasecmp("blue", value->desc.ident) == 0) return 1;
    if (strcasecmp("fuchsia", value->desc.ident) == 0) return 1;
    if (strcasecmp("gray", value->desc.ident) == 0) return 1;
    if (strcasecmp("green", value->desc.ident) == 0) return 1;
    if (strcasecmp("lime", value->desc.ident) == 0) return 1;
    if (strcasecmp("maroon", value->desc.ident) == 0) return 1;
    if (strcasecmp("navy", value->desc.ident) == 0) return 1;
    if (strcasecmp("olive", value->desc.ident) == 0) return 1;
    if (strcasecmp("orange", value->desc.ident) == 0) return 1;
    if (strcasecmp("purple", value->desc.ident) == 0) return 1;
    if (strcasecmp("red", value->desc.ident) == 0) return 1;
    if (strcasecmp("silver", value->desc.ident) == 0) return 1;
    if (strcasecmp("teal", value->desc.ident) == 0) return 1;
    if (strcasecmp("white", value->desc.ident) == 0) return 1;
    if (strcasecmp("yellow", value->desc.ident) == 0) return 1;
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



static int isLength(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_LENGTH_EM) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_EX) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_PIXEL) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_INCH) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_CENTIMETER) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_POINT) return 1;
  if (value->lexicalUnitType == SAC_LENGTH_PICA) return 1;
  if (value->lexicalUnitType == SAC_REAL && value->desc.real == 0) return 1;
  if (value->lexicalUnitType == SAC_INTEGER && value->desc.integer == 0)
    return 1;
  return 0;
}



struct _CSSOM_CSSPropertyValue_vtable {
  int (*emit)(const CSSOM_CSSPropertyValue *property, FILE *out);
};



struct _CSSOM_CSSPropertyValue {
  struct _CSSOM_CSSPropertyValue_vtable *vtable;
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



static int CSSPropertyValue_emit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  return property->vtable->emit(property, out);
}



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



static struct _CSSOM_CSSPropertyValue_vtable GenericCSSPropertyValue_vtable = {
  (int (*)(const CSSOM_CSSPropertyValue*, FILE*))&GenericCSSPropertyValue_emit
};



static int BackgroundCSSPropertyValue_emit(
  const CSSOM_CSSPropertyValue *property, FILE *out)
{
  int emited;
  const char *cssText;

  emited = 0;

  cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
    property->parentValues, CSSOM_BACKGROUND_COLOR_PROPERTY);
  if (cssText != NULL) {
    if (emited) {
      if (fprintf(out, " ") < 0) return 1;
    } else {
      emited = 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
    property->parentValues, CSSOM_BACKGROUND_IMAGE_PROPERTY);
  if (cssText != NULL) {
    if (emited) {
      if (fprintf(out, " ") < 0) return 1;
    } else {
      emited = 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
    property->parentValues, CSSOM_BACKGROUND_REPEAT_PROPERTY);
  if (cssText != NULL) {
    if (emited) {
      if (fprintf(out, " ") < 0) return 1;
    } else {
      emited = 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
    property->parentValues, CSSOM_BACKGROUND_ATTACHMENT_PROPERTY);
  if (cssText != NULL) {
    if (emited) {
      if (fprintf(out, " ") < 0) return 1;
    } else {
      emited = 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
    property->parentValues, CSSOM_BACKGROUND_POSITION_PROPERTY);
  if (cssText != NULL) {
    if (emited) {
      if (fprintf(out, " ") < 0) return 1;
    } else {
      emited = 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

  return 0;
}



static struct _CSSOM_CSSPropertyValue_vtable
BackgroundCSSPropertyValue_vtable = {
  (int (*)(const CSSOM_CSSPropertyValue*, FILE*))
  &BackgroundCSSPropertyValue_emit
};



static int azimuth_isAngleIdent(const char *ident) {
  if (strcasecmp("left-side", ident) == 0) return 1;
  if (strcasecmp("far-left", ident) == 0) return 1;
  if (strcasecmp("left", ident) == 0) return 1;
  if (strcasecmp("center-left", ident) == 0) return 1;
  if (strcasecmp("center", ident) == 0) return 1;
  if (strcasecmp("center-right", ident) == 0) return 1;
  if (strcasecmp("right", ident) == 0) return 1;
  if (strcasecmp("far-right", ident) == 0) return 1;
  if (strcasecmp("right-side", ident) == 0) return 1;
  return 0;
}



static void releaseProperties(CSSOM_CSSPropertyValue **properties,
  size_t size)
{
  size_t i;

  for (i = 0; i < size; ++i) {
    CSSOM_CSSPropertyValue_release(properties[i]);
    properties[i] = NULL;
  }
}



static const SAC_LexicalUnit** CSSPropertyValue_shorthand(
  const CSSOM *cssom, CSSOM_CSSPropertyValue *shorthand,
  PropertyHandler *handlers, const CSSOM_CSSPropertyType *types,
  const SAC_LexicalUnit **(*initial)[2], CSSOM_CSSPropertyValue **properties,
  size_t size, const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  int *error)
{
  size_t i;
  size_t length;
  const SAC_LexicalUnit **at;
  const SAC_LexicalUnit **tail;
  CSSOM_CSSPropertyValue *property;
  int rval;



  /**
   * analyze input
   */

  at = begin;
  while (*at != NULL) {

    for (i = 0; i < size; ++i) {
      if (handlers[i] == NULL) continue;

      tail = handlers[i](at, end);
      if (tail != at) {
        handlers[i] = NULL;
        break;
      }
    }

    length = tail - at;
    if (length == 0) break;

    property = CSSOM_CSSPropertyValue__alloc(cssom, shorthand->parentValues,
      shorthand, types[i], at, tail, SAC_FALSE, NULL);
    if (property == NULL) {
      releaseProperties(properties, size);
      if (error != NULL) *error = 1;
      return &begin[0];
    }

    properties[i] = property;

    at = tail;
  }



  /**
   * add initial
   */

  for (i = 0; i < size; ++i) {
    if (properties[i] != NULL) continue;

    properties[i] = CSSOM_CSSPropertyValue__alloc(cssom, property->parentValues,
      property, types[i], initial[i][0], initial[i][1], SAC_FALSE, &rval);

    if (properties[i] == NULL) {
      releaseProperties(properties, size);
      if (error != NULL) *error = rval;
      return &begin[0];
    }
  }



  /**
   * assign values
   */

  if ((rval = CSSOM_CSSStyleDeclarationValue__assignProperties(
    property->parentValues, properties, size)) != 0)
  {
    releaseProperties(properties, size);
    if (error != NULL) *error = rval;
    return &begin[0];
  }

  if (error != NULL) *error = 0;
  return at;
}



/**
 * azimuth
 */

static const SAC_LexicalUnit** azimuth_angle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (strcasecmp("behind", begin[0]->desc.ident) == 0) return &begin[1];
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** azimuth_behind(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (azimuth_isAngleIdent(begin[0]->desc.ident)) return &begin[1];
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_azimuth(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  if (isAngle(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("leftwards", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcasecmp("rightwards", begin[0]->desc.ident) == 0) return &begin[1];

    if (azimuth_isAngleIdent(begin[0]->desc.ident))
      return azimuth_angle(&begin[1], end);

    if (strcasecmp("behind", begin[0]->desc.ident) == 0)
      return azimuth_behind(&begin[1], end);

  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * background-attachment
 */

static const SAC_LexicalUnit** CSSPropertyValue_backgroundAttachment(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("scroll", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcasecmp("fixed", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * background-color
 */

static const SAC_LexicalUnit** CSSPropertyValue_backgroundColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isColor(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("transparent", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * background-image
 */

static const SAC_LexicalUnit** CSSPropertyValue_backgroundImage(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isUrl(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("none", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
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
    if (strcasecmp("top", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("bottom", expr[0]->desc.ident) == 0) return &expr[1];
  }

  return &expr[0];
}



static const SAC_LexicalUnit** backgroundPosition_vertical(
  const SAC_LexicalUnit **expr)
{
  if (expr[0] == NULL) {
    return &expr[0];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("left", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("right", expr[0]->desc.ident) == 0) return &expr[1];
  }
  return &expr[0];
}



static const SAC_LexicalUnit** CSSPropertyValue_backgroundPosition(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (isPercentage(begin[0]) || isLength(begin[0])) {
    return backgroundPosition_horizontal(&begin[1]);
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {

    if (strcasecmp("left", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcasecmp("right", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcasecmp("top", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcasecmp("bottom", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcasecmp("center", begin[0]->desc.ident) == 0) {
      const SAC_LexicalUnit **tail;

      if (begin[1] == NULL) return &begin[1];

      tail = backgroundPosition_horizontal(&begin[1]);
      if (tail != &begin[1]) return tail;

      return backgroundPosition_vertical(&begin[1]);
    }

  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * background-repeat
 */

static const SAC_LexicalUnit** CSSPropertyValue_backgroundRepeat(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("repeat", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcasecmp("repeat-x", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcasecmp("repeat-y", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcasecmp("no-repeat", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_INHERIT) {
    return &begin[1];
  }
  return &begin[0];
}



/**
 * background
 */

static const SAC_LexicalUnit** CSSPropertyValue_background(
  const CSSOM *cssom, CSSOM_CSSPropertyValue *property,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end, int *error)
{
  static const SAC_LexicalUnit *initialColor[] = {
    &unit_transparent
  };

  static const SAC_LexicalUnit *initialImage[] = {
    &unit_none
  };

  static const SAC_LexicalUnit *initialRepeat[] = {
    &unit_repeat
  };

  static const SAC_LexicalUnit *initialAttachment[] = {
    &unit_scroll
  };

  static const SAC_LexicalUnit *initialPosition[] = {
    &unit_50pct, &unit_50pct
  };

  static const CSSOM_CSSPropertyType types[] = {
    CSSOM_BACKGROUND_COLOR_PROPERTY,
    CSSOM_BACKGROUND_IMAGE_PROPERTY,
    CSSOM_BACKGROUND_REPEAT_PROPERTY,
    CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
    CSSOM_BACKGROUND_POSITION_PROPERTY
  };

  static const SAC_LexicalUnit **initial[ASIZE(types)][2] = {
    INITIAL(initialColor),
    INITIAL(initialImage),
    INITIAL(initialRepeat),
    INITIAL(initialAttachment),
    INITIAL(initialPosition)
  };

  PropertyHandler handlers[ASIZE(types)] = {
    CSSPropertyValue_backgroundColor,
    CSSPropertyValue_backgroundImage,
    CSSPropertyValue_backgroundRepeat,
    CSSPropertyValue_backgroundAttachment,
    CSSPropertyValue_backgroundPosition
  };

  CSSOM_CSSPropertyValue *properties[ASIZE(types)] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  };

  if (CSSPropertyValue_shorthand(cssom, property, handlers, types, initial,
    properties, ASIZE(types), begin, end, error) != end)
  {
    return begin;
  }

  if (error != NULL) *error = 0;
  return end;
}



static int CSSPropertyValue_init(const CSSOM *cssom,
  CSSOM_CSSPropertyValue *property, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  int error;

  switch (property->type) {
    case CSSOM_AZIMUTH_PROPERTY:
      if (CSSPropertyValue_azimuth(begin, end) != end) return 1;
      break;
    case CSSOM_BACKGROUND_PROPERTY:
      if (CSSPropertyValue_background(cssom, property, begin, end,
        &error) != end)
      {
        return error;
      }
      property->vtable = &BackgroundCSSPropertyValue_vtable;
      break;
    case CSSOM_BACKGROUND_ATTACHMENT_PROPERTY:
      if (CSSPropertyValue_backgroundAttachment(begin, end) != end) return 1;
      break;
    case CSSOM_BACKGROUND_COLOR_PROPERTY:
      if (CSSPropertyValue_backgroundColor(begin, end) != end) return 1;
      break;
    case CSSOM_BACKGROUND_IMAGE_PROPERTY:
      if (CSSPropertyValue_backgroundImage(begin, end) != end) return 1;
      break;
    case CSSOM_BACKGROUND_POSITION_PROPERTY:
      if (CSSPropertyValue_backgroundPosition(begin, end) != end) return 1;
      break;
    case CSSOM_BACKGROUND_REPEAT_PROPERTY:
      if (CSSPropertyValue_backgroundRepeat(begin, end) != end) return 1;
      break;
    case CSSOM_BORDER_PROPERTY:
    case CSSOM_BORDER_COLLAPSE_PROPERTY:
    case CSSOM_BORDER_COLOR_PROPERTY:
    case CSSOM_BORDER_SPACING_PROPERTY:
    case CSSOM_BORDER_STYLE_PROPERTY:
    case CSSOM_BORDER_TOP_PROPERTY:
    case CSSOM_BORDER_RIGHT_PROPERTY:
    case CSSOM_BORDER_BOTTOM_PROPERTY:
    case CSSOM_BORDER_LEFT_PROPERTY:
    case CSSOM_BORDER_TOP_COLOR_PROPERTY:
    case CSSOM_BORDER_RIGHT_COLOR_PROPERTY:
    case CSSOM_BORDER_BOTTOM_COLOR_PROPERTY:
    case CSSOM_BORDER_LEFT_COLOR_PROPERTY:
    case CSSOM_BORDER_TOP_STYLE_PROPERTY:
    case CSSOM_BORDER_RIGHT_STYLE_PROPERTY:
    case CSSOM_BORDER_BOTTOM_STYLE_PROPERTY:
    case CSSOM_BORDER_LEFT_STYLE_PROPERTY:
    case CSSOM_BORDER_TOP_WIDTH_PROPERTY:
    case CSSOM_BORDER_RIGHT_WIDTH_PROPERTY:
    case CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY:
    case CSSOM_BORDER_LEFT_WIDTH_PROPERTY:
    case CSSOM_BORDER_WIDTH_PROPERTY:
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
  return 0;
}



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  SAC_Boolean important, int *error)
{
  const SAC_LexicalUnit **holder;
  CSSOM_CSSPropertyValue *property;
  int rval;

  if (end == NULL) {
    holder = (const SAC_LexicalUnit**)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * 2);
    if (holder == NULL) {
      *error = -1;
      return NULL;
    }
    holder[0] = *begin;
    holder[1] = NULL;
  } else {
    holder = NULL;
  }

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) {
    if (error != NULL) *error = -1;
    return NULL;
  }

  property->vtable = &GenericCSSPropertyValue_vtable;
  property->handles = 1;
  property->parentValues = parentValues;
  property->shorthand = shorthand;
  property->parser = NULL;
  property->type = type;
  property->name = CSSOM__properties(cssom)[type];
  property->holder = holder;
  if (property->holder != NULL) {
    property->begin = &property->holder[0];
    property->end = &property->holder[1];
  } else {
    property->begin = begin;
    property->end = end;
  }
  property->important = important;
  property->cssText = NULL;

  if ((rval = CSSPropertyValue_init(cssom, property, property->begin,
    property->end)) != 0)
  {
    if (error != NULL) {
      CSSOM_CSSPropertyValue_release(property);
      *error = rval;
    }
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
