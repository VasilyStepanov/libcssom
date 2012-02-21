#ifndef CSSOM_H
#define CSSOM_H

#include <cssom/CSSRule.h>
#include <cssom/CSSStyleRule.h>
#include <cssom/CSSRuleList.h>
#include <cssom/CSSStyleSheet.h>



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_parse(const char *cssText);



#endif
