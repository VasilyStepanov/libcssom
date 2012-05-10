#ifndef _CSSOM_CSS_STYLE_DECLARATION_H
#define _CSSOM_CSS_STYLE_DECLARATION_H

#include <cssom/CSSStyleDeclaration.h>

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  CSSOM_CSSRule *parentRule);

void CSSOM_CSSStyleDeclaration__keepParser(CSSOM_CSSStyleDeclaration *style,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif
