#include "MediaList.h"

#include "Media.h"
#include "Deque_Media.h"
#include "memory.h"
#include "gcc.h"

#include <assert.h>



struct _CSSOM_MediaList {
  size_t handles;
  const SAC_MediaQuery **query;
  CSSOM_Deque_Media *data;
};



static void MediaDeque_free(CSSOM_Deque_Media *deque) {
  CSSOM_DequeIter_Media it;

  for (
    it = CSSOM_Deque_Media_begin(deque);
    it != CSSOM_Deque_Media_end(deque);
    it = CSSOM_DequeIter_Media_next(it))
  {
    CSSOM_Media_release(*it);
  }

  CSSOM_Deque_Media_free(deque);
}



CSSOM_MediaList* CSSOM_MediaList__alloc(const SAC_MediaQuery **query) {
  CSSOM_MediaList *media;
  CSSOM_Deque_Media *data;
  const SAC_MediaQuery **it;
  size_t size;

  for (it = query, size = 0; *it != NULL; ++it) ++size;

  data = CSSOM_Deque_Media_alloc_ex(0, size);
  if (data == NULL) return NULL;

  for (it = query; *it != NULL; ++it) {
    CSSOM_Media *mediaItem;

    mediaItem = CSSOM_Media__alloc(*it);
    if (mediaItem == NULL) {
      MediaDeque_free(data);
      return NULL;
    }

    if (CSSOM_Deque_Media_append(data, mediaItem) ==
      CSSOM_Deque_Media_end(data))
    {
      MediaDeque_free(data);
      return NULL;
    }

  }

  media = (CSSOM_MediaList*)CSSOM_malloc(sizeof(CSSOM_MediaList));
  if (media == NULL) {
    CSSOM_Deque_Media_free(data);
    return NULL;
  }

  media->handles = 1;
  media->query = query;
  media->data = data;

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

  MediaDeque_free(media->data);
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



unsigned long CSSOM_MediaList_length(const CSSOM_MediaList *media) {
  return CSSOM_Deque_Media_size(media->data);
}
