#include "MediaQuery.h"

#include "MediaList.h"
#include "CSSEmitter.h"
#include "memory.h"
#include "gcc.h"

#include <assert.h>
#include <stdio.h>



struct _CSSOM_MediaQuery {
  size_t handles;
  CSSOM_MediaList *ownerMedia;
  char *mediaText;
  const SAC_MediaQuery *query;
};



CSSOM_MediaQuery* CSSOM_MediaQuery__alloc(CSSOM_MediaList *ownerMedia,
  const SAC_MediaQuery *mediaQuery)
{
  CSSOM_MediaQuery *query;

  query = (CSSOM_MediaQuery*)CSSOM_malloc(sizeof(CSSOM_MediaQuery));
  if (query == NULL) return NULL;

  query->handles = 1;
  query->ownerMedia = ownerMedia;
  query->mediaText = NULL;
  query->query = mediaQuery;

  return query;
}



void CSSOM_MediaQuery_acquire(CSSOM_MediaQuery *query) {
  if (query == NULL) return;

  ++query->handles;
  CSSOM_MediaList_acquire(query->ownerMedia);
}



void CSSOM_MediaQuery_release(CSSOM_MediaQuery *query) {
  if (query == NULL) return;

  assert(query->handles > 0);
  --query->handles;
  if (query->handles > 0) {
    CSSOM_MediaList_release(query->ownerMedia);
    return;
  }

  CSSOM_native_free(query->mediaText);
  CSSOM_free(query);
}



const char* CSSOM_MediaQuery_mediaText(const CSSOM_MediaQuery *query) {
  if (query->mediaText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_query(out, query) != 0) {
      fclose(out);
      CSSOM_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_MediaQuery*)query)->mediaText = buf;
  }
  return query->mediaText;
}



const SAC_MediaQuery* CSSOM_MediaQuery_query(const CSSOM_MediaQuery *query) {
  return query->query;
}
