#include "CSSStyleSheet.h"

#include "CSSMediaRule.h"
#include "CSSOM.h"
#include "CSSPageRule.h"
#include "CSSRuleList.h"
#include "CSSStyleRule.h"
#include "Sequence.h"
#include "memory.h"

#include <sacc.h>

#include <string.h>
#include <assert.h>



struct _CSSOM_CSSStyleSheet {
  size_t handles;
  const CSSOM *cssom;
  SAC_Parser parser;
  CSSOM_CSSRule *ownerRule;
  CSSOM_CSSRuleList *cssRules;
};



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(const CSSOM *cssom,
  SAC_Parser parser, CSSOM_CSSRule *ownerRule)
{
  CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  cssRules = CSSOM_CSSRuleList__alloc();
  if (cssRules == NULL) return NULL;

  styleSheet = (CSSOM_CSSStyleSheet*)CSSOM_malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    CSSOM_Sequence_release(cssRules);
    return NULL;
  }

  styleSheet->handles = 1;
  styleSheet->cssom = cssom;
  styleSheet->parser = parser;
  styleSheet->ownerRule = ownerRule;
  styleSheet->cssRules = cssRules;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_acquire(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  ++styleSheet->handles;
  CSSOM_CSSRule_acquire(styleSheet->ownerRule);
}



void CSSOM_CSSStyleSheet_release(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  assert(styleSheet->handles > 0);
  --styleSheet->handles;
  if (styleSheet->handles > 0) {
    CSSOM_CSSRule_release(styleSheet->ownerRule);
    return;
  }

  CSSOM_Sequence_release(styleSheet->cssRules);
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



unsigned long CSSOM_CSSStyleSheet_insertRule(CSSOM_CSSStyleSheet *styleSheet,
  const char * rule, unsigned long index)
{
  CSSOM_CSSRule *newCSSRule;
  size_t size;

  size = CSSOM_Sequence_size(styleSheet->cssRules);

  if (index > size) {
    CSSOM__indexSizeErr(styleSheet->cssom);
    return (unsigned long)-1;
  }

  newCSSRule = CSSOM__parseCSSRule(styleSheet->cssom,
    styleSheet, rule, strlen(rule));
  if (newCSSRule == NULL) return (unsigned long)-1;

  if (!CSSOM_CSSRuleList__testHierarchy(styleSheet->cssRules,
    index, newCSSRule))
  {
    CSSOM_CSSRule_release(newCSSRule);
    CSSOM__hierarchyRequestErr(styleSheet->cssom);
    return (unsigned long)-1;
  }

  if (index != size) {
    if (CSSOM_Sequence__insert(styleSheet->cssRules,
      index, newCSSRule) == NULL)
    {
      CSSOM_CSSRule_release(newCSSRule);
      return (unsigned long)-1;
    }
  } else {
    if (CSSOM_Sequence__append(styleSheet->cssRules, newCSSRule) == NULL) {
      CSSOM_CSSRule_release(newCSSRule);
      return (unsigned long)-1;
    }
  }

  return index;
}



void CSSOM_CSSStyleSheet_deleteRule(CSSOM_CSSStyleSheet *styleSheet,
  unsigned long index)
{
  CSSOM_CSSRule *at;

  if (index >= CSSOM_Sequence_size(styleSheet->cssRules)) {
    CSSOM__indexSizeErr(styleSheet->cssom);
    return;
  }

  at = CSSOM_CSSRuleList_at(styleSheet->cssRules, index);
  CSSOM_CSSRule_release(at);
  CSSOM_Sequence__remove(styleSheet->cssRules, index);
}



CSSOM_CSSRule* CSSOM_CSSStyleSheet_ownerRule(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->ownerRule;
}
