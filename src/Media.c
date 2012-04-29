#include "Media.h"

#include "memory.h"

#include <assert.h>



struct _CSSOM_Media {
  size_t handles;
  const SAC_MediaQuery *query;
};



CSSOM_Media* CSSOM_Media__alloc(const SAC_MediaQuery *query) {
  CSSOM_Media *media;

  media = (CSSOM_Media*)CSSOM_malloc(sizeof(CSSOM_Media));
  if (media == NULL) return NULL;

  media->handles = 1;
  media->query = query;

  return media;
}



void CSSOM_Media_acquire(CSSOM_Media *media) {
  if (media == NULL) return;

  ++media->handles;
}



void CSSOM_Media_release(CSSOM_Media *media) {
  if (media == NULL) return;

  assert(media->handles > 0);
  --media->handles;
  if (media->handles > 0) return;

  CSSOM_free(media);
}
