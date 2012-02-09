#include <cssom/parser.h>

#include <cssom/types.h>

#include <sacc.h>

#include <stdlib.h>
#include <string.h>



struct _CSSOM_Parser {
  SAC_Parser sac;
};



CSSOM_Parser* CSSOM_Parser_create() {
  CSSOM_Parser *parser;
  SAC_Parser sac;

  sac = SAC_CreateParser();
  if (sac == NULL) return NULL;
 
  parser = malloc(sizeof(struct _CSSOM_Parser));
  if (parser == NULL) return parser;

  parser->sac = sac;
  SAC_SetUserData(sac, parser);
 
  return parser;
}



void CSSOM_Parser_release(CSSOM_Parser *parser) {
  SAC_DisposeParser(parser->sac);
  free(parser);
}



CSSOM_CSSStyleSheet* CSSOM_Parser_parseStyleSheet(CSSOM_Parser *parser,
  const char *cssText)
{
  SAC_ParseStyleSheet(parser->sac, cssText, strlen(cssText));
  return NULL;
}
