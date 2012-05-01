#include "CSSEmitter.h"

#include "CSSPageRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleRule.h"
#include "MediaList.h"
#include "gcc.h"

#include <cssom/CSSFontFaceRule.h>
#include <cssom/CSSImportRule.h>
#include <cssom/CSSMediaRule.h>
#include <cssom/CSSNamespaceRule.h>
#include <cssom/CSSRuleList.h>

#include <stdio.h>



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
      if (fprintf(out, "[") < 0) return 1;
      if (emit_name(out,
        condition->desc.attribute.namespaceURI,
        condition->desc.attribute.localName) != 0)
      {
        return 1;
      }

      switch (condition->conditionType) {
        case SAC_ID_CONDITION:
          if (fprintf(out, "\"id\"") < 0) return 1;
          break;
        case SAC_CLASS_CONDITION:
          if (fprintf(out, "\"class\"") < 0) return 1;
          break;
        case SAC_PREFIX_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"prefix\"") < 0) return 1;
          break;
        case SAC_SUFFIX_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"suffix\"") < 0) return 1;
          break;
        case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"substr\"") < 0) return 1;
          break;
        case SAC_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"attr\"") < 0) return 1;
          break;
        case SAC_ONE_OF_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"one_of\"") < 0) return 1;
          break;
        case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
          if (fprintf(out, "\"begin_hypen\"") < 0) return 1;
          break;
        default:
          if (fprintf(out, "\"unknown_%d\"", condition->conditionType) < 0)
            return 1;
          break;
      }

      if (condition->desc.attribute.value != NULL) {
        if (fprintf(out, "=\"%s\"", condition->desc.attribute.value) < 0) {
          return 1;
        }
      }

      if (fprintf(out, "]") < 0) return 1;

      break;
    case SAC_PSEUDO_CLASS_CONDITION:
    case SAC_PSEUDO_ELEMENT_CONDITION:
      {
        switch (condition->conditionType) {
          case SAC_PSEUDO_CLASS_CONDITION:
            if (fprintf(out, ":") < 0) return 1;
            break;
          case SAC_PSEUDO_ELEMENT_CONDITION:
            if (fprintf(out, "::") < 0) return 1;
            break;
          default:
            if (fprintf(out, "?") < 0) return 1;
            break;
        }
        if (CSSOM_CSSEmitter_lexicalUnit(out, condition->desc.pseudo) != 0)
          return 1;
      }
      break;
    case SAC_AND_CONDITION:
      if (emit_condition(out, condition->desc.combinator.firstCondition) != 0)
        return 1;
      if (emit_condition(out, condition->desc.combinator.secondCondition) != 0)
        return 1;
      break;
    case SAC_NEGATIVE_CONDITION:
      if (fprintf(out, "not(") < 0) return 1;
      if (emit_selector(out, condition->desc.selector) != 0) return 1;
      if (fprintf(out, ")") < 0) return 1;
      break;
    case SAC_OR_CONDITION:
    case SAC_POSITIONAL_CONDITION:
    case SAC_LANG_CONDITION:
    case SAC_ONLY_CHILD_CONDITION:
    case SAC_ONLY_TYPE_CONDITION:
    case SAC_CONTENT_CONDITION:
      if (fprintf(out, "?") < 0) return 1;
      break;
  }
  return 0;
}



static int emit_selector(FILE *out, const SAC_Selector *selector) {
  switch (selector->selectorType) {
    case SAC_CONDITIONAL_SELECTOR:
      if (selector->desc.conditional.simpleSelector->selectorType !=
        SAC_ANY_NODE_SELECTOR)
      {
        if (emit_selector(out,
          selector->desc.conditional.simpleSelector) != 0)
        {
          return 1;
        }
      }
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
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
          return 1;
      }
      break;
    case SAC_LENGTH_EX:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_PIXEL:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_INCH:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_CENTIMETER:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_MILLIMETER:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_POINT:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_LENGTH_PICA:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_PERCENTAGE:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DEGREE:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_GRADIAN:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_RADIAN:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.sreal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_MILLISECOND:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_SECOND:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_HERTZ:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_KILOHERTZ:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DOTS_PER_INCH:
      if (fprintf(out, "%g%s",
        value->desc.dimension.value.ureal, value->desc.dimension.unit) < 0)
      {
        return 1;
      }
      break;
    case SAC_DOTS_PER_CENTIMETER:
      if (fprintf(out, "%g%s",
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



static int anyNodeSelector(const SAC_Selector *selectors[]) {
  return selectors[0] != NULL
    && selectors[1] == NULL
    && selectors[0]->selectorType == SAC_ANY_NODE_SELECTOR;
}



int CSSOM_CSSEmitter_pageSelectors(FILE *out, const SAC_Selector *selectors[]) {
  const SAC_Selector **it;

  if (anyNodeSelector(selectors)) return 0;

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



static int emit_media_query(FILE *out, const SAC_MediaQuery *mediaQuery) {
  switch (mediaQuery->mediaQueryType) {
    case SAC_TYPE_MEDIA_QUERY:
      if (fprintf(out, "%s", mediaQuery->desc.type) < 0) return 1;
      break;
    case SAC_FEATURE_MEDIA_QUERY:
      if (fprintf(out, "(%s: ", mediaQuery->desc.feature.name) < 0) return 1;
      if (CSSOM_CSSEmitter_lexicalUnit(out,
        mediaQuery->desc.feature.value) != 0)
      {
        return 1;
      }
      if (fprintf(out, ")") < 0) return 1;
      break;
    case SAC_AND_MEDIA_QUERY:
      if (emit_media_query(out, mediaQuery->desc.combinator.firstQuery) != 0)
        return 1;
      if (fprintf(out, " and ") < 0) return 1;
      if (emit_media_query(out, mediaQuery->desc.combinator.secondQuery) != 0)
        return 1;
      break;
    case SAC_ONLY_MEDIA_QUERY:
      if (fprintf(out, "only ") < 0) return 1;
      if (emit_media_query(out, mediaQuery->desc.subQuery) != 0) return 1;
      break;
    case SAC_NOT_MEDIA_QUERY:
      if (fprintf(out, "not ") < 0) return 1;
      if (emit_media_query(out, mediaQuery->desc.subQuery) != 0) return 1;
      break;
  }

  return 0;
}



int CSSOM_CSSEmitter_query(FILE *out, const CSSOM_MediaQuery *query) {
  const SAC_MediaQuery *mediaQuery;

  mediaQuery = CSSOM_MediaQuery_query(query);

  if (emit_media_query(out, mediaQuery) != 0) return 1;

  return 0;
}



int CSSOM_CSSEmitter_media(FILE *out, const CSSOM_MediaList *media) {
  unsigned long length;
  unsigned long i;

  length = CSSOM_MediaList_length(media);

  if (length > 0) {
    if (CSSOM_CSSEmitter_query(out, CSSOM_MediaList__at(media, 0)) != 0)
      return 1;

    for (i = 1; i < length; ++i) {
      if (fprintf(out, ", ") < 0) return 1;

      if (CSSOM_CSSEmitter_query(out, CSSOM_MediaList__at(media, i)) != 0)
        return 1;
    }
  }

  return 0;
}



int CSSOM_CSSEmitter_cssStyleDeclaration(FILE *out,
  const CSSOM_CSSStyleDeclaration *style)
{
  const CSSOM_CSSStyleDeclarationValue *values;
  CSSOM_CSSStyleDeclarationValueConstIter it;

  values = CSSOM_CSSStyleDeclaration_values(style);

  it = CSSOM_CSSStyleDeclarationValue__cbegin(values);
  if (it == CSSOM_CSSStyleDeclarationValue__cend(values)) return 0;

  if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;

  for (
    it = CSSOM_CSSStyleDeclarationValueConstIter_next(it);
    it != CSSOM_CSSStyleDeclarationValue__cend(values);
    it = CSSOM_CSSStyleDeclarationValueConstIter_next(it))
  {
    if (fprintf(out, " ") < 0) return 1;
    if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;
  }

  return 0;
}



int CSSOM_CSSEmitter_cssRule(FILE *out, const CSSOM_CSSRule *cssRule) {
  unsigned short type = CSSOM_CSSRule_type(cssRule);

  if (type == CSSOM_CSSRule_STYLE_RULE) {
    if (CSSOM_CSSEmitter_cssStyleRule(out, (CSSOM_CSSStyleRule*)cssRule) != 0) {
      return 1;
    }
  } else if (type == CSSOM_CSSRule_FONT_FACE_RULE) {
    if (CSSOM_CSSEmitter_cssFontFaceRule(out,
      (CSSOM_CSSFontFaceRule*)cssRule) != 0)
    {
      return 1;
    }
  } else if (type == CSSOM_CSSRule_IMPORT_RULE) {
    if (CSSOM_CSSEmitter_cssImportRule(out,
      (CSSOM_CSSImportRule*)cssRule) != 0)
    {
      return 1;
    }
  } else if (type == CSSOM_CSSRule_MEDIA_RULE) {
    if (CSSOM_CSSEmitter_cssMediaRule(out, (CSSOM_CSSMediaRule*)cssRule) != 0) {
      return 1;
    }
  } else if (type == CSSOM_CSSRule_NAMESPACE_RULE) {
    if (CSSOM_CSSEmitter_cssNamespaceRule(out,
      (CSSOM_CSSNamespaceRule*)cssRule) != 0)
    {
      return 1;
    }
  } else if (type == CSSOM_CSSRule_PAGE_RULE) {
    if (CSSOM_CSSEmitter_cssPageRule(out, (CSSOM_CSSPageRule*)cssRule) != 0) {
      return 1;
    }
  }

  return 0;
}



int CSSOM_CSSEmitter_cssRules(FILE *out, const CSSOM_CSSRuleList *cssRules) {
  size_t size;
  size_t i;

  size = CSSOM_CSSRuleList_length(cssRules);
  if (size != 0) {
    CSSOM_CSSRule *cssRule;

    cssRule = CSSOM_CSSRuleList_at(cssRules, 0);
    CSSOM_CSSEmitter_cssRule(out, cssRule);

    for (i = 1; i < size; ++i) {
      if (fprintf(out, " ") < 0) return 1;

      cssRule = CSSOM_CSSRuleList_at(cssRules, i);
      CSSOM_CSSEmitter_cssRule(out, cssRule);
    }
  }

  return 0;
}



int CSSOM_CSSEmitter_cssFontFaceRule(FILE *out,
  const CSSOM_CSSFontFaceRule *cssRule)
{
  if (fprintf(out, "@font-face { ") < 0) return 1;
  if (CSSOM_CSSEmitter_cssStyleDeclaration(out,
    CSSOM_CSSFontFaceRule_style(cssRule)) != 0)
  {
    return 1;
  }
  if (fprintf(out, " }") < 0) return 1;
  return 0;
}



int CSSOM_CSSEmitter_cssImportRule(FILE *out,
  const CSSOM_CSSImportRule *cssRule)
{
  if (fprintf(out, "@import url('%s')",
    CSSOM_CSSImportRule_href(cssRule)) < 0)
  {
    return 1;
  }
  if (CSSOM_MediaList_length(CSSOM_CSSImportRule_media(cssRule)) > 0) {
    if (fprintf(out, " ") < 0) return 1;
    if (CSSOM_CSSEmitter_media(out, CSSOM_CSSImportRule_media(cssRule)) != 0)
      return 1;
  }
  if (fprintf(out, ";") < 0)
    return 1;
  return 0;
}



int CSSOM_CSSEmitter_cssMediaRule(FILE *out,
  const CSSOM_CSSMediaRule *cssRule)
{
  if (fprintf(out, "@media") < 0) return 1;
  if (CSSOM_MediaList_length(CSSOM_CSSMediaRule_media(cssRule)) > 0) {
    if (fprintf(out, " ") < 0) return 1;
    if (CSSOM_CSSEmitter_media(out, CSSOM_CSSMediaRule_media(cssRule)) != 0)
      return 1;
  }
  if (fprintf(out, " { ") < 0) return 1;
  if (CSSOM_CSSEmitter_cssRules(out, CSSOM_CSSMediaRule_cssRules(cssRule)) != 0)
    return 1;
  if (fprintf(out, " }") < 0) return 1;
  return 0;
}



int CSSOM_CSSEmitter_cssNamespaceRule(FILE *out,
  const CSSOM_CSSNamespaceRule *cssRule)
{
  const char *prefix;
  const char *uri;

  prefix = CSSOM_CSSNamespaceRule_prefix(cssRule);
  uri = CSSOM_CSSNamespaceRule_namespaceURI(cssRule);

  if (prefix != NULL) {
    if (fprintf(out, "@namespace %s url('%s');", prefix, uri) < 0) return 1;
  } else {
    if (fprintf(out, "@namespace url('%s');", uri) < 0) return 1;
  }
  return 0;
}



int CSSOM_CSSEmitter_cssPageRule(FILE *out, const CSSOM_CSSPageRule *cssRule) {
  const SAC_Selector **selectors;

  selectors = CSSOM_Selector_selectors(CSSOM_CSSPageRule__selector(cssRule));

  if (anyNodeSelector(selectors)) {
    if (fprintf(out, "@page") < 0) return 1;
  } else {
    if (fprintf(out, "@page ") < 0) return 1;
  }
  if (CSSOM_CSSEmitter_pageSelectors(out, selectors) != 0) return 1;
  if (fprintf(out, " { ") < 0) return 1;
  if (CSSOM_CSSEmitter_cssStyleDeclaration(out,
    CSSOM_CSSPageRule_style(cssRule)) != 0)
  {
    return 1;
  }
  if (fprintf(out, " }") < 0) return 1;
  return 0;
}



int CSSOM_CSSEmitter_cssStyleRule(FILE *out,
  const CSSOM_CSSStyleRule *cssRule)
{
  if (CSSOM_CSSEmitter_selectors(out, CSSOM_Selector_selectors(
    CSSOM_CSSStyleRule__selector(cssRule))) != 0)
  {
    return 1;
  }
  if (fprintf(out, " { ") < 0) return 1;
  if (CSSOM_CSSEmitter_cssStyleDeclaration(out,
    CSSOM_CSSStyleRule_style(cssRule)) != 0)
  {
    return 1;
  }
  if (fprintf(out, " }") < 0) return 1;
  return 0;
}
