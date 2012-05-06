#ifndef _CSSOM_CSS_PAGE_RULE_H
#define _CSSOM_CSS_PAGE_RULE_H

#include <cssom/CSSPageRule.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPageRule* CSSOM_CSSPageRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_Selector *selectors[]);



#ifdef __cplusplus
}
#endif

#endif
