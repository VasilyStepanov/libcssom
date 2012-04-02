#ifndef CSSOM_CSS_RULE_H
#define CSSOM_CSS_RULE_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSRule CSSOM_CSSRule;



void CSSOM_CSSRule_acquire(
  CSSOM_CSSRule * cssRule);



void CSSOM_CSSRule_release(
  CSSOM_CSSRule * cssRule);



extern unsigned short CSSOM_CSSRule_STYLE_RULE;



extern unsigned short CSSOM_CSSRule_IMPORT_RULE;



extern unsigned short CSSOM_CSSRule_MEDIA_RULE;



extern unsigned short CSSOM_CSSRule_FONT_FACE_RULE;



extern unsigned short CSSOM_CSSRule_PAGE_RULE;



extern unsigned short CSSOM_CSSRule_NAMESPACE_RULE;



unsigned short CSSOM_CSSRule_type(const CSSOM_CSSRule * cssRule);



#ifdef __cplusplus
}
#endif

#endif
