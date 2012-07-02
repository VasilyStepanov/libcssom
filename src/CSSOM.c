#include "CSSOM.h"

#include "MediaList.h"
#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSPropertyData.h"
#include "CSSPropertySetting.h"
#include "CSSPropertyValue.h"
#include "LexicalUnitRange_azimuth.h"
#include "LexicalUnitRange_background.h"
#include "LexicalUnitRange_border.h"
#include "LexicalUnitRange_bottom.h"
#include "LexicalUnitRange_captionSide.h"
#include "LexicalUnitRange_clear.h"
#include "LexicalUnitRange_clip.h"
#include "LexicalUnitRange_color.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "Parser.h"
#include "ParserStack.h"
#include "Selector.h"
#include "memory.h"
#include "gcc.h"

#include <sacc.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>



#define _CSSOM_INITIAL(initial) \
  (initial), &(initial)[_CSSOM_ARSIZE(initial)], -1



static int inited = 0;



static SAC_LexicalUnit unit_transparent;
static SAC_LexicalUnit unit_none;
static SAC_LexicalUnit unit_repeat;
static SAC_LexicalUnit unit_scroll;
static SAC_LexicalUnit unit_0pct;
static SAC_LexicalUnit unit_rgb000;
static SAC_LexicalUnit unit_comma;
static SAC_LexicalUnit unit_0;
static SAC_LexicalUnit *unit_rgb000_paramteters[6];
static SAC_LexicalUnit unit_medium;



/**
 * background
 */

static const SAC_LexicalUnit *backgroundColor[] = {
  &unit_transparent
};

static const SAC_LexicalUnit *backgroundImage[] = {
  &unit_none
};

static const SAC_LexicalUnit *backgroundRepeat[] = {
  &unit_repeat
};

static const SAC_LexicalUnit *backgroundAttachment[] = {
  &unit_scroll
};

static const SAC_LexicalUnit *backgroundPosition[] = {
  &unit_0pct, &unit_0pct
};



static const int backgroundSubhashes[] = {
  CSSOM_BACKGROUND_COLOR_PROPERTY,
  CSSOM_BACKGROUND_IMAGE_PROPERTY,
  CSSOM_BACKGROUND_REPEAT_PROPERTY,
  CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
  CSSOM_BACKGROUND_POSITION_PROPERTY
};



static const struct _CSSOM_LexicalUnitRange
backgroundInitial[_CSSOM_ARSIZE(backgroundSubhashes)] = {
  { CSSOM_BACKGROUND_COLOR_PROPERTY, _CSSOM_INITIAL(backgroundColor) },
  { CSSOM_BACKGROUND_IMAGE_PROPERTY, _CSSOM_INITIAL(backgroundImage) },
  { CSSOM_BACKGROUND_REPEAT_PROPERTY, _CSSOM_INITIAL(backgroundRepeat) },
  { CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
    _CSSOM_INITIAL(backgroundAttachment) },
  { CSSOM_BACKGROUND_POSITION_PROPERTY, _CSSOM_INITIAL(backgroundPosition) }
};



/**
 * border
 */

static const SAC_LexicalUnit *borderColor[] = {
  &unit_rgb000
};

static const SAC_LexicalUnit *borderStyle[] = {
  &unit_none
};

static const SAC_LexicalUnit *borderWidth[] = {
  &unit_medium
};



static const int borderColorSubhashes[] = {
  CSSOM_BORDER_TOP_COLOR_PROPERTY,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY
};

static const int borderStyleSubhashes[] = {
  CSSOM_BORDER_TOP_STYLE_PROPERTY,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY
};

static const int borderWidthSubhashes[] = {
  CSSOM_BORDER_TOP_WIDTH_PROPERTY,
  CSSOM_BORDER_RIGHT_WIDTH_PROPERTY,
  CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY,
  CSSOM_BORDER_LEFT_WIDTH_PROPERTY
};

static const int borderSubhashes[] = {
  CSSOM_BORDER_WIDTH_PROPERTY,
  CSSOM_BORDER_STYLE_PROPERTY,
  CSSOM_BORDER_COLOR_PROPERTY
};

static const struct _CSSOM_LexicalUnitRange
borderInitial[_CSSOM_ARSIZE(borderSubhashes)] = {
  { CSSOM_BORDER_WIDTH_PROPERTY, _CSSOM_INITIAL(borderWidth) },
  { CSSOM_BORDER_STYLE_PROPERTY, _CSSOM_INITIAL(borderStyle) },
  { CSSOM_BORDER_COLOR_PROPERTY, _CSSOM_INITIAL(borderColor) }
};

static const int borderTopSubhashes[] = {
  CSSOM_BORDER_TOP_WIDTH_PROPERTY,
  CSSOM_BORDER_TOP_STYLE_PROPERTY,
  CSSOM_BORDER_TOP_COLOR_PROPERTY
};

static const struct _CSSOM_LexicalUnitRange
borderTopInitial[_CSSOM_ARSIZE(borderTopSubhashes)] = {
  { CSSOM_BORDER_TOP_WIDTH_PROPERTY, _CSSOM_INITIAL(borderWidth) },
  { CSSOM_BORDER_TOP_STYLE_PROPERTY, _CSSOM_INITIAL(borderStyle) },
  { CSSOM_BORDER_TOP_COLOR_PROPERTY, _CSSOM_INITIAL(borderColor) }
};

static const int borderRightSubhashes[] = {
  CSSOM_BORDER_RIGHT_WIDTH_PROPERTY,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY
};

static const struct _CSSOM_LexicalUnitRange
borderRightInitial[_CSSOM_ARSIZE(borderRightSubhashes)] = {
  { CSSOM_BORDER_RIGHT_WIDTH_PROPERTY, _CSSOM_INITIAL(borderWidth) },
  { CSSOM_BORDER_RIGHT_STYLE_PROPERTY, _CSSOM_INITIAL(borderStyle) },
  { CSSOM_BORDER_RIGHT_COLOR_PROPERTY, _CSSOM_INITIAL(borderColor) }
};

static const int borderBottomSubhashes[] = {
  CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY
};

static const struct _CSSOM_LexicalUnitRange
borderBottomInitial[_CSSOM_ARSIZE(borderBottomSubhashes)] = {
  { CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY, _CSSOM_INITIAL(borderWidth) },
  { CSSOM_BORDER_BOTTOM_STYLE_PROPERTY, _CSSOM_INITIAL(borderStyle) },
  { CSSOM_BORDER_BOTTOM_COLOR_PROPERTY, _CSSOM_INITIAL(borderColor) }
};

static const int borderLeftSubhashes[] = {
  CSSOM_BORDER_LEFT_WIDTH_PROPERTY,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY
};

static const struct _CSSOM_LexicalUnitRange
borderLeftInitial[_CSSOM_ARSIZE(borderLeftSubhashes)] = {
  { CSSOM_BORDER_LEFT_WIDTH_PROPERTY, _CSSOM_INITIAL(borderWidth) },
  { CSSOM_BORDER_LEFT_STYLE_PROPERTY, _CSSOM_INITIAL(borderStyle) },
  { CSSOM_BORDER_LEFT_COLOR_PROPERTY, _CSSOM_INITIAL(borderColor) }
};





const struct _CSSOM_CSSPropertySetting CSSOM_propertySettings[] = {
  /* CSSOM_AZIMUTH_PROPERTY */
  { "azimuth",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_azimuth,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BACKGROUND_PROPERTY */
  { "background",
    backgroundSubhashes,
    backgroundInitial,
    _CSSOM_ARSIZE(backgroundSubhashes),
    CSSOM_LexicalUnitRange_background,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BACKGROUND_ATTACHMENT_PROPERTY */
  { "background-attachment",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundAttachment,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BACKGROUND_COLOR_PROPERTY */
  { "background-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundColor,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BACKGROUND_IMAGE_PROPERTY */
  { "background-image",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundImage,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BACKGROUND_POSITION_PROPERTY */
  { "background-position",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundPosition,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BACKGROUND_REPEAT_PROPERTY */
  { "background-repeat",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundRepeat,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_PROPERTY */
  { "border",
    borderSubhashes,
    borderInitial,
    _CSSOM_ARSIZE(borderSubhashes),
    CSSOM_LexicalUnitRange_border,
    &CSSOM_CSSPropertyValue__omitRecursiveShorthand },
  /* CSSOM_BORDER_COLLAPSE_PROPERTY */
  { "border-collapse",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderCollapse,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_COLOR_PROPERTY */
  { "border-color",
    borderColorSubhashes,
    NULL,
    _CSSOM_ARSIZE(borderColorSubhashes),
    CSSOM_LexicalUnitRange_borderColor,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BORDER_SPACING_PROPERTY */
  { "border-spacing",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderSpacing,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_STYLE_PROPERTY */
  { "border-style",
    borderStyleSubhashes,
    NULL,
    _CSSOM_ARSIZE(borderStyleSubhashes),
    CSSOM_LexicalUnitRange_borderStyle,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BORDER_TOP_PROPERTY */
  { "border-top",
    borderTopSubhashes,
    borderTopInitial,
    _CSSOM_ARSIZE(borderTopSubhashes),
    CSSOM_LexicalUnitRange_borderTop,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BORDER_RIGHT_PROPERTY */
  { "border-right",
    borderRightSubhashes,
    borderRightInitial,
    _CSSOM_ARSIZE(borderRightSubhashes),
    CSSOM_LexicalUnitRange_borderRight,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BORDER_BOTTOM_PROPERTY */
  { "border-bottom",
    borderBottomSubhashes,
    borderBottomInitial,
    _CSSOM_ARSIZE(borderBottomSubhashes),
    CSSOM_LexicalUnitRange_borderBottom,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BORDER_LEFT_PROPERTY */
  { "border-left",
    borderLeftSubhashes,
    borderLeftInitial,
    _CSSOM_ARSIZE(borderLeftSubhashes),
    CSSOM_LexicalUnitRange_borderLeft,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BORDER_TOP_COLOR_PROPERTY */
  { "border-top-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopColor,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_RIGHT_COLOR_PROPERTY */
  { "border-right-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightColor,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_BOTTOM_COLOR_PROPERTY */
  { "border-bottom-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomColor,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_LEFT_COLOR_PROPERTY */
  { "border-left-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftColor,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_TOP_STYLE_PROPERTY */
  { "border-top-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopStyle,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_RIGHT_STYLE_PROPERTY */
  { "border-right-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightStyle,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_BOTTOM_STYLE_PROPERTY */
  { "border-bottom-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomStyle,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_LEFT_STYLE_PROPERTY */
  { "border-left-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftStyle,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_TOP_WIDTH_PROPERTY */
  { "border-top-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopWidth,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_RIGHT_WIDTH_PROPERTY */
  { "border-right-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightWidth,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY */
  { "border-bottom-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomWidth,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_LEFT_WIDTH_PROPERTY */
  { "border-left-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftWidth,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_BORDER_WIDTH_PROPERTY */
  { "border-width",
    borderWidthSubhashes,
    NULL,
    _CSSOM_ARSIZE(borderWidthSubhashes),
    CSSOM_LexicalUnitRange_borderWidth,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BOTTOM_PROPERTY */
  { "bottom",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_bottom,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CAPTION_SIDE_PROPERTY */
  { "caption-side",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_captionSide,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CLEAR_PROPERTY */
  { "clear",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_clear,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CLIP_PROPERTY */
  { "clip",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_clip,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_COLOR_PROPERTY */
  { "color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_color,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CONTENT_PROPERTY */
  { "content",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_COUNTER_INCREMENT_PROPERTY */
  { "counter",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_COUNTER_RESET_PROPERTY */
  { "counter-reset",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CUE_PROPERTY */
  { "cue",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CUE_AFTER_PROPERTY */
  { "cue-after",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CUE_BEFORE_PROPERTY */
  { "cue-before",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_CURSOR_PROPERTY */
  { "cursor",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_DIRECTION_PROPERTY */
  { "direction",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_DISPLAY_PROPERTY */
  { "display",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_ELEVATION_PROPERTY */
  { "elevation",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_EMPTY_CELLS_PROPERTY */
  { "empty-cells",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FLOAT_PROPERTY */
  { "float",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_PROPERTY */
  { "font",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_FAMILY_PROPERTY */
  { "font-family",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_SIZE_PROPERTY */
  { "font-size",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_SIZE_ADJUST_PROPERTY */
  { "font-size-adjust",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_STRETCH_PROPERTY */
  { "font-stretch",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_STYLE_PROPERTY */
  { "font-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_VARIANT_PROPERTY */
  { "font-variant",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_FONT_WEIGHT_PROPERTY */
  { "font-weight",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_HEIGHT_PROPERTY */
  { "height",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LEFT_PROPERTY */
  { "left",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LETTER_SPACING_PROPERTY */
  { "letter-spacing",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LINE_HEIGHT_PROPERTY */
  { "line-height",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LIST_STYLE_PROPERTY */
  { "list-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LIST_STYLE_IMAGE_PROPERTY */
  { "list-style-image",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LIST_STYLE_POSITION_PROPERTY */
  { "list-style-position",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_LIST_STYLE_TYPE_PROPERTY */
  { "list-style-type",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARGIN_PROPERTY */
  { "margin",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARGIN_TOP_PROPERTY */
  { "margin-top",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARGIN_RIGHT_PROPERTY */
  { "margin-right",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARGIN_BOTTOM_PROPERTY */
  { "margin-bottom",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARGIN_LEFT_PROPERTY */
  { "margin-left",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARKER_OFFSET_PROPERTY */
  { "marker-offset",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MARKS_PROPERTY */
  { "marks",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MAX_HEIGHT_PROPERTY */
  { "max-height",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MAX_WIDTH_PROPERTY */
  { "max-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MIN_HEIGHT_PROPERTY */
  { "min-height",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_MIN_WIDTH_PROPERTY */
  { "min-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_ORPHANS_PROPERTY */
  { "orphans",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_OUTLINE_PROPERTY */
  { "outline",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_OUTLINE_COLOR_PROPERTY */
  { "outline-color",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_OUTLINE_STYLE_PROPERTY */
  { "outline-style",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_OUTLINE_WIDTH_PROPERTY */
  { "outline-width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_OVERFLOW_PROPERTY */
  { "overflow",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PADDING_PROPERTY */
  { "padding",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PADDING_TOP_PROPERTY */
  { "padding-top",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PADDING_RIGHT_PROPERTY */
  { "padding-right",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PADDING_BOTTOM_PROPERTY */
  { "padding-bottom",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PADDING_LEFT_PROPERTY */
  { "padding-left",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAGE_PROPERTY */
  { "page",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAGE_BREAK_AFTER_PROPERTY */
  { "page-break-after",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAGE_BREAK_BEFORE_PROPERTY */
  { "page-break-before",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAGE_BREAK_INSIDE_PROPERTY */
  { "page-break-inside",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAUSE_PROPERTY */
  { "pause",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAUSE_AFTER_PROPERTY */
  { "pause-after",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PAUSE_BEFORE_PROPERTY */
  { "pause-before",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PITCH_PROPERTY */
  { "pitch",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PITCH_RANGE_PROPERTY */
  { "pitch-range",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_PLAY_DURING_PROPERTY */
  { "play-during",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_POSITION_PROPERTY */
  { "position",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_QUOTES_PROPERTY */
  { "quotes",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_RICHNESS_PROPERTY */
  { "richness",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_RIGHT_PROPERTY */
  { "right",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SIZE_PROPERTY */
  { "size",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SPEAK_PROPERTY */
  { "speak",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SPEAK_HEADER_PROPERTY */
  { "speak-header",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SPEAK_NUMERAL_PROPERTY */
  { "speak-numeral",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SPEAK_PUNCTUATION_PROPERTY */
  { "speak-punctuation",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SPEECH_RATE_PROPERTY */
  { "speech-rate",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_SRC_PROPERTY */
  { "src",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_STRESS_PROPERTY */
  { "stress",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TABLE_LAYOUT_PROPERTY */
  { "table-layout",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TEXT_ALIGN_PROPERTY */
  { "text-align",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TEXT_DECORATION_PROPERTY */
  { "text-decoration",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TEXT_INDENT_PROPERTY */
  { "text-indent",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TEXT_SHADOW_PROPERTY */
  { "text-shadow",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TEXT_TRANSFORM_PROPERTY */
  { "text-transform",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_TOP_PROPERTY */
  { "top",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_UNICODE_BIDI_PROPERTY */
  { "unicode-bidi",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_VERTICAL_ALIGN_PROPERTY */
  { "vertical-align",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_VISIBILITY_PROPERTY */
  { "visibility",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_VOICE_FAMILY_PROPERTY */
  { "voice-family",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_VOLUME_PROPERTY */
  { "volume",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_WHITE_SPACE_PROPERTY */
  { "white-space",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_WIDOWS_PROPERTY */
  { "widows",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_WIDTH_PROPERTY */
  { "width",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_WORD_SPACING_PROPERTY */
  { "word-spacing",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial },
  /* CSSOM_Z_INDEX_PROPERTY */
  { "z-index",
    NULL,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    &CSSOM_CSSPropertyValue__omitTrivial }
};



static void initGlobals(void) {
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

  unit_comma.lexicalUnitType = SAC_OPERATOR_COMMA;

  unit_0.lexicalUnitType = SAC_INTEGER;
  unit_0.desc.integer = 0;

  unit_rgb000_paramteters[0] = &unit_0;
  unit_rgb000_paramteters[1] = &unit_comma;
  unit_rgb000_paramteters[2] = &unit_0;
  unit_rgb000_paramteters[3] = &unit_comma;
  unit_rgb000_paramteters[4] = &unit_0;
  unit_rgb000_paramteters[5] = NULL;

  unit_rgb000.lexicalUnitType = SAC_RGBCOLOR;
  unit_rgb000.desc.function.name = "rgb";
  unit_rgb000.desc.function.parameters = unit_rgb000_paramteters;

  unit_medium.lexicalUnitType = SAC_IDENT;
  unit_medium.desc.ident = "medium";
}



struct _CSSOM {
  size_t handles;
  const char **properties;
  const struct _CSSOM_CSSPropertySetting *settings;
  size_t nproperties;
  size_t nshorthands;
  CSSOM_FSMTable_CSSPropertyValue * table;
  CSSOM_ErrorHandler errorHandler;
  void * userData;
  CSSOM_DOMAPI domapi;
};



CSSOM* CSSOM_create(void) {
  size_t i;
  const char **properties;
  size_t nshorthands;
  CSSOM_FSMTable_CSSPropertyValue *table;
  CSSOM *cssom;

  properties = (const char**)CSSOM_malloc(
    sizeof(const char *) * (CSSOM_nproperties + 1));
  if (properties == NULL) return NULL;

  nshorthands = 0;
  for (i = 0; i < CSSOM_nproperties; ++i) {
    const struct _CSSOM_CSSPropertySetting *setting;

    setting = &CSSOM_propertySettings[i];

    properties[i] = setting->name;
    if (setting->nsubhashes != 0) ++nshorthands;
  }
  properties[CSSOM_nproperties] = NULL;

  table = CSSOM_FSMTable_CSSPropertyValue_alloc(properties);
  if (table == NULL) {
    CSSOM_free(properties);
    return NULL;
  }

  cssom = (CSSOM*)CSSOM_malloc(sizeof(CSSOM));
  if (cssom == NULL) {
    CSSOM_free(properties);
    CSSOM_FSMTable_CSSPropertyValue_free(table);
    return NULL;
  }

  cssom->handles = 1;
  cssom->properties = properties;
  cssom->settings = CSSOM_propertySettings;
  cssom->nproperties = CSSOM_nproperties;
  cssom->nshorthands = nshorthands;
  cssom->table = table;
  cssom->errorHandler = NULL;
  cssom->userData = NULL;

  if (!inited) {
    initGlobals();
    inited = 1;
  }

  return cssom;
}



void CSSOM_acquire(CSSOM *cssom) {
  ++cssom->handles;
}



void CSSOM_release(CSSOM *cssom) {
  if (cssom == NULL) return;

  assert(cssom->handles > 0);
  --cssom->handles;
  if (cssom->handles > 0) return;

  CSSOM_FSMTable_CSSPropertyValue_free(cssom->table);
  CSSOM_free(cssom->properties);
  CSSOM_free(cssom);
}



void * CSSOM_getUserData(const CSSOM * cssom) {
  return cssom->userData;
}



void CSSOM_setUserData(CSSOM * cssom, void * userData) {
  cssom->userData = userData;
}



const CSSOM_DOMAPI* CSSOM_getDOMAPI(const CSSOM * cssom) {
  return &cssom->domapi;
}



void CSSOM_setDOMAPI(CSSOM *cssom, const CSSOM_DOMAPI *domapi) {
  cssom->domapi = *domapi;
}



void CSSOM_setErrorHandler(CSSOM * cssom, CSSOM_ErrorHandler handler) {
  cssom->errorHandler = handler;
}



void CSSOM__invalidModificationErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_INVALID_MODIFICATION_ERR;
    e.data = "Invalid modification error";
    cssom->errorHandler(cssom->userData, &e);
  }
}



void CSSOM__indexSizeErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_INDEX_SIZE_ERR;
    e.data = "Index size error";
    cssom->errorHandler(cssom->userData, &e);
  }
}



void CSSOM__hierarchyRequestErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_HIERARCHY_REQUEST_ERR;
    e.data = "Hierarchy request error";
    cssom->errorHandler(cssom->userData, &e);
  }
}



int CSSOM__error(const CSSOM *cssom, const SAC_Error *error) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = error->line;
    e.column = error->column;
    e.code = error->code;
    e.data = error->data;
    return cssom->errorHandler(cssom->userData, &e);
  }
  return 0;
}



CSSOM_CSSStyleSheet* CSSOM_parse(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSStyleSheet *styleSheet;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  styleSheet = CSSOM_CSSStyleSheet__alloc(cssom, NULL);
  if (styleSheet == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  if (CSSOM_ParserStack_pushCSSStyleSheet(stack, styleSheet) == NULL) {
    CSSOM_CSSStyleSheet_release(styleSheet);
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseStyleSheet(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSStyleSheet__keepParser(styleSheet, parser);

  return styleSheet;
}



CSSOM_CSSRule* CSSOM__parseRule(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *styleSheet,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSRule *cssRule;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  cssRule = NULL;
  if (CSSOM_ParserStack_pushCSSRuleCatcher(stack,
    parentRule, styleSheet, &cssRule) == NULL)
  {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseRule(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  if (cssRule != NULL) CSSOM_CSSRule__keepParser(cssRule, parser);

  return cssRule;
}



CSSOM_CSSStyleDeclaration* CSSOM__parseStyleDeclaration(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSStyleDeclaration *style;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  style = CSSOM_CSSStyleDeclaration__alloc(parentRule);
  if (style == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }


  if (CSSOM_ParserStack_pushCSSStyleDeclaration(stack, style) == NULL) {
    CSSOM_CSSStyleDeclaration_release(style);
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseStyleDeclaration(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSStyleDeclaration__keepParser(style, parser);

  return style;
}



CSSOM_MediaList* CSSOM__parseMedia(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *mediaText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_MediaQuery **mediaQuery;
  CSSOM_MediaList *media;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  mediaQuery = SAC_ParseMediaQuery(parser, mediaText, len);
  if (mediaQuery == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  media = CSSOM_MediaList__alloc(parentRule, mediaQuery);
  if (media == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_MediaList__keepParser(media, parser);

  return media;
}



CSSOM_MediaQuery* CSSOM__parseMediaQuery(const CSSOM *cssom,
  CSSOM_MediaList *parentMedia, const char *mediaText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_MediaQuery **mediaQuery;
  CSSOM_MediaQuery *query;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  mediaQuery = SAC_ParseMediaQuery(parser, mediaText, len);
  if (mediaQuery == NULL || mediaQuery[1] != NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  query = CSSOM_MediaQuery__alloc(parentMedia, *mediaQuery);
  if (query == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_MediaQuery__keepParser(query, parser);

  return query;
}



CSSOM_Selector* CSSOM__parseSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_Selector **selectors;
  CSSOM_Selector *selector;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  selectors = SAC_ParseSelectors(parser, selectorText, len);
  if (selectors == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  selector = CSSOM_Selector__alloc(cssom, parentRule, selectors);
  if (selector == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_Selector__keepParser(selector, parser);

  return selector;
}



CSSOM_Selector* CSSOM_parseSelector(const CSSOM *cssom,
  const char *selectorText, int len)
{
  return CSSOM__parseSelector(cssom, NULL, selectorText, len);
}



CSSOM_Selector* CSSOM__parsePageSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_Selector **selectors;
  CSSOM_Selector *selector;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  selectors = SAC_ParsePageSelectors(parser, selectorText, len);
  if (selectors == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  selector = CSSOM_Selector__alloc(cssom, parentRule, selectors);
  if (selector == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_Selector__keepParser(selector, parser);

  return selector;
}



int CSSOM__parsePriority(const CSSOM *cssom, const char *priority, int len) {
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  size_t errors;
  SAC_Boolean important;

  parser = SAC_CreateParser();
  if (parser == NULL) return -1;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return -1;
  }

  CSSOM_Parser_setup(parser, stack);

  important = SAC_ParsePriority(parser, priority, len);
  errors = CSSOM_ParserStats_syntaxErrors(CSSOM_ParserStack_stats(stack));

  CSSOM_ParserStack_free(stack);

  SAC_DisposeParser(parser);

  if (errors != 0) return -1;

  return important == SAC_TRUE ? 1 : 0;
}



CSSOM_CSSPropertyValue* CSSOM__parsePropertyValue(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *values, int hash, const char *value,
  int valueLen, const char *priority, int priorityLen)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_LexicalUnit *lu;
  SAC_Boolean important;
  CSSOM_CSSPropertyData *propertyData;
  CSSOM_CSSPropertyValue *propertyValue;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  lu = SAC_ParsePropertyValue(parser, value, valueLen);
  if (lu == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  important = SAC_FALSE;
  if (priority != NULL && priorityLen != 0) {
    int rval;

    rval = CSSOM__parsePriority(cssom, priority, priorityLen);
    if (rval == -1) {
      CSSOM_ParserStack_free(stack);
      SAC_DisposeParser(parser);
      return NULL;
    }
    important = rval == 1 ? SAC_TRUE : SAC_FALSE;
  }

  propertyData = CSSOM_CSSPropertyData__alloc(lu);
  if (propertyData == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  propertyValue = CSSOM_CSSPropertyValue__alloc(cssom, values, hash,
    propertyData, important, NULL);
  if (propertyValue == NULL) {
    CSSOM_CSSPropertyData_release(propertyData);
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSPropertyData__keepParser(propertyData, parser);
  CSSOM_CSSPropertyData_release(propertyData);

  return propertyValue;
}



const CSSOM_FSMTable_CSSPropertyValue* CSSOM__table(const CSSOM *cssom) {
  return cssom->table;
}



const struct _CSSOM_CSSPropertySetting* CSSOM__propertySetting(
  const CSSOM *cssom, int hash)
{
  return &cssom->settings[hash];
}



size_t CSSOM__nproperties(const CSSOM *cssom) {
  return cssom->nproperties;
}



size_t CSSOM__nshorthands(const CSSOM *cssom) {
  return cssom->nshorthands;
}
