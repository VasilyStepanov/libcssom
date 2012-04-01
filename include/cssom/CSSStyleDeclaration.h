#ifndef CSSOM_CSS_STYLE_DECLARATION_H
#define CSSOM_CSS_STYLE_DECLARATION_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclaration.idl'
 */



#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSStyleDeclaration CSSOM_CSSStyleDeclaration;



const char * CSSOM_CSSStyleDeclaration_cssText(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



unsigned long CSSOM_CSSStyleDeclaration_length(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



const char * CSSOM_CSSStyleDeclaration_getPropertyValue(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property);



const char * CSSOM_CSSStyleDeclaration_getPropertyPriority(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property);



#ifdef __cplusplus
}
#endif

#endif