#ifndef CSSOM_CSSPROPERTY_H
#define CSSOM_CSSPROPERTY_H

#ifdef __cplusplus
extern "C" {
#endif



typedef enum _CSSOM_CSSPropertyType {
  CSSOM_AZIMUTH_PROPERTY = 0,
  CSSOM_BACKGROUND_PROPERTY = 1,
  CSSOM_BACKGROUND_ATTACHMENT_PROPERTY = 2,
  CSSOM_BACKGROUND_COLOR_PROPERTY = 3,
  CSSOM_BACKGROUND_IMAGE_PROPERTY = 4,
  CSSOM_BACKGROUND_POSITION_PROPERTY = 5,
  CSSOM_BACKGROUND_REPEAT_PROPERTY = 6,
  CSSOM_BORDER_PROPERTY = 7,
  CSSOM_BORDER_COLLAPSE_PROPERTY = 8,
  CSSOM_BORDER_COLOR_PROPERTY = 9,
  CSSOM_BORDER_SPACING_PROPERTY = 10,
  CSSOM_BORDER_STYLE_PROPERTY = 11,
  CSSOM_BORDER_TOP_PROPERTY = 12,
  CSSOM_BORDER_RIGHT_PROPERTY = 13,
  CSSOM_BORDER_BOTTOM_PROPERTY = 14,
  CSSOM_BORDER_LEFT_PROPERTY = 15,
  CSSOM_BORDER_TOP_COLOR_PROPERTY = 16,
  CSSOM_BORDER_RIGHT_COLOR_PROPERTY = 17,
  CSSOM_BORDER_BOTTOM_COLOR_PROPERTY = 18,
  CSSOM_BORDER_LEFT_COLOR_PROPERTY = 19,
  CSSOM_BORDER_TOP_STYLE_PROPERTY = 20,
  CSSOM_BORDER_RIGHT_STYLE_PROPERTY = 21,
  CSSOM_BORDER_BOTTOM_STYLE_PROPERTY = 22,
  CSSOM_BORDER_LEFT_STYLE_PROPERTY = 23,
  CSSOM_BORDER_TOP_WIDTH_PROPERTY = 24,
  CSSOM_BORDER_RIGHT_WIDTH_PROPERTY = 25,
  CSSOM_BORDER_BOTTOM_WIDTH_PROPERTY = 26,
  CSSOM_BORDER_LEFT_WIDTH_PROPERTY = 27,
  CSSOM_BORDER_WIDTH_PROPERTY = 28,
  CSSOM_BOTTOM_PROPERTY = 29,
  CSSOM_CAPTION_SIDE_PROPERTY = 30,
  CSSOM_CLEAR_PROPERTY = 31,
  CSSOM_CLIP_PROPERTY = 32,
  CSSOM_COLOR_PROPERTY = 33,
  CSSOM_CONTENT_PROPERTY = 34,
  CSSOM_COUNTER_INCREMENT_PROPERTY = 35,
  CSSOM_COUNTER_RESET_PROPERTY = 36,
  CSSOM_CUE_PROPERTY = 37,
  CSSOM_CUE_AFTER_PROPERTY = 38,
  CSSOM_CUE_BEFORE_PROPERTY = 39,
  CSSOM_CURSOR_PROPERTY = 40,
  CSSOM_DIRECTION_PROPERTY = 41,
  CSSOM_DISPLAY_PROPERTY = 42,
  CSSOM_ELEVATION_PROPERTY = 43,
  CSSOM_EMPTY_CELLS_PROPERTY = 44,
  CSSOM_FLOAT_PROPERTY = 45,
  CSSOM_FONT_PROPERTY = 46,
  CSSOM_FONT_FAMILY_PROPERTY = 47,
  CSSOM_FONT_SIZE_PROPERTY = 48,
  CSSOM_FONT_SIZE_ADJUST_PROPERTY = 49,
  CSSOM_FONT_STRETCH_PROPERTY = 50,
  CSSOM_FONT_STYLE_PROPERTY = 51,
  CSSOM_FONT_VARIANT_PROPERTY = 52,
  CSSOM_FONT_WEIGHT_PROPERTY = 53,
  CSSOM_HEIGHT_PROPERTY = 54,
  CSSOM_LEFT_PROPERTY = 55,
  CSSOM_LETTER_SPACING_PROPERTY = 56,
  CSSOM_LINE_HEIGHT_PROPERTY = 57,
  CSSOM_LIST_STYLE_PROPERTY = 58,
  CSSOM_LIST_STYLE_IMAGE_PROPERTY = 59,
  CSSOM_LIST_STYLE_POSITION_PROPERTY = 60,
  CSSOM_LIST_STYLE_TYPE_PROPERTY = 61,
  CSSOM_MARGIN_PROPERTY = 62,
  CSSOM_MARGIN_TOP_PROPERTY = 63,
  CSSOM_MARGIN_RIGHT_PROPERTY = 64,
  CSSOM_MARGIN_BOTTOM_PROPERTY = 65,
  CSSOM_MARGIN_LEFT_PROPERTY = 66,
  CSSOM_MARKER_OFFSET_PROPERTY = 67,
  CSSOM_MARKS_PROPERTY = 68,
  CSSOM_MAX_HEIGHT_PROPERTY = 69,
  CSSOM_MAX_WIDTH_PROPERTY = 70,
  CSSOM_MIN_HEIGHT_PROPERTY = 71,
  CSSOM_MIN_WIDTH_PROPERTY = 72,
  CSSOM_ORPHANS_PROPERTY = 73,
  CSSOM_OUTLINE_PROPERTY = 74,
  CSSOM_OUTLINE_COLOR_PROPERTY = 75,
  CSSOM_OUTLINE_STYLE_PROPERTY = 76,
  CSSOM_OUTLINE_WIDTH_PROPERTY = 77,
  CSSOM_OVERFLOW_PROPERTY = 78,
  CSSOM_PADDING_PROPERTY = 79,
  CSSOM_PADDING_TOP_PROPERTY = 80,
  CSSOM_PADDING_RIGHT_PROPERTY = 81,
  CSSOM_PADDING_BOTTOM_PROPERTY = 82,
  CSSOM_PADDING_LEFT_PROPERTY = 83,
  CSSOM_PAGE_PROPERTY = 84,
  CSSOM_PAGE_BREAK_AFTER_PROPERTY = 85,
  CSSOM_PAGE_BREAK_BEFORE_PROPERTY = 86,
  CSSOM_PAGE_BREAK_INSIDE_PROPERTY = 87,
  CSSOM_PAUSE_PROPERTY = 88,
  CSSOM_PAUSE_AFTER_PROPERTY = 89,
  CSSOM_PAUSE_BEFORE_PROPERTY = 90,
  CSSOM_PITCH_PROPERTY = 91,
  CSSOM_PITCH_RANGE_PROPERTY = 92,
  CSSOM_PLAY_DURING_PROPERTY = 93,
  CSSOM_POSITION_PROPERTY = 94,
  CSSOM_QUOTES_PROPERTY = 95,
  CSSOM_RICHNESS_PROPERTY = 96,
  CSSOM_RIGHT_PROPERTY = 97,
  CSSOM_SIZE_PROPERTY = 98,
  CSSOM_SPEAK_PROPERTY = 99,
  CSSOM_SPEAK_HEADER_PROPERTY = 100,
  CSSOM_SPEAK_NUMERAL_PROPERTY = 101,
  CSSOM_SPEAK_PUNCTUATION_PROPERTY = 102,
  CSSOM_SPEECH_RATE_PROPERTY = 103,
  CSSOM_STRESS_PROPERTY = 104,
  CSSOM_TABLE_LAYOUT_PROPERTY = 105,
  CSSOM_TEXT_ALIGN_PROPERTY = 106,
  CSSOM_TEXT_DECORATION_PROPERTY = 107,
  CSSOM_TEXT_INDENT_PROPERTY = 108,
  CSSOM_TEXT_SHADOW_PROPERTY = 109,
  CSSOM_TEXT_TRANSFORM_PROPERTY = 110,
  CSSOM_TOP_PROPERTY = 111,
  CSSOM_UNICODE_BIDI_PROPERTY = 112,
  CSSOM_VERTICAL_ALIGN_PROPERTY = 113,
  CSSOM_VISIBILITY_PROPERTY = 114,
  CSSOM_VOICE_FAMILY_PROPERTY = 115,
  CSSOM_VOLUME_PROPERTY = 116,
  CSSOM_WHITE_SPACE_PROPERTY = 117,
  CSSOM_WIDOWS_PROPERTY = 118,
  CSSOM_WIDTH_PROPERTY = 119,
  CSSOM_WORD_SPACING_PROPERTY = 120,
  CSSOM_Z_INDEX_PROPERTY = 121
} CSSOM_CSSPropertyType;



extern const char *CSSOM_CSSProperties[];



typedef struct _CSSOM_CSSProperty CSSOM_CSSProperty;



const char* CSSOM_CSSProperty_cssText(const CSSOM_CSSProperty *property);

int CSSOM_CSSProperty_priority(const CSSOM_CSSProperty *property);



#ifdef __cplusplus
}
#endif

#endif
