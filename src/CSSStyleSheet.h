#ifndef _CSSOM_CSSSTYLESHEET_H
#define _CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(SAC_Parser parser);

void CSSOM_CSSStyleSheet__acquire(CSSOM_CSSStyleSheet *styleSheet);

void CSSOM_CSSStyleSheet__release(CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSRule* CSSOM_CSSStyleSheet__append(CSSOM_CSSStyleSheet *styleSheet,
  CSSOM_CSSRule *cssRule);



#endif
