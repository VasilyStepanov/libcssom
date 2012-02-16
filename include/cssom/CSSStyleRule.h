#ifndef CSSOM_CSSSTYLERULE_H
#define CSSOM_CSSSTYLERULE_H

#include <cssom/CSSStyleDeclaration.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleRule CSSOM_CSSStyleRule;



const CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(
  CSSOM_CSSStyleRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
