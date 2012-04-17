#include "CSSOM.h"

#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSProperty.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "ParserStack.h"
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



static int propertyHandler(void *userData,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important)
{
  CSSOM_ParserStack *stack;
  CSSOM_CSSProperty *property;
  
  stack = (CSSOM_ParserStack*)userData;

  property = CSSOM_ParserStack_setProperty(stack,
    propertyName, value, important);
  if (property == NULL) return 1;

  return 0;
}



static int startPageHandler(void *userData,
  const SAC_Selector *selectors[])
{
  CSSOM_ParserStack *stack;
  CSSOM_CSSPageRule *cssRule;
  
  stack = (CSSOM_ParserStack*)userData;

  cssRule = CSSOM_ParserStack_pushCSSPageRule(stack, selectors);
  if (cssRule == NULL) return 1;

  return 0;
}



static int endPageHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  CSSOM_ParserStack *stack;

  stack = (CSSOM_ParserStack*)userData;

  CSSOM_ParserStack_pop(stack);

  return 0;
}



static int startMediaHandler(void *userData,
  const SAC_MediaQuery *media[])
{
  CSSOM_ParserStack *stack;
  CSSOM_CSSMediaRule *cssRule;
  
  stack = (CSSOM_ParserStack*)userData;

  cssRule = CSSOM_ParserStack_pushCSSMediaRule(stack, media);
  if (cssRule == NULL) return 1;

  return 0;
}



static int endMediaHandler(void *userData,
  const SAC_MediaQuery *media[] CSSOM_UNUSED)
{
  CSSOM_ParserStack *stack;

  stack = (CSSOM_ParserStack*)userData;

  CSSOM_ParserStack_pop(stack);

  return 0;
}



static int startStyleHandler(void *userData,
  const SAC_Selector *selectors[])
{
  CSSOM_ParserStack *stack;
  CSSOM_CSSStyleRule *cssRule;
  
  stack = (CSSOM_ParserStack*)userData;

  cssRule = CSSOM_ParserStack_pushCSSStyleRule(stack, selectors);
  if (cssRule == NULL) return 1;

  return 0;
}



static int endStyleHandler(void *userData,
  const SAC_Selector *selectors[] CSSOM_UNUSED)
{
  CSSOM_ParserStack *stack;

  stack = (CSSOM_ParserStack*)userData;

  CSSOM_ParserStack_pop(stack);

  return 0;
}



static void freeProperties(char **properties) {
  char **it;

  if (properties == (char**)CSSOM_CSSProperties) return;

  for (it = properties; *it != NULL; ++it)
    CSSOM_free(*it);

  CSSOM_free(properties);
}



static int errorHandler(void *userData, const SAC_Error *error) {
  CSSOM_ParserStack *stack;

  stack = (CSSOM_ParserStack*)userData;

  return CSSOM_ParserStack_error(stack, error);
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



void CSSOM__invalidModificationErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_INVALID_MODIFICATION_ERR;
    e.data = "Invalid modification error";
    cssom->errorHandler(cssom->userData, &e);
  }
}



void CSSOM__indexSizeErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_INDEX_SIZE_ERR;
    e.data = "Index size error";
    cssom->errorHandler(cssom->userData, &e);
  }
}



int CSSOM__error(const CSSOM *cssom, const SAC_Error *error) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = error->line;
    e.column = error->column;
    e.code = error->code;
    e.data = error->data;
    return cssom->errorHandler(cssom->userData, &e);
  }
  return 0;
}



static void parserSetup(SAC_Parser parser, CSSOM_ParserStack *stack) {
  SAC_SetPageHandler(parser, startPageHandler, endPageHandler);
  SAC_SetMediaHandler(parser, startMediaHandler, endMediaHandler);
  SAC_SetStyleHandler(parser, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, stack);
  SAC_SetErrorHandler(parser, errorHandler);
}



CSSOM_CSSStyleSheet* CSSOM_parse(const CSSOM *cssom,
  const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSStyleSheet *styleSheet;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  styleSheet = CSSOM_CSSStyleSheet__alloc(cssom, parser);
  if (styleSheet == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  if (CSSOM_ParserStack_pushCSSStyleSheet(stack, styleSheet) == NULL) {
    CSSOM_CSSStyleSheet_release(styleSheet);
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  parserSetup(parser, stack);

  SAC_ParseStyleSheet(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  CSSOM_ParserStack_free(stack);

  return styleSheet;
}



CSSOM_CSSRule* CSSOM__parseCSSRule(const CSSOM *cssom,
  CSSOM_CSSStyleSheet *styleSheet, const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSRule *cssRule;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  cssRule = NULL;
  if (CSSOM_ParserStack_pushCSSRuleCatcher(stack,
    styleSheet, &cssRule) == NULL)
  {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  parserSetup(parser, stack);

  SAC_ParseRule(parser, cssText, len);

  /**
   * TODO: SAC_DisposeParser here
   */

  CSSOM_ParserStack_free(stack);

  return cssRule;
}



const CSSOM_FSMTable_CSSProperty* CSSOM__table(const CSSOM *cssom) {
  return cssom->table;
}
