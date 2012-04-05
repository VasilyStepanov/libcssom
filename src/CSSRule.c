#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSNamespaceRule.h"

#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
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
  CSSOM_CSSStyleSheet *parentStyleSheet;
  unsigned short type;
};



static void CSSRule_init(CSSOM_CSSRule *cssRule,
  struct _CSSOM_CSSRule_vtable *vtable, CSSOM_CSSStyleSheet *parentStyleSheet,
  unsigned short type)
{
  cssRule->vtable = vtable;
  cssRule->parentStyleSheet = parentStyleSheet;
  cssRule->type = type;
}



void CSSOM_CSSRule__free(CSSOM_CSSRule *cssRule) {
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



CSSOM_CSSStyleSheet* CSSOM_CSSRule_parentStyleSheet(
  const CSSOM_CSSRule *cssRule)
{
  return cssRule->parentStyleSheet;
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
  CSSOM_native_free(cssRule->cssText);
  CSSOM_CSSStyleDeclaration__free(cssRule->style);
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
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    ((CSSOM_CSSRule*)cssRule)->parentStyleSheet);

  newCSSRule = CSSOM__parseCSSRule(cssom, cssText, strlen(cssText));
  if (newCSSRule == NULL) return;

  if (CSSOM_CSSRule_type(newCSSRule) != CSSOM_CSSRule_STYLE_RULE) {
    CSSOM__invalidModificationErr(cssom);
    return;
  }
  
  CSSOM_native_free(cssRule->cssText);
  cssRule->cssText = NULL;
  newCSSRule->parentStyleSheet = ((CSSOM_CSSRule*)cssRule)->parentStyleSheet;
  CSSStyleRule_swap(cssRule, (CSSOM_CSSStyleRule*)newCSSRule);

  CSSOM_CSSRule__free(newCSSRule);
}



static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_release,
  (const char*(*)(const CSSOM_CSSRule*))&CSSStyleRule_cssText,
  (void(*)(CSSOM_CSSRule*, const char *cssText))&CSSStyleRule_setCSSText
};



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet,
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleRule *cssRule;

  style = CSSOM_CSSStyleDeclaration__alloc(table);
  if (style == NULL) return NULL;

  cssRule = (CSSOM_CSSStyleRule*)CSSOM_malloc(sizeof(CSSOM_CSSStyleRule));
  if (cssRule == NULL) {
    CSSOM_CSSStyleDeclaration__free(style);
    return NULL;
  }

  CSSRule_init((CSSOM_CSSRule*)cssRule,
    &CSSStyleRule_vtable, parentStyleSheet, CSSOM_CSSRule_STYLE_RULE);
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
  CSSOM_free(cssRule);
}



static struct _CSSOM_CSSRule_vtable CSSNamespaceRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSNamespaceRule_release,
  NULL,
  NULL
};



CSSOM_CSSNamespaceRule* CSSOM_CSSNamespaceRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet)
{
  CSSOM_CSSNamespaceRule *cssRule;

  cssRule = (CSSOM_CSSNamespaceRule*)CSSOM_malloc(
    sizeof(CSSOM_CSSNamespaceRule));
  if (cssRule == NULL) return NULL;

  CSSRule_init((CSSOM_CSSRule*)cssRule, &CSSNamespaceRule_vtable,
    parentStyleSheet, CSSOM_CSSRule_NAMESPACE_RULE);

  return cssRule;
}
