#ifndef _CSSOM_CSSRULE_H
#define _CSSOM_CSSRULE_H

#include <cssom/CSSRule.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_CSSRule__acquire(CSSOM_CSSRule *cssRule);

void CSSOM_CSSRule__release(CSSOM_CSSRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
