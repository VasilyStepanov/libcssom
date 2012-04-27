#ifndef _CSSOM_MEDIA_LIST_H
#define _CSSOM_MEDIA_LIST_H

#include <cssom/MediaList.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_MediaList* CSSOM_MediaList__alloc(const SAC_MediaQuery **query);

const SAC_MediaQuery** CSSOM_MediaList__query(const CSSOM_MediaList *media);



#ifdef __cplusplus
}
#endif

#endif
