#include <cssom/Parser.h>

#include "CSSStyleSheet.h"
#include "CSSRule.h"
#include "List_CSSRule.h"

#include <cssom/types.h>

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
  CSSOM_CSSRule *rule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  rule = CSSOM_CSSRule_alloc(CSSOM_STYLE_RULE);
  if (rule == NULL) return 1;

  if (CSSOM_CSSStyleSheet_append(stack->styleSheet, rule) == NULL) {
    CSSOM_CSSRule_free(rule);
    return 1;
  }

  return 0;
}



static int endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  
  stack = (struct _CSSOM_ParserStack*)userData;
  return 0;
}



CSSOM_Parser* CSSOM_Parser_alloc() {
  CSSOM_Parser *parser;
  SAC_Parser sac;

  sac = SAC_CreateParser();
  SAC_SetStyleHandler(sac, startStyleHandler, endStyleHandler);

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
  if (parserStack.styleSheet == NULL) return NULL;
  SAC_SetUserData(parser->sac, &parserStack);
  SAC_ParseStyleSheet(parser->sac, cssText, strlen(cssText));

  return parserStack.styleSheet;
}
