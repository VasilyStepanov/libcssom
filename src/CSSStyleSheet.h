#ifndef _CSSOM_CSSSTYLESHEET_H
#define _CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(const CSSOM *cssom,
  CSSOM_CSSRule *ownerRule);

const CSSOM* CSSOM_CSSStyleSheet__cssom(const CSSOM_CSSStyleSheet *styleSheet);

void CSSOM_CSSStyleSheet__keepParser(CSSOM_CSSStyleSheet *styleSheet,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif
