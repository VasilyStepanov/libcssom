#include "CSSRule.h"
#include "CSSNamespaceRule.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"

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



#define SWAP(lhs, rhs) \
  do { \
    void *t = (void*)lhs; \
    lhs = rhs; \
    rhs = t; \
  } while (0)



/**
 * CSSRule
 */

struct _CSSOM_CSSRule_vtable {
  void (*free)(CSSOM_CSSRule *cssRule);
  void (*swap)(CSSOM_CSSRule *lhs, CSSOM_CSSRule *rhs);
  const char* (*cssText)(const CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSRule {
  struct _CSSOM_CSSRule_vtable *vtable;
  CSSOM_CSSStyleSheet *parentStyleSheet;
  unsigned short type;
  char *cssText;
};



static void CSSRule_init(CSSOM_CSSRule *cssRule,
  struct _CSSOM_CSSRule_vtable *vtable, CSSOM_CSSStyleSheet *parentStyleSheet,
  unsigned short type)
{
  cssRule->vtable = vtable;
  cssRule->parentStyleSheet = parentStyleSheet;
  cssRule->type = type;
  cssRule->cssText = NULL;
}



void CSSOM_CSSRule__free(CSSOM_CSSRule *cssRule) {
  cssRule->vtable->free(cssRule);

  CSSOM_native_free(cssRule->cssText);
}



const char* CSSOM_CSSRule_cssText(const CSSOM_CSSRule *cssRule) {
  return cssRule->vtable->cssText(cssRule);
}



unsigned short CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule) {
  return cssRule->type;
}



CSSOM_CSSStyleSheet* CSSOM_CSSRule_parentStyleSheet(
  const CSSOM_CSSRule *cssRule)
{
  return cssRule->parentStyleSheet;
}



static void CSSRule_swap(CSSOM_CSSRule *lhs, CSSOM_CSSRule *rhs) {
  lhs->vtable->swap(lhs, rhs);
}



static void CSSRule_swap_impl(CSSOM_CSSRule *lhs, CSSOM_CSSRule *rhs) {
  SWAP(lhs->cssText, rhs->cssText);
}



void CSSOM_CSSRule_setCSSText(CSSOM_CSSRule *cssRule, const char *cssText) {
  CSSOM_CSSRule *newCSSRule;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(cssRule->parentStyleSheet);
  newCSSRule = CSSOM__parseCSSRule(cssom, cssText, strlen(cssText));
  if (newCSSRule == NULL) return;

  if (CSSOM_CSSRule_type(newCSSRule) != CSSOM_CSSRule_type(cssRule)) {
    CSSOM__invalidModificationErr(cssom);
    return;
  }
  
  CSSOM_native_free(cssRule->cssText);
  cssRule->cssText = NULL;
  newCSSRule->parentStyleSheet = cssRule->parentStyleSheet;
  CSSRule_swap(cssRule, newCSSRule);

  CSSOM_CSSRule__free(newCSSRule);
}



/**
 * CSSStyleRule
 */

struct _CSSOM_CSSStyleRule {
  CSSOM_CSSRule super;
  char *selectorText;
  const SAC_Selector **selectors;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSStyleRule_free(CSSOM_CSSStyleRule *cssRule) {
  CSSOM_CSSStyleDeclaration__free(cssRule->style);
  CSSOM_native_free(cssRule->selectorText);
  CSSOM_free(cssRule);
}



static const char* CSSStyleRule_cssText(const CSSOM_CSSStyleRule *cssRule) {
  if (((CSSOM_CSSRule*)cssRule)->cssText == NULL) {
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

    ((CSSOM_CSSRule*)cssRule)->cssText = buf;
  }
  return ((CSSOM_CSSRule*)cssRule)->cssText;
}



static void CSSStyleRule_swap(
  CSSOM_CSSStyleRule *lhs, CSSOM_CSSStyleRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->selectorText, rhs->selectorText);
  SWAP(lhs->selectors, rhs->selectors);
  SWAP(lhs->style, rhs->style);
}



static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSStyleRule_swap,
  (const char*(*)(const CSSOM_CSSRule*))&CSSStyleRule_cssText
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



static void CSSNamespaceRule_free(CSSOM_CSSNamespaceRule *cssRule) {
  CSSOM_free(cssRule);
}



static struct _CSSOM_CSSRule_vtable CSSNamespaceRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSNamespaceRule_free,
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



/**
 * CSSPageRule
 */

struct _CSSOM_CSSPageRule {
  CSSOM_CSSRule super;
  char *selectorText;
  const SAC_Selector **selectors;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSPageRule_free(CSSOM_CSSPageRule *cssRule) {
  CSSOM_CSSStyleDeclaration__free(cssRule->style);
  CSSOM_native_free(cssRule->selectorText);
  CSSOM_free(cssRule);
}



static struct _CSSOM_CSSRule_vtable CSSPageRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSPageRule_free,
  NULL,
  NULL
};



CSSOM_CSSPageRule* CSSOM_CSSPageRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet,
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSPageRule *cssRule;

  style = CSSOM_CSSStyleDeclaration__alloc(table);
  if (style == NULL) return NULL;

  cssRule = (CSSOM_CSSPageRule*)CSSOM_malloc(
    sizeof(CSSOM_CSSPageRule));
  if (cssRule == NULL) {
    CSSOM_CSSStyleDeclaration__free(style);
    return NULL;
  }

  CSSRule_init((CSSOM_CSSRule*)cssRule, &CSSPageRule_vtable,
    parentStyleSheet, CSSOM_CSSRule_PAGE_RULE);
  cssRule->selectorText = NULL;
  cssRule->selectors = selectors;
  cssRule->style = style;

  return cssRule;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSPageRule_style(
  const CSSOM_CSSPageRule *cssRule)
{
  return cssRule->style;
}



const char* CSSOM_CSSPageRule_selectorText(
  const CSSOM_CSSPageRule *cssRule)
{
  if (cssRule->selectorText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (!(cssRule->selectors[0] != NULL && cssRule->selectors[1] == NULL &&
      cssRule->selectors[0]->selectorType == SAC_ANY_NODE_SELECTOR))
    {
      if (CSSOM_CSSEmitter_selectors(out, cssRule->selectors) != 0) {
        fclose(out);
        CSSOM_free(buf);
        return NULL;
      }
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_CSSPageRule*)cssRule)->selectorText = buf;
  }
  return cssRule->selectorText;
}
