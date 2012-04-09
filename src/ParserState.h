#ifndef _CSSOM_PARSER_STATE_H
#define _CSSOM_PARSER_STATE_H

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_ParserState CSSOM_ParserState;



CSSOM_ParserState* CSSOM_ParserState_alloc(void);

void CSSOM_ParserState_free(CSSOM_ParserState *state);

CSSOM_CSSProperty* CSSOM_ParserState_setProperty(CSSOM_ParserState *state,
  const SAC_STRING propertyName,
  const SAC_LexicalUnit *value,
  SAC_Boolean important);

void CSSOM_ParserState_pop(CSSOM_ParserState *state);

CSSOM_CSSRule** CSSOM_ParserState_pushCSSRuleCatcher(CSSOM_ParserState *state,
  CSSOM_CSSRule **cssRule);

CSSOM_CSSStyleSheet* CSSOM_ParserState_pushCSSStyleSheetHolder(
  CSSOM_ParserState *state, CSSOM_CSSStyleSheet *styleSheet);

CSSOM_CSSPageRule* CSSOM_ParserState_pushCSSPageRule(
  CSSOM_ParserState *state, const SAC_Selector *selectors[]);

CSSOM_CSSMediaRule* CSSOM_ParserState_pushCSSMediaRule(
  CSSOM_ParserState *state);

CSSOM_CSSStyleRule* CSSOM_ParserState_pushCSSStyleRule(
  CSSOM_ParserState *state, const SAC_Selector *selectors[]);

int CSSOM_ParserState_error(const CSSOM_ParserState *state,
  void *userData, const SAC_Error *error);



#ifdef __cplusplus
}
#endif

#endif
