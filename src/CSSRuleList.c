#include "CSSRuleList.h"

#include "CSSFontFaceRule.h"
#include "CSSMediaRule.h"
#include "CSSNamespaceRule.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"



CSSOM_CSSFontFaceRule* CSSOM_CSSRuleList__appendCSSFontFaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet)
{
  CSSOM_CSSFontFaceRule *cssRule;

  cssRule = CSSOM_CSSFontFaceRule__alloc(styleSheet);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSMediaRule* CSSOM_CSSRuleList__appendCSSMediaRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_MediaQuery *media[])
{
  CSSOM_CSSMediaRule *cssRule;

  cssRule = CSSOM_CSSMediaRule__alloc(styleSheet, media);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSNamespaceRule* CSSOM_CSSRuleList__appendCSSNamespaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  CSSOM_CSSNamespaceRule *cssRule;

  cssRule = CSSOM_CSSNamespaceRule__alloc(styleSheet, prefix, uri);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSPageRule* CSSOM_CSSRuleList__appendCSSPageRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;

  cssRule = CSSOM_CSSPageRule__alloc(styleSheet, selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleRule* CSSOM_CSSRuleList__appendCSSStyleRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;

  cssRule = CSSOM_CSSStyleRule__alloc(styleSheet, selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}
