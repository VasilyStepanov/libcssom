#ifndef CSSOM_CSS_RULE_LIST_H
#define CSSOM_CSS_RULE_LIST_H

#include <cssom/css_rule.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSRuleList CSSOM_CSSRuleList;

void CSSOM_CSSRuleList_free(CSSOM_CSSRuleList *cssRules);



#ifdef __cplusplus
}
#endif

#endif
