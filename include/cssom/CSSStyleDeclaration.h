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



const char * CSSOM_CSSStyleDeclaration_border(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBorder(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * border);



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



const char * CSSOM_CSSStyleDeclaration_bottom(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setBottom(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * bottom);



const char * CSSOM_CSSStyleDeclaration_captionSide(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCaptionSide(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * captionSide);



const char * CSSOM_CSSStyleDeclaration_clear(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setClear(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * clear);



const char * CSSOM_CSSStyleDeclaration_clip(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setClip(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * clip);



const char * CSSOM_CSSStyleDeclaration_color(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setColor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * color);



const char * CSSOM_CSSStyleDeclaration_content(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setContent(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * content);



const char * CSSOM_CSSStyleDeclaration_counterIncrement(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCounterIncrement(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * counterIncrement);



const char * CSSOM_CSSStyleDeclaration_counterReset(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCounterReset(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * counterReset);



const char * CSSOM_CSSStyleDeclaration_cue(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCue(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cue);



const char * CSSOM_CSSStyleDeclaration_cueAfter(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCueAfter(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cueAfter);



const char * CSSOM_CSSStyleDeclaration_cueBefore(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCueBefore(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cueBefore);



const char * CSSOM_CSSStyleDeclaration_cursor(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCursor(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cursor);



const char * CSSOM_CSSStyleDeclaration_direction(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setDirection(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * direction);



const char * CSSOM_CSSStyleDeclaration_display(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setDisplay(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * display);



const char * CSSOM_CSSStyleDeclaration_elevation(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setElevation(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * elevation);



const char * CSSOM_CSSStyleDeclaration_emptyCells(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setEmptyCells(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * emptyCells);



const char * CSSOM_CSSStyleDeclaration_cssFloat(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setCSSFloat(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * cssFloat);



const char * CSSOM_CSSStyleDeclaration_fontFamily(const CSSOM_CSSStyleDeclaration * cssStyleDeclaration);



void CSSOM_CSSStyleDeclaration_setFontFamily(CSSOM_CSSStyleDeclaration * cssStyleDeclaration, const char * fontFamily);



#ifdef __cplusplus
}
#endif

#endif
