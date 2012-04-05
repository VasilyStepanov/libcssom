#include "CSSOM.h"

#include "CSSPageRule.h"
#include "CSSProperty.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "gcc.h"
#include "memory.h"

#include <sacc.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>



struct _CSSOM {
  size_t handles;
  char * * properties;
  CSSOM_FSMTable_CSSProperty * table;
  CSSOM_ErrorHandler errorHandler;
  void * userData;
};



struct _CSSOM_ParserStack {
  const CSSOM * cssom;
  CSSOM_CSSStyleSheet * styleSheet;
  CSSOM_CSSRule * cssRule;
  CSSOM_CSSStyleDeclaration * style;
};



static int propertyHandler(void *userData,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSProperty *property;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  property = CSSOM_CSSStyleDeclaration__setProperty(stack->style,
    propertyName, value, important);
  if (property == NULL) {
    CSSOM_CSSRule__free(stack->cssRule);
    return 1;
  }

  return 0;
}



static int startPageHandler(void *userData,
  const SAC_STRING name, const SAC_STRING pseudoPage)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSPageRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = CSSOM_CSSPageRule__alloc(stack->styleSheet,
    stack->cssom->table, name, pseudoPage);
  if (cssRule == NULL) return 1;

  stack->cssRule = (CSSOM_CSSRule*)cssRule;
  stack->style = CSSOM_CSSPageRule_style(cssRule);

  return 0;
}



static int endPageHandler(void *userData,
  const SAC_STRING name CSSOM_UNUSED, const SAC_STRING pseudoPage CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;

  stack = (struct _CSSOM_ParserStack*)userData;

  if (CSSOM_CSSStyleSheet__append(stack->styleSheet, stack->cssRule) == NULL) {
    CSSOM_CSSRule__free(stack->cssRule);
    return 1;
  }

  stack->style = NULL;
  stack->cssRule = NULL;

  return 0;
}



static int startStyleHandler(void *userData,
  const SAC_Selector *selectors[])
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSStyleRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = CSSOM_CSSStyleRule__alloc(stack->styleSheet,
    stack->cssom->table, selectors);
  if (cssRule == NULL) return 1;

  stack->cssRule = (CSSOM_CSSRule*)cssRule;
  stack->style = CSSOM_CSSStyleRule_style(cssRule);

  return 0;
}



static int endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;

  stack = (struct _CSSOM_ParserStack*)userData;

  if (CSSOM_CSSStyleSheet__append(stack->styleSheet, stack->cssRule) == NULL) {
    CSSOM_CSSRule__free(stack->cssRule);
    return 1;
  }

  stack->style = NULL;
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
  struct _CSSOM_ParserStack *stack;
  const CSSOM * cssom;
  
  stack = (struct _CSSOM_ParserStack*)userData;
  cssom = stack->cssom;

  if (cssom->errorHandler != NULL) {
    CSSOM_Error cssomError;
    cssomError.line = error->line;
    cssomError.column = error->column;
    cssomError.code = error->code;
    cssomError.data = error->data;
    cssom->errorHandler(cssom->userData, &cssomError);
  }
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
    CSSOM_CSSProperty__free);
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



void CSSOM_setErrorHandler(CSSOM * cssom, CSSOM_ErrorHandler handler) {
  cssom->errorHandler = handler;
}



void CSSOM__invalidModificationErr(const CSSOM * cssom) {
  printf("CSSOM_ERROR_INVALID_MODIFICATION_ERR\n");
  if (cssom->errorHandler != NULL) {
    CSSOM_Error error;
    error.line = -1;
    error.column = -1;
    error.code = CSSOM_ERROR_INVALID_MODIFICATION_ERR;
    error.data = "Invalid modification error";
    cssom->errorHandler(cssom->userData, &error);
  }
}



CSSOM_CSSStyleSheet* CSSOM_parse(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_CSSStyleSheet *styleSheet;
  struct _CSSOM_ParserStack stack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  styleSheet = CSSOM_CSSStyleSheet__alloc(cssom, parser);
  if (styleSheet == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  stack.styleSheet = styleSheet;
  stack.cssRule = NULL;
  stack.style = NULL;
  stack.cssom = cssom;

  SAC_SetPageHandler(parser, startPageHandler, endPageHandler);
  SAC_SetStyleHandler(parser, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, &stack);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseStyleSheet(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  return styleSheet;
}



CSSOM_CSSRule* CSSOM__parseCSSRule(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  struct _CSSOM_ParserStack stack;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack.styleSheet = NULL;
  stack.cssRule = NULL;
  stack.style = NULL;
  stack.cssom = cssom;

  SAC_SetPageHandler(parser, startPageHandler, NULL);
  SAC_SetStyleHandler(parser, startStyleHandler, NULL);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, &stack);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseRule(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  return stack.cssRule;
}
