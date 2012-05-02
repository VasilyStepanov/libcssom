#include "CSSStyleDeclaration.h"

#include "CSSEmitter.h"
#include "CSSStyleDeclarationValue.h"
#include "memory.h"

#include <cssom/CSSRule.h>

#include <stdio.h>
#include <assert.h>



struct _CSSOM_CSSStyleDeclaration {
  size_t handles;
  CSSOM_CSSRule *parentRule;
  CSSOM_CSSStyleDeclarationValue *values;
  char *cssText;
};



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  CSSOM_CSSRule *parentRule)
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleDeclarationValue *values;

  style = (CSSOM_CSSStyleDeclaration*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) return NULL;

  style->handles = 1;
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



/*
void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration *style,
  const char *property, const char *value)
{
  CSSOM_CSSStyleDeclarationValue_setProperty(style->values, property, value);
}
*/



const char* CSSOM_CSSStyleDeclaration_cssText(
  const CSSOM_CSSStyleDeclaration *style)
{
  if (style->cssText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_cssStyleDeclaration(out, style) != 0) {
      fclose(out);
      CSSOM_native_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_native_free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleDeclaration*)style)->cssText = buf;
  }
  return style->cssText;
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
