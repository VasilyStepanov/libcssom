#include "CSSEmitter.h"



static void emit_selector(FILE *out, const SAC_Selector *selector);



static void emit_name(FILE *out,
  const char *namespaceURI, const char *localName)
{
  if (namespaceURI != NULL && localName != NULL) {
    fprintf(out, "%s|%s", namespaceURI, localName);
  } else if (namespaceURI != NULL) {
    fprintf(out, "%s|*", namespaceURI);
  } else if (localName != NULL) {
    fprintf(out, "%s", localName);
  } else {
    fprintf(out, "*");
  }
}



static void emit_condition(FILE *out, const SAC_Condition *condition) {
  switch (condition->conditionType) {
    case SAC_ONE_OF_ATTRIBUTE_CONDITION:
    case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
    case SAC_PREFIX_ATTRIBUTE_CONDITION:
    case SAC_SUFFIX_ATTRIBUTE_CONDITION:
    case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
    case SAC_ATTRIBUTE_CONDITION:
    case SAC_CLASS_CONDITION:
    case SAC_ID_CONDITION:
      fprintf(out, "[");
      emit_name(out,
        condition->desc.attribute.namespaceURI,
        condition->desc.attribute.localName);

      switch (condition->conditionType) {
        case SAC_ID_CONDITION:
          fprintf(out, "\"id\"");
          break;
        case SAC_CLASS_CONDITION:
          fprintf(out, "\"class\"");
          break;
        case SAC_PREFIX_ATTRIBUTE_CONDITION:
          fprintf(out, "\"prefix\"");
          break;
        case SAC_SUFFIX_ATTRIBUTE_CONDITION:
          fprintf(out, "\"suffix\"");
          break;
        case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
          fprintf(out, "\"substr\"");
          break;
        case SAC_ATTRIBUTE_CONDITION:
          fprintf(out, "\"attr\"");
          break;
        case SAC_ONE_OF_ATTRIBUTE_CONDITION:
          fprintf(out, "\"one_of\"");
          break;
        case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
          fprintf(out, "\"begin_hypen\"");
          break;
        default:
          fprintf(out, "\"unknown_%d\"", condition->conditionType);
          break;
      }

      if (condition->desc.attribute.value != NULL)
        fprintf(out, "=\"%s\"", condition->desc.attribute.value);

      fprintf(out, "]");

      break;
    case SAC_PSEUDO_CLASS_CONDITION:
    case SAC_PSEUDO_ELEMENT_CONDITION:
      {
        switch (condition->conditionType) {
          case SAC_PSEUDO_CLASS_CONDITION:
            fprintf(out, ":");
            break;
          case SAC_PSEUDO_ELEMENT_CONDITION:
            fprintf(out, "::");
            break;
          default:
            fprintf(out, "?");
            break;
        }
        CSSOM_CSSEmitter_lexicalUnit(out, condition->desc.pseudo);
      }
      break;
    case SAC_AND_CONDITION:
      emit_condition(out, condition->desc.combinator.firstCondition);
      emit_condition(out, condition->desc.combinator.secondCondition);
      break;
    case SAC_NEGATIVE_CONDITION:
      fprintf(out, "not(");
      emit_selector(out, condition->desc.selector);
      fprintf(out, ")");
      break;
    case SAC_OR_CONDITION:
    case SAC_POSITIONAL_CONDITION:
    case SAC_LANG_CONDITION:
    case SAC_ONLY_CHILD_CONDITION:
    case SAC_ONLY_TYPE_CONDITION:
    case SAC_CONTENT_CONDITION:
      fprintf(out, "?");
      break;
  }
}



static void emit_selector(FILE *out, const SAC_Selector *selector) {
  switch (selector->selectorType) {
    case SAC_CONDITIONAL_SELECTOR:
      emit_selector(out, selector->desc.conditional.simpleSelector);
      emit_condition(out, selector->desc.conditional.condition);
      break;
    case SAC_ANY_NODE_SELECTOR:
      fprintf(out, "*");
      break;
    case SAC_ELEMENT_NODE_SELECTOR:
      emit_name(out,
        selector->desc.element.namespaceURI,
        selector->desc.element.localName);
      break;
    case SAC_DESCENDANT_SELECTOR:
    case SAC_CHILD_SELECTOR:
      emit_selector(out, selector->desc.descendant.descendantSelector);
      switch (selector->selectorType) {
        case SAC_DESCENDANT_SELECTOR:
          fprintf(out, " ");
          break;
        case SAC_CHILD_SELECTOR:
          fprintf(out, " + ");
          break;
        default:
          fprintf(out, " ? ");
          break;
      }
      emit_selector(out, selector->desc.descendant.simpleSelector);
      break;
    case SAC_DIRECT_ADJACENT_SELECTOR:
      emit_selector(out, selector->desc.sibling.firstSelector);
      fprintf(out, " > ");
      emit_selector(out, selector->desc.sibling.secondSelector);
      break;
    case SAC_GENERAL_ADJACENT_SELECTOR:
      emit_selector(out, selector->desc.sibling.firstSelector);
      fprintf(out, " ~ ");
      emit_selector(out, selector->desc.sibling.secondSelector);
      break;
    case SAC_TEXT_NODE_SELECTOR:
    case SAC_CDATA_SECTION_NODE_SELECTOR:
    case SAC_PROCESSING_INSTRUCTION_NODE_SELECTOR:
    case SAC_COMMENT_NODE_SELECTOR:
      fprintf(out, "?");
      break;
  }
}



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



void CSSOM_CSSEmitter_selectors(FILE *out, const SAC_Selector *selectors[]) {
  const SAC_Selector **it;

  it = selectors;
  if (*it != NULL) {
    emit_selector(out, *it);
    while (*(++it) != NULL) {
      fprintf(out, ", ");
      emit_selector(out, *it);
    }
  }
}
