#include "CSSStyleDeclarationValue.h"

#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSPropertyValue.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclaration.h>
#include <cssom/CSSStyleRule.h>

#include <assert.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>



struct _CSSOM_CSSStyleDeclarationValue {
  size_t handles;
  CSSOM_CSSStyleDeclaration *parentStyle;
  CSSOM_FSM_CSSPropertyValue *fsm;
  char *removedPropertyHolder;
};



static int CSSStyleDeclarationValue__assignProperties(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyValue **properties,
  size_t size)
{
  const CSSOM *cssom;
  size_t i;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  for (i = 0; i < size; ++i) {
    propertyValue = properties[i];

    if (propertyValue == NULL) continue;

    it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm,
      CSSOM_CSSPropertyValue__name(propertyValue), NULL);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

    if (it->value != NULL) {
      it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
      if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
        CSSOM_CSSPropertyValue_release(propertyValue);
        return -1;
      }
      CSSOM_CSSPropertyValue_release(it->value);
    }
    it->value = propertyValue;
  }

  return 0;
}



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclarationValue__alloc(
  CSSOM_CSSStyleDeclaration *parentStyle)
{
  const CSSOM_FSMTable_CSSPropertyValue *table;
  CSSOM_CSSStyleDeclarationValue *values;
  CSSOM_FSM_CSSPropertyValue *fsm;

  table = CSSOM__table(
    CSSOM_CSSStyleSheet__cssom(
      CSSOM_CSSRule_parentStyleSheet(
        CSSOM_CSSStyleDeclaration_parentRule(parentStyle))));

  fsm = CSSOM_FSM_CSSPropertyValue_alloc(table);
  if (fsm == NULL) return NULL;

  values = (CSSOM_CSSStyleDeclarationValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclarationValue));
  if (values == NULL) {
    CSSOM_FSM_CSSPropertyValue_free(fsm);
    return NULL;
  }

  values->handles = 1;
  values->parentStyle = parentStyle;
  values->fsm = fsm;
  values->removedPropertyHolder = NULL;

  return values;
}



void CSSOM_CSSStyleDeclarationValue_acquire(
  CSSOM_CSSStyleDeclarationValue *values)
{
  if (values == NULL) return;

  ++values->handles;
  CSSOM_CSSStyleDeclaration_acquire(values->parentStyle);
}



void CSSOM_CSSStyleDeclarationValue_release(
  CSSOM_CSSStyleDeclarationValue *values)
{
  CSSOM_FSMIter_CSSPropertyValue it;
  
  if (values == NULL) return;

  assert(values->handles > 0);
  --values->handles;
  if (values->handles > 0) {
    CSSOM_CSSStyleDeclaration_release(values->parentStyle);
    return;
  }

  CSSOM_native_free(values->removedPropertyHolder);
  for (
    it = CSSOM_FSM_CSSPropertyValue_begin(values->fsm);
    it != CSSOM_FSM_CSSPropertyValue_end(values->fsm);
    it = CSSOM_FSMIter_CSSPropertyValue_next(it))
  {
    CSSOM_CSSPropertyValue_release(it->value);
  }
  CSSOM_FSM_CSSPropertyValue_free(values->fsm);
  CSSOM_free(values);
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclarationValue_parentStyle(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return values->parentStyle;
}



unsigned long CSSOM_CSSStyleDeclarationValue_length(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_size(values->fsm);
}



const char* CSSOM_CSSStyleDeclarationValue_item(
  CSSOM_CSSStyleDeclarationValue *values, unsigned long index)
{
  CSSOM_FSMConstIter_CSSPropertyValue match;

  if (index >= CSSOM_FSM_CSSPropertyValue_size(values->fsm)) return NULL;

  match = CSSOM_FSM_CSSPropertyValue_at(values->fsm, index);

  return CSSOM_CSSPropertyValue__name(match->value);
}



const char* CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  return CSSOM_CSSPropertyValue_cssText(it->value);
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue_getProperty(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_find(values->fsm, property);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  return it->value;
}



const char* CSSOM_CSSStyleDeclarationValue__getPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(values, property);

  if (value == NULL) return NULL;

  return CSSOM_CSSPropertyValue_cssText(value);
}



const char* CSSOM_CSSStyleDeclarationValue__getPropertyPriority(
  const CSSOM_CSSStyleDeclarationValue *values, const char * property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(values, property);

  if (value == NULL) return "";
  if (CSSOM_CSSPropertyValue__important(value) == 0) return "";

  return "important";
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



static const SAC_LexicalUnit** azimuth_angle(const SAC_LexicalUnit **expr) {
  if (expr[0] != NULL) {
    if (expr[0]->lexicalUnitType == SAC_IDENT) {
      if (strcasecmp("behind", expr[0]->desc.ident) == 0) return &expr[1];
    }
  }
  return &expr[0];
}



static const SAC_LexicalUnit** azimuth_behind(const SAC_LexicalUnit **expr) {
  if (expr[0] != NULL) {
    if (expr[0]->lexicalUnitType == SAC_IDENT) {
      if (azimuth_isAngleIdent(expr[0]->desc.ident)) return &expr[1];
    }
  }
  return &expr[0];
}



static const SAC_LexicalUnit** CSSStyleDeclarationValue_azimuth(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (isAngle(expr[0])) {
    return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("leftwards", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("rightwards", expr[0]->desc.ident) == 0) return &expr[1];

    if (azimuth_isAngleIdent(expr[0]->desc.ident))
      return azimuth_angle(&expr[1]);

    if (strcasecmp("behind", expr[0]->desc.ident) == 0)
      return azimuth_behind(&expr[1]);

  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
}




static const SAC_LexicalUnit** CSSStyleDeclarationValue_backgroundAttachment(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("scroll", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("fixed", expr[0]->desc.ident) == 0) return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
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



static const SAC_LexicalUnit** CSSStyleDeclarationValue_backgroundColor(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (isColor(expr[0])) {
    return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("transparent", expr[0]->desc.ident) == 0) return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
}



static const SAC_LexicalUnit** CSSStyleDeclarationValue_backgroundImage(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (isUrl(expr[0])) {
    return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("none", expr[0]->desc.ident) == 0) return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
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



static const SAC_LexicalUnit** CSSStyleDeclarationValue_backgroundPosition(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (isPercentage(expr[0]) || isLength(expr[0])) {
    return backgroundPosition_horizontal(&expr[1]);
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {

    if (strcasecmp("left", expr[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&expr[1]);

    if (strcasecmp("right", expr[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&expr[1]);

    if (strcasecmp("top", expr[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&expr[1]);

    if (strcasecmp("bottom", expr[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&expr[1]);

    if (strcasecmp("center", expr[0]->desc.ident) == 0) {
      const SAC_LexicalUnit **tail;

      if (expr[1] == NULL) return &expr[1];

      tail = backgroundPosition_horizontal(&expr[1]);
      if (tail != &expr[1]) return tail;

      return backgroundPosition_vertical(&expr[1]);
    }

  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
}



static const SAC_LexicalUnit** CSSStyleDeclarationValue_backgroundRepeat(
  CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **expr)
{
  if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcasecmp("repeat", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("repeat-x", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("repeat-y", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcasecmp("no-repeat", expr[0]->desc.ident) == 0) return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_INHERIT) {
    return &expr[1];
  }
  return &expr[0];
}



typedef const SAC_LexicalUnit**(*PropertyHandler)(
  CSSOM_CSSStyleDeclarationValue *values, const SAC_LexicalUnit **expr);



static const SAC_LexicalUnit** CSSStyleDeclarationValue_shorthand(
  CSSOM_CSSStyleDeclarationValue *values, PropertyHandler *handlers,
  CSSOM_CSSPropertyType *types, CSSOM_CSSPropertyValue **properties,
  size_t size, const SAC_LexicalUnit **expr)
{
  const CSSOM *cssom;
  size_t i;
  const SAC_LexicalUnit **at;
  const SAC_LexicalUnit **tail;
  CSSOM_CSSPropertyValue *property;
  const char *sproperty;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  at = expr;
  while (*at != NULL) {
    const SAC_LexicalUnit *value;

    for (i = 0; i < size; ++i) {
      if (handlers[i] == NULL) continue;

      tail = handlers[i](values, at);
      if (tail != at) {
        handlers[i] = NULL;
        break;
      }
    }

    if (tail == at) break;

    value = *at;
    sproperty = CSSOM__properties(cssom)[types[i]];

    property = CSSOM_CSSPropertyValue__alloc(values, NULL, sproperty, value,
      SAC_FALSE);
    if (property == NULL) return &expr[0];

    properties[i] = property;

    at = tail;
  }

  if (*at != NULL || CSSStyleDeclarationValue__assignProperties(values,
    properties, size) != 0)
  {
    for (i = 0; i < sizeof(handlers) / sizeof(handlers[0]); ++i) {
      CSSOM_CSSPropertyValue_release(properties[i]);
      properties[i] = NULL;
    }
  }

  return at;
}



static const SAC_LexicalUnit** CSSStyleDeclarationValue_background(
  CSSOM_CSSStyleDeclarationValue *values, const SAC_LexicalUnit **expr)
{
  PropertyHandler handlers[] = {
    CSSStyleDeclarationValue_backgroundAttachment,
    CSSStyleDeclarationValue_backgroundColor,
    CSSStyleDeclarationValue_backgroundImage,
    CSSStyleDeclarationValue_backgroundPosition,
    CSSStyleDeclarationValue_backgroundRepeat
  };

  CSSOM_CSSPropertyType types[] = {
    CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
    CSSOM_BACKGROUND_COLOR_PROPERTY,
    CSSOM_BACKGROUND_IMAGE_PROPERTY,
    CSSOM_BACKGROUND_POSITION_PROPERTY,
    CSSOM_BACKGROUND_REPEAT_PROPERTY
  };

  CSSOM_CSSPropertyValue *properties[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  };

  return CSSStyleDeclarationValue_shorthand(values, handlers, types, properties,
    sizeof(handlers) / sizeof(handlers[0]), expr);
}



static int CSSStyleDeclarationValue_propertySetter(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property,
  const SAC_LexicalUnit *value)
{
  const SAC_LexicalUnit *arr[2];
  const SAC_LexicalUnit **expr;
  if (value->lexicalUnitType != SAC_SUB_EXPRESSION) {
    arr[0] = value;
    arr[1] = NULL;
    expr = arr;
  } else {
    expr = (const SAC_LexicalUnit**)value->desc.subValues;
  }
  switch (property) {
    case CSSOM_AZIMUTH_PROPERTY:
      return *CSSStyleDeclarationValue_azimuth(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_PROPERTY:
      return *CSSStyleDeclarationValue_background(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_ATTACHMENT_PROPERTY:
      return *CSSStyleDeclarationValue_backgroundAttachment(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_COLOR_PROPERTY:
      return *CSSStyleDeclarationValue_backgroundColor(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_IMAGE_PROPERTY:
      return *CSSStyleDeclarationValue_backgroundImage(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_POSITION_PROPERTY:
      return *CSSStyleDeclarationValue_backgroundPosition(values,
        expr) == NULL;
    case CSSOM_BACKGROUND_REPEAT_PROPERTY:
      return *CSSStyleDeclarationValue_backgroundRepeat(values,
        expr) == NULL;
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
      return 1;
  }
  return 1;
}



int CSSOM_CSSStyleDeclarationValue__setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean priority)
{
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

  if (CSSStyleDeclarationValue_propertySetter(values, it->hash, value) == 0) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return 1;
  }

  propertyValue = CSSOM_CSSPropertyValue__alloc(values, NULL, it->key, value,
    priority);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return -1;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return -1;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

  return 0;
}



void CSSOM_CSSStyleDeclarationValue_setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value)
{
  CSSOM_CSSStyleDeclarationValue_setPropertyEx(values, property, value, NULL);
}



void CSSOM_CSSStyleDeclarationValue_setPropertyEx(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value, const char *priority)
{
  const CSSOM *cssom;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  int priorityLen;

  if (property == NULL) return;
  if (value == NULL) {
    CSSOM_CSSStyleDeclarationValue_removeProperty(values, property);
    return;
  }

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  if (priority == NULL) {
    priorityLen = 0;
  } else {
    priorityLen = strlen(priority);
  }
  propertyValue = CSSOM__parsePropertyValue(cssom, values, it->key,
    value, strlen(value), priority, priorityLen);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (CSSStyleDeclarationValue_propertySetter(values, it->hash,
    CSSOM_CSSPropertyValue__value(propertyValue)) == 0)
  {
    CSSOM_CSSPropertyValue_release(propertyValue);
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

}



static void CSSStyleDeclarationValue__fremoveProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue match;
  
  match = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  if (match == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  CSSOM_CSSPropertyValue_release(match->value);
  CSSOM_FSM_CSSPropertyValue_erase(values->fsm, match);
}



void CSSOM_CSSStyleDeclarationValue__fsetProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  CSSOM_CSSPropertyType property, const char *value)
{
  const CSSOM *cssom;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  const char *sproperty;

  if (value == NULL) {
    CSSStyleDeclarationValue__fremoveProperty(values, property);
    return;
  }

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  sproperty = CSSOM__properties(cssom)[property];

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, sproperty, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  propertyValue = CSSOM__parsePropertyValue(cssom, values, it->key,
    value, strlen(value), NULL, 0);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (CSSStyleDeclarationValue_propertySetter(values, it->hash,
    CSSOM_CSSPropertyValue__value(propertyValue)) == 0)
  {
    CSSOM_CSSPropertyValue_release(propertyValue);
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

}



const char* CSSOM_CSSStyleDeclarationValue_removeProperty(
  CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSPropertyValue match;
  
  match = CSSOM_FSM_CSSPropertyValue_find(values->fsm, property);
  if (match == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  CSSOM_native_free(values->removedPropertyHolder);
  values->removedPropertyHolder = strdup(CSSOM_CSSPropertyValue_cssText(
    match->value));

  CSSOM_CSSPropertyValue_release(match->value);
  CSSOM_FSM_CSSPropertyValue_erase(values->fsm, match);

  return values->removedPropertyHolder;
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__begin(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_begin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__end(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_end(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter
CSSOM_CSSStyleDeclarationValueIter_next(
  CSSOM_CSSStyleDeclarationValueIter iter)
{
  return CSSOM_FSMIter_CSSPropertyValue_next(iter);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cbegin(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_cbegin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cend(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_cend(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter
CSSOM_CSSStyleDeclarationValueConstIter_next(
  CSSOM_CSSStyleDeclarationValueConstIter iter)
{
  return CSSOM_FSMConstIter_CSSPropertyValue_next(iter);
}




