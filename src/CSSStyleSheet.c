#include "CSSStyleSheet.h"
#include <cssom/CSSStyleSheet.h>

#include "List_CSSRule.h"
#include "CSSRuleList.h"
#include "CSSRule.h"

#include <cssom/types.h>

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



static const CSSOM_CSSRuleList* DynamicCSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  size_t size;
  CSSOM_CSSRuleList *cssRules;
  CSSOM_ListIter_CSSRule lit;
  CSSOM_CSSRuleList *vit;

  size = CSSOM_List_CSSRule_size(styleSheet->_cssRules);

  cssRules = (CSSOM_CSSRuleList*)malloc(sizeof(CSSOM_CSSRuleList) * (size + 1));
  if (cssRules == NULL) return NULL;

  for (lit = CSSOM_List_CSSRule_begin(styleSheet->_cssRules), vit = cssRules;
    lit != CSSOM_List_CSSRule_end(styleSheet->_cssRules);
    lit = CSSOM_ListIter_CSSRule_next(lit), ++vit)
  {
    *vit = *lit;
  }
  cssRules[size] = NULL;

  free(styleSheet->cssRules);
  ((CSSOM_CSSStyleSheet*)styleSheet)->cssRules = cssRules;
  return styleSheet->cssRules;
}



static CSSOM_CSSRule* DynamicCSSStyleSheet_append(
  CSSOM_CSSStyleSheet *styleSheet, CSSOM_CSSRule *cssRule)
{
  if (CSSOM_List_CSSRule_append(styleSheet->_cssRules, cssRule) == NULL)
    return NULL;
  return cssRule;
}



static struct _CSSOM_CSSStyleSheet_vtable DynamicCSSStyleSheet_vtable = {
  &DynamicCSSStyleSheet_cssRules,
  &DynamicCSSStyleSheet_append
};



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
