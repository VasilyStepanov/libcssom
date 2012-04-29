#include "CSSOM.h"

#include "MediaList.h"
#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSProperty.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "Parser.h"
#include "ParserStack.h"
#include "memory.h"

#include <sacc.h>

#include <string.h>
#include <assert.h>



struct _CSSOM {
  size_t handles;
  char * * properties;
  CSSOM_FSMTable_CSSProperty * table;
  CSSOM_ErrorHandler errorHandler;
  void * userData;
};



static void freeProperties(char **properties) {
  char **it;

  if (properties == (char**)CSSOM_CSSProperties) return;

  for (it = properties; *it != NULL; ++it)
    CSSOM_free(*it);

  CSSOM_free(properties);
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
  if (cssom == NULL) return;

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



void CSSOM__hierarchyRequestErr(const CSSOM *cssom) {
  if (cssom->errorHandler != NULL) {
    CSSOM_Error e;
    e.line = -1;
    e.column = -1;
    e.code = CSSOM_ERROR_HIERARCHY_REQUEST_ERR;
    e.data = "Hierarchy request error";
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

  styleSheet = CSSOM_CSSStyleSheet__alloc(cssom, NULL);
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

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseStyleSheet(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSStyleSheet__keepParser(styleSheet, parser);

  return styleSheet;
}



CSSOM_CSSRule* CSSOM__parseCSSRule(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *styleSheet,
  const char *cssText, int len)
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
    parentRule, styleSheet, &cssRule) == NULL)
  {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseRule(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  if (cssRule != NULL) CSSOM_CSSRule__keepParser(cssRule, parser);

  return cssRule;
}



CSSOM_MediaList* CSSOM__parseMediaList(const CSSOM *cssom,
  CSSOM_CSSMediaRule *ownerRule, const char *mediaText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_MediaQuery **mediaQuery;
  CSSOM_MediaList *media;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  mediaQuery = SAC_ParseMediaQuery(parser, mediaText, len);
  if (mediaQuery == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  media = CSSOM_MediaList__alloc(ownerRule, mediaQuery);
  if (media == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_MediaList__keepParser(media, parser);

  return media;
}



const CSSOM_FSMTable_CSSProperty* CSSOM__table(const CSSOM *cssom) {
  return cssom->table;
}
