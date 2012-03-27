#ifndef CSSOM_CSS_STYLE_DECLARATION_H
#define CSSOM_CSS_STYLE_DECLARATION_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleDeclaration CSSOM_CSSStyleDeclaration;



const char * CSSOM_CSSStyleDeclaration_cssText(const CSSOM_CSSStyleDeclaration *);



void CSSOM_CSSStyleDeclaration_setCssText(CSSOM_CSSStyleDeclaration *, const char * cssText);



unsigned long CSSOM_CSSStyleDeclaration_length(const CSSOM_CSSStyleDeclaration *);



const char * CSSOM_CSSStyleDeclaration_getPropertyValue(CSSOM_CSSStyleDeclaration *, const char * property);



const char * CSSOM_CSSStyleDeclaration_getPropertyPriority(CSSOM_CSSStyleDeclaration *, const char * property);



#ifdef __cplusplus
}
#endif

#endif
