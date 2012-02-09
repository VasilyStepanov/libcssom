#include <cssom/parser.h>

#include "css_style_sheet.h"

#include <cssom/types.h>

#include <sacc.h>

#include <stdlib.h>
#include <string.h>



struct _CSSOM_Parser {
  SAC_Parser sac;
};



struct _CSSOM_ParserStack {
  int dummy;
};



CSSOM_Parser* CSSOM_Parser_alloc() {
  CSSOM_Parser *parser;
  SAC_Parser sac;

  sac = SAC_CreateParser();
  if (sac == NULL) return NULL;
 
  parser = malloc(sizeof(struct _CSSOM_Parser));
  if (parser == NULL) return parser;

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

  SAC_SetUserData(parser->sac, &parserStack);
  SAC_ParseStyleSheet(parser->sac, cssText, strlen(cssText));

  return CSSOM_CSSStyleSheet_alloc();
}
