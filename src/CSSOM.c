#include <cssom/CSSOM.h>

#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "gcc.h"

#include <sacc.h>

#include <stdlib.h>
#include <string.h>



struct _CSSOM {
  CSSOM_FSMTable_CSSProperty *table;
};



struct _CSSOM_ParserStack {
  const CSSOM_FSMTable_CSSProperty *table;
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule *curCSSRule;
};



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



static int endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;

  stack = (struct _CSSOM_ParserStack*)userData;

  stack->curCSSRule = NULL;

  return 0;
}



static int startStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc(stack->table);
  if (cssRule == NULL) return 1;

  if (CSSOM_CSSStyleSheet_append(stack->styleSheet, cssRule) == NULL) {
    CSSOM_CSSRule_free(cssRule);
    return 1;
  }

  stack->curCSSRule = cssRule;

  return 0;
}



CSSOM* CSSOM_create(const char **properties) {
  CSSOM_FSMTable_CSSProperty *table;
  CSSOM *cssom;

  table = CSSOM_FSMTable_CSSProperty_alloc(properties);
  if (table == NULL) return NULL;

  cssom = (CSSOM*)malloc(sizeof(CSSOM));
  if (cssom == NULL) {
    CSSOM_FSMTable_CSSProperty_free(table);
    return NULL;
  }

  cssom->table = table;

  return cssom;
}



void CSSOM_dispose(CSSOM *cssom) {
  CSSOM_FSMTable_CSSProperty_free(cssom->table);
  free(cssom);
}



CSSOM_CSSStyleSheet* CSSOM_parse(CSSOM *cssom, const char *cssText) { 
  SAC_Parser parser;
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack parserStack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  styleSheet = CSSOM_CSSStyleSheet_alloc(parser);
  if (styleSheet == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  parserStack.styleSheet = styleSheet;
  parserStack.curCSSRule = NULL;
  parserStack.table = cssom->table;

  SAC_SetStyleHandler(parser,startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, &parserStack);
  SAC_ParseStyleSheet(parser, cssText, strlen(cssText));

  return parserStack.styleSheet;
}
