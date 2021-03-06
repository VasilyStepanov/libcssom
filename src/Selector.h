#ifndef _CSSOM_SELECTOR_H
#define _CSSOM_SELECTOR_H

#include <cssom/Selector.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_Selector* CSSOM_Selector__alloc(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const SAC_Selector *selectors[]);

CSSOM_Selector* CSSOM_PageSelector__alloc(const CSSOM *cssom,
  CSSOM_CSSPageRule *parentRule, const SAC_Selector *selectors[]);

const SAC_Selector** CSSOM_Selector__selectors(const CSSOM_Selector *selector);

void CSSOM_Selector__keepParser(CSSOM_Selector *selector,
  SAC_Parser parser);

void CSSOM_Selector__setParentRule(CSSOM_Selector *selector,
  CSSOM_CSSRule *parentRule);



#ifdef __cplusplus
}
#endif

#endif
