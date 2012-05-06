#ifndef _CSSOM_CSSSTYLERULE_H
#define _CSSOM_CSSSTYLERULE_H

#include <cssom/CSSStyleRule.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_Selector *selectors[]);



#ifdef __cplusplus
}
#endif

#endif
