#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include "list_css_rule.h"

#include <cssom/css_rule_list.h>



CSSOM_CSSRuleList* CSSOM_CSSRuleList_alloc(CSSOM_List_CSSRule *list);

void CSSOM_CSSRuleList_free(CSSOM_CSSRuleList *cssRules);



#endif
