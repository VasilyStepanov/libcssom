#include "Selector.h"

#include "CSSEmitter.h"
#include "CSSStyleSheet.h"
#include "CSSOM.h"
#include "Deque_void.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSRule.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



struct _CSSOM_Selector_vtable {
  const char* (*selectorText)(const CSSOM_Selector *selector);
  void (*setSelectorText)(CSSOM_Selector *selector, const char *selectorText);
};



struct _CSSOM_Selector {
  struct _CSSOM_Selector_vtable *vtable;
  size_t handles;
  const CSSOM *cssom;
  SAC_Parser parser;
  CSSOM_CSSRule *parentRule;
  char *selectorText;
  const SAC_Selector **selectors;
};



static void Selector_swap(CSSOM_Selector *lhs, CSSOM_Selector *rhs) {
  SWAP(lhs->parser, rhs->parser);
  SWAP(lhs->parentRule, rhs->parentRule);
  SWAP(lhs->selectorText, rhs->selectorText);
  SWAP(lhs->selectors, rhs->selectors);
}



static void Selector_ctor(CSSOM_Selector *selector,
  struct _CSSOM_Selector_vtable *vtable, const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const SAC_Selector *selectors[])
{
  selector->vtable = vtable;
  selector->handles = 1;
  selector->cssom = cssom;
  selector->parser = NULL;
  selector->parentRule = parentRule;
  selector->selectorText = NULL;
  selector->selectors = selectors;
}



static const char* Selector_selectorText(const CSSOM_Selector *selector) {
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(selector->selectorText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_selector(out, selector) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_Selector*)selector)->selectorText = buf;

  return selector->selectorText;
}



static void Selector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  CSSOM_Selector *newSelector;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(selector->parentRule));
  newSelector = CSSOM__parseSelector(cssom, selector->parentRule,
    selectorText, strlen(selectorText));
  if (newSelector == NULL) return;

  Selector_swap(selector, newSelector);

  CSSOM_Selector_release(newSelector);
}



static struct _CSSOM_Selector_vtable Selector_vtable = {
  Selector_selectorText,
  Selector_setSelectorText
};



CSSOM_Selector* CSSOM_Selector__alloc(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const SAC_Selector *selectors[])
{
  CSSOM_Selector *selector;

  selector = (CSSOM_Selector*)CSSOM_malloc(sizeof(CSSOM_Selector));
  if (selector == NULL) return NULL;
  
  Selector_ctor(selector, &Selector_vtable, cssom, parentRule, selectors);

  return selector;
}



static const char* PageSelector_selectorText(const CSSOM_Selector *selector) {
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(selector->selectorText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_pageSelector(out, selector) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_Selector*)selector)->selectorText = buf;

  return selector->selectorText;
}



static void PageSelector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  CSSOM_Selector *newSelector;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(selector->parentRule));
  newSelector = CSSOM__parsePageSelector(cssom, selector->parentRule,
    selectorText, strlen(selectorText));
  if (newSelector == NULL) return;

  Selector_swap(selector, newSelector);

  CSSOM_Selector_release(newSelector);
}



static struct _CSSOM_Selector_vtable PageSelector_vtable = {
  PageSelector_selectorText,
  PageSelector_setSelectorText
};



CSSOM_Selector* CSSOM_PageSelector__alloc(const CSSOM *cssom,
  CSSOM_CSSPageRule *parentRule, const SAC_Selector *selectors[])
{
  CSSOM_Selector *selector;

  selector = (CSSOM_Selector*)CSSOM_malloc(sizeof(CSSOM_Selector));
  if (selector == NULL) return NULL;
  
  Selector_ctor(selector, &PageSelector_vtable,
    cssom, (CSSOM_CSSRule*)parentRule, selectors);

  return selector;
}



void CSSOM_Selector_acquire(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  ++selector->handles;
  CSSOM_CSSRule_acquire(selector->parentRule);
}



void CSSOM_Selector_release(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  assert(selector->handles > 0);
  --selector->handles;
  if (selector->handles > 0) {
    CSSOM_CSSRule_release(selector->parentRule);
    return;
  }

  CSSOM_native_free(selector->selectorText);
  SAC_DisposeParser(selector->parser);
  CSSOM_free(selector);
}



CSSOM_CSSRule* CSSOM_Selector_parentRule(const CSSOM_Selector *selector) {
  return selector->parentRule;
}



const char* CSSOM_Selector_selectorText(const CSSOM_Selector *selector) {
  return selector->vtable->selectorText(selector);
}



void CSSOM_Selector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  selector->vtable->setSelectorText(selector, selectorText);
}



const SAC_Selector** CSSOM_Selector__selectors(const CSSOM_Selector *selector) {
  return selector->selectors;
}



void CSSOM_Selector__keepParser(CSSOM_Selector *selector,
  SAC_Parser parser)
{
  assert(selector->parser == NULL);
  selector->parser = parser;
}



void CSSOM_Selector_select(CSSOM_Selector *selector, void *root,
  void *selection)
{
  const CSSOM_DOMAPI *domapi;
  CSSOM_Deque_void *deque;

  deque = CSSOM_Deque_void_alloc(0);

  domapi = CSSOM_getDOMAPI(selector->cssom);

  CSSOM_Deque_void_append(deque, root);
  while (CSSOM_Deque_void_size(deque) != 0) {
    void *child;
    void *top = *CSSOM_Deque_void_back(deque);
    CSSOM_Deque_void_pop_back(deque);

    domapi->Selection_append(selection, top);

    for (
      child = domapi->Node_children(top);
      child != NULL;
      child = domapi->Node_next(child))
    {
      CSSOM_Deque_void_append(deque, child);
    }
  }
}
