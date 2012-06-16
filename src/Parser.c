#include "Parser.h"

#include "gcc.h"



static int propertyHandler(void *userData, const SAC_STRING propertyName,
  const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_ParserStack *stack;
  
  stack = (CSSOM_ParserStack*)userData;

  if (CSSOM_ParserStack_setProperty(stack, propertyName, value, important) < 0)
    return 1;

  return 0;
}



static int importHandler(void *userData,
  const SAC_STRING base, const SAC_STRING uri,
  const SAC_MediaQuery *media[], const SAC_STRING defaultNamepaceURI)
{
  CSSOM_ParserStack *stack;
  
  stack = (CSSOM_ParserStack*)userData;

  if (CSSOM_ParserStack_appendCSSImportRule(stack,
    base, uri, media, defaultNamepaceURI) == NULL)
  {
    return 1;
  }

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



static int startFontFaceHandler(void *userData) {
  CSSOM_ParserStack *stack;
  CSSOM_CSSFontFaceRule *cssRule;
  
  stack = (CSSOM_ParserStack*)userData;

  cssRule = CSSOM_ParserStack_pushCSSFontFaceRule(stack);
  if (cssRule == NULL) return 1;

  return 0;
}



static int endFontFaceHandler(void *userData) {
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



static int namespaceHandler(void *userData,
  const SAC_STRING prefix, const SAC_STRING uri)
{
  CSSOM_ParserStack *stack;
  
  stack = (CSSOM_ParserStack*)userData;

  if (CSSOM_ParserStack_appendCSSNamespaceRule(stack, prefix, uri) == NULL)
    return 1;

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



static int errorHandler(void *userData, const SAC_Error *error) {
  CSSOM_ParserStack *stack;

  stack = (CSSOM_ParserStack*)userData;

  return CSSOM_ParserStack_error(stack, error);
}



void CSSOM_Parser_setup(SAC_Parser parser, CSSOM_ParserStack *stack) {
  SAC_SetImportHandler(parser, importHandler);
  SAC_SetPageHandler(parser, startPageHandler, endPageHandler);
  SAC_SetFontFaceHandler(parser, startFontFaceHandler, endFontFaceHandler);
  SAC_SetMediaHandler(parser, startMediaHandler, endMediaHandler);
  SAC_SetNamespaceHandler(parser, namespaceHandler);
  SAC_SetStyleHandler(parser, startStyleHandler, endStyleHandler);
  SAC_SetPropertyHandler(parser, propertyHandler);
  SAC_SetUserData(parser, stack);
  SAC_SetErrorHandler(parser, errorHandler);
}
