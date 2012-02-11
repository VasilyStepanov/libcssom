#ifndef CSSOM_CSSSTYLESHEET_H
#define CSSOM_CSSSTYLESHEET_H

#include <cssom/css_rule_list.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleSheet CSSOM_CSSStyleSheet;



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet);

const CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
