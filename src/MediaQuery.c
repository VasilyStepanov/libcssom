#include "MediaQuery.h"

#include "memory.h"
#include "gcc.h"

#include <assert.h>



struct _CSSOM_MediaQuery {
  size_t handles;
  const SAC_MediaQuery *query;
};



CSSOM_MediaQuery* CSSOM_MediaQuery__alloc(const SAC_MediaQuery *queryData) {
  CSSOM_MediaQuery *query;

  query = (CSSOM_MediaQuery*)CSSOM_malloc(sizeof(CSSOM_MediaQuery));
  if (query == NULL) return NULL;

  query->handles = 1;
  query->query = queryData;

  return query;
}



void CSSOM_MediaQuery_acquire(CSSOM_MediaQuery *query) {
  if (query == NULL) return;

  ++query->handles;
}



void CSSOM_MediaQuery_release(CSSOM_MediaQuery *query) {
  if (query == NULL) return;

  assert(query->handles > 0);
  --query->handles;
  if (query->handles > 0) return;

  CSSOM_free(query);
}



const char* CSSOM_MediaQuery_mediaText(
  const CSSOM_MediaQuery *query CSSOM_UNUSED)
{
  return "";
}
