#include "ParserStats.h"

#include "memory.h"



struct _CSSOM_ParserStats {
  size_t syntaxErrors;
};



CSSOM_ParserStats* CSSOM_ParserStats_alloc(void) {
  CSSOM_ParserStats *stats;

  stats = (CSSOM_ParserStats*)CSSOM_malloc(sizeof(CSSOM_ParserStats));
  if (stats == NULL) return NULL;

  stats->syntaxErrors = 0;

  return stats;
}



void CSSOM_ParserStats_free(CSSOM_ParserStats *stats) {
  CSSOM_free(stats);
}



void CSSOM_ParserStats_errorHandler(CSSOM_ParserStats *stats,
  const SAC_Error *error)
{
  switch (error->code) {
    case SAC_ERROR_SYNTAX:
      ++stats->syntaxErrors;
      break;
    case SAC_ERROR_NOT_SUPPORTED:
      break;
  }
}



size_t CSSOM_ParserStats_syntaxErrors(const CSSOM_ParserStats *stats){
  return stats->syntaxErrors;
}
