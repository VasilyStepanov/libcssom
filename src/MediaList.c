#include "MediaList.h"

#include "memory.h"

#include <assert.h>



struct _CSSOM_MediaList {
  size_t handles;
};



CSSOM_MediaList* CSSOM_MediaList__alloc(void) {
  CSSOM_MediaList *media;

  media = (CSSOM_MediaList*)CSSOM_malloc(sizeof(CSSOM_MediaList));
  if (media == NULL) return NULL;

  media->handles = 1;

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
