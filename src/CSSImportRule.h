#ifndef _CSSOM_CSS_IMRPOT_RULE_H
#define _CSSOM_CSS_IMPORT_RULE_H

#include <cssom/CSSMediaRule.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSImportRule* CSSOM_CSSImportRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *mediaQuery[], const SAC_STRING defaultNamepaceURI);



#ifdef __cplusplus
}
#endif

#endif
