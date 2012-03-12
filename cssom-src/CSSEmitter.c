#include "CSSEmitter.h"



void CSSOM_CSSEmitter_lexicalUnit(FILE *out, const SAC_LexicalUnit *value) {
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
        if (*arg != NULL) {
          CSSOM_CSSEmitter_lexicalUnit(out, *arg);
          while (*(++arg) != NULL) {
            fprintf(out, " ");
            CSSOM_CSSEmitter_lexicalUnit(out, *arg);
          }
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
        if (*sub != NULL) {
          CSSOM_CSSEmitter_lexicalUnit(out, *sub);
          while (*(++sub) != NULL) {
            fprintf(out, " ");
            CSSOM_CSSEmitter_lexicalUnit(out, *sub);
          }
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



void CSSOM_CSSEmitter_cssProperty(FILE *out,
  const CSSOM_CSSProperty *property)
{
  fprintf(out, "%s : %s",
    CSSOM_CSSProperty_name(property), CSSOM_CSSProperty_cssText(property));
  if (CSSOM_CSSProperty_important(property)) fprintf(out, "!important");
}
