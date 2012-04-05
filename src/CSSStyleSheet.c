#include "CSSStyleSheet.h"

#include "CSSRuleList.h"
#include "Sequence.h"
#include "memory.h"

#include <cssom/CSSRule.h>

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



CSSOM_CSSRule* CSSOM_CSSStyleSheet__append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule)
{
  return CSSOM_Sequence__append(styleSheet->cssRules, cssRule);
}

