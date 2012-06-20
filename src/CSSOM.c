#include "CSSOM.h"

#include "MediaList.h"
#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSPropertySetting.h"
#include "CSSPropertyValue.h"
#include "LexicalUnitRange_azimuth.h"
#include "LexicalUnitRange_background.h"
#include "LexicalUnitRange_border.h"
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



const struct _CSSOM_CSSPropertySetting CSSOM_propertySettings[] = {
  /* CSSOM_AZIMUTH_PROPERTY */
  { "azimuth",
    NULL,
    0,
    CSSOM_LexicalUnitRange_azimuth,
    NULL },
  /* CSSOM_BACKGROUND_PROPERTY */
  { "background",
    CSSOM_CSSPropertyValue_backgroundSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes),
    CSSOM_LexicalUnitRange_background,
    &CSSOM_CSSPropertyValue__omitGenericShorthand },
  /* CSSOM_BACKGROUND_ATTACHMENT_PROPERTY */
  { "background-attachment",
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundAttachment,
    NULL },
  /* CSSOM_BACKGROUND_COLOR_PROPERTY */
  { "background-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundColor,
    NULL },
  /* CSSOM_BACKGROUND_IMAGE_PROPERTY */
  { "background-image",
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundImage,
    NULL },
  /* CSSOM_BACKGROUND_POSITION_PROPERTY */
  { "background-position",
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundPosition,
    NULL },
  /* CSSOM_BACKGROUND_REPEAT_PROPERTY */
  { "background-repeat",
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundRepeat,
    NULL },
  /* CSSOM_BORDER_PROPERTY */
  { "border",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_BORDER_COLLAPSE_PROPERTY */
  { "border-collapse",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderCollapse,
    NULL },
  /* CSSOM_BORDER_COLOR_PROPERTY */
  { "border-color",
    CSSOM_CSSPropertyValue_borderColorSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderColorSubtypes),
    CSSOM_LexicalUnitRange_borderColor,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BORDER_SPACING_PROPERTY */
  { "border-spacing",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderSpacing,
    NULL },
  /* CSSOM_BORDER_STYLE_PROPERTY */
  { "border-style",
    CSSOM_CSSPropertyValue_borderStyleSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderStyleSubtypes),
    CSSOM_LexicalUnitRange_borderStyle,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BORDER_TOP_PROPERTY */
  { "border-top",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_BORDER_RIGHT_PROPERTY */
  { "border-right",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_BORDER_BOTTOM_PROPERTY */
  { "border-bottom",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_BORDER_LEFT_PROPERTY */
  { "border-left",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_BORDER_TOP_COLOR_PROPERTY */
  { "border-top-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopColor,
    NULL },
  /* CSSOM_BORDER_RIGHT_COLOR_PROPERTY */
  { "border-right-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightColor,
    NULL },
  /* CSSOM_BORDER_BOTTOM_COLOR_PROPERTY */
  { "border-bottom-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomColor,
    NULL },
  /* CSSOM_BORDER_LEFT_COLOR_PROPERTY */
  { "border-left-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftColor,
    NULL },
  /* CSSOM_BORDER_TOP_STYLE_PROPERTY */
  { "border-top-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopStyle,
    NULL },
  /* CSSOM_BORDER_RIGHT_STYLE_PROPERTY */
  { "border-right-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightStyle,
    NULL },
  /* CSSOM_BORDER_BOTTOM_STYLE_PROPERTY */
  { "border-bottom-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomStyle,
    NULL },
  /* CSSOM_BORDER_LEFT_STYLE_PROPERTY */
  { "border-left-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftStyle,
    NULL },
  /* CSSOM_BORDER_TOP_WIDTH_PROPERTY */
  { "border-top-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopWidth,
    NULL },
  /* CSSOM_BORDER_RIGHT_WIDTH_PROPERTY */
  { "border-right-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightWidth,
    NULL },
  /* CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY */
  { "border-bottom-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomWidth,
    NULL },
  /* CSSOM_BORDER_LEFT_WIDTH_PROPERTY */
  { "border-left-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftWidth,
    NULL },
  /* CSSOM_BORDER_WIDTH_PROPERTY */
  { "border-width",
    CSSOM_CSSPropertyValue_borderWidthSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderWidthSubtypes),
    CSSOM_LexicalUnitRange_borderWidth,
    &CSSOM_CSSPropertyValue__omitBoxShorthand },
  /* CSSOM_BOTTOM_PROPERTY */
  { "bottom",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CAPTION_SIDE_PROPERTY */
  { "caption-side",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CLEAR_PROPERTY */
  { "clear",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CLIP_PROPERTY */
  { "clip",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_COLOR_PROPERTY */
  { "color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CONTENT_PROPERTY */
  { "content",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_COUNTER_INCREMENT_PROPERTY */
  { "counter",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_COUNTER_RESET_PROPERTY */
  { "counter-reset",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CUE_PROPERTY */
  { "cue",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CUE_AFTER_PROPERTY */
  { "cue-after",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CUE_BEFORE_PROPERTY */
  { "cue-before",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_CURSOR_PROPERTY */
  { "cursor",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_DIRECTION_PROPERTY */
  { "direction",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_DISPLAY_PROPERTY */
  { "display",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_ELEVATION_PROPERTY */
  { "elevation",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_EMPTY_CELLS_PROPERTY */
  { "empty-cells",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FLOAT_PROPERTY */
  { "float",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_PROPERTY */
  { "font",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_FAMILY_PROPERTY */
  { "font-family",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_SIZE_PROPERTY */
  { "font-size",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_SIZE_ADJUST_PROPERTY */
  { "font-size-adjust",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_STRETCH_PROPERTY */
  { "font-stretch",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_STYLE_PROPERTY */
  { "font-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_VARIANT_PROPERTY */
  { "font-variant",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_FONT_WEIGHT_PROPERTY */
  { "font-weight",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_HEIGHT_PROPERTY */
  { "height",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LEFT_PROPERTY */
  { "left",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LETTER_SPACING_PROPERTY */
  { "letter-spacing",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LINE_HEIGHT_PROPERTY */
  { "line-height",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LIST_STYLE_PROPERTY */
  { "list-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LIST_STYLE_IMAGE_PROPERTY */
  { "list-style-image",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LIST_STYLE_POSITION_PROPERTY */
  { "list-style-position",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_LIST_STYLE_TYPE_PROPERTY */
  { "list-style-type",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARGIN_PROPERTY */
  { "margin",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARGIN_TOP_PROPERTY */
  { "margin-top",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARGIN_RIGHT_PROPERTY */
  { "margin-right",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARGIN_BOTTOM_PROPERTY */
  { "margin-bottom",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARGIN_LEFT_PROPERTY */
  { "margin-left",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARKER_OFFSET_PROPERTY */
  { "marker-offset",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MARKS_PROPERTY */
  { "marks",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MAX_HEIGHT_PROPERTY */
  { "max-height",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MAX_WIDTH_PROPERTY */
  { "max-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MIN_HEIGHT_PROPERTY */
  { "min-height",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_MIN_WIDTH_PROPERTY */
  { "min-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_ORPHANS_PROPERTY */
  { "orphans",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_OUTLINE_PROPERTY */
  { "outline",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_OUTLINE_COLOR_PROPERTY */
  { "outline-color",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_OUTLINE_STYLE_PROPERTY */
  { "outline-style",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_OUTLINE_WIDTH_PROPERTY */
  { "outline-width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_OVERFLOW_PROPERTY */
  { "overflow",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PADDING_PROPERTY */
  { "padding",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PADDING_TOP_PROPERTY */
  { "padding-top",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PADDING_RIGHT_PROPERTY */
  { "padding-right",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PADDING_BOTTOM_PROPERTY */
  { "padding-bottom",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PADDING_LEFT_PROPERTY */
  { "padding-left",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAGE_PROPERTY */
  { "page",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAGE_BREAK_AFTER_PROPERTY */
  { "page-break-after",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAGE_BREAK_BEFORE_PROPERTY */
  { "page-break-before",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAGE_BREAK_INSIDE_PROPERTY */
  { "page-break-inside",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAUSE_PROPERTY */
  { "pause",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAUSE_AFTER_PROPERTY */
  { "pause-after",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PAUSE_BEFORE_PROPERTY */
  { "pause-before",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PITCH_PROPERTY */
  { "pitch",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PITCH_RANGE_PROPERTY */
  { "pitch-range",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_PLAY_DURING_PROPERTY */
  { "play-during",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_POSITION_PROPERTY */
  { "position",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_QUOTES_PROPERTY */
  { "quotes",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_RICHNESS_PROPERTY */
  { "richness",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_RIGHT_PROPERTY */
  { "right",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SIZE_PROPERTY */
  { "size",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SPEAK_PROPERTY */
  { "speak",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SPEAK_HEADER_PROPERTY */
  { "speak-header",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SPEAK_NUMERAL_PROPERTY */
  { "speak-numeral",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SPEAK_PUNCTUATION_PROPERTY */
  { "speak-punctuation",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SPEECH_RATE_PROPERTY */
  { "speech-rate",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_SRC_PROPERTY */
  { "src",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_STRESS_PROPERTY */
  { "stress",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TABLE_LAYOUT_PROPERTY */
  { "table-layout",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TEXT_ALIGN_PROPERTY */
  { "text-align",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TEXT_DECORATION_PROPERTY */
  { "text-decoration",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TEXT_INDENT_PROPERTY */
  { "text-indent",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TEXT_SHADOW_PROPERTY */
  { "text-shadow",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TEXT_TRANSFORM_PROPERTY */
  { "text-transform",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_TOP_PROPERTY */
  { "top",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_UNICODE_BIDI_PROPERTY */
  { "unicode-bidi",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_VERTICAL_ALIGN_PROPERTY */
  { "vertical-align",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_VISIBILITY_PROPERTY */
  { "visibility",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_VOICE_FAMILY_PROPERTY */
  { "voice-family",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_VOLUME_PROPERTY */
  { "volume",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_WHITE_SPACE_PROPERTY */
  { "white-space",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_WIDOWS_PROPERTY */
  { "widows",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_WIDTH_PROPERTY */
  { "width",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_WORD_SPACING_PROPERTY */
  { "word-spacing",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL },
  /* CSSOM_Z_INDEX_PROPERTY */
  { "z-index",
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever,
    NULL }
};



struct _CSSOM {
  size_t handles;
  const char **properties;
  const struct _CSSOM_CSSPropertySetting *settings;
  CSSOM_FSMTable_CSSPropertyValue * table;
  CSSOM_ErrorHandler errorHandler;
  void * userData;
  CSSOM_DOMAPI domapi;
};



CSSOM* CSSOM_create(void) {
  size_t i;
  const char **properties;
  CSSOM_FSMTable_CSSPropertyValue *table;
  CSSOM *cssom;

  properties = (const char**)CSSOM_malloc(
    sizeof(const char *) * (CSSOM_nproperties + 1));
  if (properties == NULL) return NULL;

  for (i = 0; i < CSSOM_nproperties; ++i)
    properties[i] = CSSOM_propertySettings[i].name;
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
  cssom->table = table;
  cssom->errorHandler = NULL;
  cssom->userData = NULL;

  CSSOM_CSSPropertyValue__initGlobals();

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
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType type,
  const char *value, int valueLen, const char *priority, int priorityLen)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_LexicalUnit *lu;
  SAC_Boolean important;
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

  propertyValue = CSSOM_CSSPropertyValue__alloc(cssom, values, type, lu,
    important, NULL);
  if (propertyValue == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSPropertyValue__keepParser(propertyValue, parser);

  return propertyValue;
}



const CSSOM_FSMTable_CSSPropertyValue* CSSOM__table(const CSSOM *cssom) {
  return cssom->table;
}



const struct _CSSOM_CSSPropertySetting* CSSOM__propertySetting(
  const CSSOM *cssom, CSSOM_CSSPropertyType type)
{
  return &cssom->settings[type];
}
