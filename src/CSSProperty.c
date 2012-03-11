#include "CSSProperty.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



static void dumpLexicalUnit(FILE *out, const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_OPERATOR_PLUS:
      fprintf(out, "+");
      break;
    case SAC_OPERATOR_MINUS:
      fprintf(out, "-");
      break;
    case SAC_OPERATOR_COMMA:
      fprintf(out, ",");
      break;
    case SAC_OPERATOR_SLASH:
      fprintf(out, "/");
      break;
    case SAC_INHERIT:
      fprintf(out, "inherit");
      break;
    case SAC_INTEGER:
      fprintf(out, "%li", value->desc.integer);
      break;
    case SAC_REAL:
      fprintf(out, "%g", value->desc.real);
      break;
    case SAC_LENGTH_EM:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_EX:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_PIXEL:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_INCH:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_CENTIMETER:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_MILLIMETER:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_POINT:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_LENGTH_PICA:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_PERCENTAGE:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_DEGREE:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_GRADIAN:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_RADIAN:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_MILLISECOND:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_SECOND:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_HERTZ:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_KILOHERTZ:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_DOTS_PER_INCH:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_DOTS_PER_CENTIMETER:
      fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit);
      break;
    case SAC_URI:
      fprintf(out, "url(\"%s\")", value->desc.uri);
      break;
    case SAC_RGBCOLOR:
    case SAC_ATTR_FUNCTION:
    case SAC_RECT_FUNCTION:
    case SAC_COUNTER_FUNCTION:
    case SAC_COUNTERS_FUNCTION:
    case SAC_NTH_CHILD_FUNCTION:
    case SAC_NTH_LAST_CHILD_FUNCTION:
    case SAC_NTH_OF_TYPE_FUNCTION:
    case SAC_NTH_LAST_OF_TYPE_FUNCTION:
    case SAC_FUNCTION:
      {
        SAC_LexicalUnit **arg;

        fprintf(out, "%s(", value->desc.function.name);

        arg = value->desc.function.parameters;
        dumpLexicalUnit(out, *arg);
        while (*(++arg) != NULL) {
          fprintf(out, " ");
          dumpLexicalUnit(out, *arg);
        }
      }
      break;
    case SAC_IDENT:
      fprintf(out, "%s", value->desc.ident);
      break;
    case SAC_STRING_VALUE:
      fprintf(out, "\"%s\"", value->desc.stringValue);
      break;
    case SAC_UNICODERANGE:
      fprintf(out, "%s", value->desc.unicodeRange);
      break;
    case SAC_SUB_EXPRESSION:
      {
        SAC_LexicalUnit **sub;

        sub = value->desc.function.parameters;
        dumpLexicalUnit(out, *sub);
        while (*(++sub) != NULL) {
          fprintf(out, " ");
          dumpLexicalUnit(out, *sub);
        }
      }
      break;
    case SAC_DIMENSION:
      fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit);
      break;
    case SAC_OPERATOR_MULTIPLY:
      fprintf(out, "*");
      break;
    case SAC_OPERATOR_MOD:
      fprintf(out, "|");
      break;
    case SAC_OPERATOR_EXP:
      fprintf(out, "E");
      break;
    case SAC_OPERATOR_LT:
      fprintf(out, "<");
      break;
    case SAC_OPERATOR_GT:
      fprintf(out, ">");
      break;
    case SAC_OPERATOR_LE:
      fprintf(out, "<=");
      break;
    case SAC_OPERATOR_GE:
      fprintf(out, ">=");
      break;
    case SAC_OPERATOR_TILDE:
      fprintf(out, "~");
      break;
  };
}



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
  char *cssText;
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
  property->cssText = NULL;

  return property;
}



void CSSOM_CSSProperty__free(CSSOM_CSSProperty *property) {
  free(property->cssText);
  free(property);
}



void CSSOM_CSSProperty__setName(CSSOM_CSSProperty *property, const char *name) {
  property->name = name;
}



const char* CSSOM_CSSProperty_cssText(const CSSOM_CSSProperty *property) {
  if (property->cssText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    dumpLexicalUnit(out, property->value);

    if (fclose(out) != 0) return NULL;

    ((CSSOM_CSSProperty*)property)->cssText = buf;
  }
  return property->cssText;
}
