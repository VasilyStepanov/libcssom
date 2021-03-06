#ifndef CSSOM_CSS_STYLE_DECLARATION_VALUE_H
#define CSSOM_CSS_STYLE_DECLARATION_VALUE_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclarationValue.idl'
 */



#include <cssom/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_CSSStyleDeclarationValue_acquire(
  CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue);



void CSSOM_CSSStyleDeclarationValue_release(
  CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue);



unsigned long CSSOM_CSSStyleDeclarationValue_length(const CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue);



const char * CSSOM_CSSStyleDeclarationValue_item(CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue, unsigned long index);



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue_getProperty(const CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue, const char * property);



void CSSOM_CSSStyleDeclarationValue_setProperty(CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue, const char * property, const char * value);



void CSSOM_CSSStyleDeclarationValue_setPropertyEx(CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue, const char * property, const char * value, const char * priority);



const char * CSSOM_CSSStyleDeclarationValue_removeProperty(CSSOM_CSSStyleDeclarationValue * cssStyleDeclarationValue, const char * property);



#ifdef __cplusplus
}
#endif

#endif
