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
  CSSOM_Sequence__alloc((void(*)(void*))CSSOM_CSSRule__free)

CSSOM_CSSPageRule* CSSOM_CSSRuleList__appendCSSPageRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_Selector *selectors[]);

CSSOM_CSSMediaRule* CSSOM_CSSRuleList__appendCSSMediaRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_MediaQuery *media[]);

CSSOM_CSSNamespaceRule* CSSOM_CSSRuleList__appendCSSNamespaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_STRING prefix, const SAC_STRING uri);

CSSOM_CSSStyleRule* CSSOM_CSSRuleList__appendCSSStyleRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSStyleSheet *styleSheet,
  const SAC_Selector *selectors[]);



#ifdef __cplusplus
}
#endif

#endif
