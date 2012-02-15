#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include <cssom/CSSRuleList.h>

#include "List_CSSRule.h"



CSSOM_CSSRuleList* CSSOM_CSSRuleList_realloc(CSSOM_CSSRuleList *cssRules,
  CSSOM_List_CSSRule *list);

void CSSOM_CSSRuleList_free(CSSOM_CSSRuleList *cssRules);



#endif
