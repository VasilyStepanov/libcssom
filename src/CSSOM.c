#include "CSSOM.h"

#include "CSSProperty.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "gcc.h"
#include "memory.h"

#include <cssom/CSSRule.h>

#include <sacc.h>

#include <string.h>
#include <assert.h>



struct _CSSOM {
  size_t handles;
  char * * properties;
  CSSOM_FSMTable_CSSProperty * table;
  SAC_ErrorHandler errorHandler;
  void * userData;
};



struct _CSSOM_CSSStyleSheetStack {
  const CSSOM * cssom;
  CSSOM_CSSStyleSheet * styleSheet;
  CSSOM_CSSRule * cssRule;
};



struct _CSSOM_CSSStyleRuleStack {
  const CSSOM * cssom;
  CSSOM_CSSStyleRule * cssRule;
};



static int cssStyleSheet_propertyHandler(void *userData,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  struct _CSSOM_CSSStyleSheetStack *stack;
  CSSOM_CSSStyleDeclaration *cssRule;
  CSSOM_CSSProperty *property;
  
  stack = (struct _CSSOM_CSSStyleSheetStack*)userData;
  cssRule = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)stack->cssRule);

  property = CSSOM_CSSStyleDeclaration__setProperty(cssRule,
    propertyName, value, important);
  if (property == NULL) return 1;

  return 0;
}



static int cssStyleSheet_startStyleHandler(void *userData,
  const SAC_Selector *selectors[])
{
  struct _CSSOM_CSSStyleSheetStack *stack;
  CSSOM_CSSRule *cssRule;
  
  stack = (struct _CSSOM_CSSStyleSheetStack*)userData;

  cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(
    stack->cssom->table, selectors);
  if (cssRule == NULL) return 1;

  if (CSSOM_CSSStyleSheet__append(stack->styleSheet, cssRule) == NULL) {
    CSSOM_CSSRule_release(cssRule);
    return 1;
  }

  stack->cssRule = cssRule;

  return 0;
}



static int cssStyleSheet_endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_CSSStyleSheetStack *stack;

  stack = (struct _CSSOM_CSSStyleSheetStack*)userData;

  stack->cssRule = NULL;

  return 0;
}



static void freeProperties(char **properties) {
  char **it;

  if (properties == (char**)CSSOM_CSSProperties) return;

  for (it = properties; *it != NULL; ++it)
    CSSOM_free(*it);

  CSSOM_free(properties);
}



static void errorHandler(void * userData, const SAC_Error * error) {
  struct _CSSOM_CSSStyleSheetStack *stack;
  const CSSOM * cssom;
  
  stack = (struct _CSSOM_CSSStyleSheetStack*)userData;
  cssom = stack->cssom;

  if (cssom->errorHandler != NULL)
    cssom->errorHandler(cssom->userData, error);
}



CSSOM* CSSOM_create(const char * * properties) {
  char **propertiesCopy;
  CSSOM_FSMTable_CSSProperty *table;
  CSSOM *cssom;

  if (properties != CSSOM_CSSProperties) {
    char **itlhs;
    const char **itrhs;
    size_t size;

    for (itrhs = properties, size = 0; *itrhs != NULL; ++itrhs, ++size);

    propertiesCopy = (char**)CSSOM_malloc(sizeof(char*) * (size + 1));
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
    CSSOM_CSSProperty_release);
  if (table == NULL) {
    freeProperties(propertiesCopy);
    return NULL;
  }

  cssom = (CSSOM*)CSSOM_malloc(sizeof(CSSOM));
  if (cssom == NULL) {
    freeProperties(propertiesCopy);
    CSSOM_FSMTable_CSSProperty_free(table);
    return NULL;
  }

  cssom->handles = 1;
  cssom->properties = propertiesCopy;
  cssom->table = table;
  cssom->errorHandler = NULL;
  cssom->userData = NULL;

  return cssom;
}



void CSSOM_acquire(CSSOM *cssom) {
  ++cssom->handles;
}



void CSSOM_release(CSSOM *cssom) {
  assert(cssom->handles > 0);
  --cssom->handles;
  if (cssom->handles > 0) return;

  CSSOM_FSMTable_CSSProperty_free(cssom->table);
  freeProperties(cssom->properties);
  CSSOM_free(cssom);
}



void * CSSOM_getUserData(const CSSOM * cssom) {
  return cssom->userData;
}



void CSSOM_setUserData(CSSOM * cssom, void * userData) {
  cssom->userData = userData;
}



void CSSOM_setErrorHandler(CSSOM * cssom, SAC_ErrorHandler handler) {
  cssom->errorHandler = handler;
}



CSSOM_CSSStyleSheet* CSSOM_parseCSSStyleSheet(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_CSSStyleSheetStack stack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  styleSheet = CSSOM_CSSStyleSheet__alloc(parser);
  if (styleSheet == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  stack.styleSheet = styleSheet;
  stack.cssRule = NULL;
  stack.cssom = cssom;

  SAC_SetStyleHandler(parser,
    cssStyleSheet_startStyleHandler, cssStyleSheet_endStyleHandler);
  SAC_SetPropertyHandler(parser, cssStyleSheet_propertyHandler);
  SAC_SetUserData(parser, &stack);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseStyleSheet(parser, cssText, len);

  return styleSheet;
}



static int cssStyleRule_propertyHandler(void *userData,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  struct _CSSOM_CSSStyleRuleStack *stack;
  CSSOM_CSSStyleDeclaration *cssRule;
  CSSOM_CSSProperty *property;
  
  stack = (struct _CSSOM_CSSStyleRuleStack*)userData;
  cssRule = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)stack->cssRule);

  property = CSSOM_CSSStyleDeclaration__setProperty(cssRule,
    propertyName, value, important);
  if (property == NULL) return 1;

  return 0;
}



static int cssStyleRule_startStyleHandler(void *userData,
  const SAC_Selector *selectors[])
{
  struct _CSSOM_CSSStyleRuleStack *stack;
  CSSOM_CSSStyleRule *cssRule;
  
  stack = (struct _CSSOM_CSSStyleRuleStack*)userData;

  cssRule = CSSOM_CSSStyleRule__alloc(stack->cssom->table, selectors);
  if (cssRule == NULL) return 1;

  assert(stack->cssRule == NULL);
  stack->cssRule = cssRule;

  return 0;
}



CSSOM_CSSStyleRule* CSSOM_parseCSSStyleRule(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  struct _CSSOM_CSSStyleRuleStack stack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack.cssRule = NULL;
  stack.cssom = cssom;

  SAC_SetStyleHandler(parser,
    cssStyleRule_startStyleHandler, NULL);
  SAC_SetPropertyHandler(parser, cssStyleRule_propertyHandler);
  SAC_SetUserData(parser, &stack);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseRule(parser, cssText, len);

  return stack.cssRule;
}
