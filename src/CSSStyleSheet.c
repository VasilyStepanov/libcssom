#include "CSSStyleSheet.h"

#include "CSSMediaRule.h"
#include "CSSOM.h"
#include "CSSPageRule.h"
#include "CSSRuleList.h"
#include "CSSStyleRule.h"
#include "Sequence.h"
#include "memory.h"

#include <sacc.h>

#include <assert.h>



struct _CSSOM_CSSStyleSheet {
  size_t handles;
  const CSSOM *cssom;
  SAC_Parser parser;
  CSSOM_CSSRuleList *cssRules;
};



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(const CSSOM *cssom,
  SAC_Parser parser)
{
  CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  cssRules = CSSOM_CSSRuleList__alloc();
  if (cssRules == NULL) return NULL;

  styleSheet = (CSSOM_CSSStyleSheet*)CSSOM_malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    CSSOM_Sequence__free(cssRules);
    return NULL;
  }

  styleSheet->handles = 1;
  styleSheet->cssom = cssom;
  styleSheet->parser = parser;
  styleSheet->cssRules = cssRules;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_acquire(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  ++styleSheet->handles;
}



void CSSOM_CSSStyleSheet_release(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  assert(styleSheet->handles > 0);
  --styleSheet->handles;
  if (styleSheet->handles > 0) return;

  CSSOM_Sequence__free(styleSheet->cssRules);
  SAC_DisposeParser(styleSheet->parser);
  CSSOM_free(styleSheet);
}



const CSSOM* CSSOM_CSSStyleSheet__cssom(const CSSOM_CSSStyleSheet *styleSheet) {
  return styleSheet->cssom;
}



CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->cssRules;
}



CSSOM_CSSPageRule* CSSOM_CSSStyleSheet__appendCSSPageRule(
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;

  cssRule = CSSOM_CSSPageRule__alloc(styleSheet,
    CSSOM__table(styleSheet->cssom), selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(styleSheet->cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSMediaRule* CSSOM_CSSStyleSheet__appendCSSMediaRule(
  CSSOM_CSSStyleSheet *styleSheet)
{
  CSSOM_CSSMediaRule *cssRule;

  cssRule = CSSOM_CSSMediaRule__alloc(styleSheet);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(styleSheet->cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleRule* CSSOM_CSSStyleSheet__appendCSSStyleRule(
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;

  cssRule = CSSOM_CSSStyleRule__alloc(styleSheet,
    CSSOM__table(styleSheet->cssom), selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(styleSheet->cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule__free((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}

