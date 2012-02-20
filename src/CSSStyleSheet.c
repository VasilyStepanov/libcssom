#include "CSSStyleSheet.h"
#include <cssom/CSSStyleSheet.h>

#include "List_CSSRule.h"
#include "CSSRuleList.h"
#include "CSSRule.h"

#include <stdlib.h>



struct _CSSOM_CSSStyleSheet_vtable {
  const CSSOM_CSSRuleList* (*cssRules)(const CSSOM_CSSStyleSheet *styleSheet);
  CSSOM_CSSRule* (*append)(CSSOM_CSSStyleSheet *styleSheet,
    CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSStyleSheet {
  struct _CSSOM_CSSStyleSheet_vtable *vtable;
  CSSOM_List_CSSRule *_cssRules;
  CSSOM_CSSRuleList *cssRules;
};



static const CSSOM_CSSRuleList* StaticCSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet);

static CSSOM_CSSRule* StaticCSSStyleSheet_append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule);

static struct _CSSOM_CSSStyleSheet_vtable StaticCSSStyleSheet_vtable = {
  &StaticCSSStyleSheet_cssRules,
  &StaticCSSStyleSheet_append
};



static const CSSOM_CSSRuleList* DynamicCSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet);

static CSSOM_CSSRule* DynamicCSSStyleSheet_append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule);

static struct _CSSOM_CSSStyleSheet_vtable DynamicCSSStyleSheet_vtable = {
  &DynamicCSSStyleSheet_cssRules,
  &DynamicCSSStyleSheet_append
};



static const CSSOM_CSSRuleList* StaticCSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->cssRules;
}



static CSSOM_CSSRule* StaticCSSStyleSheet_append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule)
{
  ((CSSOM_CSSStyleSheet*)styleSheet)->vtable = &DynamicCSSStyleSheet_vtable;
  return CSSOM_CSSStyleSheet_append(styleSheet, cssRule);
}



static const CSSOM_CSSRuleList* DynamicCSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  CSSOM_CSSRuleList *cssRules;

  cssRules = CSSOM_CSSRuleList_realloc(styleSheet->cssRules,
    styleSheet->_cssRules);
  if (cssRules == NULL) return NULL;

  ((CSSOM_CSSStyleSheet*)styleSheet)->cssRules = cssRules;

  ((CSSOM_CSSStyleSheet*)styleSheet)->vtable = &StaticCSSStyleSheet_vtable;
  return CSSOM_CSSStyleSheet_cssRules(styleSheet);
}



static CSSOM_CSSRule* DynamicCSSStyleSheet_append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule)
{
  if (CSSOM_List_CSSRule_append(styleSheet->_cssRules, cssRule) ==
    CSSOM_List_CSSRule_end(styleSheet->_cssRules)) return NULL;
  return cssRule;
}



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_alloc() {
  CSSOM_List_CSSRule *_cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  _cssRules = CSSOM_List_CSSRule_alloc();
  if (_cssRules == NULL) return NULL;

  styleSheet = (CSSOM_CSSStyleSheet*)malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    CSSOM_List_CSSRule_free(_cssRules);
    return NULL;
  }

  styleSheet->vtable = &DynamicCSSStyleSheet_vtable;
  styleSheet->_cssRules = _cssRules;
  styleSheet->cssRules = NULL;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet) {
  CSSOM_ListIter_CSSRule it;

  if (styleSheet == NULL) return;

  for (it = CSSOM_List_CSSRule_begin(styleSheet->_cssRules);
    it != CSSOM_List_CSSRule_end(styleSheet->_cssRules);
    it = CSSOM_ListIter_CSSRule_next(it))
  {
    CSSOM_CSSRule_free(*it);
  }

  CSSOM_List_CSSRule_free(styleSheet->_cssRules);
  CSSOM_CSSRuleList_free(styleSheet->cssRules);
  free(styleSheet);
}



CSSOM_CSSRule* CSSOM_CSSStyleSheet_append(CSSOM_CSSStyleSheet *styleSheet,
  CSSOM_CSSRule *cssRule)
{
  return styleSheet->vtable->append(styleSheet, cssRule);
}



const CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->vtable->cssRules(styleSheet);
}
