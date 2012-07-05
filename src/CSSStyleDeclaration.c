#include "CSSStyleDeclaration.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "CSSStyleDeclarationValue.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSRule.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>



struct _CSSOM_CSSStyleDeclaration {
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSRule *parentRule;
  CSSOM_CSSStyleDeclarationValue *values;
  char *cssText;
};



static void CSSStyleDeclaration_swap(
  CSSOM_CSSStyleDeclaration *lhs, CSSOM_CSSStyleDeclaration *rhs)
{
  assert(lhs->parentRule == rhs->parentRule);
  SWAPP(lhs->parser, rhs->parser);
  SWAPP(lhs->values, rhs->values);
  CSSOM_CSSStyleDeclarationValue__setParentStyle(lhs->values, lhs);
  CSSOM_CSSStyleDeclarationValue__setParentStyle(rhs->values, rhs);
  SWAPP(lhs->cssText, rhs->cssText);
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  CSSOM_CSSRule *parentRule)
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleDeclarationValue *values;

  style = (CSSOM_CSSStyleDeclaration*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) return NULL;

  style->handles = 1;
  style->parser = NULL;
  style->parentRule = parentRule;
  style->values = NULL;
  style->cssText = NULL;

  values = CSSOM_CSSStyleDeclarationValue__alloc(style);
  if (values == NULL) {
    CSSOM_CSSStyleDeclaration_release(style);
    return NULL;
  }
  style->values = values;

  return style;
}



void CSSOM_CSSStyleDeclaration_acquire(CSSOM_CSSStyleDeclaration *style) {
  if (style == NULL) return;

  ++style->handles;
  CSSOM_CSSRule_acquire(style->parentRule);
}



void CSSOM_CSSStyleDeclaration_release(CSSOM_CSSStyleDeclaration *style) {
  if (style == NULL) return;

  assert(style->handles > 0);
  --style->handles;
  if (style->handles > 0) {
    CSSOM_CSSRule_release(style->parentRule);
    return;
  }

  CSSOM_native_free(style->cssText);
  CSSOM_CSSStyleDeclarationValue_release(style->values);
  SAC_DisposeParser(style->parser);
  CSSOM_free(style);
}



void CSSOM_CSSStyleDeclaration__setParentRule(CSSOM_CSSStyleDeclaration *style,
  CSSOM_CSSRule *parentRule)
{
  size_t i;

  for (i = 0; i < style->handles - 1; ++i) {
    CSSOM_CSSRule_release(style->parentRule);
    CSSOM_CSSRule_acquire(parentRule);
  }

  style->parentRule = parentRule;
}



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue_length(style->values);
}



const char* CSSOM_CSSStyleDeclaration_item(CSSOM_CSSStyleDeclaration *style,
  unsigned long index)
{
  return CSSOM_CSSStyleDeclarationValue_item(style->values, index);
}




const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(style->values, property);

  if (value == NULL) return NULL;

  return CSSOM_CSSPropertyValue_cssText(value);
}



const char* CSSOM_CSSStyleDeclaration_getPropertyPriority(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(style->values, property);

  if (value == NULL) return "";
  if (CSSOM_CSSPropertyValue__important(value) == 0) return "";

  return "important";
}



void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  CSSOM_CSSStyleDeclarationValue_setProperty(style->values, property, value);
}



void CSSOM_CSSStyleDeclaration_setPropertyEx(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value, const char *priority)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  CSSOM_CSSStyleDeclarationValue_setPropertyEx(style->values,
    property, value, priority);
}



const char* CSSOM_CSSStyleDeclaration_removeProperty(
  CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  return CSSOM_CSSStyleDeclarationValue_removeProperty(style->values, property);
}



const char* CSSOM_CSSStyleDeclaration_cssText(
  const CSSOM_CSSStyleDeclaration *style)
{
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(style->cssText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_styleDeclaration(out, style) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_CSSStyleDeclaration*)style)->cssText = buf;

  return style->cssText;
}



void CSSOM_CSSStyleDeclaration_setCSSText(CSSOM_CSSStyleDeclaration *style,
  const char *cssText)
{
  CSSOM_CSSStyleDeclaration *newStyle;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(style->parentRule));
  newStyle = CSSOM__parseStyleDeclaration(cssom, style->parentRule,
    cssText, strlen(cssText));
  if (newStyle == NULL) return;

  CSSStyleDeclaration_swap(style, newStyle);

  CSSOM_CSSStyleDeclaration_release(newStyle);
}



CSSOM_CSSRule* CSSOM_CSSStyleDeclaration_parentRule(
  const CSSOM_CSSStyleDeclaration *style)
{
  return style->parentRule;
}



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclaration_values(
  const CSSOM_CSSStyleDeclaration *style)
{
  return style->values;
}



void CSSOM_CSSStyleDeclaration__keepParser(CSSOM_CSSStyleDeclaration *style,
  SAC_Parser parser)
{
  assert(style->parser == NULL);
  style->parser = parser;
}



const char * CSSOM_CSSStyleDeclaration_azimuth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_AZIMUTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setAzimuth(CSSOM_CSSStyleDeclaration *style,
  const char *azimuth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_AZIMUTH_PROPERTY, azimuth);
}



const char * CSSOM_CSSStyleDeclaration_background(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackground(CSSOM_CSSStyleDeclaration *style,
  const char *background)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_PROPERTY, background);
}



const char* CSSOM_CSSStyleDeclaration_backgroundAttachment(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_ATTACHMENT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackgroundAttachment(
  CSSOM_CSSStyleDeclaration *style, const char *backgroundAttachment)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_ATTACHMENT_PROPERTY, backgroundAttachment);
}



const char* CSSOM_CSSStyleDeclaration_backgroundColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackgroundColor(
  CSSOM_CSSStyleDeclaration *style, const char *backgroundColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_COLOR_PROPERTY, backgroundColor);
}



const char* CSSOM_CSSStyleDeclaration_backgroundImage(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_IMAGE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackgroundImage(
  CSSOM_CSSStyleDeclaration *style, const char *backgroundImage)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_IMAGE_PROPERTY, backgroundImage);
}



const char* CSSOM_CSSStyleDeclaration_backgroundPosition(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_POSITION_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackgroundPosition(
  CSSOM_CSSStyleDeclaration *style, const char *backgroundPosition)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_POSITION_PROPERTY, backgroundPosition);
}



const char* CSSOM_CSSStyleDeclaration_backgroundRepeat(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BACKGROUND_REPEAT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBackgroundRepeat(
  CSSOM_CSSStyleDeclaration *style, const char *backgroundRepeat)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BACKGROUND_REPEAT_PROPERTY, backgroundRepeat);
}



const char* CSSOM_CSSStyleDeclaration_border(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorder(
  CSSOM_CSSStyleDeclaration *style, const char *border)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_PROPERTY, border);
}



const char* CSSOM_CSSStyleDeclaration_borderCollapse(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_COLLAPSE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderCollapse(
  CSSOM_CSSStyleDeclaration *style, const char *borderCollapse)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_COLLAPSE_PROPERTY, borderCollapse);
}



const char* CSSOM_CSSStyleDeclaration_borderColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderColor(
  CSSOM_CSSStyleDeclaration *style, const char *borderColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_COLOR_PROPERTY, borderColor);
}



const char* CSSOM_CSSStyleDeclaration_borderSpacing(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_SPACING_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderSpacing(
  CSSOM_CSSStyleDeclaration *style, const char *borderSpacing)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_SPACING_PROPERTY, borderSpacing);
}



const char* CSSOM_CSSStyleDeclaration_borderStyle(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_STYLE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderStyle(
  CSSOM_CSSStyleDeclaration *style, const char *borderStyle)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_STYLE_PROPERTY, borderStyle);
}



const char* CSSOM_CSSStyleDeclaration_borderTop(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_TOP_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderTop(
  CSSOM_CSSStyleDeclaration *style, const char *borderTop)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_TOP_PROPERTY, borderTop);
}



const char* CSSOM_CSSStyleDeclaration_borderRight(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_RIGHT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderRight(
  CSSOM_CSSStyleDeclaration *style, const char *borderRight)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_RIGHT_PROPERTY, borderRight);
}



const char* CSSOM_CSSStyleDeclaration_borderBottom(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_BOTTOM_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderBottom(
  CSSOM_CSSStyleDeclaration *style, const char *borderBottom)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_BOTTOM_PROPERTY, borderBottom);
}



const char* CSSOM_CSSStyleDeclaration_borderLeft(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_LEFT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderLeft(
  CSSOM_CSSStyleDeclaration *style, const char *borderLeft)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_LEFT_PROPERTY, borderLeft);
}



const char* CSSOM_CSSStyleDeclaration_borderTopColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_TOP_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderTopColor(
  CSSOM_CSSStyleDeclaration *style, const char *borderTopColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_TOP_COLOR_PROPERTY, borderTopColor);
}



const char* CSSOM_CSSStyleDeclaration_borderRightColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_RIGHT_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderRightColor(
  CSSOM_CSSStyleDeclaration *style, const char *borderRightColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_RIGHT_COLOR_PROPERTY, borderRightColor);
}



const char* CSSOM_CSSStyleDeclaration_borderBottomColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_BOTTOM_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderBottomColor(
  CSSOM_CSSStyleDeclaration *style, const char *borderBottomColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_BOTTOM_COLOR_PROPERTY, borderBottomColor);
}



const char* CSSOM_CSSStyleDeclaration_borderLeftColor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_LEFT_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderLeftColor(
  CSSOM_CSSStyleDeclaration *style, const char *borderLeftColor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_LEFT_COLOR_PROPERTY, borderLeftColor);
}



const char* CSSOM_CSSStyleDeclaration_borderTopStyle(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_TOP_STYLE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderTopStyle(
  CSSOM_CSSStyleDeclaration *style, const char *borderTopStyle)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_TOP_STYLE_PROPERTY, borderTopStyle);
}



const char* CSSOM_CSSStyleDeclaration_borderRightStyle(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_RIGHT_STYLE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderRightStyle(
  CSSOM_CSSStyleDeclaration *style, const char *borderRightStyle)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_RIGHT_STYLE_PROPERTY, borderRightStyle);
}



const char* CSSOM_CSSStyleDeclaration_borderBottomStyle(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_BOTTOM_STYLE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderBottomStyle(
  CSSOM_CSSStyleDeclaration *style, const char *borderBottomStyle)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, borderBottomStyle);
}



const char* CSSOM_CSSStyleDeclaration_borderLeftStyle(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_LEFT_STYLE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderLeftStyle(
  CSSOM_CSSStyleDeclaration *style, const char *borderLeftStyle)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_LEFT_STYLE_PROPERTY, borderLeftStyle);
}



const char* CSSOM_CSSStyleDeclaration_borderTopWidth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_TOP_WIDTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderTopWidth(
  CSSOM_CSSStyleDeclaration *style, const char *borderTopWidth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_TOP_WIDTH_PROPERTY, borderTopWidth);
}



const char* CSSOM_CSSStyleDeclaration_borderRightWidth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_RIGHT_WIDTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderRightWidth(
  CSSOM_CSSStyleDeclaration *style, const char *borderRightWidth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, borderRightWidth);
}



const char* CSSOM_CSSStyleDeclaration_borderBottomWidth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderBottomWidth(
  CSSOM_CSSStyleDeclaration *style, const char *borderBottomWidth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, borderBottomWidth);
}



const char* CSSOM_CSSStyleDeclaration_borderLeftWidth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_LEFT_WIDTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderLeftWidth(
  CSSOM_CSSStyleDeclaration *style, const char *borderLeftWidth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_LEFT_WIDTH_PROPERTY, borderLeftWidth);
}



const char* CSSOM_CSSStyleDeclaration_borderWidth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BORDER_WIDTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBorderWidth(
  CSSOM_CSSStyleDeclaration *style, const char *borderWidth)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BORDER_WIDTH_PROPERTY, borderWidth);
}



const char* CSSOM_CSSStyleDeclaration_bottom(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_BOTTOM_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setBottom(
  CSSOM_CSSStyleDeclaration *style, const char *bottom)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_BOTTOM_PROPERTY, bottom);
}



const char* CSSOM_CSSStyleDeclaration_captionSide(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CAPTION_SIDE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCaptionSide(
  CSSOM_CSSStyleDeclaration *style, const char *captionSide)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CAPTION_SIDE_PROPERTY, captionSide);
}



const char* CSSOM_CSSStyleDeclaration_clear(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CLEAR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setClear(
  CSSOM_CSSStyleDeclaration *style, const char *clear)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CLEAR_PROPERTY, clear);
}



const char* CSSOM_CSSStyleDeclaration_clip(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CLIP_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setClip(
  CSSOM_CSSStyleDeclaration *style, const char *clip)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CLIP_PROPERTY, clip);
}



const char* CSSOM_CSSStyleDeclaration_color(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_COLOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setColor(
  CSSOM_CSSStyleDeclaration *style, const char *color)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_COLOR_PROPERTY, color);
}



const char* CSSOM_CSSStyleDeclaration_content(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CONTENT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setContent(
  CSSOM_CSSStyleDeclaration *style, const char *content)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CONTENT_PROPERTY, content);
}



const char* CSSOM_CSSStyleDeclaration_counterIncrement(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_COUNTER_INCREMENT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCounterIncrement(
  CSSOM_CSSStyleDeclaration *style, const char *counterIncrement)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_COUNTER_INCREMENT_PROPERTY, counterIncrement);
}



const char* CSSOM_CSSStyleDeclaration_counterReset(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_COUNTER_RESET_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCounterReset(
  CSSOM_CSSStyleDeclaration *style, const char *counterReset)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_COUNTER_RESET_PROPERTY, counterReset);
}



const char* CSSOM_CSSStyleDeclaration_cue(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CUE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCue(
  CSSOM_CSSStyleDeclaration *style, const char *cue)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CUE_PROPERTY, cue);
}



const char* CSSOM_CSSStyleDeclaration_cueAfter(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CUE_AFTER_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCueAfter(
  CSSOM_CSSStyleDeclaration *style, const char *cueAfter)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CUE_AFTER_PROPERTY, cueAfter);
}



const char* CSSOM_CSSStyleDeclaration_cueBefore(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CUE_BEFORE_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCueBefore(
  CSSOM_CSSStyleDeclaration *style, const char *cueBefore)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CUE_BEFORE_PROPERTY, cueBefore);
}



const char* CSSOM_CSSStyleDeclaration_cursor(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_CURSOR_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCursor(
  CSSOM_CSSStyleDeclaration *style, const char *cursor)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_CURSOR_PROPERTY, cursor);
}



const char* CSSOM_CSSStyleDeclaration_direction(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_DIRECTION_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setDirection(
  CSSOM_CSSStyleDeclaration *style, const char *direction)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_DIRECTION_PROPERTY, direction);
}



const char* CSSOM_CSSStyleDeclaration_display(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_DISPLAY_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setDisplay(
  CSSOM_CSSStyleDeclaration *style, const char *display)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_DISPLAY_PROPERTY, display);
}



const char* CSSOM_CSSStyleDeclaration_elevation(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_ELEVATION_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setElevation(
  CSSOM_CSSStyleDeclaration *style, const char *elevation)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_ELEVATION_PROPERTY, elevation);
}



const char* CSSOM_CSSStyleDeclaration_emptyCells(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_EMPTY_CELLS_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setEmptyCells(
  CSSOM_CSSStyleDeclaration *style, const char *emptyCells)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_EMPTY_CELLS_PROPERTY, emptyCells);
}



const char* CSSOM_CSSStyleDeclaration_cssFloat(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_FLOAT_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setCSSFloat(
  CSSOM_CSSStyleDeclaration *style, const char *cssFloat)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_FLOAT_PROPERTY, cssFloat);
}



const char* CSSOM_CSSStyleDeclaration_fontFamily(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_FONT_FAMILY_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setFontFamily(
  CSSOM_CSSStyleDeclaration *style, const char *fontFamily)
{
  CSSOM_CSSStyleDeclarationValue__fsetProperty(style->values,
    CSSOM_FONT_FAMILY_PROPERTY, fontFamily);
}
