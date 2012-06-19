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
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_azimuth },
  /* CSSOM_BACKGROUND_PROPERTY */
  { "background",
    &CSSOM_CSSPropertyValue__genericShorthandEmit,
    CSSOM_CSSPropertyValue_backgroundSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes),
    CSSOM_LexicalUnitRange_background },
  /* CSSOM_BACKGROUND_ATTACHMENT_PROPERTY */
  { "background-attachment",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundAttachment },
  /* CSSOM_BACKGROUND_COLOR_PROPERTY */
  { "background-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundColor },
  /* CSSOM_BACKGROUND_IMAGE_PROPERTY */
  { "background-image",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundImage },
  /* CSSOM_BACKGROUND_POSITION_PROPERTY */
  { "background-position",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundPosition },
  /* CSSOM_BACKGROUND_REPEAT_PROPERTY */
  { "background-repeat",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_backgroundRepeat },
  /* CSSOM_BORDER_PROPERTY */
  { "border",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_BORDER_COLLAPSE_PROPERTY */
  { "border-collapse",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderCollapse },
  /* CSSOM_BORDER_COLOR_PROPERTY */
  { "border-color",
    &CSSOM_CSSPropertyValue__boxShorthandEmit,
    CSSOM_CSSPropertyValue_borderColorSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderColorSubtypes),
    CSSOM_LexicalUnitRange_borderColor },
  /* CSSOM_BORDER_SPACING_PROPERTY */
  { "border-spacing",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderSpacing },
  /* CSSOM_BORDER_STYLE_PROPERTY */
  { "border-style",
    &CSSOM_CSSPropertyValue__boxShorthandEmit,
    CSSOM_CSSPropertyValue_borderStyleSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderStyleSubtypes),
    CSSOM_LexicalUnitRange_borderStyle },
  /* CSSOM_BORDER_TOP_PROPERTY */
  { "border-top",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_BORDER_RIGHT_PROPERTY */
  { "border-right",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_BORDER_BOTTOM_PROPERTY */
  { "border-bottom",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_BORDER_LEFT_PROPERTY */
  { "border-left",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_BORDER_TOP_COLOR_PROPERTY */
  { "border-top-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopColor },
  /* CSSOM_BORDER_RIGHT_COLOR_PROPERTY */
  { "border-right-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightColor },
  /* CSSOM_BORDER_BOTTOM_COLOR_PROPERTY */
  { "border-bottom-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomColor },
  /* CSSOM_BORDER_LEFT_COLOR_PROPERTY */
  { "border-left-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftColor },
  /* CSSOM_BORDER_TOP_STYLE_PROPERTY */
  { "border-top-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopStyle },
  /* CSSOM_BORDER_RIGHT_STYLE_PROPERTY */
  { "border-right-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightStyle },
  /* CSSOM_BORDER_BOTTOM_STYLE_PROPERTY */
  { "border-bottom-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomStyle },
  /* CSSOM_BORDER_LEFT_STYLE_PROPERTY */
  { "border-left-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftStyle },
  /* CSSOM_BORDER_TOP_WIDTH_PROPERTY */
  { "border-top-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderTopWidth },
  /* CSSOM_BORDER_RIGHT_WIDTH_PROPERTY */
  { "border-right-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderRightWidth },
  /* CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY */
  { "border-bottom-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderBottomWidth },
  /* CSSOM_BORDER_LEFT_WIDTH_PROPERTY */
  { "border-left-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_borderLeftWidth },
  /* CSSOM_BORDER_WIDTH_PROPERTY */
  { "border-width",
    &CSSOM_CSSPropertyValue__boxShorthandEmit,
    CSSOM_CSSPropertyValue_borderWidthSubtypes,
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_borderWidthSubtypes),
    CSSOM_LexicalUnitRange_borderWidth },
  /* CSSOM_BOTTOM_PROPERTY */
  { "bottom",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CAPTION_SIDE_PROPERTY */
  { "caption-side",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CLEAR_PROPERTY */
  { "clear",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CLIP_PROPERTY */
  { "clip",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_COLOR_PROPERTY */
  { "color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CONTENT_PROPERTY */
  { "content",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_COUNTER_INCREMENT_PROPERTY */
  { "counter",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_COUNTER_RESET_PROPERTY */
  { "counter-reset",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CUE_PROPERTY */
  { "cue",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CUE_AFTER_PROPERTY */
  { "cue-after",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CUE_BEFORE_PROPERTY */
  { "cue-before",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_CURSOR_PROPERTY */
  { "cursor",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_DIRECTION_PROPERTY */
  { "direction",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_DISPLAY_PROPERTY */
  { "display",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_ELEVATION_PROPERTY */
  { "elevation",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_EMPTY_CELLS_PROPERTY */
  { "empty-cells",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FLOAT_PROPERTY */
  { "float",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_PROPERTY */
  { "font",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_FAMILY_PROPERTY */
  { "font-family",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_SIZE_PROPERTY */
  { "font-size",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_SIZE_ADJUST_PROPERTY */
  { "font-size-adjust",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_STRETCH_PROPERTY */
  { "font-stretch",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_STYLE_PROPERTY */
  { "font-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_VARIANT_PROPERTY */
  { "font-variant",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_FONT_WEIGHT_PROPERTY */
  { "font-weight",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_HEIGHT_PROPERTY */
  { "height",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LEFT_PROPERTY */
  { "left",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LETTER_SPACING_PROPERTY */
  { "letter-spacing",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LINE_HEIGHT_PROPERTY */
  { "line-height",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LIST_STYLE_PROPERTY */
  { "list-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LIST_STYLE_IMAGE_PROPERTY */
  { "list-style-image",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LIST_STYLE_POSITION_PROPERTY */
  { "list-style-position",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_LIST_STYLE_TYPE_PROPERTY */
  { "list-style-type",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARGIN_PROPERTY */
  { "margin",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARGIN_TOP_PROPERTY */
  { "margin-top",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARGIN_RIGHT_PROPERTY */
  { "margin-right",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARGIN_BOTTOM_PROPERTY */
  { "margin-bottom",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARGIN_LEFT_PROPERTY */
  { "margin-left",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARKER_OFFSET_PROPERTY */
  { "marker-offset",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MARKS_PROPERTY */
  { "marks",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MAX_HEIGHT_PROPERTY */
  { "max-height",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MAX_WIDTH_PROPERTY */
  { "max-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MIN_HEIGHT_PROPERTY */
  { "min-height",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_MIN_WIDTH_PROPERTY */
  { "min-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_ORPHANS_PROPERTY */
  { "orphans",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_OUTLINE_PROPERTY */
  { "outline",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_OUTLINE_COLOR_PROPERTY */
  { "outline-color",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_OUTLINE_STYLE_PROPERTY */
  { "outline-style",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_OUTLINE_WIDTH_PROPERTY */
  { "outline-width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_OVERFLOW_PROPERTY */
  { "overflow",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PADDING_PROPERTY */
  { "padding",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PADDING_TOP_PROPERTY */
  { "padding-top",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PADDING_RIGHT_PROPERTY */
  { "padding-right",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PADDING_BOTTOM_PROPERTY */
  { "padding-bottom",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PADDING_LEFT_PROPERTY */
  { "padding-left",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAGE_PROPERTY */
  { "page",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAGE_BREAK_AFTER_PROPERTY */
  { "page-break-after",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAGE_BREAK_BEFORE_PROPERTY */
  { "page-break-before",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAGE_BREAK_INSIDE_PROPERTY */
  { "page-break-inside",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAUSE_PROPERTY */
  { "pause",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAUSE_AFTER_PROPERTY */
  { "pause-after",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PAUSE_BEFORE_PROPERTY */
  { "pause-before",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PITCH_PROPERTY */
  { "pitch",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PITCH_RANGE_PROPERTY */
  { "pitch-range",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_PLAY_DURING_PROPERTY */
  { "play-during",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_POSITION_PROPERTY */
  { "position",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_QUOTES_PROPERTY */
  { "quotes",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_RICHNESS_PROPERTY */
  { "richness",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_RIGHT_PROPERTY */
  { "right",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SIZE_PROPERTY */
  { "size",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SPEAK_PROPERTY */
  { "speak",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SPEAK_HEADER_PROPERTY */
  { "speak-header",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SPEAK_NUMERAL_PROPERTY */
  { "speak-numeral",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SPEAK_PUNCTUATION_PROPERTY */
  { "speak-punctuation",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SPEECH_RATE_PROPERTY */
  { "speech-rate",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_SRC_PROPERTY */
  { "src",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_STRESS_PROPERTY */
  { "stress",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TABLE_LAYOUT_PROPERTY */
  { "table-layout",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TEXT_ALIGN_PROPERTY */
  { "text-align",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TEXT_DECORATION_PROPERTY */
  { "text-decoration",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TEXT_INDENT_PROPERTY */
  { "text-indent",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TEXT_SHADOW_PROPERTY */
  { "text-shadow",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TEXT_TRANSFORM_PROPERTY */
  { "text-transform",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_TOP_PROPERTY */
  { "top",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_UNICODE_BIDI_PROPERTY */
  { "unicode-bidi",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_VERTICAL_ALIGN_PROPERTY */
  { "vertical-align",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_VISIBILITY_PROPERTY */
  { "visibility",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_VOICE_FAMILY_PROPERTY */
  { "voice-family",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_VOLUME_PROPERTY */
  { "volume",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_WHITE_SPACE_PROPERTY */
  { "white-space",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_WIDOWS_PROPERTY */
  { "widows",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_WIDTH_PROPERTY */
  { "width",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_WORD_SPACING_PROPERTY */
  { "word-spacing",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever },
  /* CSSOM_Z_INDEX_PROPERTY */
  { "z-index",
    &CSSOM_CSSPropertyValue__genericEmit,
    NULL,
    0,
    CSSOM_LexicalUnitRange_whatever }
};struct _CSSOM {
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
