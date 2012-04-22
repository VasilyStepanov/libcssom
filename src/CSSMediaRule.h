#ifndef _CSSOM_CSS_MEDIA_RULE_H
#define _CSSOM_CSS_MEDIA_RULE_H

#include <cssom/CSSMediaRule.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSMediaRule* CSSOM_CSSMediaRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_MediaQuery *media[]);



#ifdef __cplusplus
}
#endif

#endif
