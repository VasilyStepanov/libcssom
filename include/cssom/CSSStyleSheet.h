#ifndef CSSOM_CSS_STYLE_SHEET_H
#define CSSOM_CSS_STYLE_SHEET_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleSheet.idl'
 */



#include <cssom/CSSRuleList.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleSheet CSSOM_CSSStyleSheet;



void CSSOM_CSSStyleSheet_acquire(
  CSSOM_CSSStyleSheet * cssStyleSheet);



void CSSOM_CSSStyleSheet_release(
  CSSOM_CSSStyleSheet * cssStyleSheet);



CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(const CSSOM_CSSStyleSheet * cssStyleSheet);



#ifdef __cplusplus
}
#endif

#endif
