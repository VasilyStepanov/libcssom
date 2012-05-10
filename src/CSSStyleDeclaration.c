#include "CSSStyleDeclaration.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "CSSStyleDeclarationValue.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSRule.h>
#include <cssom/CSSProperties.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>



struct _CSSOM_CSSStyleDeclaration {
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSRule *parentRule;
  CSSOM_CSSStyleDeclarationValue *values;
  char *cssText;
};



static void CSSStyleDeclaration_swap(
  CSSOM_CSSStyleDeclaration *lhs, CSSOM_CSSStyleDeclaration *rhs)
{
  SWAP(lhs->parser, rhs->parser);
  SWAP(lhs->parentRule, rhs->parentRule);
  SWAP(lhs->values, rhs->values);
  SWAP(lhs->cssText, rhs->cssText);
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  CSSOM_CSSRule *parentRule)
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleDeclarationValue *values;

  style = (CSSOM_CSSStyleDeclaration*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) return NULL;

  style->handles = 1;
  style->parser = NULL;
  style->parentRule = parentRule;
  style->values = NULL;
  style->cssText = NULL;

  values = CSSOM_CSSStyleDeclarationValue__alloc(style);
  if (values == NULL) {
    CSSOM_CSSStyleDeclaration_release(style);
    return NULL;
  }
  style->values = values;

  return style;
}



void CSSOM_CSSStyleDeclaration_acquire(CSSOM_CSSStyleDeclaration *style) {
  if (style == NULL) return;

  ++style->handles;
  CSSOM_CSSRule_acquire(style->parentRule);
}



void CSSOM_CSSStyleDeclaration_release(CSSOM_CSSStyleDeclaration *style) {
  if (style == NULL) return;

  assert(style->handles > 0);
  --style->handles;
  if (style->handles > 0) {
    CSSOM_CSSRule_release(style->parentRule);
    return;
  }

  CSSOM_native_free(style->cssText);
  CSSOM_CSSStyleDeclarationValue_release(style->values);
  SAC_DisposeParser(style->parser);
  CSSOM_free(style);
}



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue_length(style->values);
}



const char* CSSOM_CSSStyleDeclaration_item(CSSOM_CSSStyleDeclaration *style,
  unsigned long index)
{
  return CSSOM_CSSStyleDeclarationValue_item(style->values, index);
}




const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  return CSSOM_CSSStyleDeclarationValue__getPropertyValue(
    style->values, property);
}



const char* CSSOM_CSSStyleDeclaration_getPropertyPriority(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  return CSSOM_CSSStyleDeclarationValue__getPropertyPriority(
    style->values, property);
}



void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  CSSOM_CSSStyleDeclarationValue_setProperty(style->values, property, value);
}



void CSSOM_CSSStyleDeclaration_setPropertyEx(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value, const char *priority)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  CSSOM_CSSStyleDeclarationValue_setPropertyEx(style->values,
    property, value, priority);
}



const char* CSSOM_CSSStyleDeclaration_removeProperty(
  CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_native_free(style->cssText);
  style->cssText = NULL;
  return CSSOM_CSSStyleDeclarationValue_removeProperty(style->values, property);
}



const char* CSSOM_CSSStyleDeclaration_cssText(
  const CSSOM_CSSStyleDeclaration *style)
{
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(style->cssText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_styleDeclaration(out, style) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_CSSStyleDeclaration*)style)->cssText = buf;

  return style->cssText;
}



void CSSOM_CSSStyleDeclaration_setCSSText(CSSOM_CSSStyleDeclaration *style,
  const char *cssText)
{
  CSSOM_CSSStyleDeclaration *newStyle;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(style->parentRule));
  newStyle = CSSOM__parseStyleDeclaration(cssom, style->parentRule,
    cssText, strlen(cssText));
  if (newStyle == NULL) return;

  CSSStyleDeclaration_swap(style, newStyle);

  CSSOM_CSSStyleDeclaration_release(newStyle);
}



CSSOM_CSSRule* CSSOM_CSSStyleDeclaration_parentRule(
  const CSSOM_CSSStyleDeclaration *style)
{
  return style->parentRule;
}



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclaration_values(
  const CSSOM_CSSStyleDeclaration *style)
{
  return style->values;
}



void CSSOM_CSSStyleDeclaration__keepParser(CSSOM_CSSStyleDeclaration *style,
  SAC_Parser parser)
{
  assert(style->parser == NULL);
  style->parser = parser;
}



const char * CSSOM_CSSStyleDeclaration_azimuth(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(style->values,
    CSSOM_AZIMUTH_PROPERTY);
}



void CSSOM_CSSStyleDeclaration_setAzimuth(CSSOM_CSSStyleDeclaration *style,
  const char *azimuth)
{
  CSSOM_CSSStyleDeclarationValue_setProperty(style->values,
    "azimuth", azimuth);
}
