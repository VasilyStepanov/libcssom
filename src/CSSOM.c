#include "CSSOM.h"

#include "CSSProperty.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "gcc.h"

#include <sacc.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>



struct _CSSOM {
  size_t handles;
  char **properties;
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
  CSSOM_CSSProperty *property;
  
  stack = (struct _CSSOM_ParserStack*)userData;
  style = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)stack->curCSSRule);

  property = CSSOM_CSSStyleDeclaration__setProperty(style,
    propertyName, value, important);
  if (property == NULL) return 1;

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

  cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(stack->table);
  if (cssRule == NULL) return 1;

  if (CSSOM_CSSStyleSheet__append(stack->styleSheet, cssRule) == NULL) {
    CSSOM_CSSRule__release(cssRule);
    return 1;
  }

  stack->curCSSRule = cssRule;

  return 0;
}



static void freeProperties(char **properties) {
  char **it;

  if (properties == (char**)CSSOM_CSSProperties) return;

  for (it = properties; *it != NULL; ++it)
    free(*it);

  free(properties);
}



CSSOM* CSSOM_create(const char **properties) {
  char **propertiesCopy;
  CSSOM_FSMTable_CSSProperty *table;
  CSSOM *cssom;

  if (properties != CSSOM_CSSProperties) {
    char **itlhs;
    const char **itrhs;
    size_t size;

    for (itrhs = properties, size = 0; *itrhs != NULL; ++itrhs, ++size);

    propertiesCopy = (char**)malloc(sizeof(char*) * (size + 1));
    if (propertiesCopy == NULL) return NULL;

    for (
      itrhs = properties, itlhs = propertiesCopy;
      *itrhs != NULL;
      ++itrhs, ++itlhs)
    {
      *itlhs = strdup(*itrhs);
      if (*itlhs == NULL) {
        freeProperties(propertiesCopy);
        return NULL;
      }
    }
  } else {
    propertiesCopy = (char**)properties;
  }

  table = CSSOM_FSMTable_CSSProperty_alloc(properties, 
    CSSOM_CSSProperty__release);
  if (table == NULL) {
    freeProperties(propertiesCopy);
    return NULL;
  }

  cssom = (CSSOM*)malloc(sizeof(CSSOM));
  if (cssom == NULL) {
    freeProperties(propertiesCopy);
    CSSOM_FSMTable_CSSProperty_free(table);
    return NULL;
  }

  cssom->handles = 1;
  cssom->properties = propertiesCopy;
  cssom->table = table;

  return cssom;
}



void CSSOM_dispose(CSSOM *cssom) {
  CSSOM__release(cssom);
}



void CSSOM__acquire(CSSOM *cssom) {
  ++cssom->handles;
}



void CSSOM__release(CSSOM *cssom) {
  assert(cssom->handles > 0);
  --cssom->handles;
  if (cssom->handles > 0) return;

  CSSOM_FSMTable_CSSProperty_free(cssom->table);
  freeProperties(cssom->properties);
  free(cssom);
}



CSSOM_CSSStyleSheet* CSSOM_parse(CSSOM *cssom, const char *cssText) { 
  SAC_Parser parser;
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack parserStack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  styleSheet = CSSOM_CSSStyleSheet__alloc(parser);
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
