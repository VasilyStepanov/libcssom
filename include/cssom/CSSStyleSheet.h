#ifndef CSSOM_CSSSTYLESHEET_H
#define CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSRuleList.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleSheet CSSOM_CSSStyleSheet;



void CSSOM_CSSStyleSheet_dispose(CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
