#ifndef _CSSOM_CSSSTYLESHEET_H
#define _CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_alloc(SAC_Parser parser);

CSSOM_CSSRule* CSSOM_CSSStyleSheet_append(CSSOM_CSSStyleSheet *styleSheet,
  CSSOM_CSSRule *cssRule);



#endif
