#ifndef CSSOM_CSS_FONT_FACE_RULE_H
#define CSSOM_CSS_FONT_FACE_RULE_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/typedefs.h>

#include <cssom/CSSRule.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSFontFaceRule_acquire(cssFontFaceRule) \
  CSSOM_CSSRule_acquire((CSSOM_CSSRule*)(cssFontFaceRule))



#define CSSOM_CSSFontFaceRule_release(cssFontFaceRule) \
  CSSOM_CSSRule_release((CSSOM_CSSRule*)(cssFontFaceRule))



CSSOM_CSSStyleDeclaration* CSSOM_CSSFontFaceRule_style(const CSSOM_CSSFontFaceRule * cssFontFaceRule);



#ifdef __cplusplus
}
#endif

#endif
