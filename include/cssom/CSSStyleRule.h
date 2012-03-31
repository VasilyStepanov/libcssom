#ifndef CSSOM_CSS_STYLE_RULE_H
#define CSSOM_CSS_STYLE_RULE_H

#include <cssom/CSSRule.h>
#include <cssom/CSSStyleDeclaration.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleRule CSSOM_CSSStyleRule;



const char * CSSOM_CSSStyleRule_selectorText(const CSSOM_CSSStyleRule * cssStyleRule);



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(const CSSOM_CSSStyleRule * cssStyleRule);



#ifdef __cplusplus
}
#endif

#endif
