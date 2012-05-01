#ifndef _CSSOM_MEDIA_LIST_H
#define _CSSOM_MEDIA_LIST_H

#include <cssom/MediaList.h>

#include "MediaQuery.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_MediaList* CSSOM_MediaList__alloc(CSSOM_CSSRule *ownerRule,
  const SAC_MediaQuery **query);

CSSOM_MediaQuery* CSSOM_MediaList__at(const CSSOM_MediaList *media,
  unsigned long index);

void CSSOM_MediaList__keepParser(CSSOM_MediaList *media,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif