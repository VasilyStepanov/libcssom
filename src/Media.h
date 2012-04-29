#ifndef _CSSOM_MEDIA_H
#define _CSSOM_MEDIA_H

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_Media CSSOM_Media;

CSSOM_Media* CSSOM_Media__alloc(const SAC_MediaQuery *query);

void CSSOM_Media_acquire(CSSOM_Media *media);

void CSSOM_Media_release(CSSOM_Media *media);

const char* CSSOM_Media_mediaText(const CSSOM_Media *media);



#ifdef __cplusplus
}
#endif

#endif
