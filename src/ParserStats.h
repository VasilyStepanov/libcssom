#ifndef _CSSOM_PARSER_STATS_H
#define _CSSOM_PARSER_STATS_H

#include <stddef.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_ParserStats CSSOM_ParserStats;



CSSOM_ParserStats* CSSOM_ParserStats_alloc(void);

void CSSOM_ParserStats_free(CSSOM_ParserStats *stats);

void CSSOM_ParserStats_errorHandler(CSSOM_ParserStats *stats,
  const SAC_Error *error);

size_t CSSOM_ParserStats_syntaxErrors(const CSSOM_ParserStats *stats);



#ifdef __cplusplus
}
#endif

#endif
