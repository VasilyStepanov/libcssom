#include "CSSRuleList.h"

#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"



CSSOM_CSSPageRule* CSSOM_CSSRuleList__appendCSSPageRule(
  CSSOM_CSSRuleList *cssRules,
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[])
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



CSSOM_CSSMediaRule* CSSOM_CSSRuleList__appendCSSMediaRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet)
{
  CSSOM_CSSMediaRule *cssRule;

  cssRule = CSSOM_CSSMediaRule__alloc(styleSheet);
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
  CSSOM_CSSRuleList *cssRules,
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[])
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
