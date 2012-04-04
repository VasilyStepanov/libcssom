#include "CSSEmitter.h"

#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"



static int emit_selector(FILE *out, const SAC_Selector *selector);



static int emit_name(FILE *out,
  const char *namespaceURI, const char *localName)
{
  if (namespaceURI != NULL && localName != NULL) {
    if (fprintf(out, "%s|%s", namespaceURI, localName) < 0) return 1;
  } else if (namespaceURI != NULL) {
    if (fprintf(out, "%s|*", namespaceURI) < 0) return 1;
  } else if (localName != NULL) {
    if (fprintf(out, "%s", localName) < 0) return 1;
  } else {
    if (fprintf(out, "*") < 0) return 1;
  }
  return 0;
}



static int emit_condition(FILE *out, const SAC_Condition *condition) {
  switch (condition->conditionType) {
    case SAC_ONE_OF_ATTRIBUTE_CONDITION:
    case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
    case SAC_PREFIX_ATTRIBUTE_CONDITION:
    case SAC_SUFFIX_ATTRIBUTE_CONDITION:
    case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
    case SAC_ATTRIBUTE_CONDITION:
    case SAC_CLASS_CONDITION:
    case SAC_ID_CONDITION:
      if (fprintf(out, "[")) return 1;
      if (emit_name(out,
        condition->desc.attribute.namespaceURI,
        condition->desc.attribute.localName) != 0)
      {
        return 1;
      }

      switch (condition->conditionType) {
        case SAC_ID_CONDITION:
          if (fprintf(out, "\"id\"")) return 1;
          break;
        case SAC_CLASS_CONDITION:
          if (fprintf(out, "\"class\"")) return 1;
          break;
        case SAC_PREFIX_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"prefix\"")) return 1;
          break;
        case SAC_SUFFIX_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"suffix\"")) return 1;
          break;
        case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"substr\"")) return 1;
          break;
        case SAC_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"attr\"")) return 1;
          break;
        case SAC_ONE_OF_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"one_of\"")) return 1;
          break;
        case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"begin_hypen\"")) return 1;
          break;
        default:
          if (fprintf(out, "\"unknown_%d\"", condition->conditionType))
            return 1;
          break;
      }

      if (condition->desc.attribute.value != NULL) {
        if (fprintf(out, "=\"%s\"", condition->desc.attribute.value)) return 1;
      }

      if (fprintf(out, "]")) return 1;

      break;
    case SAC_PSEUDO_CLASS_CONDITION:
    case SAC_PSEUDO_ELEMENT_CONDITION:
      {
        switch (condition->conditionType) {
          case SAC_PSEUDO_CLASS_CONDITION:
            if (fprintf(out, ":")) return 1;
            break;
          case SAC_PSEUDO_ELEMENT_CONDITION:
            if (fprintf(out, "::")) return 1;
            break;
          default:
            if (fprintf(out, "?")) return 1;
            break;
        }
        if (CSSOM_CSSEmitter_lexicalUnit(out, condition->desc.pseudo) != 0)
          return 1;
      }
      break;
    case SAC_AND_CONDITION:
      if (emit_condition(out, condition->desc.combinator.firstCondition))
        return 1;
      if (emit_condition(out, condition->desc.combinator.secondCondition))
        return 1;
      break;
    case SAC_NEGATIVE_CONDITION:
      if (fprintf(out, "not(")) return 1;
      if (emit_selector(out, condition->desc.selector)) return 1;
      if (fprintf(out, ")")) return 1;
      break;
    case SAC_OR_CONDITION:
    case SAC_POSITIONAL_CONDITION:
    case SAC_LANG_CONDITION:
    case SAC_ONLY_CHILD_CONDITION:
    case SAC_ONLY_TYPE_CONDITION:
    case SAC_CONTENT_CONDITION:
      if (fprintf(out, "?")) return 1;
      break;
  }
  return 0;
}



static int emit_selector(FILE *out, const SAC_Selector *selector) {
  switch (selector->selectorType) {
    case SAC_CONDITIONAL_SELECTOR:
      if (emit_selector(out, selector->desc.conditional.simpleSelector) != 0)
        return 1;
      if (emit_condition(out, selector->desc.conditional.condition) != 0)
        return 1;
      break;
    case SAC_ANY_NODE_SELECTOR:
      if (fprintf(out, "*") < 0) return 1;
      break;
    case SAC_ELEMENT_NODE_SELECTOR:
      if (emit_name(out,
        selector->desc.element.namespaceURI,
        selector->desc.element.localName) != 0)
      {
        return 1;
      }
      break;
    case SAC_DESCENDANT_SELECTOR:
    case SAC_CHILD_SELECTOR:
      if (emit_selector(out, selector->desc.descendant.descendantSelector) != 0)
        return 1;
      switch (selector->selectorType) {
        case SAC_DESCENDANT_SELECTOR:
          if (fprintf(out, " ") < 0) return 1;
          break;
        case SAC_CHILD_SELECTOR:
          if (fprintf(out, " + ") < 0) return 1;
          break;
        default:
          if (fprintf(out, " ? ") < 0) return 1;
          break;
      }
      if (emit_selector(out, selector->desc.descendant.simpleSelector) != 0)
        return 1;
      break;
    case SAC_DIRECT_ADJACENT_SELECTOR:
      if (emit_selector(out, selector->desc.sibling.firstSelector) != 0)
        return 1;
      if (fprintf(out, " > ") < 0) return 1;
      if (emit_selector(out, selector->desc.sibling.secondSelector) != 0)
        return 1;
      break;
    case SAC_GENERAL_ADJACENT_SELECTOR:
      if (emit_selector(out, selector->desc.sibling.firstSelector) != 0)
        return 1;
      if (fprintf(out, " ~ ") < 0) return 1;
      if (emit_selector(out, selector->desc.sibling.secondSelector) != 0)
        return 1;
      break;
    case SAC_TEXT_NODE_SELECTOR:
    case SAC_CDATA_SECTION_NODE_SELECTOR:
    case SAC_PROCESSING_INSTRUCTION_NODE_SELECTOR:
    case SAC_COMMENT_NODE_SELECTOR:
      if (fprintf(out, "?") < 0) return 1;
      break;
  }
  return 0;
}



int CSSOM_CSSEmitter_lexicalUnit(FILE *out, const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_OPERATOR_PLUS:
      if (fprintf(out, "+") < 0) return 1;
      break;
    case SAC_OPERATOR_MINUS:
      if (fprintf(out, "-") < 0) return 1;
      break;
    case SAC_OPERATOR_COMMA:
      if (fprintf(out, ",") < 0) return 1;
      break;
    case SAC_OPERATOR_SLASH:
      if (fprintf(out, "/") < 0) return 1;
      break;
    case SAC_INHERIT:
      if (fprintf(out, "inherit") < 0) return 1;
      break;
    case SAC_INTEGER:
      if (fprintf(out, "%li", value->desc.integer) < 0) return 1;
      break;
    case SAC_REAL:
      if (fprintf(out, "%g", value->desc.real) < 0) return 1;
      break;
    case SAC_LENGTH_EM:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
          return 1;
      }
      break;
    case SAC_LENGTH_EX:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_PIXEL:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_INCH:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_CENTIMETER:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_MILLIMETER:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_POINT:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_PICA:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_PERCENTAGE:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DEGREE:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_GRADIAN:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_RADIAN:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_MILLISECOND:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_SECOND:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_HERTZ:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_KILOHERTZ:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DOTS_PER_INCH:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DOTS_PER_CENTIMETER:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_URI:
      if (fprintf(out, "url(\"%s\")", value->desc.uri) < 0) return 1;
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

        if (fprintf(out, "%s(", value->desc.function.name) < 0) return 1;

        arg = value->desc.function.parameters;
        if (*arg != NULL) {
          if (CSSOM_CSSEmitter_lexicalUnit(out, *arg) != 0) return 1;
          while (*(++arg) != NULL) {
            if (fprintf(out, " ") < 0) return 1;
            if (CSSOM_CSSEmitter_lexicalUnit(out, *arg) != 0) return 1;
          }
        }
      }
      break;
    case SAC_IDENT:
      if (fprintf(out, "%s", value->desc.ident) < 0) return 1;
      break;
    case SAC_STRING_VALUE:
      if (fprintf(out, "\"%s\"", value->desc.stringValue) < 0) return 1;
      break;
    case SAC_UNICODERANGE:
      if (fprintf(out, "%s", value->desc.unicodeRange) < 0) return 1;
      break;
    case SAC_SUB_EXPRESSION:
      {
        SAC_LexicalUnit **sub;

        sub = value->desc.function.parameters;
        if (*sub != NULL) {
          if (CSSOM_CSSEmitter_lexicalUnit(out, *sub) != 0) return 1;
          while (*(++sub) != NULL) {
            if (fprintf(out, " ") < 0) return 1;
            if (CSSOM_CSSEmitter_lexicalUnit(out, *sub) != 0) return 1;
          }
        }
      }
      break;
    case SAC_DIMENSION:
      if (fprintf(out, "%g %s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit))
      {
        return 1;
      }
      break;
    case SAC_OPERATOR_MULTIPLY:
      if (fprintf(out, "*") < 0) return 1;
      break;
    case SAC_OPERATOR_MOD:
      if (fprintf(out, "|") < 0) return 1;
      break;
    case SAC_OPERATOR_EXP:
      if (fprintf(out, "E") < 0) return 1;
      break;
    case SAC_OPERATOR_LT:
      if (fprintf(out, "<") < 0) return 1;
      break;
    case SAC_OPERATOR_GT:
      if (fprintf(out, ">") < 0) return 1;
      break;
    case SAC_OPERATOR_LE:
      if (fprintf(out, "<=") < 0) return 1;
      break;
    case SAC_OPERATOR_GE:
      if (fprintf(out, ">=") < 0) return 1;
      break;
    case SAC_OPERATOR_TILDE:
      if (fprintf(out, "~") < 0) return 1;
      break;
  };
  return 0;
}



int CSSOM_CSSEmitter_cssProperty(FILE *out, const CSSOM_CSSProperty *property) {
  if (!CSSOM_CSSProperty_important(property)) {
    if (fprintf(out, "%s : %s;",
      CSSOM_CSSProperty_name(property),
      CSSOM_CSSProperty_cssText(property)) < 0)
    {
        return 1;
    }
  } else {
    if (fprintf(out, "%s : %s !important;",
      CSSOM_CSSProperty_name(property),
      CSSOM_CSSProperty_cssText(property)) < 0)
    {
        return 1;
    }
  }
  return 0;
}



int CSSOM_CSSEmitter_selectors(FILE *out, const SAC_Selector *selectors[]) {
  const SAC_Selector **it;

  it = selectors;
  if (*it != NULL) {
    if (emit_selector(out, *it) != 0) return 1;
    while (*(++it) != NULL) {
      if (fprintf(out, ", ") < 0) return 1;
      if (emit_selector(out, *it) != 0) return 1;
    }
  }
  return 0;
}



int CSSOM_CSSEmitter_cssStyleDeclaration(FILE *out,
  const CSSOM_CSSStyleDeclaration *style)
{
  CSSOM_CSSStyleDeclarationConstIter it;

  it = CSSOM_CSSStyleDeclaration__cbegin(style);
  if (it == CSSOM_CSSStyleDeclaration__cend(style)) return 0;

  if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;

  for (
    it = CSSOM_CSSStyleDeclarationConstIter_next(it);
    it != CSSOM_CSSStyleDeclaration__cend(style);
    it = CSSOM_CSSStyleDeclarationConstIter_next(it))
  {
    if (fprintf(out, " ") < 0) return 1;
    if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;
  }

  return 0;
}



int CSSOM_CSSEmitter_cssStyleRule(FILE *out,
  const CSSOM_CSSStyleRule *cssRule)
{
  if (CSSOM_CSSEmitter_selectors(out, CSSOM_CSSStyleRule__selectors(cssRule)))
    return 1;
  if (fprintf(out, " { ") < 0) return 1;
  if (CSSOM_CSSEmitter_cssStyleDeclaration(out,
    CSSOM_CSSStyleRule_style(cssRule)))
  {
    return 1;
  }
  if (fprintf(out, " }") < 0) return 1;
  return 0;
}
