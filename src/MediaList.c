#include "MediaList.h"

#include "memory.h"
#include "gcc.h"

#include <assert.h>



struct _CSSOM_MediaList {
  size_t handles;
  const SAC_MediaQuery **query;
};



CSSOM_MediaList* CSSOM_MediaList__alloc(const SAC_MediaQuery **query) {
  CSSOM_MediaList *media;

  media = (CSSOM_MediaList*)CSSOM_malloc(sizeof(CSSOM_MediaList));
  if (media == NULL) return NULL;

  media->handles = 1;
  media->query = query;

  return media;
}



void CSSOM_MediaList_acquire(CSSOM_MediaList *media) {
  if (media == NULL) return;

  ++media->handles;
}



void CSSOM_MediaList_release(CSSOM_MediaList *media) {
  if (media == NULL) return;

  assert(media->handles > 0);
  --media->handles;
  if (media->handles > 0) return;

  CSSOM_free(media);
}



const SAC_MediaQuery** CSSOM_MediaList__query(const CSSOM_MediaList *media) {
  return media->query;
}



void CSSOM_MediaList_setMediaText(CSSOM_MediaList *media CSSOM_UNUSED,
  const char *mediaText CSSOM_UNUSED)
{
}



const char* CSSOM_MediaList_mediaText(
  const CSSOM_MediaList *media CSSOM_UNUSED)
{
  return "";
}



unsigned long CSSOM_MediaList_length(
  const CSSOM_MediaList *media CSSOM_UNUSED)
{
  return 0;
}
