#include "CSSStyleSheet.h"
#include <cssom/CSSStyleSheet.h>

#include "List_CSSRule.h"
#include "CSSRuleList.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "gcc.h"

#include <sacc.h>

#include <stdlib.h>
#include <string.h>



struct _CSSOM_CSSStyleSheet_vtable {
  const CSSOM_CSSRuleList* (*cssRules)(const CSSOM_CSSStyleSheet *styleSheet);
  CSSOM_CSSRule* (*append)(CSSOM_CSSStyleSheet *styleSheet,
    CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSStyleSheet {
  struct _CSSOM_CSSStyleSheet_vtable *vtable;
  SAC_Parser sac;
  CSSOM_List_CSSRule *_cssRules;
  CSSOM_CSSRuleList *cssRules;
};



struct _CSSOM_ParserStack {
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule *curCSSRule;
};



static int startStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc();
  if (cssRule == NULL) return 1;

  if (CSSOM_CSSStyleSheet_append(stack->styleSheet, cssRule) == NULL) {
    CSSOM_CSSRule_free(cssRule);
    return 1;
  }

  stack->curCSSRule = cssRule;

  return 0;
}



static int endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;

  stack = (struct _CSSOM_ParserStack*)userData;

  stack->curCSSRule = NULL;

  return 0;
}



static int propertyHandler(void *userData,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSStyleDeclaration *style;
  
  stack = (struct _CSSOM_ParserStack*)userData;
  style = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)stack->curCSSRule);

  CSSOM_CSSStyleDeclaration_append(style, propertyName, value, important);

  return 0;
}



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
  SAC_Parser sac;
  CSSOM_List_CSSRule *_cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  sac = SAC_CreateParser();
  if (sac == NULL) return NULL;

  _cssRules = CSSOM_List_CSSRule_alloc();
  if (_cssRules == NULL) {
    SAC_DisposeParser(sac);
    return NULL;
  }

  styleSheet = (CSSOM_CSSStyleSheet*)malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    SAC_DisposeParser(sac);
    CSSOM_List_CSSRule_free(_cssRules);
    return NULL;
  }

  SAC_SetStyleHandler(sac, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(sac, propertyHandler);

  styleSheet->vtable = &DynamicCSSStyleSheet_vtable;
  styleSheet->sac = sac;
  styleSheet->_cssRules = _cssRules;
  styleSheet->cssRules = NULL;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet) {
  CSSOM_ListIter_CSSRule it;

  if (styleSheet == NULL) return;

  CSSOM_CSSRuleList_free(styleSheet->cssRules);

  for (it = CSSOM_List_CSSRule_begin(styleSheet->_cssRules);
    it != CSSOM_List_CSSRule_end(styleSheet->_cssRules);
    it = CSSOM_ListIter_CSSRule_next(it))
  {
    CSSOM_CSSRule_free(*it);
  }
  CSSOM_List_CSSRule_free(styleSheet->_cssRules);

  SAC_DisposeParser(styleSheet->sac);

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



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_parse(const char *cssText) { 
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack parserStack;

  styleSheet = CSSOM_CSSStyleSheet_alloc();
  if (styleSheet == NULL) return NULL;

  parserStack.styleSheet = styleSheet;
  parserStack.curCSSRule = NULL;
  SAC_SetUserData(styleSheet->sac, &parserStack);
  SAC_ParseStyleSheet(styleSheet->sac, cssText, strlen(cssText));

  return parserStack.styleSheet;
}
