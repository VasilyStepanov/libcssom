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



static void List_CSSRule_cleanup(CSSOM_List_CSSRule *list) {
  CSSOM_ListIter_CSSRule it;

  for (it = CSSOM_List_CSSRule_begin(list);
    it != CSSOM_List_CSSRule_end(list);
    it = CSSOM_ListIter_CSSRule_next(it))
  {
    CSSOM_CSSRule_free(*it);
  }
}



struct _CSSOM_Parser {
  SAC_Parser sac;
};



struct _CSSOM_ParserStack {
  CSSOM_List_CSSRule *cssRules;
  CSSOM_CSSRule *curCSSRule;
};



static void startStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  
  stack = (struct _CSSOM_ParserStack*)userData;
}



static void endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  
  stack = (struct _CSSOM_ParserStack*)userData;
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
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack parserStack;

  parserStack.cssRules = CSSOM_List_CSSRule_alloc();
  SAC_SetUserData(parser->sac, &parserStack);
  SAC_ParseStyleSheet(parser->sac, cssText, strlen(cssText));

  styleSheet = CSSOM_CSSStyleSheet_alloc(parserStack.cssRules);
  if (styleSheet == NULL) {
    List_CSSRule_cleanup(parserStack.cssRules);
    CSSOM_List_CSSRule_free(parserStack.cssRules);
    return NULL;
  }

  CSSOM_List_CSSRule_free(parserStack.cssRules);

  return styleSheet;
}
