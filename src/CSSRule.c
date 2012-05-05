#include "CSSRule.h"
#include "CSSFontFaceRule.h"
#include "CSSMediaRule.h"
#include "CSSNamespaceRule.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"

#include "CSSRuleList.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "CSSEmitter.h"
#include "CSSOM.h"
#include "MediaList.h"
#include "Selector.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>



unsigned short CSSOM_CSSRule_STYLE_RULE = 1;



unsigned short CSSOM_CSSRule_IMPORT_RULE = 3;



unsigned short CSSOM_CSSRule_MEDIA_RULE = 4;



unsigned short CSSOM_CSSRule_FONT_FACE_RULE = 5;



unsigned short CSSOM_CSSRule_PAGE_RULE = 6;



unsigned short CSSOM_CSSRule_NAMESPACE_RULE = 10;



/**
 * CSSRule
 */

struct _CSSOM_CSSRule_vtable {
  void (*free)(CSSOM_CSSRule *cssRule);
  void (*swap)(CSSOM_CSSRule *lhs, CSSOM_CSSRule *rhs);
  int (*emit)(FILE *out, const CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSRule {
  struct _CSSOM_CSSRule_vtable *vtable;
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSRule *parentRule;
  CSSOM_CSSStyleSheet *parentStyleSheet;
  unsigned short type;
  char *cssText;
};



static void CSSRule_ctor(CSSOM_CSSRule *cssRule,
  struct _CSSOM_CSSRule_vtable *vtable, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, unsigned short type)
{
  cssRule->vtable = vtable;
  cssRule->handles = 1;
  cssRule->parser = NULL;
  cssRule->parentRule = parentRule;
  cssRule->parentStyleSheet = parentStyleSheet;
  cssRule->type = type;
  cssRule->cssText = NULL;
}



void CSSOM_CSSRule_acquire(CSSOM_CSSRule *cssRule) {
  if (cssRule == NULL) return;

  ++cssRule->handles;
  CSSOM_CSSRule_acquire(cssRule->parentRule);
  CSSOM_CSSStyleSheet_acquire(cssRule->parentStyleSheet);
}



void CSSOM_CSSRule_release(CSSOM_CSSRule *cssRule) {
  if (cssRule == NULL) return;

  assert(cssRule->handles > 0);
  --cssRule->handles;
  if (cssRule->handles > 0) {
    CSSOM_CSSStyleSheet_release(cssRule->parentStyleSheet);
    CSSOM_CSSRule_release(cssRule->parentRule);
    return;
  }

  cssRule->vtable->free(cssRule);
  CSSOM_native_free(cssRule->cssText);
  SAC_DisposeParser(cssRule->parser);
  CSSOM_free(cssRule);
}



const char* CSSOM_CSSRule_cssText(const CSSOM_CSSRule *cssRule) {
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(cssRule->cssText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (cssRule->vtable->emit(out, cssRule) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_CSSRule*)cssRule)->cssText = buf;

  return cssRule->cssText;
}



unsigned short CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule) {
  return cssRule->type;
}



CSSOM_CSSRule* CSSOM_CSSRule_parentRule(const CSSOM_CSSRule *cssRule) {
  return cssRule->parentRule;
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
  SWAP(lhs->parser, rhs->parser);
  SWAP(lhs->cssText, rhs->cssText);
}



void CSSOM_CSSRule_setCSSText(CSSOM_CSSRule *cssRule, const char *cssText) {
  CSSOM_CSSRule *newCSSRule;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(cssRule->parentStyleSheet);
  newCSSRule = CSSOM__parseRule(cssom, cssRule->parentRule,
    cssRule->parentStyleSheet, cssText, strlen(cssText));
  if (newCSSRule == NULL) return;

  if (CSSOM_CSSRule_type(newCSSRule) != CSSOM_CSSRule_type(cssRule)) {
    CSSOM_CSSRule_release(newCSSRule);
    CSSOM__invalidModificationErr(cssom);
    return;
  }
  
  CSSOM_native_free(cssRule->cssText);
  cssRule->cssText = NULL;
  CSSRule_swap(cssRule, newCSSRule);

  CSSOM_CSSRule_release(newCSSRule);
}



void CSSOM_CSSRule__keepParser(CSSOM_CSSRule *cssRule, SAC_Parser parser) {
  assert(cssRule->parser == NULL);
  cssRule->parser = parser;
}



/**
 * CSSFontFaceRule
 */

struct _CSSOM_CSSFontFaceRule {
  CSSOM_CSSRule super;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSFontFaceRule_free(CSSOM_CSSFontFaceRule *cssRule) {
  CSSOM_CSSStyleDeclaration_release(cssRule->style);
}



static void CSSFontFaceRule_swap(
  CSSOM_CSSFontFaceRule *lhs, CSSOM_CSSFontFaceRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->style, rhs->style);
}



static struct _CSSOM_CSSRule_vtable CSSFontFaceRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSFontFaceRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSFontFaceRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_fontFaceRule
};



CSSOM_CSSFontFaceRule* CSSOM_CSSFontFaceRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet)
{
  CSSOM_CSSFontFaceRule *cssRule;
  CSSOM_CSSStyleDeclaration *style;

  cssRule = (CSSOM_CSSFontFaceRule*)CSSOM_malloc(sizeof(CSSOM_CSSFontFaceRule));
  if (cssRule == NULL) return NULL;

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSFontFaceRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_FONT_FACE_RULE);

  cssRule->style = NULL;

  style = CSSOM_CSSStyleDeclaration__alloc((CSSOM_CSSRule*)cssRule);
  if (style == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }
  cssRule->style = style;

  return cssRule;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSFontFaceRule_style(
  const CSSOM_CSSFontFaceRule *cssRule)
{
  return cssRule->style;
}



/**
 * CSSImportRule
 */

struct _CSSOM_CSSImportRule {
  CSSOM_CSSRule super;
  char *href;
  CSSOM_MediaList *media;
};



static void CSSImportRule_free(CSSOM_CSSImportRule *cssRule) {
  CSSOM_native_free(cssRule->href);
  CSSOM_MediaList_release(cssRule->media);
}



static void CSSImportRule_swap(
  CSSOM_CSSImportRule *lhs, CSSOM_CSSImportRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->href, rhs->href);
  SWAP(lhs->media, rhs->media);
}



static struct _CSSOM_CSSRule_vtable CSSImportRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSImportRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSImportRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_importRule
};



CSSOM_CSSImportRule* CSSOM_CSSImportRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_STRING base CSSOM_UNUSED, const SAC_STRING uri,
  const SAC_MediaQuery *mediaQuery[],
  const SAC_STRING defaultNamepaceURI CSSOM_UNUSED)
{
  CSSOM_CSSImportRule *cssRule;
  char *href;
  CSSOM_MediaList *media;

  cssRule = (CSSOM_CSSImportRule*)CSSOM_malloc(sizeof(CSSOM_CSSImportRule));
  if (cssRule == NULL) return NULL;

  href = strdup(uri);
  if (href == NULL) return NULL;

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSImportRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_IMPORT_RULE);

  cssRule->href = href;
  cssRule->media = NULL;



  media = CSSOM_MediaList__alloc((CSSOM_CSSRule*)cssRule, mediaQuery);
  if (media == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  cssRule->media = media;

  return cssRule;
}



const char* CSSOM_CSSImportRule_href(const CSSOM_CSSImportRule *cssRule) {
  return cssRule->href;
}



void CSSOM_CSSImportRule_setMedia(CSSOM_CSSImportRule *cssRule,
  const char *media)
{
  CSSOM_MediaList_setMediaText(cssRule->media, media);
}



CSSOM_MediaList* CSSOM_CSSImportRule_media(const CSSOM_CSSImportRule *cssRule) {
  return cssRule->media;
}



/**
 * CSSStyleRule
 */

struct _CSSOM_CSSStyleRule {
  CSSOM_CSSRule super;
  CSSOM_Selector *selector;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSStyleRule_free(CSSOM_CSSStyleRule *cssRule) {
  CSSOM_CSSStyleDeclaration_release(cssRule->style);
  CSSOM_Selector_release(cssRule->selector);
}



static void CSSStyleRule_swap(
  CSSOM_CSSStyleRule *lhs, CSSOM_CSSStyleRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->selector, rhs->selector);
  SWAP(lhs->style, rhs->style);
}



static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSStyleRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_styleRule
};



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;
  CSSOM_Selector *selector;
  CSSOM_CSSStyleDeclaration *style;

  cssRule = (CSSOM_CSSStyleRule*)CSSOM_malloc(sizeof(CSSOM_CSSStyleRule));
  if (cssRule == NULL) return NULL;

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSStyleRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_STYLE_RULE);
  cssRule->selector = NULL;
  cssRule->style = NULL;

  selector = CSSOM_Selector__alloc((CSSOM_CSSRule*)cssRule, selectors);
  if (selector == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }
  cssRule->selector = selector;

  style = CSSOM_CSSStyleDeclaration__alloc((CSSOM_CSSRule*)cssRule);
  if (style == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }
  cssRule->style = style;

  return cssRule;
}



CSSOM_Selector* CSSOM_CSSStyleRule__selector(
  const CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->selector;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(
  const CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->style;
}



const char* CSSOM_CSSStyleRule_selectorText(
  const CSSOM_CSSStyleRule *cssRule)
{
  return CSSOM_Selector_selectorText(cssRule->selector);
}



void CSSOM_CSSStyleRule_setSelectorText(CSSOM_CSSStyleRule *cssRule,
  const char * selectorText)
{
  CSSOM_Selector_setSelectorText(cssRule->selector, selectorText);
}



/**
 * CSSMediaRule
 */

struct _CSSOM_CSSMediaRule {
  CSSOM_CSSRule super;
  CSSOM_MediaList *media;
  CSSOM_CSSRuleList *cssRules;
};



static void CSSMediaRule_free(CSSOM_CSSMediaRule *cssRule) {
  CSSOM_MediaList_release(cssRule->media);
  CSSOM_Sequence_release(cssRule->cssRules);
}



static void CSSMediaRule_swap(
  CSSOM_CSSMediaRule *lhs, CSSOM_CSSMediaRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->media, rhs->media);
  SWAP(lhs->cssRules, rhs->cssRules);
}



static struct _CSSOM_CSSRule_vtable CSSMediaRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSMediaRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSMediaRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_mediaRule
};



CSSOM_CSSMediaRule* CSSOM_CSSMediaRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_MediaQuery *mediaQuery[])
{
  CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSMediaRule *cssRule;
  CSSOM_MediaList *media;

  cssRules = CSSOM_CSSRuleList__alloc();
  if (cssRules == NULL) return NULL;

  cssRule = (CSSOM_CSSMediaRule*)CSSOM_malloc(sizeof(CSSOM_CSSMediaRule));
  if (cssRule == NULL) {
    CSSOM_Sequence_release(cssRules);
    return NULL;
  }

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSMediaRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_MEDIA_RULE);

  cssRule->cssRules = cssRules;
  cssRule->media = NULL;



  media = CSSOM_MediaList__alloc((CSSOM_CSSRule*)cssRule, mediaQuery);
  if (media == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  cssRule->media = media;

  return cssRule;
}



CSSOM_CSSRuleList* CSSOM_CSSMediaRule_cssRules(
  const CSSOM_CSSMediaRule *cssRule)
{
  return cssRule->cssRules;
}



unsigned long CSSOM_CSSMediaRule_insertRule(CSSOM_CSSMediaRule * cssRule,
  const char * rule, unsigned long index)
{
  CSSOM_CSSRule *newCSSRule;
  const CSSOM *cssom;
  size_t size;

  size = CSSOM_CSSRuleList_length(cssRule->cssRules);
  cssom = CSSOM_CSSStyleSheet__cssom(
    ((CSSOM_CSSRule*)cssRule)->parentStyleSheet);
  if (index > size) {
    CSSOM__indexSizeErr(cssom);
    return (unsigned long)-1;
  }

  newCSSRule = CSSOM__parseRule(cssom, ((CSSOM_CSSRule*)cssRule)->parentRule,
    ((CSSOM_CSSRule*)cssRule)->parentStyleSheet, rule, strlen(rule));
  if (newCSSRule == NULL) return (unsigned long)-1;

  if (!CSSOM_CSSRuleList__testHierarchy(cssRule->cssRules, index, newCSSRule)) {
    CSSOM_CSSRule_release(newCSSRule);
    CSSOM__hierarchyRequestErr(cssom);
    return (unsigned long)-1;
  }

  CSSOM_native_free(((CSSOM_CSSRule*)cssRule)->cssText);
  ((CSSOM_CSSRule*)cssRule)->cssText = NULL;
  if (index != size) {
    if (CSSOM_Sequence__insert(cssRule->cssRules, index, newCSSRule) == NULL) {
      CSSOM_CSSRule_release(newCSSRule);
      return (unsigned long)-1;
    }
  } else {
    if (CSSOM_Sequence__append(cssRule->cssRules, newCSSRule) == NULL) {
      CSSOM_CSSRule_release(newCSSRule);
      return (unsigned long)-1;
    }
  }

  return index;
}



void CSSOM_CSSMediaRule_deleteRule(CSSOM_CSSMediaRule * cssRule,
  unsigned long index)
{
  const CSSOM *cssom;
  CSSOM_CSSRule *at;

  cssom = CSSOM_CSSStyleSheet__cssom(
    ((CSSOM_CSSRule*)cssRule)->parentStyleSheet);
  if (index >= CSSOM_CSSRuleList_length(cssRule->cssRules)) {
    CSSOM__indexSizeErr(cssom);
    return;
  }

  CSSOM_native_free(((CSSOM_CSSRule*)cssRule)->cssText);
  ((CSSOM_CSSRule*)cssRule)->cssText = NULL;
  at = CSSOM_CSSRuleList_at(cssRule->cssRules, index);
  CSSOM_CSSRule_release(at);
  CSSOM_Sequence__remove(cssRule->cssRules, index);
}



void CSSOM_CSSMediaRule_setMedia(CSSOM_CSSMediaRule *cssRule,
  const char *media)
{
  CSSOM_MediaList_setMediaText(cssRule->media, media);
}



CSSOM_MediaList* CSSOM_CSSMediaRule_media(const CSSOM_CSSMediaRule *cssRule) {
  return cssRule->media;
}



/**
 * CSSNamespaceRule
 */

struct _CSSOM_CSSNamespaceRule {
  CSSOM_CSSRule super;
  const SAC_STRING prefix;
  const SAC_STRING uri;
};



static void CSSNamespaceRule_free(
  CSSOM_CSSNamespaceRule *cssRule CSSOM_UNUSED)
{}



static void CSSNamespaceRule_swap(
  CSSOM_CSSNamespaceRule *lhs, CSSOM_CSSNamespaceRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->prefix, rhs->prefix);
  SWAP(lhs->uri, rhs->uri);
}



static struct _CSSOM_CSSRule_vtable CSSNamespaceRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSNamespaceRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSNamespaceRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_namespaceRule
};



CSSOM_CSSNamespaceRule* CSSOM_CSSNamespaceRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  CSSOM_CSSNamespaceRule *cssRule;

  cssRule = (CSSOM_CSSNamespaceRule*)CSSOM_malloc(
    sizeof(CSSOM_CSSNamespaceRule));
  if (cssRule == NULL) return NULL;

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSNamespaceRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_NAMESPACE_RULE);

  cssRule->prefix = prefix;
  cssRule->uri = uri;

  return cssRule;
}



const char * CSSOM_CSSNamespaceRule_namespaceURI(
  const CSSOM_CSSNamespaceRule * cssRule)
{
  return cssRule->uri;
}



const char * CSSOM_CSSNamespaceRule_prefix(
  const CSSOM_CSSNamespaceRule * cssRule)
{
  return cssRule->prefix;
}



/**
 * CSSPageRule
 */

struct _CSSOM_CSSPageRule {
  CSSOM_CSSRule super;
  CSSOM_Selector *selector;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSPageRule_free(CSSOM_CSSPageRule *cssRule) {
  CSSOM_CSSStyleDeclaration_release(cssRule->style);
  CSSOM_Selector_release(cssRule->selector);
}



static void CSSPageRule_swap(
  CSSOM_CSSPageRule *lhs, CSSOM_CSSPageRule *rhs)
{
  CSSRule_swap_impl((CSSOM_CSSRule*)lhs, (CSSOM_CSSRule*)rhs);
  SWAP(lhs->selector, rhs->selector);
  SWAP(lhs->style, rhs->style);
}



static struct _CSSOM_CSSRule_vtable CSSPageRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSPageRule_free,
  (void(*)(CSSOM_CSSRule*, CSSOM_CSSRule*))&CSSPageRule_swap,
  (int (*)(FILE*, const CSSOM_CSSRule*))&CSSOM_CSSEmitter_pageRule
};



CSSOM_CSSPageRule* CSSOM_CSSPageRule__alloc(
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *parentStyleSheet,
  const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;
  CSSOM_Selector *selector;
  CSSOM_CSSStyleDeclaration *style;

  cssRule = (CSSOM_CSSPageRule*)CSSOM_malloc(sizeof(CSSOM_CSSPageRule));
  if (cssRule == NULL) return NULL;

  CSSRule_ctor((CSSOM_CSSRule*)cssRule, &CSSPageRule_vtable,
    parentRule, parentStyleSheet, CSSOM_CSSRule_PAGE_RULE);
  cssRule->selector = NULL;
  cssRule->style = NULL;

  selector = CSSOM_PageSelector__alloc(cssRule, selectors);
  if (selector == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }
  cssRule->selector = selector;

  style = CSSOM_CSSStyleDeclaration__alloc((CSSOM_CSSRule*)cssRule);
  if (style == NULL) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }
  cssRule->style = style;

  return cssRule;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSPageRule_style(
  const CSSOM_CSSPageRule *cssRule)
{
  return cssRule->style;
}



CSSOM_Selector* CSSOM_CSSPageRule__selector(const CSSOM_CSSPageRule *cssRule) {
  return cssRule->selector;
}



const char* CSSOM_CSSPageRule_selectorText(
  const CSSOM_CSSPageRule *cssRule)
{
  return CSSOM_Selector_selectorText(cssRule->selector);
}



void CSSOM_CSSPageRule_setSelectorText(CSSOM_CSSPageRule *cssRule,
  const char * selectorText)
{
  CSSOM_Selector_setSelectorText(cssRule->selector, selectorText);
}
