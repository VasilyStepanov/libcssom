#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include <cssom/CSSRuleList.h>

#include "CSSRule.h"
#include "Sequence.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSRuleList__alloc() \
  CSSOM_Sequence__alloc((void(*)(void*))CSSOM_CSSRule_release)

CSSOM_CSSFontFaceRule* CSSOM_CSSRuleList__appendCSSFontFaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet);

CSSOM_CSSImportRule* CSSOM_CSSRuleList__appendCSSImportRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_STRING base,
  const SAC_STRING uri, const SAC_MediaQuery *media[],
  const SAC_STRING defaultNamepaceURI);

CSSOM_CSSMediaRule* CSSOM_CSSRuleList__appendCSSMediaRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_MediaQuery *media[]);

CSSOM_CSSNamespaceRule* CSSOM_CSSRuleList__appendCSSNamespaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_STRING prefix,
  const SAC_STRING uri);

CSSOM_CSSPageRule* CSSOM_CSSRuleList__appendCSSPageRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_Selector *selectors[]);

CSSOM_CSSStyleRule* CSSOM_CSSRuleList__appendCSSStyleRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_Selector *selectors[]);

int CSSOM_CSSRuleList__testHierarchy(const CSSOM_CSSRuleList *cssRules,
  unsigned long index, CSSOM_CSSRule *cssRule);

void CSSOM_CSSRuleList__setParentRule(CSSOM_CSSRuleList *cssRules,
  CSSOM_CSSRule *parentRule);



#ifdef __cplusplus
}
#endif

#endif
