#ifndef _CSSOM_PARSER_STATE_H
#define _CSSOM_PARSER_STATE_H

#include <cssom/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_ParserState CSSOM_ParserState;



CSSOM_ParserState* CSSOM_ParserState_alloc(void);
void CSSOM_ParserState_free(CSSOM_ParserState *state);

CSSOM_CSSRule** CSSOM_ParserState_pushCSSRuleCatcher(CSSOM_CSSRule **cssRule);

CSSOM_ParserState* CSSOM_ParserStateHoldStyleSheet_alloc(
  CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
