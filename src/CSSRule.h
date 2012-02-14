#ifndef _CSSOM_CSSRULE_H
#define _CSSOM_CSSRULE_H

#include <cssom/CSSRule.h>



CSSOM_CSSRule* CSSOM_CSSRule_alloc(CSSOM_CSSRuleType type);

void CSSOM_CSSRule_free(CSSOM_CSSRule *cssRule);



#endif
