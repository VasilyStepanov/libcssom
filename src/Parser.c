#include <cssom/Parser.h>

#include "CSSStyleSheet.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "List_CSSRule.h"

#include <sacc.h>

#include <stdlib.h>
#include <string.h>

#include "gcc.h"
#include <stdio.h>



struct _CSSOM_Parser {
  SAC_Parser sac;
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
  const CSSOM_CSSStyleDeclaration *style;
  
  stack = (struct _CSSOM_ParserStack*)userData;
  style = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)stack->curCSSRule);

  CSSOM_CSSStyleDeclaration_append((CSSOM_CSSStyleDeclaration*)style,
    propertyName, value, important);

  return 0;
}



CSSOM_Parser* CSSOM_Parser_alloc() {
  CSSOM_Parser *parser;
  SAC_Parser sac;

  sac = SAC_CreateParser();
  SAC_SetStyleHandler(sac, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(sac, propertyHandler);

  if (sac == NULL) return NULL;
 
  parser = malloc(sizeof(CSSOM_Parser));
  if (parser == NULL) {
    SAC_DisposeParser(sac);
    return NULL;
  }

  parser->sac = sac;
 
  return parser;
}



void CSSOM_Parser_free(CSSOM_Parser *parser) {
  SAC_DisposeParser(parser->sac);
  free(parser);
}



CSSOM_CSSStyleSheet* CSSOM_Parser_parseStyleSheet(CSSOM_Parser *parser,
  const char *cssText)
{ 
  struct _CSSOM_ParserStack parserStack;

  parserStack.styleSheet = CSSOM_CSSStyleSheet_alloc();
  parserStack.curCSSRule = NULL;
  if (parserStack.styleSheet == NULL) return NULL;
  SAC_SetUserData(parser->sac, &parserStack);
  SAC_ParseStyleSheet(parser->sac, cssText, strlen(cssText));

  return parserStack.styleSheet;
}
