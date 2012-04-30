#ifndef _CSSOM_CSS_PAGE_RULE_H
#define _CSSOM_CSS_PAGE_RULE_H

#include <cssom/CSSPageRule.h>

#include "Selector.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPageRule* CSSOM_CSSPageRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_Selector *selectors[]);

CSSOM_Selector* CSSOM_CSSPageRule__selector(const CSSOM_CSSPageRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
