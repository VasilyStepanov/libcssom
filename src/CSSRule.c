#include <cssom/CSSRule.h>
#include "CSSStyleRule.h"
#include "CSSNamespaceRule.h"

#include "CSSStyleDeclaration.h"
#include "CSSEmitter.h"
#include "CSSOM.h"
#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>



unsigned short CSSOM_CSSRule_STYLE_RULE = 1;



unsigned short CSSOM_CSSRule_IMPORT_RULE = 3;



unsigned short CSSOM_CSSRule_MEDIA_RULE = 4;



unsigned short CSSOM_CSSRule_FONT_FACE_RULE = 5;



unsigned short CSSOM_CSSRule_PAGE_RULE = 6;



unsigned short CSSOM_CSSRule_NAMESPACE_RULE = 10;



#define swap(lhs, rhs) \
  do { \
    void *t = (void*)lhs; \
    lhs = rhs; \
    rhs = t; \
  } while (0)



/**
 * CSSRule
 */

struct _CSSOM_CSSRule_vtable {
  void (*release)(CSSOM_CSSRule *cssRule);
  const char* (*cssText)(const CSSOM_CSSRule *cssRule);
  void (*setCSSText)(CSSOM_CSSRule *cssRule, const char *cssText);
};



struct _CSSOM_CSSRule {
  struct _CSSOM_CSSRule_vtable *vtable;
  size_t handles;
  const CSSOM *cssom;
  unsigned short type;
};



static void CSSRule_init(CSSOM_CSSRule *cssRule,
  struct _CSSOM_CSSRule_vtable *vtable, const CSSOM *cssom, unsigned short type)
{
  cssRule->vtable = vtable;
  cssRule->handles = 1;
  cssRule->cssom = cssom;
  cssRule->type = type;
}



void CSSOM_CSSRule_acquire(CSSOM_CSSRule *cssRule) {
  ++cssRule->handles;
}



void CSSOM_CSSRule_release(CSSOM_CSSRule *cssRule) {
  cssRule->vtable->release(cssRule);
}



const char* CSSOM_CSSRule_cssText(const CSSOM_CSSRule *cssRule) {
  return cssRule->vtable->cssText(cssRule);
}



void CSSOM_CSSRule_setCSSText(CSSOM_CSSRule *cssRule, const char *cssText) {
  cssRule->vtable->setCSSText(cssRule, cssText);
}



unsigned short CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule) {
  return cssRule->type;
}



/**
 * CSSStyleRule
 */

struct _CSSOM_CSSStyleRule {
  CSSOM_CSSRule super;
  char *selectorText;
  const SAC_Selector **selectors;
  CSSOM_CSSStyleDeclaration *style;
  char *cssText;
};



static void CSSStyleRule_release(CSSOM_CSSStyleRule *cssRule) {
  assert(((CSSOM_CSSRule*)cssRule)->handles > 0);
  --((CSSOM_CSSRule*)cssRule)->handles;
  if (((CSSOM_CSSRule*)cssRule)->handles > 0) return;

  CSSOM_native_free(cssRule->cssText);
  CSSOM_CSSStyleDeclaration_release(cssRule->style);
  CSSOM_native_free(cssRule->selectorText);
  CSSOM_free(cssRule);
}



static const char* CSSStyleRule_cssText(const CSSOM_CSSStyleRule *cssRule) {
  if (cssRule->cssText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_cssStyleRule(out, cssRule) != 0) {
      fclose(out);
      CSSOM_native_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_native_free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleRule*)cssRule)->cssText = buf;
  }
  return cssRule->cssText;
}



static void CSSStyleRule_swap(
  CSSOM_CSSStyleRule *lhs, CSSOM_CSSStyleRule *rhs)
{
  swap(lhs->selectorText, rhs->selectorText);
  swap(lhs->selectors, rhs->selectors);
  swap(lhs->style, rhs->style);
  swap(lhs->cssText, rhs->cssText);
}



static void CSSStyleRule_setCSSText(CSSOM_CSSStyleRule *cssRule,
  const char *cssText)
{
  CSSOM_CSSRule *newCSSRule;

  newCSSRule = CSSOM__parseCSSRule(
    ((CSSOM_CSSRule*)cssRule)->cssom, cssText, strlen(cssText));
  if (newCSSRule == NULL) return;

  if (CSSOM_CSSRule_type(newCSSRule) != CSSOM_CSSRule_STYLE_RULE) {
    CSSOM__invalidModificationErr(((CSSOM_CSSRule*)cssRule)->cssom);
    return;
  }
  
  CSSOM_native_free(cssRule->cssText);
  cssRule->cssText = NULL;

  CSSStyleRule_swap(cssRule, (CSSOM_CSSStyleRule*)newCSSRule);

  CSSOM_CSSStyleRule_release(newCSSRule);
}



static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_release,
  (const char*(*)(const CSSOM_CSSRule*))&CSSStyleRule_cssText,
  (void(*)(CSSOM_CSSRule*, const char *cssText))&CSSStyleRule_setCSSText
};



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(const CSSOM *cssom,
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleRule *cssRule;

  style = CSSOM_CSSStyleDeclaration__alloc(table);
  if (style == NULL) return NULL;

  cssRule = (CSSOM_CSSStyleRule*)CSSOM_malloc(sizeof(CSSOM_CSSStyleRule));
  if (cssRule == NULL) {
    CSSOM_CSSStyleDeclaration_release(style);
    return NULL;
  }

  CSSRule_init((CSSOM_CSSRule*)cssRule,
    &CSSStyleRule_vtable, cssom, CSSOM_CSSRule_STYLE_RULE);
  cssRule->selectorText = NULL;
  cssRule->selectors = selectors;
  cssRule->style = style;
  cssRule->cssText = NULL;

  return cssRule;
}



const SAC_Selector** CSSOM_CSSStyleRule__selectors(
  const CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->selectors;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(
  const CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->style;
}



const char* CSSOM_CSSStyleRule_selectorText(
  const CSSOM_CSSStyleRule *cssRule)
{
  if (cssRule->selectorText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_selectors(out, cssRule->selectors) != 0) {
      fclose(out);
      CSSOM_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleRule*)cssRule)->selectorText = buf;
  }
  return cssRule->selectorText;
}



/**
 * CSSNamespaceRule
 */

struct _CSSOM_CSSNamespaceRule {
  CSSOM_CSSRule super;
};



static void CSSNamespaceRule_release(CSSOM_CSSNamespaceRule *cssRule) {
  assert(((CSSOM_CSSRule*)cssRule)->handles > 0);
  --((CSSOM_CSSRule*)cssRule)->handles;
  if (((CSSOM_CSSRule*)cssRule)->handles > 0) return;

  CSSOM_free(cssRule);
}



static struct _CSSOM_CSSRule_vtable CSSNamespaceRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSNamespaceRule_release,
  NULL,
  NULL
};



CSSOM_CSSNamespaceRule* CSSOM_CSSNamespaceRule__alloc(const CSSOM *cssom) {
  CSSOM_CSSNamespaceRule *cssRule;

  cssRule = (CSSOM_CSSNamespaceRule*)CSSOM_malloc(
    sizeof(CSSOM_CSSNamespaceRule));
  if (cssRule == NULL) return NULL;

  CSSRule_init((CSSOM_CSSRule*)cssRule,
    &CSSNamespaceRule_vtable, cssom, CSSOM_CSSRule_NAMESPACE_RULE);

  return cssRule;
}
