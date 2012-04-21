#ifndef CSSOM_CSS_STYLE_RULE_H
#define CSSOM_CSS_STYLE_RULE_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleRule.idl'
 */



#include <cssom/typedefs.h>

#include <cssom/CSSRule.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSStyleRule_acquire(cssStyleRule) \
  CSSOM_CSSRule_acquire((CSSOM_CSSRule*)(cssStyleRule))



#define CSSOM_CSSStyleRule_release(cssStyleRule) \
  CSSOM_CSSRule_release((CSSOM_CSSRule*)(cssStyleRule))



const char * CSSOM_CSSStyleRule_selectorText(const CSSOM_CSSStyleRule * cssStyleRule);



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(const CSSOM_CSSStyleRule * cssStyleRule);



#ifdef __cplusplus
}
#endif

#endif
