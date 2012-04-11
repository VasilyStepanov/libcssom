#ifndef _CSSOM_CSSSTYLESHEET_H
#define _CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(const CSSOM *cssom,
  SAC_Parser parser);

CSSOM_CSSPageRule* CSSOM_CSSStyleSheet__appendCSSPageRule(
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[]);

CSSOM_CSSMediaRule* CSSOM_CSSStyleSheet__appendCSSMediaRule(
  CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSStyleRule* CSSOM_CSSStyleSheet__appendCSSStyleRule(
  CSSOM_CSSStyleSheet *styleSheet, const SAC_Selector *selectors[]);

const CSSOM* CSSOM_CSSStyleSheet__cssom(const CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
