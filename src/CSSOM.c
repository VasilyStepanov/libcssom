#include "CSSOM.h"

#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSProperty.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "ParserState.h"
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
  const SAC_Selector *selectors[])
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSPageRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = CSSOM_CSSPageRule__alloc(stack->styleSheet,
    stack->cssom->table, selectors);
  if (cssRule == NULL) return 1;

  stack->cssRule = (CSSOM_CSSRule*)cssRule;
  stack->style = CSSOM_CSSPageRule_style(cssRule);

  return 0;
}



static int endPageHandler(void *userData,
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



static int startMediaHandler(void *userData,
  const SAC_MediaQuery *media[] CSSOM_UNUSED)
{
  struct _CSSOM_ParserStack *stack;
  CSSOM_CSSMediaRule *cssRule;
  
  stack = (struct _CSSOM_ParserStack*)userData;

  cssRule = CSSOM_CSSMediaRule__alloc(stack->styleSheet);
  if (cssRule == NULL) return 1;

  stack->cssRule = (CSSOM_CSSRule*)cssRule;
  stack->style = NULL;

  return 0;
}



static int endMediaHandler(void *userData,
  const SAC_MediaQuery *media[] CSSOM_UNUSED)
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
  CSSOM_ParserState *state;
  CSSOM_CSSStyleRule *cssRule;
  
  state = (CSSOM_ParserState*)userData;

  cssRule = CSSOM_CSSStyleRule__alloc(stack->styleSheet,
    stack->cssom->table, selectors);
  if (cssRule == NULL) return 1;



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



static int errorHandler(void * userData, const SAC_Error * error) {
  struct _CSSOM_ParserStack *stack;
  const CSSOM * cssom;
  CSSOM_Error cssomError;

  stack = (struct _CSSOM_ParserStack*)userData;
  cssom = stack->cssom;

  if (cssom->errorHandler == NULL) return 0;

  cssomError.line = error->line;
  cssomError.column = error->column;
  cssomError.code = error->code;
  cssomError.data = error->data;
  return cssom->errorHandler(cssom->userData, &cssomError);
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
  CSSOM_ParserState *state;
  CSSOM_CSSStyleSheet *styleSheet;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  state = CSSOM_ParserState_alloc();
  if (state == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  styleSheet = CSSOM_CSSStyleSheet__alloc(cssom, parser);
  if (styleSheet == NULL) {
    CSSOM_ParserState_free(state);
    SAC_DisposeParser(parser);
    return NULL;
  }

  SAC_SetPageHandler(parser, startPageHandler, endPageHandler);
  SAC_SetMediaHandler(parser, startMediaHandler, endMediaHandler);
  SAC_SetStyleHandler(parser, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, state);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseStyleSheet(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  CSSOM_ParserState_free(state);

  return styleSheet;
}



CSSOM_CSSRule* CSSOM__parseCSSRule(const CSSOM *cssom CSSOM_UNUSED,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserState *state;
  CSSOM_CSSRule *cssRule;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  state = CSSOM_ParserState_alloc();
  if (state == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  cssRule = NULL;
  if (CSSOM_ParserState_pushCSSRuleCatcher(&cssRule) == NULL) {
    CSSOM_ParserState_free(state);
    SAC_DisposeParser(parser);
    return NULL;
  }

  SAC_SetPageHandler(parser, startPageHandler, endPageHandler);
  SAC_SetMediaHandler(parser, startMediaHandler, endMediaHandler);
  SAC_SetStyleHandler(parser, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, state);
  SAC_SetErrorHandler(parser, errorHandler);
  SAC_ParseRule(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  CSSOM_ParserState_free(state);

  return cssRule;
}
