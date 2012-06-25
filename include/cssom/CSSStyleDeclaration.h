#ifndef CSSOM_CSS_STYLE_DECLARATION_H
#define CSSOM_CSS_STYLE_DECLARATION_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclaration.idl'
 */



#include <cssom/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_CSSStyleDeclaration_acquire(
  CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_release(
  CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



const char * CSSOM_CSSStyleDeclaration_cssText(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCSSText(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cssText);



unsigned long CSSOM_CSSStyleDeclaration_length(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



const char * CSSOM_CSSStyleDeclaration_item(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, unsigned long index);



const char * CSSOM_CSSStyleDeclaration_getPropertyValue(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property);



const char * CSSOM_CSSStyleDeclaration_getPropertyPriority(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property);



void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property, const char * value);



void CSSOM_CSSStyleDeclaration_setPropertyEx(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property, const char * value, const char * priority);



const char * CSSOM_CSSStyleDeclaration_removeProperty(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * property);



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclaration_values(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



CSSOM_CSSRule* CSSOM_CSSStyleDeclaration_parentRule(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



const char * CSSOM_CSSStyleDeclaration_azimuth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setAzimuth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * azimuth);



const char * CSSOM_CSSStyleDeclaration_background(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackground(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * background);



const char * CSSOM_CSSStyleDeclaration_backgroundAttachment(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackgroundAttachment(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * backgroundAttachment);



const char * CSSOM_CSSStyleDeclaration_backgroundColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackgroundColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * backgroundColor);



const char * CSSOM_CSSStyleDeclaration_backgroundImage(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackgroundImage(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * backgroundImage);



const char * CSSOM_CSSStyleDeclaration_backgroundPosition(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackgroundPosition(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * backgroundPosition);



const char * CSSOM_CSSStyleDeclaration_backgroundRepeat(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBackgroundRepeat(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * backgroundRepeat);



const char * CSSOM_CSSStyleDeclaration_borderCollapse(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderCollapse(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderCollapse);



const char * CSSOM_CSSStyleDeclaration_borderColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderColor);



const char * CSSOM_CSSStyleDeclaration_borderSpacing(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderSpacing(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderSpacing);



const char * CSSOM_CSSStyleDeclaration_borderStyle(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderStyle(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderStyle);



const char * CSSOM_CSSStyleDeclaration_borderTop(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderTop(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderTop);



const char * CSSOM_CSSStyleDeclaration_borderRight(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderRight(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderRight);



const char * CSSOM_CSSStyleDeclaration_borderBottom(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderBottom(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderBottom);



const char * CSSOM_CSSStyleDeclaration_borderLeft(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderLeft(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderLeft);



const char * CSSOM_CSSStyleDeclaration_borderTopColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderTopColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderTopColor);



const char * CSSOM_CSSStyleDeclaration_borderRightColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderRightColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderRightColor);



const char * CSSOM_CSSStyleDeclaration_borderBottomColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderBottomColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderBottomColor);



const char * CSSOM_CSSStyleDeclaration_borderLeftColor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderLeftColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderLeftColor);



const char * CSSOM_CSSStyleDeclaration_borderTopStyle(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderTopStyle(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderTopStyle);



const char * CSSOM_CSSStyleDeclaration_borderRightStyle(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderRightStyle(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderRightStyle);



const char * CSSOM_CSSStyleDeclaration_borderBottomStyle(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderBottomStyle(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderBottomStyle);



const char * CSSOM_CSSStyleDeclaration_borderLeftStyle(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderLeftStyle(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderLeftStyle);



const char * CSSOM_CSSStyleDeclaration_borderTopWidth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderTopWidth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderTopWidth);



const char * CSSOM_CSSStyleDeclaration_borderRightWidth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderRightWidth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderRightWidth);



const char * CSSOM_CSSStyleDeclaration_borderBottomWidth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderBottomWidth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderBottomWidth);



const char * CSSOM_CSSStyleDeclaration_borderLeftWidth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderLeftWidth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderLeftWidth);



const char * CSSOM_CSSStyleDeclaration_borderWidth(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorderWidth(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * borderWidth);



#ifdef __cplusplus
}
#endif

#endif
