#include <cssom/CSSOM.h>

#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "gcc.h"

#include <sacc.h>

#include <stdlib.h>
#include <string.h>



struct _CSSOM {
  int dummy;
};



struct _CSSOM_ParserStack {
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

  cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc();
  if (cssRule == NULL) return 1;

  if (CSSOM_CSSStyleSheet_append(stack->styleSheet, cssRule) == NULL) {
    CSSOM_CSSRule_free(cssRule);
    return 1;
  }

  stack->curCSSRule = cssRule;

  return 0;
}



CSSOM* CSSOM_create() {
  CSSOM *cssom;

  cssom = (CSSOM*)malloc(sizeof(CSSOM));
  if (cssom == NULL) return NULL;

  return cssom;
}



void CSSOM_dispose(CSSOM *cssom) {
  free(cssom);
}



CSSOM_CSSStyleSheet* CSSOM_parse(CSSOM *cssom CSSOM_UNUSED,
  const char *cssText)
{ 
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack parserStack;

  styleSheet = CSSOM_CSSStyleSheet_alloc();
  if (styleSheet == NULL) return NULL;

  parserStack.styleSheet = styleSheet;
  parserStack.curCSSRule = NULL;

  SAC_SetStyleHandler(CSSOM_CSSStyleSheet_parser(styleSheet),
    startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(CSSOM_CSSStyleSheet_parser(styleSheet),
    propertyHandler);
  SAC_SetUserData(CSSOM_CSSStyleSheet_parser(styleSheet), &parserStack);
  SAC_ParseStyleSheet(CSSOM_CSSStyleSheet_parser(styleSheet),
    cssText, strlen(cssText));

  return parserStack.styleSheet;
}
