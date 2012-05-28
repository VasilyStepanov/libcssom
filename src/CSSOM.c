#include "CSSOM.h"

#include "MediaList.h"
#include "CSSMediaRule.h"
#include "CSSPageRule.h"
#include "CSSProperties.h"
#include "CSSPropertyValue.h"
#include "CSSRule.h"
#include "CSSStyleRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleSheet.h"
#include "Parser.h"
#include "ParserStack.h"
#include "Selector.h"
#include "memory.h"
#include "gcc.h"

#include <sacc.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>



struct _CSSOM {
  size_t handles;
  const char **properties;
  CSSOM_FSMTable_CSSPropertyValue * table;
  CSSOM_ErrorHandler errorHandler;
  void * userData;
  CSSOM_DOMAPI domapi;
};



CSSOM* CSSOM_create(void) {
  CSSOM_FSMTable_CSSPropertyValue *table;
  CSSOM *cssom;

  table = CSSOM_FSMTable_CSSPropertyValue_alloc(CSSOM_CSSProperties);
  if (table == NULL) return NULL;

  cssom = (CSSOM*)CSSOM_malloc(sizeof(CSSOM));
  if (cssom == NULL) {
    CSSOM_FSMTable_CSSPropertyValue_free(table);
    return NULL;
  }

  cssom->handles = 1;
  cssom->properties = CSSOM_CSSProperties;
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

  CSSOM_FSMTable_CSSPropertyValue_free(cssom->table);
  CSSOM_free(cssom);
}



void * CSSOM_getUserData(const CSSOM * cssom) {
  return cssom->userData;
}



void CSSOM_setUserData(CSSOM * cssom, void * userData) {
  cssom->userData = userData;
}



const CSSOM_DOMAPI* CSSOM_getDOMAPI(const CSSOM * cssom) {
  return &cssom->domapi;
}



void CSSOM_setDOMAPI(CSSOM *cssom, const CSSOM_DOMAPI *domapi) {
  cssom->domapi = *domapi;
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



CSSOM_CSSRule* CSSOM__parseRule(const CSSOM *cssom,
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



CSSOM_CSSStyleDeclaration* CSSOM__parseStyleDeclaration(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *cssText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  CSSOM_CSSStyleDeclaration *style;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  style = CSSOM_CSSStyleDeclaration__alloc(parentRule);
  if (style == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }


  if (CSSOM_ParserStack_pushCSSStyleDeclaration(stack, style) == NULL) {
    CSSOM_CSSStyleDeclaration_release(style);
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  SAC_ParseStyleDeclaration(parser, cssText, len);

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSStyleDeclaration__keepParser(style, parser);

  return style;
}



CSSOM_MediaList* CSSOM__parseMedia(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *mediaText, int len)
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

  media = CSSOM_MediaList__alloc(parentRule, mediaQuery);
  if (media == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_MediaList__keepParser(media, parser);

  return media;
}



CSSOM_MediaQuery* CSSOM__parseMediaQuery(const CSSOM *cssom,
  CSSOM_MediaList *parentMedia, const char *mediaText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_MediaQuery **mediaQuery;
  CSSOM_MediaQuery *query;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  mediaQuery = SAC_ParseMediaQuery(parser, mediaText, len);
  if (mediaQuery == NULL || mediaQuery[1] != NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  query = CSSOM_MediaQuery__alloc(parentMedia, *mediaQuery);
  if (query == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_MediaQuery__keepParser(query, parser);

  return query;
}



CSSOM_Selector* CSSOM__parseSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_Selector **selectors;
  CSSOM_Selector *selector;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  selectors = SAC_ParseSelectors(parser, selectorText, len);
  if (selectors == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  selector = CSSOM_Selector__alloc(cssom, parentRule, selectors);
  if (selector == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_Selector__keepParser(selector, parser);

  return selector;
}



CSSOM_Selector* CSSOM_parseSelector(const CSSOM *cssom,
  const char *selectorText, int len)
{
  return CSSOM__parseSelector(cssom, NULL, selectorText, len);
}



CSSOM_Selector* CSSOM__parsePageSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_Selector **selectors;
  CSSOM_Selector *selector;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  selectors = SAC_ParsePageSelectors(parser, selectorText, len);
  if (selectors == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  selector = CSSOM_Selector__alloc(cssom, parentRule, selectors);
  if (selector == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_Selector__keepParser(selector, parser);

  return selector;
}



int CSSOM__parsePriority(const CSSOM *cssom, const char *priority, int len) {
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  size_t errors;
  SAC_Boolean important;

  parser = SAC_CreateParser();
  if (parser == NULL) return -1;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return -1;
  }

  CSSOM_Parser_setup(parser, stack);

  important = SAC_ParsePriority(parser, priority, len);
  errors = CSSOM_ParserStats_syntaxErrors(CSSOM_ParserStack_stats(stack));

  CSSOM_ParserStack_free(stack);

  SAC_DisposeParser(parser);

  if (errors != 0) return -1;

  return important == SAC_TRUE ? 1 : 0;
}



CSSOM_CSSPropertyValue* CSSOM__parsePropertyValue(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType type,
  const char *value, int valueLen, const char *priority, int priorityLen)
{
  SAC_Parser parser;
  CSSOM_ParserStack *stack;
  const SAC_LexicalUnit *lu;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  SAC_Boolean important;
  CSSOM_CSSPropertyValue *propertyValue;

  parser = SAC_CreateParser();
  if (parser == NULL) return NULL;

  stack = CSSOM_ParserStack_alloc(cssom);
  if (stack == NULL) {
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_Parser_setup(parser, stack);

  lu = SAC_ParsePropertyValue(parser, value, valueLen);
  if (lu == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  important = SAC_FALSE;
  if (priority != NULL && priorityLen != 0) {
    int rval;

    rval = CSSOM__parsePriority(cssom, priority, priorityLen);
    if (rval == -1) {
      CSSOM_ParserStack_free(stack);
      SAC_DisposeParser(parser);
      return NULL;
    }
    important = rval == 1 ? SAC_TRUE : SAC_FALSE;
  }

  if (lu->lexicalUnitType != SAC_SUB_EXPRESSION) {
    begin = &lu;
    end = NULL;
  } else {
    begin = (const SAC_LexicalUnit**)lu->desc.subValues;
    end = begin;
    while (*end != NULL) ++end;
  }

  propertyValue = CSSOM_CSSPropertyValue__alloc(cssom, values, NULL, type, 
    begin, end, important, NULL);
  if (propertyValue == NULL) {
    CSSOM_ParserStack_free(stack);
    SAC_DisposeParser(parser);
    return NULL;
  }

  CSSOM_ParserStack_free(stack);

  CSSOM_CSSPropertyValue__keepParser(propertyValue, parser);

  return propertyValue;
}



const CSSOM_FSMTable_CSSPropertyValue* CSSOM__table(const CSSOM *cssom) {
  return cssom->table;
}



const char** CSSOM__properties(const CSSOM *cssom) {
  return (const char**)cssom->properties;
}
