#ifndef _CSSOM_PARSER_H
#define _CSSOM_PARSER_H

#include "ParserStack.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_Parser_setup(SAC_Parser parser, CSSOM_ParserStack *stack);



#ifdef __cplusplus
}
#endif

#endif
