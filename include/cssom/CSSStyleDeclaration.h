#ifndef CSSOM_CSSSTYLEDECLARATION_H
#define CSSOM_CSSSTYLEDECLARATION_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleDeclaration CSSOM_CSSStyleDeclaration;



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style);

void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value);



#ifdef __cplusplus
}
#endif

#endif