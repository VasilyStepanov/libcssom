#ifndef CSSOM_CSSSTYLEDECLARATION_H
#define CSSOM_CSSSTYLEDECLARATION_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleDeclaration CSSOM_CSSStyleDeclaration;



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style);

const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style, const char *property);

const char* CSSOM_CSSStyleDeclaration_getPropertyPriority(
  const CSSOM_CSSStyleDeclaration *style, const char *property);

const char* CSSOM_CSSStyleDeclaration_cssText(
  const CSSOM_CSSStyleDeclaration *style);



#ifdef __cplusplus
}
#endif

#endif
