#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include <cssom/CSSRuleList.h>



CSSOM_CSSRuleList* CSSOM_CSSRuleList__alloc();

void CSSOM_CSSRuleList__acquire(CSSOM_CSSRuleList *cssRules);

void CSSOM_CSSRuleList__release(CSSOM_CSSRuleList *cssRules);

CSSOM_CSSRule* CSSOM_CSSRuleList__append(CSSOM_CSSRuleList *cssRules,
  CSSOM_CSSRule *cssRule);



#endif
