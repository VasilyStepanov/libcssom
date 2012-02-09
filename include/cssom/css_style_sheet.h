#ifndef CSSOM_CSS_STYLE_SHEET_H
#define CSSOM_CSS_STYLE_SHEET_H

#include <cssom/css_rule_list.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleSheet CSSOM_CSSStyleSheet;

const CSSOM_CSSRuleList*
CSSOM_CSSStyleSheet_get_cssRules(CSSOM_CSSStyleSheet *styleSheet);

void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
