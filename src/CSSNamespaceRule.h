#ifndef _CSSOM_CSS_NAMESPACE_RULE_H
#define _CSSOM_CSS_NAMESPACE_RULE_H

#include <cssom/CSSNamespaceRule.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSNamespaceRule* CSSOM_CSSNamespaceRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_STRING prefix, const SAC_STRING uri);



#ifdef __cplusplus
}
#endif

#endif
