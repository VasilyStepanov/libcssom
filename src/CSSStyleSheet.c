#include "CSSStyleSheet.h"

#include "Deque_CSSRule.h"
#include "CSSRuleList.h"
#include "CSSRule.h"

#include <sacc.h>

#include <stdlib.h>
#include <assert.h>



struct _CSSOM_CSSStyleSheet {
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSRuleList *cssRules;
};



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(SAC_Parser parser) {
  CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  cssRules = CSSOM_CSSRuleList__alloc();
  if (cssRules == NULL) return NULL;

  styleSheet = (CSSOM_CSSStyleSheet*)malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    CSSOM_CSSRuleList__release(cssRules);
    return NULL;
  }

  styleSheet->handles = 1;
  styleSheet->parser = parser;
  styleSheet->cssRules = cssRules;

  return styleSheet;
}



void CSSOM_CSSStyleSheet__acquire(CSSOM_CSSStyleSheet *styleSheet) {
  ++styleSheet->handles;
}



void CSSOM_CSSStyleSheet__release(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  assert(styleSheet->handles > 0);
  --styleSheet->handles;
  if (styleSheet->handles > 0) return;

  CSSOM_CSSRuleList__release(styleSheet->cssRules);
  SAC_DisposeParser(styleSheet->parser);
  free(styleSheet);
}



void CSSOM_CSSStyleSheet_dispose(CSSOM_CSSStyleSheet *styleSheet) {
  CSSOM_CSSStyleSheet__release(styleSheet);
}



const CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->cssRules;
}



CSSOM_CSSRule* CSSOM_CSSStyleSheet__append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule)
{
  return CSSOM_CSSRuleList__append(styleSheet->cssRules, cssRule);
}

