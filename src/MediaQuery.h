#ifndef _CSSOM_MEDIA_QUERY_H
#define _CSSOM_MEDIA_QUERY_H

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_MediaQuery CSSOM_MediaQuery;

CSSOM_MediaQuery* CSSOM_MediaQuery__alloc(CSSOM_MediaList *parentMedia,
  const SAC_MediaQuery *mediaQuery);

void CSSOM_MediaQuery_acquire(CSSOM_MediaQuery *query);

void CSSOM_MediaQuery_release(CSSOM_MediaQuery *query);

const char* CSSOM_MediaQuery_mediaText(const CSSOM_MediaQuery *query);

const SAC_MediaQuery* CSSOM_MediaQuery_query(const CSSOM_MediaQuery *query);

void CSSOM_MediaQuery__keepParser(CSSOM_MediaQuery *query,
  SAC_Parser parser);

void CSSOM_MediaQuery__setParentMedia(CSSOM_MediaQuery *query,
  CSSOM_MediaList *parentMedia);



#ifdef __cplusplus
}
#endif

#endif
