#include "MediaList.h"

#include "MediaQuery.h"
#include "CSSEmitter.h"
#include "Deque_MediaQuery.h"
#include "memory.h"
#include "gcc.h"

#include <assert.h>
#include <stdio.h>



struct _CSSOM_MediaList {
  size_t handles;
  char *mediaText;
  const SAC_MediaQuery **query;
  CSSOM_Deque_MediaQuery *data;
};



static void MediaDeque_free(CSSOM_Deque_MediaQuery *deque) {
  CSSOM_DequeIter_MediaQuery it;

  for (
    it = CSSOM_Deque_MediaQuery_begin(deque);
    it != CSSOM_Deque_MediaQuery_end(deque);
    it = CSSOM_DequeIter_MediaQuery_next(it))
  {
    CSSOM_MediaQuery_release(*it);
  }

  CSSOM_Deque_MediaQuery_free(deque);
}



CSSOM_MediaList* CSSOM_MediaList__alloc(const SAC_MediaQuery **query) {
  CSSOM_MediaList *media;
  CSSOM_Deque_MediaQuery *data;
  const SAC_MediaQuery **it;
  size_t size;

  for (it = query, size = 0; *it != NULL; ++it) ++size;

  data = CSSOM_Deque_MediaQuery_alloc_ex(0, size);
  if (data == NULL) return NULL;

  for (it = query; *it != NULL; ++it) {
    CSSOM_MediaQuery *query;

    query = CSSOM_MediaQuery__alloc(*it);
    if (query == NULL) {
      MediaDeque_free(data);
      return NULL;
    }

    if (CSSOM_Deque_MediaQuery_append(data, query) ==
      CSSOM_Deque_MediaQuery_end(data))
    {
      MediaDeque_free(data);
      return NULL;
    }

  }

  media = (CSSOM_MediaList*)CSSOM_malloc(sizeof(CSSOM_MediaList));
  if (media == NULL) {
    CSSOM_Deque_MediaQuery_free(data);
    return NULL;
  }

  media->handles = 1;
  media->mediaText = NULL;
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
  CSSOM_native_free(media->mediaText);
  CSSOM_free(media);
}



const SAC_MediaQuery** CSSOM_MediaList__query(const CSSOM_MediaList *media) {
  return media->query;
}



void CSSOM_MediaList_setMediaText(CSSOM_MediaList *media CSSOM_UNUSED,
  const char *mediaText CSSOM_UNUSED)
{
}



const char* CSSOM_MediaList_mediaText(const CSSOM_MediaList *media) {
  if (media->mediaText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_media(out, media) != 0) {
      fclose(out);
      CSSOM_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_MediaList*)media)->mediaText = buf;
  }
  return media->mediaText;
}



unsigned long CSSOM_MediaList_length(const CSSOM_MediaList *media) {
  return CSSOM_Deque_MediaQuery_size(media->data);
}



const char * CSSOM_MediaList_item(const CSSOM_MediaList *media,
  unsigned long index)
{
  CSSOM_MediaQuery *query;

  if (index >= CSSOM_Deque_MediaQuery_size(media->data)) return NULL;

  query = *CSSOM_Deque_MediaQuery_at(media->data, index);

  return CSSOM_MediaQuery_mediaText(query);
}



CSSOM_MediaQuery* CSSOM_MediaList__at(const CSSOM_MediaList *media,
  unsigned long index)
{
  return *CSSOM_Deque_MediaQuery_at(media->data, index);
}
