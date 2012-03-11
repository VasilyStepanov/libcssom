#include "CSSProperty.h"

#include <stdlib.h>



const char *CSSOM_CSSProperties[] = {
  "azimuth",
  "background",
  "background-attachment",
  "background-color",
  "background-image",
  "background-position",
  "background-repeat",
  "border",
  "border-collapse",
  "border-color",
  "border-spacing",
  "border-style",
  "border-top",
  "border-right",
  "border-bottom",
  "border-left",
  "border-top-color",
  "border-right-color",
  "border-bottom-color",
  "border-left-color",
  "border-top-style",
  "border-right-style",
  "border-bottom-style",
  "border-left-style",
  "border-top-width",
  "border-right-width",
  "border-bottom-width",
  "border-left-width",
  "border-width",
  "bottom",
  "caption-side",
  "clear",
  "clip",
  "color",
  "content",
  "counter-increment",
  "counter-reset",
  "cue",
  "cue-after",
  "cue-before",
  "cursor",
  "direction",
  "display",
  "elevation",
  "empty-cells",
  "float",
  "font",
  "font-family",
  "font-size",
  "font-size-adjust",
  "font-stretch",
  "font-style",
  "font-variant",
  "font-weight",
  "height",
  "left",
  "letter-spacing",
  "line-height",
  "list-style",
  "list-style-image",
  "list-style-position",
  "list-style-type",
  "margin",
  "margin-top",
  "margin-right",
  "margin-bottom",
  "margin-left",
  "marker-offset",
  "marks",
  "max-height",
  "max-width",
  "min-height",
  "min-width",
  "orphans",
  "outline",
  "outline-color",
  "outline-style",
  "outline-width",
  "overflow",
  "padding",
  "padding-top",
  "padding-right",
  "padding-bottom",
  "padding-left",
  "page",
  "page-break-after",
  "page-break-before",
  "page-break-inside",
  "pause",
  "pause-after",
  "pause-before",
  "pitch",
  "pitch-range",
  "play-during",
  "position",
  "quotes",
  "richness",
  "right",
  "size",
  "speak",
  "speak-header",
  "speak-numeral",
  "speak-punctuation",
  "speech-rate",
  "stress",
  "table-layout",
  "text-align",
  "text-decoration",
  "text-indent",
  "text-shadow",
  "text-transform",
  "top",
  "unicode-bidi",
  "vertical-align",
  "visibility",
  "voice-family",
  "volume",
  "white-space",
  "widows",
  "width",
  "word-spacing",
  "z-index",
  NULL
};



struct _CSSOM_CSSProperty {
  const char *name;
  const SAC_LexicalUnit *value;
  SAC_Boolean important;
};



CSSOM_CSSProperty* CSSOM_CSSProperty__alloc(
  const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSProperty *property;

  property = (CSSOM_CSSProperty*)malloc(sizeof(CSSOM_CSSProperty));
  if (property == NULL) return NULL;

  property->value = value;
  property->important = important;

  return property;
}



void CSSOM_CSSProperty__free(CSSOM_CSSProperty *property) {
  free(property);
}



void CSSOM_CSSProperty__setName(CSSOM_CSSProperty *property, const char *name) {
  property->name = name;
}
